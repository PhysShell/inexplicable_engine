#include "stdafx.h"

// to suppress warnings in winapi-specific files
#pragma warning( push )
#pragma warning( disable: 4365 ) // signed/unsigned mismatch
#pragma warning( disable: 4668 ) // undefined macro replaced with 0
#pragma warning( disable: 4820 ) // padding added
#pragma warning( disable: 4710 ) // function not inlined
#include "RpcExStackTraceEngine.h"
#pragma warning( pop )

#include <strsafe.h>
class CRpcExCritSecLock
{
private:
    LPCRITICAL_SECTION m_cs;
    bool m_bLocked;

private:
    //
    // Private to avoid accidental use.
    //
    CRpcExCritSecLock( const CRpcExCritSecLock& );
    CRpcExCritSecLock& operator=( const CRpcExCritSecLock& );

public:
    inline CRpcExCritSecLock(
        ATL::CComAutoCriticalSection* pcs,
        bool bInitialLock = true) :
        m_cs(&pcs->m_sec),
        m_bLocked(false)
    {
        if(bInitialLock)
            Lock();
    }

    inline CRpcExCritSecLock(
        ATL::CComAutoCriticalSection& acs,
        bool bInitialLock = true) :
        m_cs(&acs.m_sec),
        m_bLocked(false)
    {
        if(bInitialLock)
            Lock();
    }

    inline CRpcExCritSecLock(
        LPCRITICAL_SECTION cs,
        bool bInitialLock = true) :
        m_cs(cs),
        m_bLocked(false)
    {
        if(bInitialLock)
            Lock();
    }

    inline CRpcExCritSecLock(
        CRITICAL_SECTION& cs,
        bool bInitialLock = true) :
        m_cs(&cs),
        m_bLocked(false)
    {
        if(bInitialLock)
            Lock();
    }
    
    inline ~CRpcExCritSecLock()
    {
        if(m_bLocked)
            Unlock();
    }

    inline void Lock()
    {
        _ASSERTE(!m_bLocked);
        EnterCriticalSection(m_cs);
        m_bLocked = true;
    }

    inline void Unlock()
    {
        _ASSERTE(m_bLocked);
        LeaveCriticalSection(m_cs);
        m_bLocked = false;
    }
};

RpcExStackTraceEngine::RpcExStackTraceEngine() :
    m_hDbhHelp(0),
    m_hProcess(0),
    pfnSymGetLineFromAddr64(0),
    pfnSymGetSymFromAddr64(0),
    pfnSymInitialize(0),
    pfnSymSetOptions(0),
    pfnSymGetOptions(0),
    pfnStackWalk64(0),
    pfnUnDecorateSymbolName(0),
    pfnSymFunctionTableAccess64(0),
    pfnSymGetModuleBase64(0),
    m_InitializationState(IS_NotPerformed)
{
}

HRESULT RpcExStackTraceEngine::Initialize()
{
    BOOL Ret;

    CRpcExCritSecLock m_DbgHelpLock(m_DbgHelpGuard);
    
    if (m_InitializationState != IS_NotPerformed)
    {
        return E_UNEXPECTED;
    }

    //
    // Assume initialization is failed.
    // I'll set this flag to the IS_Done in the
    // end of this function.
    //
    m_InitializationState = IS_Failed;

    //
    // Load dbghelp.dll dynamically.
    //
    if ((m_hDbhHelp = LoadLibrary("dbghelp.dll")) == 0)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    //
    // Load procedures.
    //
    pfnSymInitialize = (tfnSymInitialize) GetProcAddress(m_hDbhHelp, "SymInitialize" );
    pfnStackWalk64 = (tfnStackWalk64) GetProcAddress(m_hDbhHelp, "StackWalk64" );
    pfnSymGetLineFromAddr64 = (tfnSymGetLineFromAddr64) GetProcAddress(m_hDbhHelp, "SymGetLineFromAddr64" );
    pfnSymGetSymFromAddr64 = (tfnSymGetSymFromAddr64) GetProcAddress(m_hDbhHelp, "SymGetSymFromAddr64" );
    pfnUnDecorateSymbolName = (tfnUnDecorateSymbolName) GetProcAddress(m_hDbhHelp, "UnDecorateSymbolName" );
    pfnSymFunctionTableAccess64 = (tfnSymFunctionTableAccess64) GetProcAddress(m_hDbhHelp, "SymFunctionTableAccess64" );
    pfnSymGetModuleBase64 = (tfnSymGetModuleBase64) GetProcAddress(m_hDbhHelp, "SymGetModuleBase64" );
    pfnSymSetOptions = (tfnSymSetOptions) GetProcAddress(m_hDbhHelp, "SymSetOptions" );
    pfnSymGetOptions = (tfnSymGetOptions) GetProcAddress(m_hDbhHelp, "SymGetOptions" );

    if ((pfnSymInitialize == 0) ||
        (pfnStackWalk64 == 0) ||
        (pfnSymGetLineFromAddr64 == 0) ||
        (pfnSymGetSymFromAddr64 == 0) ||
        (pfnUnDecorateSymbolName == 0) ||
        (pfnSymFunctionTableAccess64 == 0) ||
        (pfnSymGetModuleBase64 == 0) ||
        (pfnSymSetOptions == 0) ||
        (pfnSymGetOptions == 0))
    {
        FreeLibrary(m_hDbhHelp);
        m_hDbhHelp = 0;
        return E_UNEXPECTED;
    }

    DWORD dwOpts = pfnSymGetOptions() ;

    //
    // Initialize symbols engine.
    //
    if ((Ret = pfnSymSetOptions(dwOpts | SYMOPT_LOAD_LINES)) == FALSE)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    m_hProcess = GetCurrentProcess();
    
        
    // 
    // SymInitialize 2-nd parameter description from the MSDN.
    // Pointer to a null-terminated string that specifies a path,
    // or series of paths separated by a semicolon (;),
    // that is used to search for symbol files.
    // If a value of NULL is used, then the library attempts to
    // form a symbol path from the following sources: 
    //   The current working directory of the application 
    //   The _NT_SYMBOL_PATH environment variable 
    //   The _NT_ALTERNATE_SYMBOL_PATH environment variable 
    //
        
    if ((Ret = pfnSymInitialize(
        m_hProcess,
        0,
        TRUE)) == FALSE)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    m_InitializationState = IS_Done;

    return S_OK;
}

RpcExStackTraceEngine::InitializationState RpcExStackTraceEngine::GetInitializationState()
{
    return m_InitializationState;
}

// Declare these so they are accessable anywhere in the project.
extern "C" void * _ReturnAddress ( void ) ;
#pragma intrinsic ( _ReturnAddress )

HRESULT RpcExStackTraceEngine::WalkStack(
    CHAR* StackTrace,
    DWORD StackTraceSize, /*in characters*/
    DWORD MaxStackTraceDepth)
{
    CRpcExCritSecLock m_DbgHelpLock(m_DbgHelpGuard);

    if ((StackTrace == 0) ||
        (IsBadWritePtr(StackTrace, StackTraceSize*sizeof(WCHAR))))
    {
        //
        // Grrrr,
        // I don“t like bad buffers.
        //
        return E_INVALIDARG;
    }

    if (m_InitializationState != IS_Done)
    {
        //
        // Looks like initialization failed
        // or not performed yet.
        //
        return E_UNEXPECTED;
    }

    //
    // Init out parameters.
    //
    StackTrace[0] = L'\0';

    HANDLE hCurrentThread = GetCurrentThread();

    //
    // The following should be enough for walking the call stack...
    //
    CONTEXT ctx = {0};
    ctx.ContextFlags = CONTEXT_FULL;
    
    __asm    call x;
    __asm x: pop eax;
    __asm    mov ctx.Eip, eax;
    __asm    mov ctx.Ebp, ebp;
    __asm    mov ctx.Esp, esp;

    //
    // Init STACKFRAME for the first call
    //
    STACKFRAME64 stfrm = {0}; // in/out stackframe
    stfrm.AddrPC.Offset = ctx.Eip;
    stfrm.AddrPC.Mode = AddrModeFlat;

    stfrm.AddrStack.Offset = ctx.Esp;
    stfrm.AddrStack.Mode = AddrModeFlat;

    stfrm.AddrFrame.Offset = ctx.Ebp;
    stfrm.AddrFrame.Mode = AddrModeFlat;

    //
    // Symbol info memory buffer.
    //
    char SymbolBuffer[65535] = {0};
    IMAGEHLP_SYMBOL64 *pSymbol = reinterpret_cast<IMAGEHLP_SYMBOL64*>(&SymbolBuffer);
    pSymbol->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);

    DWORD SymbolNameSize = (DWORD)sizeof(SymbolBuffer) - offsetof(IMAGEHLP_SYMBOL64, Name);
    pSymbol->MaxNameLength = SymbolNameSize;

    //
    // Line info.
    //
    IMAGEHLP_LINE64 Line = {0};
    Line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

    for(ULONG StackNumber = 0; StackNumber < MaxStackTraceDepth; ++StackNumber)
    {
        //
        // TODO:
        //    Use heap instead of stack.
        //    USES_CONVERSION uses stack to store strings.
        //
        USES_CONVERSION;

        //
        // IMAGE_FILE_MACHINE_I386 is only supported now.
        // I have no other platforms to check this code :(
        //
        pfnStackWalk64(
            IMAGE_FILE_MACHINE_I386,
            m_hProcess,
            hCurrentThread,
            &stfrm,
            &ctx,
            0,
            pfnSymFunctionTableAccess64,
            pfnSymGetModuleBase64,
            0);

        if (stfrm.AddrPC.Offset == 0)
            break;

        //
        // If StackWalk64 fails it does not cleans ->Name.
        // We must do this manually.
        //
        pSymbol->Name[0] = '\0';

        //
        // Get procedure info.
        //
        DWORD64 SymbolDisplacement = 0;
        pfnSymGetSymFromAddr64(
            m_hProcess,
            stfrm.AddrPC.Offset,
            &SymbolDisplacement,
            pSymbol);

        //
        // Get line info.
        //
        DWORD LineDisplacement = 0;
        pfnSymGetLineFromAddr64(
            m_hProcess,
            stfrm.AddrPC.Offset,
            &LineDisplacement,
            &Line);

        //
        // Append symbol name.
        //
        if ((pSymbol->Name == 0) ||
            (pSymbol->Name[0] == '\0'))
        {
            StringCchCat(
                StackTrace,
                StackTraceSize,
                "Procedure: <unknown>");
        }
        else
        {
            StringCchCat(
                StackTrace,
                StackTraceSize,
                "Procedure: ");

            StringCchCat(
                StackTrace,
                StackTraceSize,
                (pSymbol->Name));
        }

        //
        // Append symbol location
        //
        if ((Line.FileName == 0) ||
            (Line.FileName[0] == '\0'))
        {
            StringCchCat(
                StackTrace,
                StackTraceSize,
                ", File: <unknown>, Line: <unknown>\n");
        }
        else
        {
            StringCchCat(
                StackTrace,
                StackTraceSize,
                " , File: ");

            StringCchCat(
                StackTrace,
                StackTraceSize,
               (Line.FileName));

            StringCchCat(
                StackTrace,
                StackTraceSize,
                ", Line: ");

            CHAR LineNumberBuffer[16];
            _itoa(Line.LineNumber, LineNumberBuffer, 10);
            StringCchCat(
                StackTrace,
                StackTraceSize,
                LineNumberBuffer);

            StringCchCat(
                StackTrace,
                StackTraceSize,
                "\n");
        }
    }

    return S_OK;
}