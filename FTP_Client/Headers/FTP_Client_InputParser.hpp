#ifndef FTP_Client_InputParser_hpp

#define FTP_Client_InputParser_hpp



#include "FTP_Client.hpp"



namespace FTP_Client
{

	namespace InputParser
	{

		enum ArgumentsIndexes : const size_t
		{
			_NullIndex = 0,
			_IpIndex = 1,
			_PortIndex = 2,
			_ActionIndex = 3,
			_PassWordIndex = 4,
			_FileNameIndex = 5
		};

		enum ActionTypes : const uint8_t
		{
			_NullAction = 0,
			_ListFilesAction = 1,
			_DownloadAction = 2,
			_UploadAction = 3,
			_RemoveAction = 4
		};

		const uint8_t GetActionType(const char* _Argument);

		bool CheckArgumentsValidity(const size_t _ArgumentsCount, const char** _Arguments);

	}

}



#endif
