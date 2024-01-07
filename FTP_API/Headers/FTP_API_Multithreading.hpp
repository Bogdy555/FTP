#ifndef FTP_API_Multithreading_hpp

#define FTP_API_Multithreading_hpp



#include "FTP_API.hpp"



#ifdef _WIN32

#define FTP_API_THREAD_RETURN_TYPE uint32_t
#define FTP_API_THREAD_RETURN_VALUE 0

#endif

#ifdef __unix__

#define FTP_API_THREAD_RETURN_TYPE void*
#define FTP_API_THREAD_RETURN_VALUE nullptr

#endif



#pragma pack(pop)



namespace FTP_API
{

	namespace Multithreading
	{

		FTP_API_WIN_CALL(typedef uint32_t (__stdcall *ThreadFnc)(void*));
		FTP_API_LNX_CALL(typedef void* (*ThreadFnc)(void*));

		class Thread
		{

		public:

			Thread();
			Thread(const Thread& _Other) = delete;
			Thread(Thread&& _Other) noexcept;
			~Thread();

			bool Spawn(const ThreadFnc _Function, void* _Params);
			void Join();

			FTP_API_WIN_CALL(operator const HANDLE() const);

			FTP_API_LNX_CALL(operator const bool() const);
			FTP_API_LNX_CALL(operator const pthread_t() const);

			Thread& operator= (const Thread& _Other) = delete;
			Thread& operator= (Thread&& _Other) noexcept;

		private:

			FTP_API_WIN_CALL(HANDLE Handle);

			FTP_API_LNX_CALL(bool Created);
			FTP_API_LNX_CALL(pthread_t Handle);

		};

		class Mutex
		{

		public:

			Mutex();
			Mutex(const Mutex& _Other) = delete;
			Mutex(Mutex&& _Other) noexcept;
			~Mutex();

			bool Create();
			void Destroy();

			void Lock();
			void Unlock();

			FTP_API_WIN_CALL(operator const HANDLE() const);

			FTP_API_LNX_CALL(operator const bool() const);
			FTP_API_LNX_CALL(operator const pthread_mutex_t() const);

			Mutex& operator= (const Mutex& _Other) = delete;
			Mutex& operator= (Mutex&& _Other) noexcept;

		private:

			FTP_API_WIN_CALL(HANDLE Handle);

			FTP_API_LNX_CALL(bool Created);
			FTP_API_LNX_CALL(pthread_mutex_t Handle);

		};

	}

}



#pragma pack(push, 1)



#endif
