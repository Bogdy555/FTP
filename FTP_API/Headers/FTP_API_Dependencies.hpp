#ifndef FTP_API_Dependencies_hpp

#define FTP_API_Dependencies_hpp



#pragma pack(pop)



#ifdef _WIN32



#pragma comment(lib, "Ws2_32.lib")



#include "FTP_API_WinTargetVer.hpp"

#include <WinSock2.h>
#include <WS2tcpip.h>

#include <Windows.h>



#endif



#ifdef __unix__



#include <pthread.h>
#include <signal.h>
#include <sys/socket.h>
#include <netdb.h>



#endif



#include <iostream>



#pragma pack(push, 1)



#include "FTP_API_Macros.hpp"



#ifdef __unix__

typedef int SOCKET;

#define INVALID_SOCKET (SOCKET)(~0)
#define SOCKET_ERROR -1
#define NO_ERROR 0

#endif



namespace FTP_API
{

	namespace Networking
	{

		class EndPoint;

	}

	namespace Multithreading
	{

		FTP_API_WIN_CALL(typedef uint32_t (__stdcall *ThreadFnc)(void*));
		FTP_API_LNX_CALL(typedef void* (*ThreadFnc)(void*));

		class Thread;

		class Mutex;

	}

}



#include "FTP_API_Templates.hpp"



#endif
