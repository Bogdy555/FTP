#ifndef FTP_Server_InputParser_hpp

#define FTP_Server_InputParser_hpp



#include "FTP_Server.hpp"



namespace FTP_Server
{

	namespace InputParser
	{

		enum ArgumentsIndexes : const size_t
		{
			_NullIndex = 0,
			_IpIndex = 1,
			_PortIndex = 2,
			_WorkingDirIndex = 3,
			_PassWordIndex = 4
		};

		bool CheckArgumentsValidity(const size_t _ArgumentsCount, const char** _Arguments);

	}

}



#endif
