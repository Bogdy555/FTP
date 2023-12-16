#include "../Headers/FTP_Client.hpp"



FTP_API::Networking::EndPoint FTP_Client::ServerConnection;



int main(const int _ArgumentsCount, const char** _Arguments)
{
	if (!_ArgumentsCount || !_Arguments)
	{
		FTP_API_PRINT_LINE("Unexpected error");

		return -1;
	}

	if (!FTP_Client::InputParser::CheckArgumentsValidity(_ArgumentsCount, _Arguments))
	{
		FTP_API_PRINT_LINE("Usage: FTP_Client ip port [action]");
		FTP_API_PRINT_LINE("[action] could be one of the following:");
		FTP_API_PRINT_LINE("\tlist_files password");
		FTP_API_PRINT_LINE("\tdownload password file_name");
		FTP_API_PRINT_LINE("\tupload password file_name");

		return -1;
	}

	const uint8_t _ActionType = FTP_Client::InputParser::GetActionType(_Arguments[FTP_Client::InputParser::_ActionIndex]);

	if (_ActionType == FTP_Client::InputParser::_NullAction)
	{
		FTP_API_PRINT_LINE("Unexpected error");

		return -1;
	}

#ifdef _WIN32

	if (!FTP_API::Networking::Init())
	{
		FTP_API_PRINT_LINE("Network driver error");

		return -1;
	}

#endif

	if (!FTP_Client::ServerConnection.Connect(_Arguments[FTP_Client::InputParser::_IpIndex], _Arguments[FTP_Client::InputParser::_PortIndex]))
	{
		FTP_API_PRINT_LINE("Could not connect to the server");

		FTP_API_WIN_CALL(FTP_API::Networking::Stop());

		return -1;
	}

	switch (_ActionType)
	{
	case FTP_Client::InputParser::_ListFilesAction:
	{
		if (!FTP_API::Protocol::RenderListFilesRequest(FTP_Client::ServerConnection, _Arguments[FTP_Client::InputParser::_PassWordIndex]))
		{
			FTP_API_PRINT_LINE("Unexpected error");

			FTP_Client::ServerConnection.Disconnect();
			FTP_API_WIN_CALL(FTP_API::Networking::Stop());

			return -1;
		}

		std::vector<std::string> _FileNames;

		if (!FTP_API::Protocol::ParseListFilesReply(FTP_Client::ServerConnection, _FileNames))
		{
			FTP_API_PRINT_LINE("Unexpected error");

			FTP_Client::ServerConnection.Disconnect();
			FTP_API_WIN_CALL(FTP_API::Networking::Stop());

			return -1;
		}

		for (size_t _Index = 0; _Index < _FileNames.size(); _Index++)
		{
			FTP_API_PRINT_LINE(_FileNames[_Index]);
		}

		break;
	}
	case FTP_Client::InputParser::_DownloadAction:
	{
		if (!FTP_API::Protocol::RenderDownloadRequest(FTP_Client::ServerConnection, _Arguments[FTP_Client::InputParser::_PassWordIndex], _Arguments[FTP_Client::InputParser::_FileNameIndex]))
		{
			FTP_API_PRINT_LINE("Unexpected error");

			FTP_Client::ServerConnection.Disconnect();
			FTP_API_WIN_CALL(FTP_API::Networking::Stop());

			return -1;
		}

		size_t _FileLength = 0;
		uint8_t* _FileData = nullptr;

		if (!FTP_API::Protocol::ParseDownloadReply(FTP_Client::ServerConnection, _FileLength, _FileData))
		{
			FTP_API_PRINT_LINE("Unexpected error");

			FTP_Client::ServerConnection.Disconnect();
			FTP_API_WIN_CALL(FTP_API::Networking::Stop());

			return -1;
		}

		break;
	}
	case FTP_Client::InputParser::_UploadAction:
	{
		if (!FTP_API::Protocol::RenderUploadRequest(FTP_Client::ServerConnection, _Arguments[FTP_Client::InputParser::_PassWordIndex], _Arguments[FTP_Client::InputParser::_FileNameIndex], 0, nullptr))
		{
			FTP_API_PRINT_LINE("Unexpected error");

			FTP_Client::ServerConnection.Disconnect();
			FTP_API_WIN_CALL(FTP_API::Networking::Stop());

			return -1;
		}

		if (!FTP_API::Protocol::ParseUploadReply(FTP_Client::ServerConnection))
		{
			FTP_API_PRINT_LINE("Unexpected error");

			FTP_Client::ServerConnection.Disconnect();
			FTP_API_WIN_CALL(FTP_API::Networking::Stop());

			return -1;
		}

		break;
	}
	default:
	{
		FTP_API_PRINT_LINE("Unexpected error");

		FTP_Client::ServerConnection.Disconnect();
		FTP_API_WIN_CALL(FTP_API::Networking::Stop());

		return -1;
	}
	}

	FTP_Client::ServerConnection.Disconnect();
	FTP_API_WIN_CALL(FTP_API::Networking::Stop());

	return 0;
}
