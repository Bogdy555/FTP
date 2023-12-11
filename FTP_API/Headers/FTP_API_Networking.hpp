#ifndef FTP_API_Networking_hpp

#define FTP_API_Networking_hpp



#include "FTP_API.hpp"



namespace FTP_API
{

	namespace Networking
	{

#ifdef _WIN32

		extern WSADATA WSAData;

		bool Init();
		void Stop();

#endif

		class EndPoint
		{

		public:

			EndPoint();
			EndPoint(const EndPoint& _Other) = delete;
			EndPoint(EndPoint&& _Other) noexcept;
			~EndPoint();

			bool Host(const char* _Address, const char* _Port);
			void StopHosting();
			bool GetNextClient(EndPoint& _NextClient, sockaddr* _Address = nullptr);

			bool Connect(const char* _Address, const char* _Port);
			void Disconnect();

			bool SendBuff(const char* _Buff, const size_t _BuffSize);
			bool RecvBuff(char* _Buff, const size_t _BuffSize);

			EndPoint& operator= (const EndPoint& _Other) = delete;
			EndPoint& operator= (EndPoint&& _Other) noexcept;

		private:

			SOCKET Socket;

		};

	}

}



#endif
