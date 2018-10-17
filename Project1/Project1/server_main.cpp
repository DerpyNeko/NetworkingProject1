// server_main.cpp
// Jenny Moon & Ryan O'Donnell

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

// #pragma comment (lib, "Mswsock.lib")
#define DEFAULT_BUFLEN 512						// Default buffer length of our buffer in characters
#define DEFAULT_PORT "27015"					// The default port to listen on

typedef struct _SOCKET_INFORMATION {

	char sRecvBuf[DEFAULT_BUFLEN];
	WSABUF sDataBuf;
	SOCKET sSocket;
	//OVERLAPPED Overlapped;
	int sSendBytes;
	int sRecvBytes;

} SOCKET_INFORMATION, *LPSOCKET_INFORMATION;

// Prototypes

BOOL CreateSocketInformation(SOCKET s);
void FreeSocketInformation(int Index);

int totalSockets = 0;
LPSOCKET_INFORMATION socketArray[FD_SETSIZE];

int main(void)
{
	WSADATA wsaData;							// holds Winsock data
	int result;									// code of the result of any command we use

	SOCKET listenSocket = INVALID_SOCKET;		// The socket used to listen for connections
	SOCKET clientSocket = INVALID_SOCKET;		// The socket of our client

	struct addrinfo *info = NULL;				// address info 
	struct addrinfo hints;						// address flags
	unsigned long nonBlock;

	FD_SET writeSet;

	FD_SET readSet;
	int total;
	DWORD flags;
	DWORD recvBytes;
	DWORD sendBytes;

	// Step #1 Initialize Winsock
	result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0)
	{
		printf("WSAStartup failed with error: %d\n", result);
		WSACleanup();
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Step #2 Resolve the server address and port
	result = getaddrinfo(NULL, DEFAULT_PORT, &hints, &info);
	if (result != 0)
	{
		printf("getaddrinfo failed with error: %d\n", result);
		WSACleanup();
		return 1;
	}

	// Step #3 Create a SOCKET for connecting to server
	listenSocket = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
	if (listenSocket == INVALID_SOCKET)
	{
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(info);
		WSACleanup();
		return 1;
	}

	// Step #4 Setup the TCP listening socket
	result = bind(listenSocket, info->ai_addr, (int)info->ai_addrlen);
	if (result == SOCKET_ERROR)
	{
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(info);
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	int broadcast = 1;
	setsockopt(listenSocket, SOL_SOCKET, SO_BROADCAST, (char*)&broadcast, sizeof(broadcast));

	freeaddrinfo(info);

	result = listen(listenSocket, SOMAXCONN);
	if (result == SOCKET_ERROR)
	{
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	// Change the socket mode from blocking to non-block

	if (ioctlsocket(listenSocket, FIONBIO, &nonBlock) == SOCKET_ERROR)
	{
		printf("ioctlsocket() failed with error %d\n", WSAGetLastError());
		return 1;
	}
	else
	{
		printf("ioctlsocket() is OK!\n");
	}

	while (TRUE)
	{
		FD_ZERO(&readSet);
		FD_ZERO(&writeSet);

		FD_SET(listenSocket, &readSet);

		for (int i = 0; i < totalSockets; i++)
		{
			if (socketArray[i]->sRecvBytes > socketArray[i]->sSendBytes)
			{
				FD_SET(socketArray[i]->sSocket, &writeSet);
			}
			else
			{
				FD_SET(socketArray[i]->sSocket, &readSet);
			}
		}

		if ((total = select(0, &readSet, &writeSet, NULL, NULL)) == SOCKET_ERROR)
		{
			printf("select() returned with error %d\n", WSAGetLastError());
			return 1;
		}
		else
		{
			printf("select() is OK!\n");
		}

		if (FD_ISSET(listenSocket, &readSet))
		{
			total--;

			if ((clientSocket = accept(listenSocket, NULL, NULL)) != INVALID_SOCKET)
			{
				nonBlock = 0;

				if (ioctlsocket(clientSocket, FIONBIO, &nonBlock) == SOCKET_ERROR)
				{
					printf("ioctlsocket(FIONBIO) failed with error %d\n", WSAGetLastError());
					return 1;
				}
				else
				{
					printf("ioctlsocket(FIONBIO) is OK!\n");
				}

				if (CreateSocketInformation(clientSocket) == FALSE)
				{
					printf("CreateSocketInformation(clientSocket) failed!\n");
					return 1;
				}
				else
				{
					printf("CreateSocketInformation() is OK!\n");
				}
			}
			else
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)
				{
					printf("accept() failed with error %d\n", WSAGetLastError());
					return 1;
				}

				else
				{
					printf("accept() is fine!\n");
				}
			}
		}

		for (int i = 0; total > 0 && i < totalSockets; i++)
		{
			LPSOCKET_INFORMATION SocketInfo = socketArray[i];

			if (FD_ISSET(SocketInfo->sSocket, &readSet))
			{
				total--;

				SocketInfo->sDataBuf.buf = SocketInfo->sRecvBuf;
				SocketInfo->sDataBuf.len = DEFAULT_BUFLEN;

				flags = 0;

				if (WSARecv(SocketInfo->sSocket, &(SocketInfo->sDataBuf), 1, &recvBytes, &flags, NULL, NULL) == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK)
					{
						printf("WSARecv() failed with error %d\n", WSAGetLastError());
						FreeSocketInformation(i);
					}
					else
					{
						printf("WSARecv() is OK!\n");
					}
					continue;
				}
				else
				{
					SocketInfo->sRecvBytes = recvBytes;

					// Closes connection
					//if (recvBytes == 0)
					//{
					//	FreeSocketInformation(i);
					//	continue;
					//}
				}
			}

			if (FD_ISSET(SocketInfo->sSocket, &writeSet))
			{
				total--;

				SocketInfo->sDataBuf.buf = SocketInfo->sRecvBuf + SocketInfo->sSendBytes;
				SocketInfo->sDataBuf.len = SocketInfo->sRecvBytes - SocketInfo->sSendBytes;

				for (auto s : socketArray)
				{
					if (s != NULL)
					{
						if (WSASend(s->sSocket, &(SocketInfo->sDataBuf), 1, &sendBytes, 0, NULL, NULL) == SOCKET_ERROR)
						{
							if (WSAGetLastError() != WSAEWOULDBLOCK)
							{
								printf("WSASend() failed with error %d\n", WSAGetLastError());
								FreeSocketInformation(i);
							}
							else
							{
								printf("WSASend() is OK!\n");
							}
							continue;
						}
						else
						{
							SocketInfo->sSendBytes += sendBytes;

							printf("WSASend() is OK!\n");

							if (SocketInfo->sSendBytes == SocketInfo->sRecvBytes)
							{
								SocketInfo->sSendBytes = 0;
								SocketInfo->sRecvBytes = 0;
							}
						}
					}
				}
			}
		}
	}
	
	// Step #7 shutdown the connection since we're done
	result = shutdown(clientSocket, SD_SEND);
	if (result == SOCKET_ERROR)
	{
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(clientSocket);
		WSACleanup();
		return 1;
	}

	// cleanup
	closesocket(clientSocket);
	WSACleanup();

	system("pause");

	return 0;
}

BOOL CreateSocketInformation(SOCKET s)
{
	LPSOCKET_INFORMATION sockInfo;

	printf("Accepted socket number %d\n", s);

	if ((sockInfo = (LPSOCKET_INFORMATION)GlobalAlloc(GPTR, sizeof(SOCKET_INFORMATION))) == NULL)
	{
		printf("GlobalAlloc() failed with error %d\n", GetLastError());
		return FALSE;
	}
	else
	{
		printf("GlobalAlloc() for SOCKET_INFORMATION is OK!\n");
	}

	// Prepare SocketInfo structure for use
	sockInfo->sSocket = s;
	sockInfo->sSendBytes = 0;
	sockInfo->sRecvBytes = 0;
	socketArray[totalSockets] = sockInfo;
	totalSockets++;

	return(TRUE);
}

void FreeSocketInformation(int index)
{
	LPSOCKET_INFORMATION sockInfo = socketArray[index];

	closesocket(sockInfo->sSocket);

	printf("Closing socket number %d\n", sockInfo->sSocket);

	GlobalFree(sockInfo);

	// Resize the socket array
	for (int i = index; i < totalSockets; i++)
	{
		socketArray[i] = socketArray[i + 1];
	}

	totalSockets--;
}
