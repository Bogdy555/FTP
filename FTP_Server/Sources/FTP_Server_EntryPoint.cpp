#include "../Headers/FTP_Server.hpp"



bool FTP_Server::On = false;
FTP_API::Multithreading::Mutex FTP_Server::OnMutex;
std::vector<std::string> FTP_Server::FileNames;
std::vector<uint8_t*> FTP_Server::FilesData;
std::vector<size_t> FTP_Server::FilesLength;
std::vector<FTP_API::Networking::EndPoint*> FTP_Server::Clients;
std::vector<FTP_API::Multithreading::Thread*> FTP_Server::ClientThreads;
std::vector<uint8_t> FTP_Server::ClientRequests;
std::vector<bool> FTP_Server::ClientError;
std::vector<bool> FTP_Server::ClientIsDone;
std::vector<std::string> FTP_Server::ClientPassWords;
std::vector<std::string> FTP_Server::ClientFileNames;
std::vector<size_t> FTP_Server::ClientFileLengths;
std::vector<uint8_t*> FTP_Server::ClientFilesData;
FTP_API::Multithreading::Mutex FTP_Server::ClientsMutex;
FTP_API::Networking::EndPoint FTP_Server::ListeningSocket;



FTP_API_THREAD_RETURN_TYPE ClientThread(void* _Data)
{
	FTP_API::Networking::EndPoint& _Client = *(FTP_API::Networking::EndPoint*)(_Data);

	uint8_t _RequestId = FTP_API::Protocol::_NullRequest;
	std::string _PassWord;
	std::string _FileName;
	size_t _FileLength = 0;
	uint8_t* _FileData = nullptr;
	bool _Error = false;

	if (!_Client.RecvUInt8(_RequestId))
	{
		_RequestId = FTP_API::Protocol::_NullRequest;
	}

	switch (_RequestId)
	{
	case FTP_API::Protocol::_ListFilesRequest:
	{
		if (!FTP_API::Protocol::ParseListFilesRequest(_Client, _PassWord))
		{
			_Error = true;
		}

		break;
	}
	case FTP_API::Protocol::_DownloadRequest:
	{
		if (!FTP_API::Protocol::ParseDownloadRequest(_Client, _PassWord, _FileName))
		{
			_Error = true;
		}

		break;
	}
	case FTP_API::Protocol::_UploadRequest:
	{
		if (!FTP_API::Protocol::ParseUploadRequest(_Client, _PassWord, _FileName, _FileLength, _FileData))
		{
			_Error = true;
		}

		break;
	}
	default:
	{
		_Error = true;
		break;
	}
	}

	FTP_Server::ClientsMutex.Lock();

	size_t _ClientIndex = FTP_Server::Clients.size();

	for (size_t _Index = 0; _Index < FTP_Server::Clients.size(); _Index++)
	{
		if (FTP_Server::Clients[_Index] = &_Client)
		{
			_ClientIndex = _Index;
			break;
		}
	}

	if (_ClientIndex == FTP_Server::Clients.size())
	{
		delete[] _FileData;
		FTP_Server::ClientsMutex.Unlock();
		return FTP_API_THREAD_RETURN_VALUE;
	}

	FTP_Server::ClientRequests[_ClientIndex] = _RequestId;
	FTP_Server::ClientError[_ClientIndex] = _Error;
	FTP_Server::ClientIsDone[_ClientIndex] = true;
	FTP_Server::ClientPassWords[_ClientIndex] = _PassWord;
	FTP_Server::ClientFileNames[_ClientIndex] = _FileName;
	FTP_Server::ClientFileLengths[_ClientIndex] = _FileLength;
	FTP_Server::ClientFilesData[_ClientIndex] = _FileData;

	FTP_Server::ClientsMutex.Unlock();

	return FTP_API_THREAD_RETURN_VALUE;
}



FTP_API_THREAD_RETURN_TYPE ListenThread(void* _Data)
{
	FTP_Server::OnMutex.Lock();

	while (FTP_Server::On)
	{
		FTP_Server::OnMutex.Unlock();

		FTP_API::Networking::EndPoint* _Client = new FTP_API::Networking::EndPoint;

		if (!_Client)
		{
			FTP_Server::OnMutex.Lock();
			continue;
		}

		if (!FTP_Server::ListeningSocket.GetNextClient(*_Client))
		{
			delete _Client;

			FTP_Server::OnMutex.Lock();
			continue;
		}

		FTP_Server::ClientsMutex.Lock();

		FTP_API::Multithreading::Thread* _ClientThread = new FTP_API::Multithreading::Thread;

		if (!_ClientThread)
		{
			_Client->Disconnect();
			delete _Client;

			FTP_Server::ClientsMutex.Unlock();

			FTP_Server::OnMutex.Lock();
			continue;
		}

		if (!_ClientThread->Spawn(ClientThread, _Client))
		{
			delete _ClientThread;

			_Client->Disconnect();
			delete _Client;

			FTP_Server::ClientsMutex.Unlock();

			FTP_Server::OnMutex.Lock();
			continue;
		}

		FTP_Server::Clients.emplace_back(_Client);
		FTP_Server::ClientThreads.emplace_back(_ClientThread);
		FTP_Server::ClientRequests.push_back(FTP_API::Protocol::_NullRequest);
		FTP_Server::ClientError.push_back(true);
		FTP_Server::ClientIsDone.push_back(false);
		FTP_Server::ClientPassWords.emplace_back(std::move(std::string()));
		FTP_Server::ClientFileNames.emplace_back(std::move(std::string()));
		FTP_Server::ClientFileLengths.push_back(0);
		FTP_Server::ClientFilesData.push_back(nullptr);

		FTP_Server::ClientsMutex.Unlock();

		FTP_Server::OnMutex.Lock();
	}

	FTP_Server::OnMutex.Unlock();

	return FTP_API_THREAD_RETURN_VALUE;
}



FTP_API_THREAD_RETURN_TYPE CLIThread(void* _Data)
{
	FTP_Server::OnMutex.Lock();

	while (FTP_Server::On)
	{
		FTP_Server::OnMutex.Unlock();

		std::string _Line;

		std::getline(std::cin, _Line);

		if (_Line == "exit")
		{
			FTP_Server::OnMutex.Lock();
			FTP_Server::On = false;
			FTP_Server::OnMutex.Unlock();
		}
		else
		{
			FTP_API_PRINT_LINE("Unknown command");
		}

		FTP_Server::OnMutex.Lock();
	}

	FTP_Server::OnMutex.Unlock();

	return FTP_API_THREAD_RETURN_VALUE;
}



int main(const int _ArgumentsCount, const char** _Arguments)
{
	if (!_ArgumentsCount || !_Arguments)
	{
		return -1;
	}

	if (!FTP_Server::InputParser::CheckArgumentsValidity(_ArgumentsCount, _Arguments))
	{
		FTP_API_PRINT_LINE("Usage: FTP_Server ip port working_dir password");

		return -1;
	}

#ifdef _WIN32

	if (!FTP_API::Networking::Init())
	{
		FTP_API_PRINT_LINE("Network driver error");

		return -1;
	}

#endif

	if (!FTP_Server::ListeningSocket.Host(_Arguments[FTP_Server::InputParser::_IpIndex], _Arguments[FTP_Server::InputParser::_PortIndex]))
	{
		FTP_API_PRINT_LINE("Could not host at specified ip and port");

		FTP_API_WIN_CALL(FTP_API::Networking::Stop());

		return -1;
	}

	FTP_Server::On = true;

	if (!FTP_Server::OnMutex.Create())
	{
		FTP_API_PRINT_LINE("Unexpected error");

		FTP_Server::On = false;
		FTP_Server::ListeningSocket.Disconnect();
		FTP_API_WIN_CALL(FTP_API::Networking::Stop());

		return -1;
	}

	if (!FTP_Server::ClientsMutex.Create())
	{
		FTP_API_PRINT_LINE("Unexpected error");

		FTP_Server::On = false;
		FTP_Server::OnMutex.Destroy();
		FTP_Server::ListeningSocket.Disconnect();
		FTP_API_WIN_CALL(FTP_API::Networking::Stop());

		return -1;
	}

	FTP_API::Multithreading::Thread _ListenThread;

	if (!_ListenThread.Spawn(ListenThread, nullptr))
	{
		FTP_API_PRINT_LINE("Unexpected error");

		FTP_Server::On = false;
		FTP_Server::OnMutex.Destroy();
		FTP_Server::ClientsMutex.Destroy();
		FTP_Server::ListeningSocket.Disconnect();
		FTP_API_WIN_CALL(FTP_API::Networking::Stop());

		return -1;
	}

	FTP_API::Multithreading::Thread _CLIThread;

	if (!_CLIThread.Spawn(CLIThread, nullptr))
	{
		FTP_API_PRINT_LINE("Unexpected error");

		FTP_Server::OnMutex.Lock();
		FTP_Server::On = false;
		FTP_Server::OnMutex.Unlock();
		FTP_API::Networking::EndPoint _QuickClient;
		_QuickClient.Connect(_Arguments[FTP_Server::InputParser::_IpIndex], _Arguments[FTP_Server::InputParser::_PortIndex]);
		_QuickClient.Disconnect();
		_ListenThread.Join();
		for (size_t _Index = 0; _Index < FTP_Server::Clients.size(); _Index++)
		{
			FTP_Server::Clients[_Index]->Disconnect();
			FTP_Server::ClientThreads[_Index]->Join();
			delete FTP_Server::Clients[_Index];
			delete FTP_Server::ClientThreads[_Index];
			delete[] FTP_Server::ClientFilesData[_Index];
		}
		FTP_Server::OnMutex.Destroy();
		FTP_Server::ClientsMutex.Destroy();
		FTP_Server::ListeningSocket.Disconnect();
		FTP_API_WIN_CALL(FTP_API::Networking::Stop());

		return -1;
	}

	FTP_Server::OnMutex.Lock();

	while (FTP_Server::On)
	{
		FTP_Server::OnMutex.Unlock();

		for (size_t _Index = 0; _Index < FTP_Server::FilesData.size(); _Index++)
		{
			delete[] FTP_Server::FilesData[_Index];
		}

		FTP_Server::FileNames.clear();
		FTP_Server::FilesData.clear();
		FTP_Server::FilesLength.clear();

		if (FTP_API::FileSystem::ListFiles(_Arguments[FTP_Server::InputParser::_WorkingDirIndex], FTP_Server::FileNames))
		{
			for (size_t _Index = 0; _Index < FTP_Server::FileNames.size(); _Index++)
			{
				size_t _Length = 0;
				uint8_t* _Data = nullptr;

				if (!FTP_API::FileSystem::LoadFile((_Arguments[FTP_Server::InputParser::_WorkingDirIndex] + FTP_Server::FileNames[_Index]).c_str(), _Length, _Data))
				{
					FTP_Server::FileNames.erase(FTP_Server::FileNames.begin() + _Index);
					_Index--;
					continue;
				}

				FTP_Server::FilesData.push_back(_Data);
				FTP_Server::FilesLength.push_back(_Length);
			}
		}

		FTP_Server::ClientsMutex.Lock();

		for (size_t _Index = 0; _Index < FTP_Server::Clients.size(); _Index++)
		{
			FTP_API::Networking::EndPoint* _Client = FTP_Server::Clients[_Index];
			FTP_API::Multithreading::Thread* _ClientThread = FTP_Server::ClientThreads[_Index];
			uint8_t _Request = FTP_Server::ClientRequests[_Index];
			bool _Error = FTP_Server::ClientError[_Index];
			bool _IsDone = FTP_Server::ClientIsDone[_Index];
			std::string _PassWord = FTP_Server::ClientPassWords[_Index];
			std::string _FileName = FTP_Server::ClientFileNames[_Index];
			size_t _FileLength = FTP_Server::ClientFileLengths[_Index];
			uint8_t* _FileData = FTP_Server::ClientFilesData[_Index];

			if (!_IsDone)
			{
				continue;
			}

			FTP_Server::Clients.erase(FTP_Server::Clients.begin() + _Index);
			FTP_Server::ClientThreads.erase(FTP_Server::ClientThreads.begin() + _Index);
			FTP_Server::ClientRequests.erase(FTP_Server::ClientRequests.begin() + _Index);
			FTP_Server::ClientError.erase(FTP_Server::ClientError.begin() + _Index);
			FTP_Server::ClientIsDone.erase(FTP_Server::ClientIsDone.begin() + _Index);
			FTP_Server::ClientPassWords.erase(FTP_Server::ClientPassWords.begin() + _Index);
			FTP_Server::ClientFileNames.erase(FTP_Server::ClientFileNames.begin() + _Index);
			FTP_Server::ClientFileLengths.erase(FTP_Server::ClientFileLengths.begin() + _Index);
			FTP_Server::ClientFilesData.erase(FTP_Server::ClientFilesData.begin() + _Index);

			_Index--;

			_ClientThread->Join();
			delete _ClientThread;

			if (_Error)
			{
				_Client->Disconnect();
				delete _Client;

				delete[] _FileData;

				continue;
			}

			switch (_Request)
			{
			case FTP_API::Protocol::_ListFilesRequest:
			{
				bool _ReplyStatus = false;
				std::vector<std::string> _ReplyFileNames;

				if (_PassWord == _Arguments[FTP_Server::InputParser::_PassWordIndex])
				{
					_ReplyStatus = true;
					_ReplyFileNames = FTP_Server::FileNames;
				}

				FTP_API::Protocol::RenderListFilesReply(*_Client, _ReplyStatus, _ReplyFileNames);

				break;
			}
			case FTP_API::Protocol::_DownloadRequest:
			{
				bool _ReplyStatus = false;
				size_t _ReplyFileLength = 0;
				uint8_t* _ReplyFileData = nullptr;

				if (_PassWord == _Arguments[FTP_Server::InputParser::_PassWordIndex])
				{
					size_t _TrueFileIndex = FTP_Server::FileNames.size();

					for (size_t _FileIndex = 0; _FileIndex < FTP_Server::FileNames.size(); _FileIndex++)
					{
						if (FTP_Server::FileNames[_FileIndex] == _FileName)
						{
							_TrueFileIndex = _FileIndex;
							break;
						}
					}

					if (_TrueFileIndex != FTP_Server::FileNames.size())
					{
						_ReplyStatus = true;
						_ReplyFileLength = FTP_Server::FilesLength[_TrueFileIndex];
						_ReplyFileData = FTP_Server::FilesData[_TrueFileIndex];
					}
				}

				FTP_API::Protocol::RenderDownloadReply(*_Client, _ReplyStatus, _ReplyFileLength, _ReplyFileData);

				break;
			}
			case FTP_API::Protocol::_UploadRequest:
			{
				bool _ReplyStatus = false;

				if (_PassWord == _Arguments[FTP_Server::InputParser::_PassWordIndex])
				{
					if (FTP_API::FileSystem::SaveFile((_Arguments[FTP_Server::InputParser::_WorkingDirIndex] + _FileName).c_str(), _FileLength, _FileData))
					{
						_ReplyStatus = true;
					}
				}

				FTP_API::Protocol::RenderUploadReply(*_Client, _ReplyStatus);

				break;
			}
			default:
			{
				break;
			}
			}

			_Client->Disconnect();
			delete _Client;

			delete[] _FileData;
		}

		FTP_Server::ClientsMutex.Unlock();

		FTP_Server::OnMutex.Lock();
	}

	FTP_Server::OnMutex.Unlock();

	_CLIThread.Join();
	FTP_API::Networking::EndPoint _QuickClient;
	_QuickClient.Connect(_Arguments[FTP_Server::InputParser::_IpIndex], _Arguments[FTP_Server::InputParser::_PortIndex]);
	_QuickClient.Disconnect();
	_ListenThread.Join();
	for (size_t _Index = 0; _Index < FTP_Server::Clients.size(); _Index++)
	{
		FTP_Server::Clients[_Index]->Disconnect();
		FTP_Server::ClientThreads[_Index]->Join();
		delete FTP_Server::Clients[_Index];
		delete FTP_Server::ClientThreads[_Index];
		delete[] FTP_Server::ClientFilesData[_Index];
	}
	for (size_t _Index = 0; _Index < FTP_Server::FilesData.size(); _Index++)
	{
		delete[] FTP_Server::FilesData[_Index];
	}
	FTP_Server::OnMutex.Destroy();
	FTP_Server::ClientsMutex.Destroy();
	FTP_Server::ListeningSocket.Disconnect();
	FTP_API_WIN_CALL(FTP_API::Networking::Stop());

	return 0;
}
