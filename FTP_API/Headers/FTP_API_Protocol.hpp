#ifndef FTP_API_Protocol_hpp

#define FTP_API_Protocol_hpp



#include "FTP_API.hpp"



namespace FTP_API
{

	namespace Protocol
	{

		enum RequestIds : const uint8_t
		{
			_NullRequest = 0,
			_ListFilesRequest = 1,
			_DownloadRequest = 2,
			_UploadRequest = 3,
			_RemoveRequest = 4
		};

		bool RenderListFilesRequest(Networking::EndPoint& _ServerConnection, const char* _PassWord);
		bool RenderDownloadRequest(Networking::EndPoint& _ServerConnection, const char* _PassWord, const char* _FileName);
		bool RenderUploadRequest(Networking::EndPoint& _ServerConnection, const char* _PassWord, const char* _FileName, const size_t _FileLength, const uint8_t* _FileData);
		bool RenderRemoveRequest(Networking::EndPoint& _ServerConnection, const char* _PassWord, const char* _FileName);

		bool RenderListFilesReply(Networking::EndPoint& _ClientConnection, const bool _Status, const std::vector<std::string>& _FileNames);
		bool RenderDownloadReply(Networking::EndPoint& _ClientConnection, const bool _Status, const size_t _FileLength, const uint8_t* _FileData);
		bool RenderUploadReply(Networking::EndPoint& _ClientConnection, const bool _Status);
		bool RenderRemoveReply(Networking::EndPoint& _ClientConnection, const bool _Status);

		bool ParseListFilesRequest(Networking::EndPoint& _ClientConnection, std::string& _PassWord);
		bool ParseDownloadRequest(Networking::EndPoint& _ClientConnection, std::string& _PassWord, std::string& _FileName);
		bool ParseUploadRequest(Networking::EndPoint& _ClientConnection, std::string& _PassWord, std::string& _FileName, size_t& _FileLength, BytesBuffer& _FileData);
		bool ParseRemoveRequest(Networking::EndPoint& _ClientConnection, std::string& _PassWord, std::string& _FileName);

		bool ParseListFilesReply(Networking::EndPoint& _ServerConnection, std::vector<std::string>& _FileNames);
		bool ParseDownloadReply(Networking::EndPoint& _ServerConnection, size_t& _FileLength, BytesBuffer& _FileData);
		bool ParseUploadReply(Networking::EndPoint& _ServerConnection);
		bool ParseRemoveReply(Networking::EndPoint& _ServerConnection);

	}

}



#endif
