#ifndef FTP_API_Macros_hpp

#define FTP_API_Macros_hpp



#include "FTP_API.hpp"



#define FTP_API_PRINT(X) std::cout << X

#define FTP_API_PRINT_LINE(X) std::cout << X << '\n'



#ifdef _DEBUG

#define FTP_API_LOG(X) std::cout << X

#define FTP_API_LOG_LINE(X) std::cout << X << '\n'

#endif

#ifndef _DEBUG

#define FTP_API_LOG(X)

#define FTP_API_LOG_LINE(X)

#endif



#ifdef _WIN32

#ifdef _DEBUG

#define FTP_API_OUTPUT_DEBUG_STR(X) OutputDebugStringA(X)

#define FTP_API_OUTPUT_DEBUG_STR_LINE(X) OutputDebugStringA(X); OutputDebugStringA("\n")

#endif

#ifndef _DEBUG

#define FTP_API_OUTPUT_DEBUG_STR(X)

#define FTP_API_OUTPUT_DEBUG_STR_LINE(X)

#endif

#endif

#ifdef __unix__

#define FTP_API_OUTPUT_DEBUG_STR(X) FTP_API_LOG(X)

#define FTP_API_OUTPUT_DEBUG_STR_LINE(X) FTP_API_LOG_LINE(X)

#endif



#ifdef _WIN32

#ifdef _DEBUG

#define FTP_API_DEBUG_BREAK() __debugbreak()

#define FTP_API_DEBUG_BREAK_MSG(Msg) MessageBoxA(NULL, Msg, "Debug break!", MB_OK | MB_ICONERROR); __debugbreak()

#endif

#ifndef _DEBUG

#define FTP_API_DEBUG_BREAK()

#define FTP_API_DEBUG_BREAK_MSG(Msg)

#endif

#endif

#ifdef __unix__

#ifdef _DEBUG

#define FTP_API_DEBUG_BREAK() raise(SIGTRAP)

#define FTP_API_DEBUG_BREAK_MSG(Msg) FTP_API_PRINT_LINE(Msg); raise(SIGTRAP)

#endif

#ifndef _DEBUG

#define FTP_API_DEBUG_BREAK()

#define FTP_API_DEBUG_BREAK_MSG(Msg)

#endif

#endif



#ifdef _DEBUG

#define FTP_API_ASSERT(Condition) if (!(Condition))\
{\
	FTP_API_DEBUG_BREAK();\
}

#define FTP_API_ASSERT_MSG(Condition, Msg) if (!(Condition))\
{\
	FTP_API_DEBUG_BREAK_MSG(Msg);\
}

#endif

#ifndef _DEBUG

#define FTP_API_ASSERT(Condition)

#define FTP_API_ASSERT_MSG(Condition, Msg)

#endif



#ifdef _DEBUG

#define FTP_API_DEBUG_CALL(X) X
#define FTP_API_RELEASE_CALL(X)

#endif

#ifndef _DEBUG

#define FTP_API_DEBUG_CALL(X)
#define FTP_API_RELEASE_CALL(X) X

#endif



#ifdef _WIN32

#define FTP_API_WIN_CALL(X) X
#define FTP_API_LNX_CALL(X)

#endif

#ifdef __unix__

#define FTP_API_WIN_CALL(X)
#define FTP_API_LNX_CALL(X) X

#endif



#ifdef _WIN32

#ifdef _WIN64

#define FTP_API_X86_CALL(X)
#define FTP_API_X64_CALL(X) X
#define FTP_API_LITTLE_ENDIAN

#endif

#ifndef _WIN64

#define FTP_API_X86_CALL(X) X
#define FTP_API_X64_CALL(X)
#define FTP_API_LITTLE_ENDIAN

#endif

#endif

#ifdef __unix__

#ifdef __x86_64__

#define FTP_API_X86_CALL(X)
#define FTP_API_X64_CALL(X) X
#define FTP_API_LITTLE_ENDIAN

#endif

#ifndef __x86_64__

#define FTP_API_X86_CALL(X) X
#define FTP_API_X64_CALL(X)
#define FTP_API_LITTLE_ENDIAN

#endif

#endif



#endif
