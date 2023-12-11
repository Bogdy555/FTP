#ifndef FTP_API_Macros_hpp

#define FTP_API_Macros_hpp



#include "FTP_API.hpp"



#ifdef UNICODE

#define FTP_API_STRING_TYPE(X) L ## X

#endif

#ifndef UNICODE

#define FTP_API_STRING_TYPE(X) X

#endif



#define FTP_API_PRINT_A(X) std::cout << X
#define FTP_API_PRINT_W(X) std::wcout << X

#ifdef UNICODE

#define FTP_API_PRINT(X) FTP_API_PRINT_W(X)

#endif

#ifndef UNICODE

#define FTP_API_PRINT(X) FTP_API_PRINT_A(X)

#endif

#define FTP_API_PRINT_LINE_A(X) std::cout << X << '\n'
#define FTP_API_PRINT_LINE_W(X) std::wcout << X << L'\n'

#ifdef UNICODE

#define FTP_API_PRINT_LINE(X) FTP_API_PRINT_LINE_W(X)

#endif

#ifndef UNICODE

#define FTP_API_PRINT_LINE(X) FTP_API_PRINT_LINE_A(X)

#endif



#ifdef _DEBUG

#define FTP_API_LOG_A(X) std::cout << X
#define FTP_API_LOG_W(X) std::wcout << X

#ifdef UNICODE

#define FTP_API_LOG(X) FTP_API_LOG_W(X)

#endif

#ifndef UNICODE

#define FTP_API_LOG(X) FTP_API_LOG_A(X)

#endif

#define FTP_API_LOG_LINE_A(X) std::cout << X << '\n'
#define FTP_API_LOG_LINE_W(X) std::wcout << X << L'\n'

#ifdef UNICODE

#define FTP_API_LOG_LINE(X) FTP_API_LOG_LINE_W(X)

#endif

#ifndef UNICODE

#define FTP_API_LOG_LINE(X) FTP_API_LOG_LINE_A(X)

#endif

#endif

#ifndef _DEBUG

#define FTP_API_LOG_A(X)
#define FTP_API_LOG_W(X)
#define FTP_API_LOG(X)

#define FTP_API_LOG_LINE_A(X)
#define FTP_API_LOG_LINE_W(X)
#define FTP_API_LOG_LINE(X)

#endif



#ifdef _WIN32

#ifdef _DEBUG

#define FTP_API_OUTPUT_DEBUG_STR_A(X) OutputDebugStringA(X)
#define FTP_API_OUTPUT_DEBUG_STR_W(X) OutputDebugStringW(X)

#ifdef UNICODE

#define FTP_API_OUTPUT_DEBUG_STR(X) FTP_API_OUTPUT_DEBUG_STR_W(X)

#endif

#ifndef UNICODE

#define FTP_API_OUTPUT_DEBUG_STR(X) FTP_API_OUTPUT_DEBUG_STR_A(X)

#endif

#define FTP_API_OUTPUT_DEBUG_STR_LINE_A(X) OutputDebugStringA(X); OutputDebugStringA("\n")
#define FTP_API_OUTPUT_DEBUG_STR_LINE_W(X) OutputDebugStringW(X); OutputDebugStringW(L"\n")

#ifdef UNICODE

#define FTP_API_OUTPUT_DEBUG_STR_LINE(X) FTP_API_OUTPUT_DEBUG_STR_LINE_W(X)

#endif

#ifndef UNICODE

#define FTP_API_OUTPUT_DEBUG_STR_LINE(X) FTP_API_OUTPUT_DEBUG_STR_LINE_A(X)

#endif

#endif

#ifndef _DEBUG

#define FTP_API_OUTPUT_DEBUG_STR_A(X)
#define FTP_API_OUTPUT_DEBUG_STR_W(X)
#define FTP_API_OUTPUT_DEBUG_STR(X)

#define FTP_API_OUTPUT_DEBUG_STR_LINE_A(X)
#define FTP_API_OUTPUT_DEBUG_STR_LINE_W(X)
#define FTP_API_OUTPUT_DEBUG_STR_LINE(X)

#endif

#endif

#ifdef __unix__

#define FTP_API_OUTPUT_DEBUG_STR_A(X) FTP_API_LOG_A(X)
#define FTP_API_OUTPUT_DEBUG_STR_W(X) FTP_API_LOG_W(X)
#define FTP_API_OUTPUT_DEBUG_STR(X) FTP_API_LOG(X)

#define FTP_API_OUTPUT_DEBUG_STR_LINE_A(X) FTP_API_LOG_LINE_A(X)
#define FTP_API_OUTPUT_DEBUG_STR_LINE_W(X) FTP_API_LOG_LINE_W(X)
#define FTP_API_OUTPUT_DEBUG_STR_LINE(X) FTP_API_LOG_LINE(X)

#endif



#ifdef _WIN32

#ifdef _DEBUG

#define FTP_API_DEBUG_BREAK() __debugbreak()

#define FTP_API_DEBUG_BREAK_MSG_A(Msg) MessageBoxA(NULL, Msg, "Debug break!", MB_OK | MB_ICONERROR); __debugbreak()
#define FTP_API_DEBUG_BREAK_MSG_W(Msg) MessageBoxW(NULL, Msg, L"Debug break!", MB_OK | MB_ICONERROR); __debugbreak()

#ifdef UNICODE

#define FTP_API_DEBUG_BREAK_MSG(Msg) FTP_API_DEBUG_BREAK_MSG_W(Msg)

#endif

#ifndef UNICODE

#define FTP_API_DEBUG_BREAK_MSG(Msg) FTP_API_DEBUG_BREAK_MSG_A(Msg)

#endif

#endif

#ifndef _DEBUG

#define FTP_API_DEBUG_BREAK()
#define FTP_API_DEBUG_BREAK_MSG_A(Msg)
#define FTP_API_DEBUG_BREAK_MSG_W(Msg)
#define FTP_API_DEBUG_BREAK_MSG(Msg)

#endif

#endif

#ifdef __unix__

#ifdef _DEBUG

#define FTP_API_DEBUG_BREAK() raise(SIGTRAP)

#define FTP_API_DEBUG_BREAK_MSG_A(Msg) FTP_API_PRINT_LINE_A(Msg); raise(SIGTRAP)
#define FTP_API_DEBUG_BREAK_MSG_W(Msg) FTP_API_PRINT_LINE_W(Msg); raise(SIGTRAP)

#ifdef UNICODE

#define FTP_API_DEBUG_BREAK_MSG(Msg) FTP_API_DEBUG_BREAK_MSG_W(Msg)

#endif

#ifndef UNICODE

#define FTP_API_DEBUG_BREAK_MSG(Msg) FTP_API_DEBUG_BREAK_MSG_A(Msg)

#endif

#endif

#ifndef _DEBUG

#define FTP_API_DEBUG_BREAK()
#define FTP_API_DEBUG_BREAK_MSG_A(Msg)
#define FTP_API_DEBUG_BREAK_MSG_W(Msg)
#define FTP_API_DEBUG_BREAK_MSG(Msg)

#endif

#endif



#ifdef _DEBUG

#define FTP_API_ASSERT(Condition) if (!(Condition))\
{\
	FTP_API_DEBUG_BREAK();\
}

#define FTP_API_ASSERT_MSG_A(Condition, Msg) if (!(Condition))\
{\
	FTP_API_DEBUG_BREAK_MSG_A(Msg);\
}

#define FTP_API_ASSERT_MSG_W(Condition, Msg) if (!(Condition))\
{\
	FTP_API_DEBUG_BREAK_MSG_W(Msg);\
}

#ifdef UNICODE

#define FTP_API_ASSERT_MSG(Condition, Msg) FTP_API_ASSERT_MSG_W(Condition, Msg)

#endif

#ifndef UNICODE

#define FTP_API_ASSERT_MSG(Condition, Msg) FTP_API_ASSERT_MSG_A(Condition, Msg)

#endif

#endif

#ifndef _DEBUG

#define FTP_API_ASSERT(Condition)
#define FTP_API_ASSERT_MSG_A(Condition, Msg)
#define FTP_API_ASSERT_MSG_W(Condition, Msg)
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

#endif

#ifndef _WIN64

#define FTP_API_X86_CALL(X) X
#define FTP_API_X64_CALL(X)

#endif

#endif

#ifdef __unix__

#ifdef __x86_64__

#define FTP_API_X86_CALL(X)
#define FTP_API_X64_CALL(X) X

#endif

#ifndef __x86_64__

#define FTP_API_X86_CALL(X) X
#define FTP_API_X64_CALL(X)

#endif

#endif



#endif
