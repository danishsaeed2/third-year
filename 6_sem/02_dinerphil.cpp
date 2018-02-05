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
	pid_t pid;

	sem_t *redF1 = sem_open ("/redF1", O_CREAT | O_EXCL, 0644, 1);
	sem_t *redF2 = sem_open ("/redF2", O_CREAT | O_EXCL, 0644, 1);
	sem_t *greenF1 = sem_open ("/greenF1", O_CREAT | O_EXCL, 0644, 1);
	sem_t *greenF2 = sem_open ("/greenF2", O_CREAT | O_EXCL, 0644, 1);
	sem_t *redS1 = sem_open ("/redS1", O_CREAT | O_EXCL, 0644, 1);
	sem_t *redS2 = sem_open ("/redS2", O_CREAT | O_EXCL, 0644, 1);
	sem_t *greenS1 = sem_open ("/greenS1", O_CREAT | O_EXCL, 0644, 1);
	sem_t *greenS2 = sem_open ("/greenS2", O_CREAT | O_EXCL, 0644, 1);

	//sem = sem_open("/sem", O_CREAT | O_EXCL, 0644, 1);

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
	int flag[5]={0};

	for (i = 0; i < 5; i++)
	{
		pid = fork();

		if (pid < 0)
		{
			sem_unlink("/redF1");
			sem_unlink("/redF2");
			sem_unlink("/greenF1");
			sem_unlink("/greenF2");
			sem_unlink("/redS1");
			sem_unlink("/redS2");
			sem_unlink("/greenS1");
			sem_unlink("/greenS2");
			
			sem_close(redF1);
			sem_close(redF2);
			sem_close(greenF1);
			sem_close(greenF2);
			sem_close(redS1);
			sem_close(redS2);
			sem_close(greenS1);
			sem_close(greenS2);
			
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

		sem_unlink("/redF1");
		sem_unlink("/redF2");
		sem_unlink("/greenF1");
		sem_unlink("/greenF2");
		sem_unlink("/redS1");
		sem_unlink("/redS2");
		sem_unlink("/greenS1");
		sem_unlink("/greenS2");
			
		sem_close(redF1);
		sem_close(redF2);
		sem_close(greenF1);
		sem_close(greenF2);
		sem_close(redS1);
		sem_close(redS2);
		sem_close(greenS1);
		sem_close(greenS2);

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
			int fork_id;

			if (!sem_trywait(redF1))
			{
				fork_id=1;
				flag[i]=0;
			}
			else if (!sem_trywait(redF2))
			{
				fork_id=2;
				flag[i]=0;
			}
			else if (!sem_trywait(greenF1))
			{
				fork_id=3;
				flag[i]=0;
			}
			else if (!sem_trywait(greenF2))
			{
				fork_id=4;
				flag[i]=0;
			}
			else
			{
				fork_id=0;
				if (flag[i]==0)
				{
					cout<< "Phil " <<i<< " -   - is waiting for fork"<<endl;
				}
				flag[i]=1;
			}

			if (fork_id>0)
			{
				while(1)
				{
					if (fork_id==1||fork_id==2)
					{
						if (!sem_trywait(redS1))
						{
							if (fork_id==1)
								cout<< "Phil " <<i<< " - P - picks up red fork1 & spoon1"<<endl;
							else if (fork_id==2)
								cout<< "Phil " <<i<< " - P - picks up red fork2 & spoon1"<<endl;
							sleep(3);
							sem_post(redS1);
							if (fork_id==1)
							{
								sem_post(redF1);
								cout<< "Phil " <<i<< " - D - drops red fork1 & spoon1"<<endl;
							}
							else if (fork_id==2)
							{
								sem_post(redF2);
								cout<< "Phil " <<i<< " - D - drops red fork2 & spoon1"<<endl;
							}
							flag[i] = 0;
							cout<< "Phil " <<i<< " -   - is thinking"<<endl;
							sleep(1);
							break;
						}
						else if (!sem_trywait(redS2))
						{
							if (fork_id==1)
								cout<< "Phil " <<i<< " - P - picks up red fork1 & spoon2"<<endl;
							else if (fork_id==2)
								cout<< "Phil " <<i<< " - P - picks up red fork2 & spoon2"<<endl;
							sleep(3);
							sem_post(redS2);
							if (fork_id==1)
							{
								sem_post(redF1);
								cout<< "Phil " <<i<< " - D - drops red fork1 & spoon2"<<endl;
							}
							else if (fork_id==2)
							{
								sem_post(redF2);
								cout<< "Phil " <<i<< " - D - drops red fork2 & spoon2"<<endl;
							}
							flag[i] = 0;
							cout<< "Phil " <<i<< " -   - is thinking"<<endl;
							sleep(1);
							break;
						}
						else
						{
							if (flag[i]==0)
							{
								cout<< "Phil " <<i<< " -   - is waiting for spoon"<<endl;
							}
							flag[i]=1;
						}
					}
					else if (fork_id==3||fork_id==4)
					{
						if (!sem_trywait(greenS1))
						{
							if (fork_id==3)
								cout<< "Phil " <<i<< " - P - picks up green fork1 & spoon1"<<endl;
							else if (fork_id==4)
								cout<< "Phil " <<i<< " - P - picks up green fork2 & spoon1"<<endl;
							sleep(3);
							sem_post(greenS1);
							if (fork_id==3)
							{
								sem_post(greenF1);
								cout<< "Phil " <<i<< " - D - drops green fork1 & spoon1"<<endl;
							}
							else if (fork_id==4)
							{
								sem_post(greenF2);
								cout<< "Phil " <<i<< " - D - drops green fork2 & spoon1"<<endl;
							}
							flag[i] = 0;
							cout<< "Phil " <<i<< " -   - is thinking"<<endl;
							sleep(1);
							break;
						}
						else if (!sem_trywait(greenS2))
						{
							if (fork_id==3)
								cout<< "Phil " <<i<< " - P - picks up green fork1 & spoon2"<<endl;
							else if (fork_id==4)
								cout<< "Phil " <<i<< " - P - picks up green fork2 & spoon2"<<endl;
							sleep(3);
							sem_post(greenS2);
							if (fork_id==3)
							{
								sem_post(greenF1);
								cout<< "Phil " <<i<< " - D - drops green fork1 & spoon2"<<endl;
							}
							else if (fork_id==4)
							{
								sem_post(greenF2);
								cout<< "Phil " <<i<< " - D - drops green fork2 & spoon2"<<endl;
							}
							flag[i] = 0;
							cout<< "Phil " <<i<< " -   - is thinking"<<endl;
							sleep(1);
							break;
						}
						else
						{
							if (flag[i]==0)
							{
								cout<< "Phil " <<i<< " -   - is waiting for spoon"<<endl;
							}
							flag[i]=1;	
						}
					}
				}
			}

		}

		exit(0);
	}
	
	return 0;
}