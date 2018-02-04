#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <unistd.h>
#include <errno.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/wait.h>

using namespace std;

int main()
{
	key_t memKey;
	int memId;
	sem_t *sem;
	pid_t pid;
	bool *redFork1;
	bool *redFork2;
	bool *greenFork1;
	bool *greenFork2;
	bool *redSpoon1;
	bool *redSpoon2;
	bool *greenSpoon1;
	bool *greenSpoon2;

	int size = 8*sizeof(bool);

	memKey = ftok("/dev/null", 5);
	memId = shmget (memKey, size, 0644 | IPC_CREAT);
	if (memId < 0)
	{
		cout << "shmget error" <<endl;
		exit(1);
	}

	redFork1 = (bool *)shmat(memId, NULL, 0);
	redFork2 = (bool *)shmat(memId, NULL, 0);
	greenFork1 = (bool *)shmat(memId, NULL, 0);
	greenFork2 = (bool *)shmat(memId, NULL, 0);
	redSpoon1 = (bool *)shmat(memId, NULL, 0);
	redSpoon2 = (bool *)shmat(memId, NULL, 0);
	greenSpoon1 = (bool *)shmat(memId, NULL, 0);
	greenSpoon2 = (bool *)shmat(memId, NULL, 0);

	*redFork1 = false;
	*redFork2 = false;
	*greenFork1 = false;
	*greenFork2 = false;
	*redSpoon1 = false;
	*redSpoon2 = false;
	*greenSpoon1 = false;
	*greenSpoon2 = false;

	//p = (bool)shmat(memId, NULL, 0);
	//*p = 0;

	sem = sem_open("/sem", O_CREAT | O_EXCL, 0644, 1);

	/*
	if (sem == SEM_FAILED || sem == NULL)
	{
		cout << "sem_open failed";
		exit(1);
	}
	*/

	int i;
	int eatingTime = 3;
	int thinkingTime = 1;
	int time = 0;
	int serves = 0;

	for (i = 0; i < 5; i++)
	{
		pid = fork();

		if (pid < 0)
		{
			sem_unlink("/sem");
			sem_close(sem);
			cout << "Failed to fork" << endl;
		}
		else if (pid == 0)
			break;
	}

	if (pid != 0)
	{
		while(pid = waitpid(-1, NULL, 0))
		{
			if (errno == ECHILD)
			{
				break;
			}
		}

		shmdt (redFork1);
		shmdt (redFork2);
		shmdt (greenFork1);
		shmdt (greenFork2);
		shmdt (redSpoon1);
		shmdt (redSpoon2);
		shmdt (greenSpoon1);
		shmdt (greenSpoon2);
		shmctl (memId, IPC_RMID, 0);

		sem_unlink("/sem");
		sem_close(sem);
		exit(0);
	}
	else
	{
		/*
		sem_wait(sem);
		
		cout << "Child "<<i<<" is in critical section"<<endl;
		sleep(1);
		incP(redSpoon2);
		cout << "*p = "<< *redSpoon2<<endl;
		cout << "Child "<<i<<" exits"<<endl;

		sem_post(sem);
		*/

		while(1)
		{
			sleep(1);
			time += thinkingTime;
			cout << "Phil "<<i<<" thinking"<<endl;

			while(1)
			{
				sem_wait(sem);

				if (*redFork1 == false && *redSpoon1 == false)
				{
					cout << "Phil "<<i<<" picks redFork1 & redSpoon1"<<endl;
					*redFork1 = true;
					*redSpoon1 = true;
					sem_post(sem);
					sleep(eatingTime);

					time += eatingTime;
					serves++;
					//sem_wait(sem);
					*redFork1 = false;
					*redSpoon1 = false;
					cout << "Phil "<<i<<" drops redFork1 & redSpoon1"<<endl;
					//sem_post(sem);
					break;
				}
				else if (*redFork1 == false && *redSpoon2 == false)
				{
					cout << "Phil "<<i<<" picks redFork1 & redSpoon2"<<endl;
					*redFork1 = true;
					*redSpoon2 = true;
					sem_post(sem);
					sleep(eatingTime);

					time += eatingTime;
					serves++;
					//sem_wait(sem);
					*redFork1 = false;
					*redSpoon2 = false;
					cout << "Phil "<<i<<" drops redFork1 & redSpoon2"<<endl;
					//sem_post(sem);
					break;
				}
				else if (*redFork2 == false && *redSpoon1 == false)
				{
					cout << "Phil "<<i<<" picks redFork2 & redSpoon1"<<endl;
					*redFork2 = true;
					*redSpoon1 = true;
					sem_post(sem);
					sleep(eatingTime);

					time += eatingTime;
					serves++;
					//sem_wait(sem);
					*redFork2 = false;
					*redSpoon1 = false;
					cout << "Phil "<<i<<" drops redFork2 & redSpoon1"<<endl;
					//sem_post(sem);
					break;
				}
				else if (*redFork2 == false && *redSpoon2 == false)
				{
					cout << "Phil "<<i<<" picks redFork2 & redSpoon2"<<endl;
					*redFork2 = true;
					*redSpoon2 = true;
					sem_post(sem);
					sleep(eatingTime);

					time += eatingTime;
					serves++;
					//sem_wait(sem);
					*redFork2 = false;
					*redSpoon2 = false;
					cout << "Phil "<<i<<" drops redFork2 & redSpoon2"<<endl;
					//sem_post(sem);
					break;
				}
				else if (*greenFork1 == false && *greenSpoon1 == false)
				{
					cout << "Phil "<<i<<" picks greenFork1 & greenSpoon1"<<endl;
					*greenFork1 = true;
					*greenSpoon1 = true;
					sem_post(sem);
					sleep(eatingTime);

					time += eatingTime;
					serves++;
					//sem_wait(sem);
					*greenFork1 = false;
					*greenSpoon1 = false;
					cout << "Phil "<<i<<" drops greenFork1 & greenSpoon1"<<endl;
					//sem_post(sem);
					break;
				}
				else if (*greenFork1 == false && *greenSpoon2 == false)
				{
					cout << "Phil "<<i<<" picks greenFork1 & greenSpoon2"<<endl;
					*greenFork1 = true;
					*greenSpoon2 = true;
					sem_post(sem);
					sleep(eatingTime);

					time += eatingTime;
					serves++;
					//sem_wait(sem);
					*greenFork1 = false;
					*greenSpoon2 = false;
					cout << "Phil "<<i<<" drops greenFork1 & greenSpoon2"<<endl;
					//sem_post(sem);
					break;
				}
				else if (*greenFork2 == false && *greenSpoon1 == false)
				{
					cout << "Phil "<<i<<" picks greenFork2 & greenSpoon1"<<endl;
					*greenFork2 = true;
					*greenSpoon1 = true;
					sem_post(sem);
					sleep(eatingTime);

					time += eatingTime;
					serves++;
					//sem_wait(sem);
					*greenFork2 = false;
					*greenSpoon1 = false;
					cout << "Phil "<<i<<" drops greenFork2 & greenSpoon1"<<endl;
					//sem_post(sem);
					break;
				}
				else if (*greenFork2 == false && *greenSpoon2 == false)
				{
					cout << "Phil "<<i<<" picks greenFork2 & greenSpoon2"<<endl;
					*greenFork2 = true;
					*greenSpoon2 = true;
					sem_post(sem);
					sleep(eatingTime);

					time += eatingTime;
					serves++;
					//sem_wait(sem);
					*greenFork2 = false;
					*greenSpoon2 = false;
					cout << "Phil "<<i<<" drops greenFork2 & greenSpoon2"<<endl;
					//sem_post(sem);
					break;
				}
				else
				{
					sem_post(sem);
					sleep(1);
					cout << "Phil "<<i<<" waiting"<<endl;
					time++;
				}
			}
		}

		exit(0);
	}
	
	return 0;
}