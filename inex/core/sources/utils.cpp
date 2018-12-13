#include "stdafx.h"
#include "utils.h"

namespace inex {
namespace core {
namespace utils {

} // namespace utils
} // namespace core
} // namespace inex

//template <typename T>
//void print_mij(T* m, int d1, int d2);
//

//template <typename T>
//void print_mij(T* m, int d1, int d2)
//{
//	for(int i=0; i<d1; ++i)
//		for(int j=0; j<d2; ++j)
//			m[i*d2+j]; // obscure
//}
//// Discovered these tricks somewhere a couple of weeks ago
//// It assures us that only pointers can be casted
//template<typename Output,typename Input>
//Output pointer_cast(Input* inp)
//{
//	return static_cast<Output>(static_cast<void*>(inp));
//}
//
//template<typename Output,typename Input>
//const Output pointer_cast(const Input* inp)
//{
//	return static_cast<Output>(static_cast<const void*>(inp));
//}
//
//// The arraysize(arr) macro returns the # of elements in an array arr.
//// The expression is a compile-time constant, and therefore can be
//// used in defining new arrays, for example.  If you use arraysize on
//// a pointer by mistake, you will get a compile-time error.
////
//// One caveat is that arraysize() doesn't accept any array of an
//// anonymous type or a type defined inside a function.  In these rare
//// cases, you have to use the unsafe ARRAYSIZE() macro below.  This is
//// due to a limitation in C++'s template system.  The limitation might
//// eventually be removed, but it hasn't happened yet.
//
//// This template function declaration is used in defining arraysize.
//// Note that the function doesn't need an implementation, as we only
//// use its type.
//
//template <typename T, size_t N>
//constexpr char (&ArraySizeHelper(T (&array)[N]))[N];
//
//// That gcc wants both of these prototypes seems mysterious. VC, for
//// its part, can't decide which to use (another mystery). Matching of
//// template overloads: the final frontier.
//
//#ifndef _MSC_VER
//template <typename T, size_t N>
//constexpr char (&ArraySizeHelper(const T (&array)[N]))[N];
//#endif // #ifndef _MSC_VER
//
//
//template <typename T1, typename T2>
//auto add(T1 t1, T2 t2) -> decltype(t1 + t2)
//{
//   static_assert(std::is_integral<T1>::value, "Type T1 must be integral");
//   static_assert(std::is_integral<T2>::value, "Type T2 must be integral");
//
//   return t1 + t2;
//}


