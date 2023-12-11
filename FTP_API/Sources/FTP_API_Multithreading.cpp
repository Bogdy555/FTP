#include "../Headers/FTP_API.hpp"



#ifdef _WIN32



FTP_API::Multithreading::Thread::Thread() : Handle(NULL)
{

}

FTP_API::Multithreading::Thread::Thread(Thread&& _Other) noexcept : Handle(_Other.Handle)
{
	_Other.Handle = NULL;
}

FTP_API::Multithreading::Thread::~Thread()
{
	FTP_API_ASSERT_MSG(Handle == NULL, FTP_API_STRING_TYPE("~Thread hit before cleanup!"));
}

bool FTP_API::Multithreading::Thread::Spawn(const ThreadFnc _Function, void* _Params)
{
	FTP_API_ASSERT_MSG(Handle == NULL, FTP_API_STRING_TYPE("Can not create new Thread over existing one!"));

	Handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(_Function), _Params, NULL, nullptr);

	if (Handle == NULL)
	{
		return false;
	}

	return true;
}

void FTP_API::Multithreading::Thread::Wait()
{
	if (!Handle)
	{
		return;
	}

	WaitForSingleObject(Handle, INFINITE);

	CloseHandle(Handle);
	Handle = NULL;
}

FTP_API::Multithreading::Thread::operator const HANDLE() const
{
	return Handle;
}

FTP_API::Multithreading::Thread& FTP_API::Multithreading::Thread::operator= (Thread&& _Other) noexcept
{
	FTP_API_ASSERT_MSG(Handle == NULL, FTP_API_STRING_TYPE("Move failed on non empty Thread object!"));

	Handle = _Other.Handle;

	_Other.Handle = NULL;

	return *this;
}



FTP_API::Multithreading::Mutex::Mutex() : Handle(NULL)
{

}

FTP_API::Multithreading::Mutex::Mutex(Mutex&& _Other) noexcept : Handle(_Other.Handle)
{
	_Other.Handle = NULL;
}

FTP_API::Multithreading::Mutex::~Mutex()
{
	FTP_API_ASSERT_MSG(Handle == NULL, FTP_API_STRING_TYPE("~Mutex hit before cleanup!"));
}

bool FTP_API::Multithreading::Mutex::Create()
{
	FTP_API_ASSERT_MSG(Handle == NULL, FTP_API_STRING_TYPE("Can not create new Mutex over existing one!"));

	Handle = CreateMutex(nullptr, false, nullptr);

	if (Handle == NULL)
	{
		return false;
	}

	return true;
}

void FTP_API::Multithreading::Mutex::Destroy()
{
	if (!Handle)
	{
		return;
	}

	CloseHandle(Handle);
	Handle = NULL;
}

void FTP_API::Multithreading::Mutex::Lock()
{
	if (Handle == NULL)
	{
		return;
	}

	WaitForSingleObject(Handle, INFINITE);
}

void FTP_API::Multithreading::Mutex::Unlock()
{
	if (Handle == NULL)
	{
		return;
	}

	ReleaseMutex(Handle);
}

FTP_API::Multithreading::Mutex::operator const HANDLE() const
{
	return Handle;
}

FTP_API::Multithreading::Mutex& FTP_API::Multithreading::Mutex::operator= (Mutex&& _Other) noexcept
{
	FTP_API_ASSERT_MSG(Handle == NULL, FTP_API_STRING_TYPE("Move failed on non empty Mutex object!"));

	Handle = _Other.Handle;

	_Other.Handle = NULL;

	return *this;
}



#endif



#ifdef __unix__







#endif
