#ifndef FTP_API_FileSystem_hpp

#define FTP_API_FileSystem_hpp



#include "FTP_API.hpp"



namespace FTP_API
{

	namespace FileSystem
	{

		bool ListFiles(const char* _Folder, std::vector<std::string>& _FileNames);

	}

}



#endif
