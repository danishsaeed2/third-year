// CROSS
#include <iostream>
#include <sys/socket.h>
#include <cstdlib>
#include <netinet/in.h>
#include <string.h>
#include <sstream>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080

using namespace std;

int main()
{
	struct sockaddr_in address;
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char buffer[1024] = {0};

	while(1)
	{
		if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
			cout << "\n Socket creation error \n";
			return -1;
		}

		memset(&serv_addr, '0', sizeof(serv_addr));

		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(PORT);

		if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
		{
			cout << "\nInvalid address/ Address not supported \n";
			return -1;
		}
	
		if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		{
			cout << "\nConnection Failed \n";
			return -1;
		}

		char move[1];
		cout << "\nEnter cross at: ";
		cin >> move;

		send(sock, move, strlen(move), 0);
		cout << "Cross moves\n";

		valread = read(sock, buffer, 1024);

		stringstream str(buffer);
		int end = 0;
		str >> end;

		if (end == -1)
			break;
	}

	return 0;
}