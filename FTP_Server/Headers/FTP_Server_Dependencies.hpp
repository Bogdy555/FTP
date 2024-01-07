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

	extern bool On;
	extern FTP_API::Multithreading::Mutex OnMutex;

	extern std::vector<std::string> FileNames;
	extern std::vector<uint8_t*> FilesData;
	extern std::vector<size_t> FilesLength;

	extern std::vector<FTP_API::Networking::EndPoint*> Clients;
	extern std::vector<FTP_API::Multithreading::Thread*> ClientThreads;
	extern std::vector<uint8_t> ClientRequests;
	extern std::vector<bool> ClientError;
	extern std::vector<bool> ClientIsDone;
	extern std::vector<std::string> ClientPassWords;
	extern std::vector<std::string> ClientFileNames;
	extern std::vector<size_t> ClientFileLengths;
	extern std::vector<uint8_t*> ClientFilesData;
	extern FTP_API::Multithreading::Mutex ClientsMutex;

	extern FTP_API::Networking::EndPoint ListeningSocket;

	namespace InputParser
	{

		enum ArgumentsIndexes : const size_t;

	}

}



#include "FTP_Server_Templates.hpp"



#endif
