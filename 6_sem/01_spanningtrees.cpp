// Find all spanning trees of a given completely connected graph

#include <iostream>
#include <vector>
using namespace std;

struct edge
{
	int src;
	int dest;
};

int count=1;

void allSubsets(vector<edge> tempEdge, vector<edge> spanEdges, int n, int ix, int i);
void constructGraph(int n, vector<edge> spanEdges);
void printGraph(vector<vector<int> > tempMatrix);
bool cycleCheck(vector<vector<int> > tempMatrix);
bool cycleWork(int r, vector<vector<int> > tempMatrix, int p, vector<bool> check);

int main(int argc, char const *argv[])
{
	int n;
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
			break;
	}

	vector<vector<int> > adjMatrix(n);

	cout<<"\n# Create edge? ";
	cin>>cont;
	cout<<endl;
	
	int sour,dest;

	if (cont=='y'||cont=='Y')
	{		
		do
		{	
			cout<<"#\n";	
			cout<<"Source Node: ";
			cin>>sour;
			while(1)
			{
				if (sour<0||sour>=n)
				{
					cout<<"\n! ERROR: Value should be between 0 and "<<n<<"\n";
					cout<<"Source Node: ";
					cin>>sour;
				}
				else
					break;
			}
			cout<<"Destination Node: ";
			cin>>dest;
			while(1)
			{
				if (dest<0||dest>=n)
				{
					cout<<"\n! ERROR: Value should be between 0 and "<<n<<"\n";
					cout<<"Destination Node: ";
					cin>>dest;
				}
				else
					break;
			}
			
			adjMatrix[sour].push_back(dest);
			adjMatrix[dest].push_back(sour);
			
			cout<<"\n# Another edge? ";
			cin>>edCont;
			cout<<"\n";
			
		} while (edCont=='y'||edCont=='Y');
	}

	printGraph(adjMatrix);

	vector<edge> edges;

	for (int i = 0; i < adjMatrix.size(); i++)
	{
		for (int j = 0; j < adjMatrix[i].size(); j++)
		{
			if (i<adjMatrix[i][j])
			{
				edge temp;
				temp.src=i;
				temp.dest=adjMatrix[i][j];

				edges.push_back(temp);
			}
		}
	}

	cout<<"\n\nEdges\ni\tSRC\tDEST\n-\t-\t-"<<endl;
	for (int i = 0; i < edges.size(); i++)
	{
		cout<<i<<"\t"<<edges[i].src<<"\t"<<edges[i].dest<<endl;
	}

	vector<edge> myEdge(n-1);
	allSubsets(edges,myEdge,n,0,0);

	return 0;
}

bool cycleCheck(vector<vector<int> > tempMatrix)
{
	vector<bool> check;
    for (int i = 0; i < tempMatrix.size(); i++)
    	check.push_back(false);

    for (int i = 0; i < tempMatrix.size(); i++)
    {
    	if (check[i]==false)
    	{
    		if (cycleWork(i,tempMatrix,-1,check))
    		{
    			return true;
    		}
    	}
    }

    return false;
}

void printGraph(vector<vector<int> > tempMatrix)
{
	cout<<"\nADJACENCY MATRIX\n";
	
	for(int u=0;u<tempMatrix.size();u++)
	{
		cout<<u<< " ->\t";
		for(int v=0;v<tempMatrix[u].size();v++)
		{
			cout<<tempMatrix[u][v]<<"\t";
		}
		cout<<"\n";
	}
}

bool cycleWork(int r, vector<vector<int> > tempMatrix, int p, vector<bool> check)
{
	check[r]=true;

	for (int i = 0; i < tempMatrix[r].size(); i++)
	{
		if (check[tempMatrix[r][i]] != true)
		{
			bool temp = cycleWork(tempMatrix[r][i],tempMatrix,r,check);
			if (temp == true)
			{
				return true;
			}
		}
		else if (tempMatrix[r][i] != r)
			return true;
	}
	return false;
}

void allSubsets(vector<edge> tempEdge, vector<edge> spanEdges, int n, int ix, int i)
{
	int e = tempEdge.size();
	int r = n-1;
	if (ix == r)
	{
		constructGraph(n,spanEdges);
		return;
	}

	if (i>=e)
	{
		return;
	}

	spanEdges[ix] = tempEdge[i];
	allSubsets(tempEdge,spanEdges,n,ix+1,i+1);
	allSubsets(tempEdge,spanEdges,n,ix,i+1);
}

void constructGraph(int n, vector<edge> spanEdges)
{
	vector<vector<int> > tempMatrix(n);

	for (int i = 0; i < spanEdges.size(); i++)
	{
		tempMatrix[spanEdges[i].src].push_back(spanEdges[i].dest);
		tempMatrix[spanEdges[i].dest].push_back(spanEdges[i].src);
	}

	for (int i = 0; i < tempMatrix.size(); i++)
	{
		if (tempMatrix[i].size()==0)
			return;
	}

	if (cycleCheck(tempMatrix))
	{
		cout<<"\n"<<count;
		count++;
		printGraph(tempMatrix);
	}
}