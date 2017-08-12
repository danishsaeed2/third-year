#include <iostream>
using namespace std;

#define INF 2147483647

int main()
{
  	cout<<"\n\nDJIKSTRA'S SHORTEST PATH ALGORITHM\n";
	int n,i,source,destination;
	char cont,edCont;
	
	cout<<"\n# Enter number of nodes: ";
	cin>>n;
	
	while(1)
	{
		if (n<=0)
		{
			cout<<"\n! ERROR: Value can't be less than or equal to zero";
			cout<<"\n# Enter number of nodes: ";
			cin>>n;
		}
		else
		{
			break;
		}
	}
	
	int adjMatrix[n][n];
	
	for(int u=0;u<n;u++)
	{
		for(int v=0;v<n;v++)
		{
			adjMatrix[u][v]=0;
		}
		cout<"\n";
	}
	
	cout<<"\n# Create edge? ";
	cin>>cont;
	cout<<endl;
	
	int sour,dest,weight;

	if (cont=='y'||cont=='Y')
	{		
		do
		{	
			cout<<"#\n";	
			cout<<"Starting Node: ";
			cin>>sour;
			while(1)
			{
				if (sour<0||sour>=n)
				{
					cout<<"\n! ERROR: Value should be between 0 and "<<n<<"\n";
					cout<<"Starting Node: ";
					cin>>sour;
				}
				else
				{
					break;
				}
			}
			cout<<"Ending Node: ";
			cin>>dest;
			while(1)
			{
				if (dest<0||dest>=n)
				{
					cout<<"\n! ERROR: Value should be between 0 and "<<n<<"\n";
					cout<<"Ending Node: ";
					cin>>dest;
				}
				else
				{
					break;
				}
			}
			cout<<"Edge Weight: ";
			cin>>weight;
			while(1)
			{
				if (weight<=0)
				{
					cout<<"\n! ERROR: Weight can't be less than or equal to 0\n";
					cout<<"Ending Node: ";
					cin>>dest;
				}
				else
				{
					break;
				}
			}
			
			adjMatrix[sour][dest]=weight;
			
			cout<<"\n# Do you want to create another edge? ";
			cin>>edCont;
			cout<<"\n";
			
		} while (edCont=='y'||edCont=='Y');
	}
	
	cout<"\n\nADJACENCY MATRIX\n";
	
	for(int u=0;u<n;u++)
	{
		for(int v=0;v<n;v++)
		{
			cout<<adjMatrix[u][v]<<"\t";
		}
		cout<<"\n";
	}
	
	cout<<"\n\n";
	cout<<"# Enter source node: ";
	cin>>source;
	cout<<"# Enter destination node: ";
	cin>>destination;
	
	while(1)
	{
		if ((adjMatrix[source][destination]==0)||source<0||source>n||destination<0||destination>=n)
		{
			cout<<"\n! ERROR: No path exists\n";
			return;
		}
		else
		{
			break;
		}
	}
	
	int shortDist[n];
	bool shortPath[n];
	int Path[n];

	for (i=0;i<n;i++)
	{
		shortDist[i]=INF;
		shortPath[i]=false;
	}
	
	shortDist[source] = 0;
  
	for (i=0;i<n-1;i++)
	{
		int min=INF,minI;

		for (int v=0;v<n;v++)
		{
			if (shortPath[v]==false && shortDist[v]<=min)
			{
				min=shortDist[v];
				minI=v;
			}
		}
		
		int u=minI;
		Path[i]=u;
		if (u==destination)
		{
			break;
		}
		

		shortPath[u]=true;

		for (int v=0;v<n;v++)
		{
			if (!shortPath[v] && adjMatrix[u][v] && shortDist[u]!=INF 
				&& (shortDist[u]+adjMatrix[u][v])<shortDist[v])
			{
				shortDist[v]=shortDist[u]+adjMatrix[u][v];
			}
		}
	}
  
	cout<<"\nShortest Distance from source node: "<<shortDist[destination];
	cout<<"\nShortest path from source node:\n";
	for(i=0;Path[i-1]!=destination;i++)
	{
		cout<<Path[i]<<" -> ";
	}
	cout<<endl;

	return 0;
}
