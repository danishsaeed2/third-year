// SERVER
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sstream>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#define PORT 8080

using namespace std;

const int m=3,n=3;
void printMatrix(char temp[m][n]);
bool checkWin(char temp[m][n]);

int main()
{
	int mySocket, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};

	char matrix[3][3];
	int check[3][3];
	int counter = 0;

	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			matrix[i][j] = '-';
			check[i][j] = 0;
		}
	}

	if ((mySocket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	  
	if (setsockopt(mySocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	
	if (bind(mySocket, (struct sockaddr *)&address, sizeof(address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	if (listen(mySocket, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}

	printMatrix(matrix);

	while(1)
	{
		if (counter%2 == 0)
		{
			if ((new_socket = accept(mySocket, (struct sockaddr *)&address, 
							(socklen_t*)&addrlen))<0)
			{
				perror("accept");
				exit(EXIT_FAILURE);
			}
			if (counter == 0)
				cout << "\n--- Player cross online\n";
			cout << "\nWaiting for cross move\n";

			valread = read(new_socket, buffer, 1024);

			stringstream str(buffer);
			int move = 0;
			str >> move;
			cout << "Cross at position " << move << "\n";

			if (move == 1)
			{
				if (check[0][0] == 0)
				{
					matrix[0][0] = 'X';
					check[0][0] = 1;
				}
				else
					cout << "\n# Already moved\n";
			}
			else if (move == 2)
			{
				if (check[0][1] == 0)
				{
					matrix[0][1] = 'X';
					check[0][1] = 1;
				}
				else
					cout << "\n# Already moved\n";
			}
			else if (move == 3)
			{
				if (check[0][2] == 0)
				{
					matrix[0][2] = 'X';
					check[0][2] = 1;
				}
				else
					cout << "\n# Already moved\n";
			}
			else if (move == 4)
			{
				if (check[1][0] == 0)
				{
					matrix[1][0] = 'X';
					check[1][0] = 1;
				}
				else
					cout << "\n# Already moved\n";
			}
			else if (move == 5)
			{
				if (check[1][1] == 0)
				{
					matrix[1][1] = 'X';
					check[1][1] = 1;
				}
				else
					cout << "\n# Already moved\n";
			}
			else if (move == 6)
			{
				if (check[1][2] == 0)
				{
					matrix[1][2] = 'X';
					check[1][2] = 1;
				}
				else
					cout << "\n# Already moved\n";
			}
			else if (move == 7)
			{
				if (check[2][0] == 0)
				{
					matrix[2][0] = 'X';
					check[2][0] = 1;
				}
				else
					cout << "\n# Already moved\n";
			}
			else if (move == 8)
			{
				if (check[2][1] == 0)
				{
					matrix[2][1] = 'X';
					check[2][1] = 1;
				}
				else
					cout << "\n# Already moved\n";
			}
			else if (move == 9)
			{
				if (check[2][2] == 0)
				{
					matrix[2][2] = 'X';
					check[2][2] = 1;
				}
				else
					cout << "\n# Already moved\n";
			}
			else
			{
				cout << "\n# Invalid move\n";
			}
		}
		else if (counter%2 == 1)
		{
			if ((new_socket = accept(mySocket, (struct sockaddr *)&address, 
							(socklen_t*)&addrlen))<0)
			{
				perror("accept");
				exit(EXIT_FAILURE);
			}
			if (counter == 1)
				cout << "\n--- Player zero online\n";
			cout << "\nWaiting for zero move\n";

			valread = read(new_socket, buffer, 1024);

			stringstream str(buffer);
			int move = 0;
			str >> move;
			cout << "Zero at position " << move << "\n";

			if (move == 1)
			{
				if (check[0][0] == 0)
				{
					matrix[0][0] = 'O';
					check[0][0] = 1;
				}
				else
					cout << "\n# Already moved\n";
			}
			else if (move == 2)
			{
				if (check[0][1] == 0)
				{
					matrix[0][1] = 'O';
					check[0][1] = 1;
				}
				else
					cout << "\n# Already moved\n";
			}
			else if (move == 3)
			{
				if (check[0][2] == 0)
				{
					matrix[0][2] = 'O';
					check[0][2] = 1;
				}
				else
					cout << "\n# Already moved\n";
			}
			else if (move == 4)
			{
				if (check[1][0] == 0)
				{
					matrix[1][0] = 'O';
					check[1][0] = 1;
				}
				else
					cout << "\n# Already moved\n";
			}
			else if (move == 5)
			{
				if (check[1][1] == 0)
				{
					matrix[1][1] = 'O';
					check[1][1] = 1;
				}
				else
					cout << "\n# Already moved\n";
			}
			else if (move == 6)
			{
				if (check[1][2] == 0)
				{
					matrix[1][2] = 'O';
					check[1][2] = 1;
				}
				else
					cout << "\n# Already moved\n";
			}
			else if (move == 7)
			{
				if (check[2][0] == 0)
				{
					matrix[2][0] = 'O';
					check[2][0] = 1;
				}
				else
					cout << "\n# Already moved\n";
			}
			else if (move == 8)
			{
				if (check[2][1] == 0)
				{
					matrix[2][1] = 'O';
					check[2][1] = 1;
				}
				else
					cout << "\n# Already moved\n";
			}
			else if (move == 9)
			{
				if (check[2][2] == 0)
				{
					matrix[2][2] = 'O';
					check[2][2] = 1;
				}
				else
					cout << "\n# Already moved\n";
			}
			else
			{
				cout << "\n# Invalid move\n";
			}
		}

		printMatrix(matrix);

		if (checkWin(matrix) == true)
		{
			char end[3] = "-1";
			send(new_socket,end,strlen(end),0);
			if (counter%2 == 0)
			{
				cout << "\nPlayer Cross wins.\n";
				break;
			}
			else if (counter%2 == 1)
			{
				cout << "\nPlayer Zero wins.\n";
				break;
			}
		}
		else
		{
			char end[2] = "0";
			send(new_socket,end,strlen(end),0);
		}

		counter++;

		if (counter == 9)
		{
			char end[3] = "-1";
			send(new_socket,end,strlen(end),0);
			cout << "\nIt's a tie.\n";
			break;
		}
	}
	
	return 0;
}

void printMatrix(char temp[m][n])
{
	cout << endl;
	cout << "---------\n";
	for (int i = 0; i < m; ++i)
	{
		cout << "| ";
		for (int j = 0; j < n; ++j)
		{
			cout << temp[i][j] << " ";
		}
		cout << "|\n";
	}
	cout << "---------\n";
}

bool checkWin(char temp[m][n])
{
	for (int i=0; i<m; i++)
	{
		if (temp[i][0] == temp[i][1] && temp[i][1] == temp[i][2] && temp[i][0] != '-')
			return true;
	}

	for (int i=0; i<n; i++)
	{
		if (temp[0][i] == temp[1][i] && temp[1][i] == temp[2][i] && temp[0][i] != '-')
			return true;
	}

	if (temp[0][0] == temp[1][1] && temp[1][1] == temp[2][2] && temp[0][0] != '-')
		return true;
		 
	if (temp[0][2] == temp[1][1] && temp[1][1] == temp[2][0] && temp[0][2] != '-')
		return true;

	return false;
}