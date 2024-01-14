#include "../Headers/FTP_API.hpp"



bool FTP_API::Protocol::RenderListFilesRequest(Networking::EndPoint& _ServerConnection, const char* _PassWord)
{
	if (_ServerConnection == INVALID_SOCKET)
	{
		return false;
	}

	if (_PassWord == nullptr || _PassWord[0] == '\0')
	{
		return false;
	}

	if (!_ServerConnection.SendUInt8(_ListFilesRequest))
	{
		return false;
	}

	if (!_ServerConnection.SendUInt32((uint32_t)(strlen(_PassWord))))
	{
		return false;
	}

	if (!_ServerConnection.SendBuff((const uint8_t*)(_PassWord), strlen(_PassWord)))
	{
		return false;
	}

	return true;
}

bool FTP_API::Protocol::RenderDownloadRequest(Networking::EndPoint& _ServerConnection, const char* _PassWord, const char* _FileName)
{
	if (_ServerConnection == INVALID_SOCKET)
	{
		return false;
	}

	if (_PassWord == nullptr || _PassWord[0] == '\0')
	{
		return false;
	}

	if (_FileName == nullptr || _FileName[0] == '\0')
	{
		return false;
	}

	if (!_ServerConnection.SendUInt8(_DownloadRequest))
	{
		return false;
	}

	if (!_ServerConnection.SendUInt32((uint32_t)(strlen(_PassWord))))
	{
		return false;
	}

	if (!_ServerConnection.SendBuff((const uint8_t*)(_PassWord), strlen(_PassWord)))
	{
		return false;
	}

	if (!_ServerConnection.SendUInt32((uint32_t)(strlen(_FileName))))
	{
		return false;
	}

	if (!_ServerConnection.SendBuff((const uint8_t*)(_FileName), strlen(_FileName)))
	{
		return false;
	}

	return true;
}

bool FTP_API::Protocol::RenderUploadRequest(Networking::EndPoint& _ServerConnection, const char* _PassWord, const char* _FileName, const size_t _FileLength, const uint8_t* _FileData)
{
	if (_ServerConnection == INVALID_SOCKET)
	{
		return false;
	}

	if (_PassWord == nullptr || _PassWord[0] == '\0')
	{
		return false;
	}

	if (_FileName == nullptr || _FileName[0] == '\0')
	{
		return false;
	}

	if (!_FileLength || _FileData == nullptr)
	{
		return false;
	}

	if (!_ServerConnection.SendUInt8(_UploadRequest))
	{
		return false;
	}

	if (!_ServerConnection.SendUInt32((uint32_t)(strlen(_PassWord))))
	{
		return false;
	}

	if (!_ServerConnection.SendBuff((const uint8_t*)(_PassWord), strlen(_PassWord)))
	{
		return false;
	}

	if (!_ServerConnection.SendUInt32((uint32_t)(strlen(_FileName))))
	{
		return false;
	}

	if (!_ServerConnection.SendBuff((const uint8_t*)(_FileName), strlen(_FileName)))
	{
		return false;
	}

	if (!_ServerConnection.SendUInt32((uint32_t)(_FileLength)))
	{
		return false;
	}

	if (!_FileLength)
	{
		return true;
	}

	if (!_ServerConnection.SendBuff(_FileData, _FileLength))
	{
		return false;
	}

	return true;
}

bool FTP_API::Protocol::RenderRemoveRequest(Networking::EndPoint& _ServerConnection, const char* _PassWord, const char* _FileName)
{
	if (_ServerConnection == INVALID_SOCKET)
	{
		return false;
	}

	if (_PassWord == nullptr || _PassWord[0] == '\0')
	{
		return false;
	}

	if (_FileName == nullptr || _FileName[0] == '\0')
	{
		return false;
	}

	if (!_ServerConnection.SendUInt8(_RemoveRequest))
	{
		return false;
	}

	if (!_ServerConnection.SendUInt32((uint32_t)(strlen(_PassWord))))
	{
		return false;
	}

	if (!_ServerConnection.SendBuff((const uint8_t*)(_PassWord), strlen(_PassWord)))
	{
		return false;
	}

	if (!_ServerConnection.SendUInt32((uint32_t)(strlen(_FileName))))
	{
		return false;
	}

	if (!_ServerConnection.SendBuff((const uint8_t*)(_FileName), strlen(_FileName)))
	{
		return false;
	}

	return true;
}

bool FTP_API::Protocol::RenderListFilesReply(Networking::EndPoint& _ClientConnection, const bool _Status, const std::vector<std::string>& _FileNames)
{
	if (_ClientConnection == INVALID_SOCKET)
	{
		return false;
	}

	if (!_Status)
	{
		return _ClientConnection.SendUInt8(0);
	}

	if (!_ClientConnection.SendUInt8(1))
	{
		return false;
	}

	size_t _TotalLength = 0;

	for (size_t _Index = 0; _Index < _FileNames.size(); _Index++)
	{
		_TotalLength += _FileNames[_Index].length() + 1;
	}

	if (!_ClientConnection.SendUInt32((uint32_t)(_TotalLength)))
	{
		return false;
	}

	for (size_t _Index = 0; _Index < _FileNames.size(); _Index++)
	{
		if (!_ClientConnection.SendBuff((const uint8_t*)(_FileNames[_Index].c_str()), _FileNames[_Index].length() + 1))
		{
			return false;
		}
	}

	return true;
}

bool FTP_API::Protocol::RenderDownloadReply(Networking::EndPoint& _ClientConnection, const bool _Status, const size_t _FileLength, const uint8_t* _FileData)
{
	if (_ClientConnection == INVALID_SOCKET)
	{
		return false;
	}

	if (!_Status)
	{
		return _ClientConnection.SendUInt8(0);
	}

	if (!_ClientConnection.SendUInt8(1))
	{
		return false;
	}

	if (!_ClientConnection.SendUInt32((uint32_t)(_FileLength)))
	{
		return false;
	}

	if (!_FileLength)
	{
		return true;
	}

	if (!_ClientConnection.SendBuff(_FileData, _FileLength))
	{
		return false;
	}

	return true;
}

bool FTP_API::Protocol::RenderUploadReply(Networking::EndPoint& _ClientConnection, const bool _Status)
{
	if (_ClientConnection == INVALID_SOCKET)
	{
		return false;
	}

	if (!_Status)
	{
		return _ClientConnection.SendUInt8(0);
	}

	if (!_ClientConnection.SendUInt8(1))
	{
		return false;
	}

	return true;
}

bool FTP_API::Protocol::RenderRemoveReply(Networking::EndPoint& _ClientConnection, const bool _Status)
{
	if (_ClientConnection == INVALID_SOCKET)
	{
		return false;
	}

	if (!_Status)
	{
		return _ClientConnection.SendUInt8(0);
	}

	if (!_ClientConnection.SendUInt8(1))
	{
		return false;
	}

	return true;
}

bool FTP_API::Protocol::ParseListFilesRequest(Networking::EndPoint& _ClientConnection, std::string& _PassWord)
{
	_PassWord.clear();

	if (_ClientConnection == INVALID_SOCKET)
	{
		return false;
	}

	size_t _PassWordLength = 0;

	{
		uint32_t _ProtocolPassWordLength = 0;

		if (!_ClientConnection.RecvUInt32(_ProtocolPassWordLength))
		{
			return false;
		}

		if (!_ProtocolPassWordLength)
		{
			return false;
		}

		_PassWordLength = _ProtocolPassWordLength;
	}

	char* _ProtocolPassWord = new char[_PassWordLength + 1];

	if (!_ProtocolPassWord)
	{
		return false;
	}

	if (!_ClientConnection.RecvBuff((uint8_t*)(_ProtocolPassWord), _PassWordLength))
	{
		delete[] _ProtocolPassWord;
		return false;
	}

	_ProtocolPassWord[_PassWordLength] = '\0';

	_PassWord = _ProtocolPassWord;

	delete[] _ProtocolPassWord;

	return true;
}

bool FTP_API::Protocol::ParseDownloadRequest(Networking::EndPoint& _ClientConnection, std::string& _PassWord, std::string& _FileName)
{
	_PassWord.clear();
	_FileName.clear();

	if (_ClientConnection == INVALID_SOCKET)
	{
		return false;
	}

	size_t _PassWordLength = 0;

	{
		uint32_t _ProtocolPassWordLength = 0;

		if (!_ClientConnection.RecvUInt32(_ProtocolPassWordLength))
		{
			return false;
		}

		if (!_ProtocolPassWordLength)
		{
			return false;
		}

		_PassWordLength = _ProtocolPassWordLength;
	}

	char* _ProtocolPassWord = new char[_PassWordLength + 1];

	if (!_ProtocolPassWord)
	{
		return false;
	}

	if (!_ClientConnection.RecvBuff((uint8_t*)(_ProtocolPassWord), _PassWordLength))
	{
		delete[] _ProtocolPassWord;
		return false;
	}

	_ProtocolPassWord[_PassWordLength] = '\0';

	_PassWord = _ProtocolPassWord;

	delete[] _ProtocolPassWord;

	size_t _FileNameLength = 0;

	{
		uint32_t _ProtocolFileNameLength = 0;

		if (!_ClientConnection.RecvUInt32(_ProtocolFileNameLength))
		{
			_PassWord.clear();
			return false;
		}

		if (!_ProtocolFileNameLength)
		{
			_PassWord.clear();
			return false;
		}

		_FileNameLength = _ProtocolFileNameLength;
	}

	char* _ProtocolFileName = new char[_FileNameLength + 1];

	if (!_ProtocolFileName)
	{
		_PassWord.clear();
		return false;
	}

	if (!_ClientConnection.RecvBuff((uint8_t*)(_ProtocolFileName), _FileNameLength))
	{
		delete[] _ProtocolFileName;
		_PassWord.clear();
		return false;
	}

	_ProtocolFileName[_FileNameLength] = '\0';

	_FileName = _ProtocolFileName;

	delete[] _ProtocolFileName;

	return true;
}

bool FTP_API::Protocol::ParseUploadRequest(Networking::EndPoint& _ClientConnection, std::string& _PassWord, std::string& _FileName, size_t& _FileLength, BytesBuffer& _FileData)
{
	_PassWord.clear();
	_FileName.clear();
	_FileLength = 0;
	_FileData = nullptr;

	if (_ClientConnection == INVALID_SOCKET)
	{
		return false;
	}

	size_t _PassWordLength = 0;

	{
		uint32_t _ProtocolPassWordLength = 0;

		if (!_ClientConnection.RecvUInt32(_ProtocolPassWordLength))
		{
			return false;
		}

		if (!_ProtocolPassWordLength)
		{
			return false;
		}

		_PassWordLength = _ProtocolPassWordLength;
	}

	char* _ProtocolPassWord = new char[_PassWordLength + 1];

	if (!_ProtocolPassWord)
	{
		return false;
	}

	if (!_ClientConnection.RecvBuff((uint8_t*)(_ProtocolPassWord), _PassWordLength))
	{
		delete[] _ProtocolPassWord;
		return false;
	}

	_ProtocolPassWord[_PassWordLength] = '\0';

	_PassWord = _ProtocolPassWord;

	delete[] _ProtocolPassWord;

	size_t _FileNameLength = 0;

	{
		uint32_t _ProtocolFileNameLength = 0;

		if (!_ClientConnection.RecvUInt32(_ProtocolFileNameLength))
		{
			_PassWord.clear();
			return false;
		}

		if (!_ProtocolFileNameLength)
		{
			_PassWord.clear();
			return false;
		}

		_FileNameLength = _ProtocolFileNameLength;
	}

	char* _ProtocolFileName = new char[_FileNameLength + 1];

	if (!_ProtocolFileName)
	{
		_PassWord.clear();
		return false;
	}

	if (!_ClientConnection.RecvBuff((uint8_t*)(_ProtocolFileName), _FileNameLength))
	{
		delete[] _ProtocolFileName;
		_PassWord.clear();
		return false;
	}

	_ProtocolFileName[_FileNameLength] = '\0';

	_FileName = _ProtocolFileName;

	delete[] _ProtocolFileName;

	{
		uint32_t _ProtocolFileLength;

		if (!_ClientConnection.RecvUInt32(_ProtocolFileLength))
		{
			_PassWord.clear();
			_FileName.clear();
			return false;
		}

		_FileLength = _ProtocolFileLength;
	}

	if (!_FileLength)
	{
		return true;
	}

	_FileData = new uint8_t[_FileLength];

	if (!_FileData)
	{
		_PassWord.clear();
		_FileName.clear();
		_FileLength = 0;
		return false;
	}

	if (!_ClientConnection.RecvBuff(_FileData, _FileLength))
	{
		_PassWord.clear();
		_FileName.clear();
		_FileLength = 0;
		delete[] _FileData;
		_FileData = nullptr;
		return false;
	}

	return true;
}

bool FTP_API::Protocol::ParseRemoveRequest(Networking::EndPoint& _ClientConnection, std::string& _PassWord, std::string& _FileName)
{
	_PassWord.clear();
	_FileName.clear();

	if (_ClientConnection == INVALID_SOCKET)
	{
		return false;
	}

	size_t _PassWordLength = 0;

	{
		uint32_t _ProtocolPassWordLength = 0;

		if (!_ClientConnection.RecvUInt32(_ProtocolPassWordLength))
		{
			return false;
		}

		if (!_ProtocolPassWordLength)
		{
			return false;
		}

		_PassWordLength = _ProtocolPassWordLength;
	}

	char* _ProtocolPassWord = new char[_PassWordLength + 1];

	if (!_ProtocolPassWord)
	{
		return false;
	}

	if (!_ClientConnection.RecvBuff((uint8_t*)(_ProtocolPassWord), _PassWordLength))
	{
		delete[] _ProtocolPassWord;
		return false;
	}

	_ProtocolPassWord[_PassWordLength] = '\0';

	_PassWord = _ProtocolPassWord;

	delete[] _ProtocolPassWord;

	size_t _FileNameLength = 0;

	{
		uint32_t _ProtocolFileNameLength = 0;

		if (!_ClientConnection.RecvUInt32(_ProtocolFileNameLength))
		{
			_PassWord.clear();
			return false;
		}

		if (!_ProtocolFileNameLength)
		{
			_PassWord.clear();
			return false;
		}

		_FileNameLength = _ProtocolFileNameLength;
	}

	char* _ProtocolFileName = new char[_FileNameLength + 1];

	if (!_ProtocolFileName)
	{
		_PassWord.clear();
		return false;
	}

	if (!_ClientConnection.RecvBuff((uint8_t*)(_ProtocolFileName), _FileNameLength))
	{
		delete[] _ProtocolFileName;
		_PassWord.clear();
		return false;
	}

	_ProtocolFileName[_FileNameLength] = '\0';

	_FileName = _ProtocolFileName;

	delete[] _ProtocolFileName;

	return true;
}

bool FTP_API::Protocol::ParseListFilesReply(Networking::EndPoint& _ServerConnection, std::vector<std::string>& _FileNames)
{
	_FileNames.clear();

	if (_ServerConnection == INVALID_SOCKET)
	{
		return false;
	}

	{
		uint8_t _RequestStatus;

		if (!_ServerConnection.RecvUInt8(_RequestStatus))
		{
			return false;
		}

		if (_RequestStatus != 1)
		{
			return false;
		}
	}

	size_t _Size;

	{
		uint32_t _ProtocolSize;

		if (!_ServerConnection.RecvUInt32(_ProtocolSize))
		{
			return false;
		}

		_Size = _ProtocolSize;
	}

	if (!_Size)
	{
		return true;
	}

	char* _Buff = new char[_Size];

	if (!_Buff)
	{
		return false;
	}

	if (!_ServerConnection.RecvBuff((uint8_t*)(_Buff), _Size))
	{
		delete[] _Buff;

		return false;
	}

	if (_Buff[_Size - 1] != '\0')
	{
		delete[] _Buff;

		return false;
	}

	size_t _Index = 0;

	while (_Index < _Size)
	{
		if (strlen(_Buff + _Index) != 0)
		{
			_FileNames.push_back(_Buff + _Index);
		}

		_Index += strlen(_Buff + _Index) + 1;
	}

	delete[] _Buff;

	return true;
}

bool FTP_API::Protocol::ParseDownloadReply(Networking::EndPoint& _ServerConnection, size_t& _FileLength, BytesBuffer& _FileData)
{
	_FileData = nullptr;

	_FileLength = 0;

	if (_ServerConnection == INVALID_SOCKET)
	{
		return false;
	}

	{
		uint8_t _RequestStatus;

		if (!_ServerConnection.RecvUInt8(_RequestStatus))
		{
			return false;
		}

		if (_RequestStatus != 1)
		{
			return false;
		}
	}

	{
		uint32_t _ProtocolFileLength;

		if (!_ServerConnection.RecvUInt32(_ProtocolFileLength))
		{
			return false;
		}

		_FileLength = _ProtocolFileLength;
	}

	if (!_FileLength)
	{
		return true;
	}

	_FileData = new uint8_t[_FileLength];

	if (!_FileData)
	{
		_FileLength = 0;

		return false;
	}

	if (!_ServerConnection.RecvBuff(_FileData, _FileLength))
	{
		delete[] _FileData;
		_FileData = nullptr;

		_FileLength = 0;

		return false;
	}

	return true;
}

bool FTP_API::Protocol::ParseUploadReply(Networking::EndPoint& _ServerConnection)
{
	if (_ServerConnection == INVALID_SOCKET)
	{
		return false;
	}

	{
		uint8_t _RequestStatus;

		if (!_ServerConnection.RecvUInt8(_RequestStatus))
		{
			return false;
		}

		if (_RequestStatus != 1)
		{
			return false;
		}
	}

	return true;
}

bool FTP_API::Protocol::ParseRemoveReply(Networking::EndPoint& _ServerConnection)
{
	if (_ServerConnection == INVALID_SOCKET)
	{
		return false;
	}

	{
		uint8_t _RequestStatus;

		if (!_ServerConnection.RecvUInt8(_RequestStatus))
		{
			return false;
		}

		if (_RequestStatus != 1)
		{
			return false;
		}
	}

	return true;
}
