#if !defined(__RPC_EX_STACK_TRACE_ENGINE_INCLUDED__)
#	define __RPC_EX_STACK_TRACE_ENGINE_INCLUDED__

#	include <atlcore.h>
#	include <um/DbgHelp.h>

// This call stack class is taken from rsdn.ru
/**
 * This is class help to obtain call stack as a
 * simple string. It uses "dbghelp.dll" to walk
 * the call stack and search symbols in the debug
 * information. It is recommended to have
 * only one instance of this class.
 *
 * WARNING:
 *   ASSERT's and TRACE's implementation use
 *   this class to show call stack, so it is
 *   not possible to use ASSERT's in this class.
 */
class RpcExStackTraceEngine
{
public:
    enum InitializationState
    {
        IS_NotPerformed,
        IS_Failed,
        IS_Done
    };

private:
    /**
     * HMODULE of the "dbghelp.dll"
     * We're loading "dbghelp.dll" dynamically to avoid
     * dependency from "dbghelp.dll" because if dependency
     * is present loading RpcExFramework library will fail
     * if "dbghelp.dll" is absent.
     */
    HMODULE m_hDbhHelp;

    /**
     * Handle of the current process.
     * We need it in almost all Sym***
     * operations.
     */
    HANDLE m_hProcess;

    /**
     * RpcExStackTraceEngine initialization state.
     * We need this because:
     *   We must do some work in the WalkStack implementation
     *   only if initialization success.
     *   We must not do some work in the Initialize only
     *   if Initialize has not been called before.
     */
    InitializationState m_InitializationState;

    /**
     * All "dbghelp.dll" functions are single threaded.
     * So we must protect calls to the "dbghelp.dll"
     * with critical section.
     */
    ATL::CComAutoCriticalSection m_DbgHelpGuard;
    //
    // Pointers to the "dbghelp.dll" functions.
    //

    // SymGetLineFromAddr64()
    typedef BOOL (__stdcall *tfnSymGetLineFromAddr64)(
        HANDLE hProcess,
        DWORD64 dwAddr,
        PDWORD pdwDisplacement,
        PIMAGEHLP_LINE64 Line);
    tfnSymGetLineFromAddr64 pfnSymGetLineFromAddr64;

    // SymGetSymFromAddr64()
    typedef BOOL (__stdcall *tfnSymGetSymFromAddr64)(
        HANDLE hProcess,
        DWORD64 dwAddr,
        PDWORD64 pdwDisplacement,
        PIMAGEHLP_SYMBOL64 Symbol);
    tfnSymGetSymFromAddr64 pfnSymGetSymFromAddr64;

    // SymInitialize()
    typedef BOOL (__stdcall *tfnSymInitialize)(
        HANDLE hProcess,
        PSTR UserSearchPath,
        BOOL fInvadeProcess );
    tfnSymInitialize pfnSymInitialize;

    // SymSetOptions()
    typedef DWORD (__stdcall *tfnSymSetOptions)(
        DWORD SymOptions);
    tfnSymSetOptions pfnSymSetOptions;

    // SymGetOptions()
    typedef DWORD (__stdcall *tfnSymGetOptions)();
    tfnSymGetOptions pfnSymGetOptions;

    // StackWalk64()
    typedef BOOL (__stdcall *tfnStackWalk64)(
        DWORD MachineType,
        HANDLE hProcess,
        HANDLE hThread,
        LPSTACKFRAME64 StackFrame,
        PVOID ContextRecord,
        PREAD_PROCESS_MEMORY_ROUTINE64 ReadMemoryRoutine,
        PFUNCTION_TABLE_ACCESS_ROUTINE64 FunctionTableAccessRoutine,
        PGET_MODULE_BASE_ROUTINE64 GetModuleBaseRoutine,
        PTRANSLATE_ADDRESS_ROUTINE64 TranslateAddress );
    tfnStackWalk64 pfnStackWalk64;

    // UnDecorateSymbolName()
    typedef DWORD (__stdcall WINAPI *tfnUnDecorateSymbolName)(
        PCSTR DecoratedName,
        PSTR UnDecoratedName,
        DWORD UndecoratedLength,
        DWORD Flags);
    tfnUnDecorateSymbolName pfnUnDecorateSymbolName;

    // SymFunctionTableAccess64()
    typedef PVOID (__stdcall *tfnSymFunctionTableAccess64)(
        HANDLE hProcess,
        DWORD64 AddrBase);
    tfnSymFunctionTableAccess64 pfnSymFunctionTableAccess64;

    // SymGetModuleBase64()
    typedef DWORD64 (__stdcall *tfnSymGetModuleBase64)(
        HANDLE hProcess,
        DWORD64 dwAddr );
    tfnSymGetModuleBase64 pfnSymGetModuleBase64;

public:
    RpcExStackTraceEngine();

    /**
     * Initializes the RpcExStackTraceEngine().
     * In fact we just initializing symbols engine.
     */
    HRESULT Initialize();

    /**
     * Returns result of the Initialize() call.
     */
    InitializationState GetInitializationState();

    /**
     * Returns stack trace as a string.
     */
    HRESULT WalkStack(
        CHAR* StackTrace,
        DWORD StackTraceSize, /*in characters*/
        DWORD MaxStackTraceDepth);
};

#endif // __RPC_EX_STACK_TRACE_ENGINE_INCLUDED__
