#include "..\Headers\FTP_API.hpp"



#ifdef _WIN32



bool FTP_API::FileSystem::ListFiles(const char* _Folder, std::vector<std::string>& _FileNames)
{
	return true;
}



#endif



#ifdef __unix__



bool FTP_API::FileSystem::ListFiles(const char* _Folder, std::vector<std::string>& _FileNames)
{
	return true;
}



#endif
