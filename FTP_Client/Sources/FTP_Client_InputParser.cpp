#include "../Headers/FTP_Client.hpp"



const uint8_t FTP_Client::InputParser::GetActionType(const char* _Argument)
{
	if (!_Argument)
	{
		return false;
	}

	if (strcmp(_Argument, "list_files") == 0)
	{
		return _ListFilesAction;
	}

	if (strcmp(_Argument, "download") == 0)
	{
		return _DownloadAction;
	}

	if (strcmp(_Argument, "upload") == 0)
	{
		return _UploadAction;
	}

	if (strcmp(_Argument, "remove") == 0)
	{
		return _RemoveAction;
	}

	return _NullAction;
}

bool FTP_Client::InputParser::CheckArgumentsValidity(const size_t _ArgumentsCount, const char** _Arguments)
{
	if (!_ArgumentsCount || !_Arguments)
	{
		return false;
	}

	if (_ArgumentsCount < 4 || _ArgumentsCount > 6)
	{
		return false;
	}

	switch (GetActionType(_Arguments[_ActionIndex]))
	{
	case _ListFilesAction:
	{
		if (_ArgumentsCount != 5)
		{
			return false;
		}

		if (_Arguments[_PassWordIndex][0] == '\0')
		{
			return false;
		}

		break;
	}
	case _DownloadAction:
	{
		if (_ArgumentsCount != 6)
		{
			return false;
		}

		if (_Arguments[_PassWordIndex][0] == '\0')
		{
			return false;
		}

		if (_Arguments[_FileNameIndex][0] == '\0')
		{
			return false;
		}

		break;
	}
	case _UploadAction:
	{
		if (_ArgumentsCount != 6)
		{
			return false;
		}

		if (_Arguments[_PassWordIndex][0] == '\0')
		{
			return false;
		}

		if (_Arguments[_FileNameIndex][0] == '\0')
		{
			return false;
		}

		break;
	}
	case _RemoveAction:
	{
		if (_ArgumentsCount != 6)
		{
			return false;
		}

		if (_Arguments[_PassWordIndex][0] == '\0')
		{
			return false;
		}

		if (_Arguments[_FileNameIndex][0] == '\0')
		{
			return false;
		}

		break;
	}
	default:
	{
		return false;
	}
	}

	return true;
}
