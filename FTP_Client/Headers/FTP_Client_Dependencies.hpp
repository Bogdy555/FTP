#ifndef FTP_Client_Dependencies_hpp

#define FTP_Client_Dependencies_hpp



#pragma pack(pop)



#ifdef _WIN32

#pragma comment(lib, "FTP_API.lib")

#endif

#ifdef __unix__



#endif



#include <FTP_API.hpp>



#pragma pack(push, 1)



#include "FTP_Client_Macros.hpp"



namespace FTP_Client
{

	extern FTP_API::Networking::EndPoint ServerConnection;

	namespace InputParser
	{

		enum ArgumentsIndexes : const size_t;

		enum ActionTypes : const uint8_t;

	}

}



#include "FTP_Client_Templates.hpp"



#endif
