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
			_UploadRequest = 3
		};

		bool RenderListFilesRequest(Networking::EndPoint& _ServerConnection, const char* _PassWord);
		bool RenderDownloadRequest(Networking::EndPoint& _ServerConnection, const char* _PassWord, const char* _FileName);
		bool RenderUploadRequest(Networking::EndPoint& _ServerConnection, const char* _PassWord, const char* _FileName, const uint32_t _FileLength, const uint8_t* _FileData);

		bool RenderListFilesReply(Networking::EndPoint& _ClientConnection);
		bool RenderDownloadReply(Networking::EndPoint& _ClientConnection);
		bool RenderUploadReply(Networking::EndPoint& _ClientConnection);

		bool ParseListFilesRequest(Networking::EndPoint& _ClientConnection);
		bool ParseDownloadRequest(Networking::EndPoint& _ClientConnection);
		bool ParseUploadRequest(Networking::EndPoint& _ClientConnection);

		bool ParseListFilesReply(Networking::EndPoint& _ServerConnection, std::vector<std::string>& _FileNames);
		bool ParseDownloadReply(Networking::EndPoint& _ServerConnection, size_t& _FileLength, BytesBuffer& _FileData);
		bool ParseUploadReply(Networking::EndPoint& _ServerConnection);

	}

}



#endif
