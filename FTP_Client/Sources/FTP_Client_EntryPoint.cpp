#include "../Headers/FTP_Client.hpp"



#ifdef _WIN32

int WINAPI wWinMain(_In_ HINSTANCE _hInstance, _In_opt_ HINSTANCE _hPrevInstance, _In_ LPWSTR _CmdLine, _In_ int _ShowCmd)
{
	FTP_API::Networking::Init();

	FTP_API::Networking::EndPoint _Client;

	_Client.Connect("localhost", "5000");

	_Client.SendBuff("Test", 4);

	char _Data[5];
	_Client.RecvBuff(_Data, 4);
	_Data[4] = '\0';
	std::cout << _Data << '\n';

	_Client.Disconnect();

	FTP_API::Networking::Stop();

	return 0;
}

#endif



#ifdef __unix__

int main()
{
	FTP_API::Networking::EndPoint _Client;

	_Client.Connect("localhost", "5000");

	_Client.SendBuff("Test", 4);

	char _Data[5];
	_Client.RecvBuff(_Data, 4);
	_Data[4] = '\0';
	std::cout << _Data << '\n';

	_Client.Disconnect();

	return 0;
}

#endif
