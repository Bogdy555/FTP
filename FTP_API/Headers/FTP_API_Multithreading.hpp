#ifndef FTP_API_Multithreading_hpp

#define FTP_API_Multithreading_hpp



#include "FTP_API.hpp"



namespace FTP_API
{

	namespace Multithreading
	{

#ifdef _WIN32

		typedef uint32_t (*ThreadFnc)(void*);

		class Thread
		{

		public:

			Thread();
			Thread(const Thread& _Other) = delete;
			Thread(Thread&& _Other) noexcept;
			~Thread();

			bool Spawn(const ThreadFnc _Function, void* _Params);
			void Wait();

			operator const HANDLE() const;

			Thread& operator= (const Thread& _Other) = delete;
			Thread& operator= (Thread&& _Other) noexcept;

		private:

			HANDLE Handle;

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

			operator const HANDLE() const;

			Mutex& operator= (const Mutex& _Other) = delete;
			Mutex& operator= (Mutex&& _Other) noexcept;

		private:

			HANDLE Handle;

		};

#endif

#ifdef __unix__

		typedef void* (*ThreadFnc)(void*);
	
		class Thread
		{
		
		public:
	
			Thread();
			Thread(const Thread& _Other) = delete;
			Thread(Thread&& _Other) noexcept;
			~Thread();
	
			bool Spawn(const ThreadFnc _Function, void* _Params);
			void Wait();
	
			operator const bool() const;
			operator const pthread_t() const;
	
			Thread& operator= (const Thread& _Other) = delete;
			Thread& operator= (Thread&& _Other) noexcept;
	
		private:
	
			bool Created;
			pthread_t Handle;
	
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
	
			operator const bool() const;
			operator const pthread_mutex_t() const;
	
			Mutex& operator= (const Mutex& _Other) = delete;
			Mutex& operator= (Mutex&& _Other) noexcept;
	
		private:
	
			bool Created;
			pthread_mutex_t Handle;

		};

#endif

	}

}



#endif
