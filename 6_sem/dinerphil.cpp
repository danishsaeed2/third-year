#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int main(int argc, char const *argv[])
{
	int c = 0;

	pid_t pid = fork();
	
	if (pid == 0)
	{
		c++;		
	}
	else if (pid <0)
	{
		cout << "Failed to fork" << endl;
	}
	else
	{

	}

	cout << c << endl;

	return 0;
}