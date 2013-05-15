#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;

bool client(const char *ip, const unsigned int port)
{
	if (ip == NULL )
	{
		return false;
	}

	int client_sock = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in client_addr;
	memset(&client_addr, 0x00, sizeof(client_addr));

	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(port);
	client_addr.sin_addr.s_addr = inet_addr(ip);

	bzero(&(client_addr.sin_zero), 8);


	int rt = connect(client_sock, (struct sockaddr *)&client_addr, sizeof(client_addr));
	if (rt == -1)
	{
		return false;
	}
	
	while (1)
	{
		char cs[20] = {0};
		gets(cs);

		write(client_sock, cs, strlen(cs));
		read(client_sock, cs, 20);

		cout << "from server char ch: " << cs << endl;
	}
	//close
	close(client_sock);


	return true;
}

int main()
{
	string ip = "127.0.0.1";
	unsigned int port = 9999;

	client(ip.c_str(), port);

	return 0;
}
