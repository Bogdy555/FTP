#ifndef FTP_Server_Dependencies_hpp

#define FTP_Server_Dependencies_hpp



#pragma pack(pop)



#ifdef _WIN32

#pragma comment(lib, "FTP_API.lib")

#endif

#ifdef __unix__



#endif



#include <FTP_API.hpp>



#pragma pack(push, 1)



#include "FTP_Server_Macros.hpp"



namespace FTP_Server
{

	namespace InputParser
	{

		enum ArgumentsIndexes : const size_t;

	}

}



#include "FTP_Server_Templates.hpp"



#endif
