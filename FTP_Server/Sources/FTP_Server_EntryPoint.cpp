#include "../Headers/FTP_Server.hpp"



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



	FTP_API_WIN_CALL(FTP_API::Networking::Stop());

	return 0;
}
