#ifndef FTP_API_FileSystem_hpp

#define FTP_API_FileSystem_hpp



#include "FTP_API.hpp"



namespace FTP_API
{

	namespace FileSystem
	{

		bool ListFiles(const char* _Folder, std::vector<std::string>& _FileNames);

		bool SaveFile(const char* _FileName, const size_t _FileLength, const uint8_t* _FileData);

		bool LoadFile(const char* _FileName, size_t& _FileLength, BytesBuffer& _FileData);

	}

}



#endif
