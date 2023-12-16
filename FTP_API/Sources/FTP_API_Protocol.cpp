#include "../Headers/FTP_API.hpp"



bool FTP_API::Protocol::RenderListFilesRequest(Networking::EndPoint& _ServerConnection, const char* _PassWord)
{
	return true;
}

bool FTP_API::Protocol::RenderDownloadRequest(Networking::EndPoint& _ServerConnection, const char* _PassWord, const char* _FileName)
{
	return true;
}

bool FTP_API::Protocol::RenderUploadRequest(Networking::EndPoint& _ServerConnection, const char* _PassWord, const char* _FileName, const uint32_t _FileLength, const uint8_t* _FileData)
{
	return true;
}

bool FTP_API::Protocol::RenderListFilesReply(Networking::EndPoint& _ClientConnection)
{
	return true;
}

bool FTP_API::Protocol::RenderDownloadReply(Networking::EndPoint& _ClientConnection)
{
	return true;
}

bool FTP_API::Protocol::RenderUploadReply(Networking::EndPoint& _ClientConnection)
{
	return true;
}

bool FTP_API::Protocol::ParseListFilesRequest(Networking::EndPoint& _ClientConnection)
{
	return true;
}

bool FTP_API::Protocol::ParseDownloadRequest(Networking::EndPoint& _ClientConnection)
{
	return true;
}

bool FTP_API::Protocol::ParseUploadRequest(Networking::EndPoint& _ClientConnection)
{
	return true;
}

bool FTP_API::Protocol::ParseListFilesReply(Networking::EndPoint& _ServerConnection, std::vector<std::string>& _FileNames)
{
	return true;
}

bool FTP_API::Protocol::ParseDownloadReply(Networking::EndPoint& _ServerConnection, size_t& _FileLength, BytesBuffer& _FileData)
{
	return true;
}

bool FTP_API::Protocol::ParseUploadReply(Networking::EndPoint& _ServerConnection)
{
	return true;
}
