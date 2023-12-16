#include "../Headers/FTP_Server.hpp"



bool FTP_Server::InputParser::CheckArgumentsValidity(const size_t _ArgumentsCount, const char** _Arguments)
{
	if (!_ArgumentsCount || !_Arguments)
	{
		return false;
	}

	if (_ArgumentsCount != 5)
	{
		return false;
	}

	if (_Arguments[_WorkingDirIndex][0] == '\0')
	{
		return false;
	}

	if (_Arguments[_PassWordIndex][0] == '\0')
	{
		return false;
	}

	return true;
}
