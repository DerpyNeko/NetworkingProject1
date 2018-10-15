#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 512						// Default buffer length of our buffer in characters
#define DEFAULT_PORT "27015"					// The default port to use
#define SERVER "127.0.0.1"						// The IP of our server

//int main(int argc, char **argv)
//{
//	WSADATA wsaData;							// holds Winsock data
//	SOCKET connectSocket = INVALID_SOCKET;		// Our connection socket used to connect to the server
//
//	struct addrinfo *infoResult = NULL;			// Holds the address information of our server
//	struct addrinfo *ptr = NULL;
//	struct addrinfo hints;
//
//	char name[32];
//	const char *sendbuf = "Hello World";		// The messsage to send to the server
//
//	char recvbuf[DEFAULT_BUFLEN];				// The maximum buffer size of a message to send
//	int result;									// code of the result of any command we use
//	int recvbuflen = DEFAULT_BUFLEN;			// The length of the buffer we receive from the server
//
//	// Step #1 Initialize Winsock
//	result = WSAStartup(MAKEWORD(2, 2), &wsaData);
//	if (result != 0)
//	{
//		printf("WSAStartup failed with error: %d\n", result);
//		return 1;
//	}
//
//	ZeroMemory(&hints, sizeof(hints));
//	hints.ai_family = AF_UNSPEC;
//	hints.ai_socktype = SOCK_STREAM;
//	hints.ai_protocol = IPPROTO_TCP;
//
//	// Step #2 Resolve the server address and port
//	result = getaddrinfo(SERVER, DEFAULT_PORT, &hints, &infoResult);
//	if (result != 0)
//	{
//		printf("getaddrinfo failed with error: %d\n", result);
//		WSACleanup();
//		return 1;
//	}
//
//	// Step #3 Attempt to connect to an address until one succeeds
//	for (ptr = infoResult; ptr != NULL; ptr = ptr->ai_next)
//	{
//		// Create a SOCKET for connecting to server
//		connectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
//
//		if (connectSocket == INVALID_SOCKET)
//		{
//			printf("socket failed with error: %ld\n", WSAGetLastError());
//			WSACleanup();
//			return 1;
//		}
//
//		// Connect to server.
//		result = connect(connectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
//		if (result == SOCKET_ERROR)
//		{
//			closesocket(connectSocket);
//			connectSocket = INVALID_SOCKET;
//			continue;
//		}
//		break;
//	}
//
//	freeaddrinfo(infoResult);
//
//	if (connectSocket == INVALID_SOCKET)
//	{
//		printf("Unable to connect to server!\n");
//		WSACleanup();
//		return 1;
//	}
//
//	std::cin.getline(name, 32);
//
//	// Step #4 Send the message to the server
//	result = send(connectSocket, name, (int)strlen(name), 0);
//	if (result == SOCKET_ERROR)
//	{
//		printf("send failed with error: %d\n", WSAGetLastError());
//		closesocket(connectSocket);
//		WSACleanup();
//		return 1;
//	}
//	printf("Bytes Sent: %ld\n", result);
//
//	//// Step #4 Send the message to the server
//	//result = send(connectSocket, sendbuf, (int)strlen(sendbuf), 0);
//	//if (result == SOCKET_ERROR)
//	//{
//	//	printf("send failed with error: %d\n", WSAGetLastError());
//	//	closesocket(connectSocket);
//	//	WSACleanup();
//	//	return 1;
//	//}
//	//printf("Bytes Sent: %ld\n", result);
//
//	// Step #5 shutdown the connection since no more data will be sent
//	//result = shutdown(connectSocket, SD_SEND);
//	//if (result == SOCKET_ERROR)
//	//{
//	//	printf("shutdown failed with error: %d\n", WSAGetLastError());
//	//	closesocket(connectSocket);
//	//	WSACleanup();
//	//	return 1;
//	//}
//
//	//result = recv(connectSocket, recvbuf, recvbuflen, 0);
//	//if (result > 0)
//	//{
//	//	printf("Bytes received: %d\n", result);
//	//	printf("Message: %s has joined the room\n", &recvbuf);
//	//}
//
//	// Step #6 Receive until the peer closes the connection
//	do {
//
//		//std::cin.getline(name, 32);
//
//		// Step #4 Send the message to the server
//		//result = send(connectSocket, name, (int)strlen(name), 0);
//		//if (result == SOCKET_ERROR)
//		//{
//		//	printf("send failed with error: %d\n", WSAGetLastError());
//		//	closesocket(connectSocket);
//		//	WSACleanup();
//		//	return 1;
//		//}
//		//printf("Bytes Sent: %ld\n", result);
//
//
//		result = recv(connectSocket, recvbuf, recvbuflen, 0);
//		if (result > 0)
//		{
//			printf("Bytes received: %d\n", result);
//			printf("Message: %s\n", &recvbuf);
//		}
//		else if (result == 0)
//		{
//			//printf("Connection closed\n");
//		}
//		else
//		{
//			printf("recv failed with error: %d\n", WSAGetLastError());
//		}
//
//	} while (result > 0 || result == 0);
//
//	// Step #7 cleanup
//	closesocket(connectSocket);
//	WSACleanup();
//
//	system("pause");
//
//	return 0;
//}
//
////// Description:
////
//////    This sample is the echo client. It connects to the TCP server,
////
//////    sends data, and reads data back from the server.
////
//////
////
////// Command Line Options:
////
//////    client [-p:x] [-s:IP] [-n:x] [-o]
////
//////           -p:x      Remote port to send to
////
//////           -s:IP     Server's IP address or hostname
////
//////           -n:x      Number of times to send message
////
//////           -o        Send messages only; don't receive
////
//////
////
////// Link to ws2_32.lib
////
////#include <winsock2.h>
////
////#include <stdio.h>
////
////#include <stdlib.h>
////
////
////
////#define DEFAULT_COUNT       20
////
////#define DEFAULT_PORT        5150
////
////#define DEFAULT_BUFFER      2048
////
////#define DEFAULT_MESSAGE     "\'A test message from client\'"
////
////
////
////char  szServer[128],                          // Server to connect to
////
////szMessage[1024];                      // Message to send to sever
////
////int   iPort = DEFAULT_PORT;    // Port on server to connect to
////
////DWORD dwCount = DEFAULT_COUNT; // Number of times to send message
////
////BOOL  bSendOnly = FALSE;                        // Send data only; don't receive
////
////
////
////// Function: usage:
////
////// Description: Print usage information and exit
////
////void usage()
////
////{
////
////	printf("Chapter5TestClient: client [-p:x] [-s:IP] [-n:x] [-o]\n\n");
////
////	printf("       -p:x      Remote port to send to\n");
////
////	printf("       -s:IP     Server's IP address or hostname\n");
////
////	printf("       -n:x      Number of times to send message\n");
////
////	printf("       -o        Send messages only; don't receive\n");
////
////	printf("\n");
////
////}
////
////
////
////// Function: ValidateArgs
////
////// Description:
////
//////    Parse the command line arguments, and set some global flags
////
//////    to indicate what actions to perform
////
////void ValidateArgs(int argc, char **argv)
////
////{
////
////	int    i;
////
////
////
////	for (i = 1; i < argc; i++)
////
////	{
////
////		if ((argv[i][0] == '-') || (argv[i][0] == '/'))
////
////		{
////
////			switch (tolower(argv[i][1]))
////
////			{
////
////			case 'p':        // Remote port
////
////				if (strlen(argv[i]) > 3)
////
////					iPort = atoi(&argv[i][3]);
////
////				break;
////
////			case 's':       // Server
////
////				if (strlen(argv[i]) > 3)
////
////					strcpy_s(szServer, sizeof(szServer), &argv[i][3]);
////
////				break;
////
////			case 'n':       // Number of times to send message
////
////				if (strlen(argv[i]) > 3)
////
////					dwCount = atol(&argv[i][3]);
////
////				break;
////
////			case 'o':       // Only send message; don't receive
////
////				bSendOnly = TRUE;
////
////				break;
////
////			default:
////
////				usage();
////
////				break;
////
////			}
////
////		}
////
////	}
////
////}
////
////
////
////// Function: main
////
////// Description:
////
//////    Main thread of execution. Initialize Winsock, parse the
////
//////    command line arguments, create a socket, connect to the
////
//////    server, and then send and receive data.
////
////int main(int argc, char **argv)
////
////{
////
////	WSADATA       wsd;
////
////	SOCKET        sClient;
////
////	char          szBuffer[DEFAULT_BUFFER];
////
////	int           ret, i;
////
////	struct sockaddr_in server;
////
////	struct hostent    *host = NULL;
////
////
////
////	if (argc < 2)
////
////	{
////
////		usage();
////
////		exit(1);
////
////	}
////
////
////
////	// Parse the command line and load Winsock
////
////	ValidateArgs(argc, argv);
////
////	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
////
////	{
////
////		printf("Failed to load Winsock library! Error %d\n", WSAGetLastError());
////
////		return 1;
////
////	}
////
////	else
////
////		printf("Winsock library loaded successfully!\n");
////
////
////
////	strcpy_s(szMessage, sizeof(szMessage), DEFAULT_MESSAGE);
////
////
////
////	// Create the socket, and attempt to connect to the server
////
////	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
////
////	if (sClient == INVALID_SOCKET)
////
////	{
////
////		printf("socket() failed with error code %d\n", WSAGetLastError());
////
////		return 1;
////
////	}
////
////	else
////
////		printf("socket() looks fine!\n");
////
////
////
////	server.sin_family = AF_INET;
////
////	server.sin_port = htons(iPort);
////
////	server.sin_addr.s_addr = inet_addr(szServer);
////
////
////
////	// If the supplied server address wasn't in the form
////
////	// "aaa.bbb.ccc.ddd" it's a hostname, so try to resolve it
////
////	if (server.sin_addr.s_addr == INADDR_NONE)
////
////	{
////
////		host = gethostbyname(szServer);
////
////		if (host == NULL)
////
////		{
////
////			printf("Unable to resolve server %s\n", szServer);
////
////			return 1;
////
////		}
////
////		else
////
////			printf("The hostname resolved successfully!\n");
////
////
////
////		CopyMemory(&server.sin_addr, host->h_addr_list[0], host->h_length);
////
////	}
////
////
////
////	if (connect(sClient, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
////
////	{
////
////		printf("connect() failed with error code %d\n", WSAGetLastError());
////
////		return 1;
////
////	}
////
////	else
////
////		printf("connect() is pretty damn fine!\n");
////
////
////
////	// Send and receive data
////
////	printf("Sending and receiving data if any...\n");
////
////
////
////	for (i = 0; i < (int)dwCount; i++)
////
////	{
////
////		ret = send(sClient, szMessage, strlen(szMessage), 0);
////
////		if (ret == 0)
////
////			break;
////
////		else if (ret == SOCKET_ERROR)
////
////		{
////
////			printf("send() failed with error code %d\n", WSAGetLastError());
////
////			break;
////
////		}
////
////
////
////		printf("send() should be fine. Send %d bytes\n", ret);
////
////		if (!bSendOnly)
////
////		{
////
////			ret = recv(sClient, szBuffer, DEFAULT_BUFFER, 0);
////
////			if (ret == 0)        // Graceful close
////
////			{
////
////				printf("It is a graceful close!\n");
////
////				break;
////
////			}
////
////			else if (ret == SOCKET_ERROR)
////
////			{
////
////				printf("recv() failed with error code %d\n", WSAGetLastError());
////
////				break;
////
////			}
////
////			szBuffer[ret] = '\0';
////
////			printf("recv() is OK. Received %d bytes: %s\n", ret, szBuffer);
////
////		}
////
////	}
////
////
////
////	if (closesocket(sClient) == 0)
////
////		printf("closesocket() is OK!\n");
////
////	else
////
////		printf("closesocket() failed with error code %d\n", WSAGetLastError());
////
////
////
////	if (WSACleanup() == 0)
////
////		printf("WSACleanup() is fine!\n");
////
////	else
////
////		printf("WSACleanup() failed with error code %d\n", WSAGetLastError());
////
////
////
////	return 0;
////
////}
////
