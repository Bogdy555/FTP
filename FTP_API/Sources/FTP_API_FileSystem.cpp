#include "../Headers/FTP_API.hpp"



#ifdef _WIN32



bool FTP_API::FileSystem::ListFiles(const char* _Folder, std::vector<std::string>& _FileNames)
{
	return true;
}

bool FTP_API::FileSystem::SaveFile(const char* _FileName, const size_t _FileLength, const uint8_t* _FileData)
{
	return true;
}

bool FTP_API::FileSystem::LoadFile(const char* _FileName, size_t& _FileLength, BytesBuffer& _FileData)
{
	return true;
}



#endif



#ifdef __unix__



bool FTP_API::FileSystem::ListFiles(const char* _Folder, std::vector<std::string>& _FileNames)
{
	return true;
}

bool FTP_API::FileSystem::SaveFile(const char* _FileName, const size_t _FileLength, const uint8_t* _FileData)
{
	return true;
}

bool FTP_API::FileSystem::LoadFile(const char* _FileName, size_t& _FileLength, BytesBuffer& _FileData)
{
	return true;
}



#endif
