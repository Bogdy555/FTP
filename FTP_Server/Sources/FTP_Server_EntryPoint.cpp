#include "../Headers/FTP_Server.hpp"



#ifdef _WIN32

int WINAPI wWinMain(_In_ HINSTANCE _hInstance, _In_opt_ HINSTANCE _hPrevInstance, _In_ LPWSTR _CmdLine, _In_ int _ShowCmd)
{
	FTP_API::Networking::Init();

	FTP_API::Networking::EndPoint _Server;

	_Server.Host("localhost", "5000");

	while (true)
	{
		FTP_API::Networking::EndPoint _Client;

		_Server.GetNextClient(_Client);

		char _Data[5];
		_Client.RecvBuff(_Data, 4);
		_Data[4] = '\0';
		std::cout << _Data << '\n';

		_Client.SendBuff("Buna", 4);

		_Client.Disconnect();
	}

	_Server.StopHosting();

	FTP_API::Networking::Stop();

	return 0;
}

#endif



#ifdef __unix__

int main()
{
	FTP_API::Networking::EndPoint _Server;

	_Server.Host("localhost", "5000");

	while (true)
	{
		FTP_API::Networking::EndPoint _Client;

		_Server.GetNextClient(_Client);

		char _Data[5];
		_Client.RecvBuff(_Data, 4);
		_Data[4] = '\0';
		std::cout << _Data << '\n';

		_Client.SendBuff("Buna", 4);

		_Client.Disconnect();
	}

	_Server.StopHosting();

	return 0;
}

#endif
