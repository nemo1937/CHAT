#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

bool server(const char *ip, unsigned int port)
{
	if (ip == NULL)
	{
		return false;
	}
	
	int server_sock = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in  server_addr;
	memset(&server_addr, 0x00, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(ip);
	server_addr.sin_port = htons(port);

	//bind
	bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));

	//listen
	listen(server_sock, 5);

	int client_sock;
	struct sockaddr_in client_addr;
	memset(&client_addr, 0x00, sizeof(client_addr));
	socklen_t len = sizeof(client_addr);


	while(1)
	{
		cout << "server wait" << endl;
		//accept
		client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &len);

		char ch[20];
		memset(ch, 0x00, sizeof(ch));

		//int len_read = 0;
	//	while ((len_read = read(client_sock, &ch, 20)) > 0)
		ssize_t recv_len = -1;
		while ((recv_len = recv(client_sock, &ch, 20, 0)) > 0)
		{
			cout << "client: " << ch ;
			fflush(stdout);

			char response[20];
			memset(response, 0x00, sizeof(response));

			cout << "server: ";
			fgets(response, sizeof(response), stdin);
			
			send(client_sock, &response, 20, 0);
			memset(ch, 0x00, sizeof(ch));
		}

		close(client_sock);
	}

	return true;
}

int main()
{
	char *ip = "127.0.0.1";
	unsigned int port = 9999;
	server(ip, port);

	return 0;
}

