#include <iostream>
#include <vector>
using namespace std;

struct edge
{
	int src;
	int dest;
};

int main()
{
	cout<<"\nALL SPANNING TREES\n";
	int n,i;
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
	
	//vector<vector<int> > adjMatrix(n);
	int adjMatrix[n][n];
	
	for(int u=0;u<n;u++)
	{
		for(int v=0;v<n;v++)
		{
			adjMatrix[u][v]=0;
		}
		cout<"\n";
	}
	
	adjMatrix[0][1]=1;
	adjMatrix[0][2]=1;
	adjMatrix[0][3]=1;
	adjMatrix[1][0]=1;
	adjMatrix[1][2]=1;
	adjMatrix[1][3]=1;
	adjMatrix[2][0]=1;
	adjMatrix[2][1]=1;
	adjMatrix[2][3]=1;
	adjMatrix[3][0]=1;
	adjMatrix[3][1]=1;
	adjMatrix[3][2]=1;

	/*

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
					cout<<"Edge Weight: ";
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

	*/
	
	cout<<"\nADJACENCY MATRIX\n";
	
	for(int u=0;u<n;u++)
	{
		for(int v=0;v<n;v++)
		{
			cout<<adjMatrix[u][v]<<"\t";
		}
		cout<<"\n";
	}

	vector<edge> edges;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (adjMatrix[i][j]!=0)
			{
				edge temp;
				temp.src=i;
				temp.dest=j;

				edges.push_back(temp);
			}
		}
	}

	cout<<"\n\nEdges\n";
	cout<<"i\tSRC\tDEST"<<endl;
	cout<<"-\t-\t-"<<endl;
	for (int i = 0; i < edges.size(); ++i)
	{
		cout<<i<<"\t"<<edges[i].src<<"\t"<<edges[i].dest<<endl;
	}

	

}