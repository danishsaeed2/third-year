// Finding shortest distance between all pair of nodes also implementing threads

#include <iostream>
#include <pthread.h>
#include <vector>
#include <cstdlib>

using namespace std;

pthread_barrier_t myBar;

int n,e,nth;
vector<vector<int> > gloDistMatrix;

void printGraph(vector<vector<int> > tempMatrix);
vector<vector<int> > createGraph(int n, int e);
void * shortPath(void * th);

int main()
{
	do
	{
		cout<<"\n# Number of nodes: ";
		cin>>n;
		if (n<=0)
			cout<<"\n! ERROR: Value can't be less than or equal to zero"<<endl;
		else
			break;
	}
	while(1);

	do
	{
		cout<<"\n# Number of edges: ";
		cin>>e;
		if (e<=0)
			cout<<"\n! ERROR: Value can't be less than or equal to zero"<<endl;
		else
			break;
	}
	while(1);

	vector<vector<int> > adjMatrix;

	adjMatrix = createGraph(n,e);
	gloDistMatrix = adjMatrix;

	printGraph(adjMatrix);

	do
	{
		cout<<"\n# Number of threads: ";
		cin>>nth;
		if (n%nth != 0)
			break;
			//cout<<"\n! ERROR: # of vertices must be multiple of # of threads"<<endl;
		else
			break;
	}
	while(1);

	pthread_t threads[50];
	pthread_barrier_init(&myBar, NULL, nth);

	int x[nth];
	for (int i = 0; i < nth; i++)
	{
		x[i]=i;
		pthread_create(&threads[i], NULL, shortPath, &x[i]);
	}

	for (int i = 0; i < nth; pthread_join(threads[i++], NULL));

	printGraph(gloDistMatrix);

	return 0;
}

void printGraph(vector<vector<int> > tempMatrix)
{
	cout<<"\nADJACENCY MATRIX\n\n\t";
	for (int u = 0; u < tempMatrix.size(); u++)
	{
		cout<<u<<"\t";
	}
	cout<<endl;
	for(int u=0;u<tempMatrix.size();u++)
	{
		cout<<"\n"<<u<< " ->\t";
		for(int v=0;v<tempMatrix[u].size();v++)
		{
			if (tempMatrix[u][v]>=1000)
				cout<<"-\t";
			else
				cout<<tempMatrix[u][v]<<"\t";
		}
	}
	cout<<endl;
}

vector<vector<int> > createGraph(int n, int e)
{
	vector<vector<int> > tempMatrix(n);
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i==j)
				tempMatrix[i].push_back(0);
			else
				tempMatrix[i].push_back(1000);
		}
	}

	int sour,dest,weight;

	for (int i = 0; i < e; i++)
	{
		cout<<"\n# Edge "<<i+1<<endl;
		do
		{
			cout<<"Source Node: ";
			cin>>sour;
			if (sour<0||sour>=n)
				cout<<"\n! ERROR: Value should be between 0 and "<<n<<endl;
			else
				break;
		}
		while(1);

		do
		{
			cout<<"Destination Node: ";
			cin>>dest;
			if (dest<0||dest>=n)
				cout<<"\n! ERROR: Value should be between 0 and "<<n<<endl;
			else
				break;
		}
		while(1);
		
		do
		{
			cout<<"Edge Weight: ";
			cin>>weight;
			if (weight<0||weight>=1000)
				cout<<"\n! ERROR: Value should be between 0 and 999"<<n<<endl;
			else
				break;
		}
		while(1);

		tempMatrix[sour][dest]=weight;
	}

	return tempMatrix;
}

void * shortPath(void * th)
{
	int myThread= * (int *) th;
	int sour1,sour2;

	sour1 = myThread * n/nth;
	sour2 = (myThread+1) * n/nth;

	cout<<"Thread: "<<myThread<<" starts for range from node: "<<sour1<<" to node: "<<sour2-1<<endl;

	for (int k = 0; k < n; k++)
	{
		pthread_barrier_wait(&myBar);
		for (int i = sour1; i < sour2; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (gloDistMatrix[i][k]+gloDistMatrix[k][j] < gloDistMatrix[i][j])
				{
					gloDistMatrix[i][j] = gloDistMatrix[i][k]+gloDistMatrix[k][j];
				}
			}
		}
	}

	cout<<"Thread: "<<myThread<<" completes."<<endl;
}