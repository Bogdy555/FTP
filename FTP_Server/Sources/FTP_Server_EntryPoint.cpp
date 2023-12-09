#include "../Headers/FTP_Server.hpp"



#ifdef _WIN32

int WINAPI wWinMain(_In_ HINSTANCE _hInstance, _In_opt_ HINSTANCE _hPrevInstance, _In_ LPWSTR _CmdLine, _In_ int _ShowCmd)
{
	return 0;
}

#endif



#ifdef __unix__

int main()
{
	return 0;
}

#endif
