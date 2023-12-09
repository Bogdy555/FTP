#ifndef FTP_API_Dependencies_hpp

#define FTP_API_Dependencies_hpp



#pragma pack(pop)



#ifdef _WIN32



#include "FTP_API_WinTargetVer.hpp"
#include <Windows.h>



#endif



#ifdef __unix__







#endif



#include <iostream>



#pragma pack(push, 1)



#include "FTP_API_Macros.hpp"



namespace FTP_API
{

	namespace Networking
	{



	}

}



#include "FTP_API_Templates.hpp"



#endif
