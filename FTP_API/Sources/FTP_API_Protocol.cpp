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

	if (!_ServerConnection.SendBuff(_FileData, _FileLength))
	{
		return false;
	}

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

		if (_ProtocolSize == 0)
		{
			return false;
		}

		_Size = _ProtocolSize;
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
