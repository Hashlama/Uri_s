#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string.h>

#pragma comment(lib, "Ws2_32.lib")

int main(int, char *[], char*[])
{
	WSADATA d;
	WSAStartup(MAKEWORD(2, 2), &d);
	struct addrinfo *result = NULL,
		hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	getaddrinfo("127.0.0.1", "8080", &hints, &result);

	int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    bind(s, result->ai_addr,result->ai_addrlen);
	listen(s, 5);
	SOCKET c = accept(s, NULL, NULL);;
	char buffer[1024];
	int  len;
	while (c != NULL)
	{
		len = recv(c, buffer, 1, 0);
		printf("Output: %.*s\n", len, buffer);
		int type = atoi((char*)buffer);
		if (type == 1)
		{
			DWORD size = 10;
			char hostname_str[10];
			GetComputerNameA(hostname_str, &size);
			send(s, hostname_str, 10, 0);
		}
		if (type == 2)
		{
			return 0;
		}
		c = accept(s, NULL, NULL);
	}
	return 0;
}