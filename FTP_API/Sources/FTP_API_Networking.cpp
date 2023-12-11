#include "../Headers/FTP_API.hpp"



#define FTP_API_LISTEN_MAX 1024



#ifdef _WIN32



WSADATA FTP_API::Networking::WSAData = { 0 };



bool FTP_API::Networking::Init()
{
	return WSAStartup(MAKEWORD(2, 2), &WSAData) == NO_ERROR;
}

void FTP_API::Networking::Stop()
{
	WSACleanup();
	WSAData = { 0 };
}



#endif



FTP_API::Networking::EndPoint::EndPoint() : Socket(INVALID_SOCKET)
{

}

FTP_API::Networking::EndPoint::EndPoint(EndPoint&& _Other) noexcept : Socket(_Other.Socket)
{
	_Other.Socket = INVALID_SOCKET;
}

FTP_API::Networking::EndPoint::~EndPoint()
{
	FTP_API_ASSERT_MSG(Socket == INVALID_SOCKET, FTP_API_STRING_TYPE("~EndPoint hit before cleanup!"));
}

bool FTP_API::Networking::EndPoint::Host(const char* _Address, const char* _Port)
{
	StopHosting();

	addrinfo* _AddressInfo = nullptr;

	{
		addrinfo _AddressHint = { 0 };

		_AddressHint.ai_family = AF_INET;
		_AddressHint.ai_socktype = SOCK_STREAM;
		_AddressHint.ai_protocol = IPPROTO_TCP;

		if (getaddrinfo(_Address, _Port, &_AddressHint, &_AddressInfo) != NO_ERROR)
		{
			return false;
		}
	}

	Socket = socket(_AddressInfo->ai_family, _AddressInfo->ai_socktype, _AddressInfo->ai_protocol);

	if (Socket == INVALID_SOCKET)
	{
		freeaddrinfo(_AddressInfo);
		return false;
	}

	if (bind(Socket, _AddressInfo->ai_addr, (int)(_AddressInfo->ai_addrlen)) != NO_ERROR)
	{
		FTP_API_WIN_CALL(closesocket(Socket));
		FTP_API_LNX_CALL(close(Socket));
		Socket = INVALID_SOCKET;
		freeaddrinfo(_AddressInfo);
		return false;
	}

	freeaddrinfo(_AddressInfo);

	if (listen(Socket, FTP_API_LISTEN_MAX) != NO_ERROR)
	{
		FTP_API_WIN_CALL(closesocket(Socket));
		FTP_API_LNX_CALL(close(Socket));
		Socket = INVALID_SOCKET;
		return false;
	}

	return true;
}

void FTP_API::Networking::EndPoint::StopHosting()
{
	if (Socket == INVALID_SOCKET)
	{
		return;
	}

	FTP_API_WIN_CALL(closesocket(Socket));
	FTP_API_LNX_CALL(close(Socket));

	Socket = INVALID_SOCKET;
}

bool FTP_API::Networking::EndPoint::GetNextClient(EndPoint& _NextClient, sockaddr* _Address)
{
	FTP_API_ASSERT_MSG(_NextClient.Socket == INVALID_SOCKET, FTP_API_STRING_TYPE("Cleanup the EndPoint befor using it to get the next client!"));

	if (Socket == INVALID_SOCKET)
	{
		return false;
	}

	if (_Address == nullptr)
	{
		_NextClient.Socket = accept(Socket, nullptr, nullptr);
	}
	else
	{
		FTP_API_WIN_CALL(int _AddressLen = sizeof(sockaddr));
		FTP_API_LNX_CALL(unsigned int _AddressLen = sizeof(sockaddr));

		_NextClient.Socket = accept(Socket, _Address, &_AddressLen);
	}

	if (_NextClient.Socket == INVALID_SOCKET)
	{
		StopHosting();
		return false;
	}

	if (listen(Socket, FTP_API_LISTEN_MAX) != NO_ERROR)
	{
		if (_Address)
		{
			*_Address = { 0 };
		}
		_NextClient.Disconnect();
		StopHosting();
		return false;
	}

	return true;
}

bool FTP_API::Networking::EndPoint::Connect(const char* _Address, const char* _Port)
{
	Disconnect();

	addrinfo* _AddressInfo = nullptr;

	{
		addrinfo _AddressHint = { 0 };

		_AddressHint.ai_family = AF_INET;
		_AddressHint.ai_socktype = SOCK_STREAM;
		_AddressHint.ai_protocol = IPPROTO_TCP;

		if (getaddrinfo(_Address, _Port, &_AddressHint, &_AddressInfo) != NO_ERROR)
		{
			return false;
		}
	}

	Socket = socket(_AddressInfo->ai_family, _AddressInfo->ai_socktype, _AddressInfo->ai_protocol);

	if (Socket == INVALID_SOCKET)
	{
		freeaddrinfo(_AddressInfo);
		return false;
	}

	if (connect(Socket, _AddressInfo->ai_addr, (int)(_AddressInfo->ai_addrlen)) != NO_ERROR)
	{
		FTP_API_WIN_CALL(closesocket(Socket));
		FTP_API_LNX_CALL(close(Socket));
		Socket = INVALID_SOCKET;
		freeaddrinfo(_AddressInfo);
		return false;
	}

	freeaddrinfo(_AddressInfo);

	return true;
}

void FTP_API::Networking::EndPoint::Disconnect()
{
	if (Socket == INVALID_SOCKET)
	{
		return;
	}

	FTP_API_WIN_CALL(closesocket(Socket));
	FTP_API_LNX_CALL(close(Socket));

	Socket = INVALID_SOCKET;
}

bool FTP_API::Networking::EndPoint::SendBuff(const char* _Buff, const size_t _BuffSize)
{
	if (Socket == INVALID_SOCKET)
	{
		return false;
	}

	size_t _Total = 0;

	do
	{
		size_t _ReturnValue = send(Socket, _Buff, (int)(_BuffSize), (int)(NULL));

		if (_ReturnValue == SOCKET_ERROR)
		{
			return false;
		}

		_Total += _ReturnValue;
	} while (_Total < _BuffSize);

	return true;
}

bool FTP_API::Networking::EndPoint::RecvBuff(char* _Buff, const size_t _BuffSize)
{
	if (Socket == INVALID_SOCKET)
	{
		return false;
	}

	if (recv(Socket, _Buff, (int)(_BuffSize), MSG_WAITALL) == SOCKET_ERROR)
	{
		return false;
	}

	return true;
}

FTP_API::Networking::EndPoint& FTP_API::Networking::EndPoint::operator= (EndPoint&& _Other) noexcept
{
	FTP_API_ASSERT_MSG(Socket == INVALID_SOCKET, FTP_API_STRING_TYPE("Move failed on non empty EndPoint object!"));

	Socket = _Other.Socket;

	_Other.Socket = INVALID_SOCKET;

	return *this;
}
