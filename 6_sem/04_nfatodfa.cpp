#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct transition
{
	char symb;
	int stat; 
};

struct DFAstate
{
	int statno;
	vector<int> oldStates;
};

vector<vector<transition> > NFA;
vector<vector<transition> > DFA;

void printTransTable(vector<vector<transition> > tempMatrix);

int main()
{	
	int nfaStates = 0;
	int nfaSymbols = 0;

	int iniState;
	vector<int> states;
	vector<int> finStates;
	vector<char> symbols;

	string line;
	ifstream infile ("nfa.txt");
	
	if (infile.is_open())
	{
		while (getline(infile,line))
		{
			if (line.at(0)=='M')
			{
				int brcount = 0;
				for (int i = 1; i < line.length(); ++i)
				{
					char temp = line.at(i);
					if (temp == '{' && brcount == 0)
					{
						brcount++;
						for (int j = i+1; line.at(j)!='}' ; ++j)
						{
							if (line.at(j)=='q')
							{
								int t = line.at(j+1) - 48;
								states.push_back(t);
								nfaStates++;
							}
							i = j;
						}
					}
					else if (temp == '{' && brcount == 1)
					{
						brcount++;
						for (int j = i+1; line.at(j)!='}' ; ++j)
						{
							if (line.at(j) != ',')
							{
								//cout << "\nCheck linat: " << line.at(j) << endl;
								symbols.push_back(line.at(j));
								nfaSymbols++;	
							}
							i = j;
						}
					}
					else if (brcount == 2 && temp == 'q')
					{
						iniState = line.at(i+1);
						iniState = iniState - 48;
					}
					else if (brcount == 2 && temp == '{')
					{
						brcount++;
						for (int j = i+1; line.at(j)!='}' ; ++j)
						{
							if (line.at(j)=='q')
							{
								int t = line.at(j+1) - 48;
								finStates.push_back(t);
							}
							i = j;
						}
					}
				}
				vector<vector<transition> > tempNFA(nfaStates);
				NFA = tempNFA;
				//cout << "\nNFA size: " << NFA.size() << endl;
			}
			else if (line.at(0)=='q')
			{
				int sour = line.at(1) - 48;
				transition temp;
				temp.stat = line.at(8) - 48;
				temp.symb = line.at(3);

				//cout << "\nCheck linat state: " << temp.stat << endl;
				//cout << "\nCheck linat symbol: " << temp.symb << endl;

				NFA[sour].push_back(temp);

				//cout << NFA[sour][NFA[sour].size()].symb <<","<< NFA[sour][NFA[sour].size()].stat << endl;
			}
		}
		infile.close();
	}

	cout << "States: " << nfaStates <<endl;
	cout << "Symbols: " << nfaSymbols <<endl;
	cout << "Final States: " << finStates.size() <<endl;

	cout << "\nInitial State: " << "q" << iniState <<endl;
	cout << "\nSymbols: ";
	for (int i = 0; i < symbols.size(); ++i)
	{
		cout << symbols[i] << " ";
	}

	cout << "\nStates: ";
	for (int i = 0; i < nfaStates; ++i)
	{
		cout << "q" << states[i] << " ";
	}

	cout << "\nFinal States: ";
	for (int i = 0; i < finStates.size(); ++i)
	{
		cout << "q" << finStates[i] << " ";
	}

	printTransTable(NFA);

	vector <DFAstate> myDFAstates;

	DFAstate temp;
	int runState = 0;
	temp.statno=runState;
	runState++;
	temp.oldStates.push_back(iniState);
	myDFAstates.push_back(temp);

	for (int i = 0; i < NFA.size(); ++i)
	{
		for (int j = 0; j < symbols.size(); ++j)
		{
			DFAstate temp;
			temp.statno = runState;
			runState++;
			for (int k = 0; k < NFA[i].size(); ++k)
			{
				if (NFA[i][k].symb == symbols[j])
				{
					temp.oldStates.push_back(NFA[i][k].stat);
				}
			}
			if (temp.oldStates.size() != 0)
			{
				sort(temp.oldStates.begin(),temp.oldStates.end());
				myDFAstates.push_back(temp);
			}	
		}
	}
	
	for (int i = 0; i < myDFAstates.size(); ++i)
	{
		for (int j = i+1; j < myDFAstates.size(); ++j)
		{
			if (myDFAstates[i].oldStates == myDFAstates[j].oldStates)
			{
				myDFAstates.erase(myDFAstates.begin()+j);
			}
		}
	}

	for (int i = 0; i < myDFAstates.size(); ++i)
	{
		vector<transition> myTempV;
		for (int j = 0; j < symbols.size(); ++j)
		{
			vector<int> tempv;
			for (int k = 0; k < myDFAstates[i].oldStates.size(); ++k)
			{
				int oldt = myDFAstates[i].oldStates[k];
				for (int l = 0; l < NFA[oldt].size(); ++l)
				{
					if (NFA[oldt][l].symb == symbols[j] && find(tempv.begin(), tempv.end(), NFA[oldt][l].stat) == tempv.end())
					{
						tempv.push_back(NFA[oldt][l].stat);
					}
				}
			}

			sort(tempv.begin(),tempv.end());
			bool check = true;
			for (int k = 0; k < myDFAstates.size(); ++k)
			{
				if (myDFAstates[k].oldStates == tempv)
				{
					check = true;
					transition temp;
					temp.symb = symbols[j];
					temp.stat = k;

					myTempV.push_back(temp);
					break;
				}
				check = false;
			}
			
			if (check == false)
			{
				DFAstate tempx;
				tempx.statno = -1;
				tempx.oldStates = tempv;
				if (tempx.oldStates.size() != 0)
				{
					myDFAstates.push_back(tempx);

					transition temp;
					temp.symb = symbols[j];
					temp.stat = myDFAstates.size()-1;
					myTempV.push_back(temp);
				}

			}
		}

		DFA.push_back(myTempV);
	}

	/*
	for (int i = 0; i < myDFAstates.size(); ++i)
	{
		if (myDFAstates[i].size() > 1)
		{
			vector <int> tempv;
			for (int k = 0; k < symbols.size(); ++k)
			{
				for (int j = 0; j < myDFAstates[i].size(); ++j)
				{
					int oldt = myDFAstates[i].oldStates[j];
					for (int l = 0; l < NFA[oldt].size(); ++l)
					{
						if (NFA[oldt][l].symb == symbols[k])
						{
							tempv.push_back(NFA[oldt][l].stat);
						}
					}
				}
			}
			
		}
	}
	*/

	cout << endl;
	for (int i = 0; i < myDFAstates.size(); ++i)
	{
		cout << "q" << i <<" -> ";
		for (int j = 0; j < myDFAstates[i].oldStates.size(); ++j)
		{
			cout << myDFAstates[i].oldStates[j] << " ";
		}
		cout << endl;
	}

	printTransTable(DFA);

	cout <<"\nFinal States: ";
	for (int i = 0; i < myDFAstates.size(); ++i)
	{
		for (int j = 0; j < finStates.size(); ++j)
		{
			if(find(myDFAstates[i].oldStates.begin(), myDFAstates[i].oldStates.end(), finStates[j]) != myDFAstates[i].oldStates.end())
			{
				cout << "q" << i << " ";
			}
		}
	}
	cout << endl;

	return 0;
}

void printTransTable(vector<vector<transition> > tempMatrix)
{
	cout<<"\n\nTransition Table"<<endl;
	/*
	for (int u = 0; u < tempMatrix.size(); u++)
	{
		cout<<u<<"\t";
	}
	*/

	for(int u=0;u<tempMatrix.size();u++)
	{
		cout<<"\nq"<<u<< " ->\t";
		for(int v=0;v<tempMatrix[u].size();v++)
		{
			cout << tempMatrix[u][v].symb <<",q"<<tempMatrix[u][v].stat<<" ";
		}
	}
	cout<<endl;
}