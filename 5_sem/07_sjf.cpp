// Non pre-emptive and pre-emptive (faulty) Shortest Job First scheduling algorithm for CPU processes

#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

class process
{
public:
	int id;
	int arrival;
	int arrivalFix;
	int bursts;
	int burstsFix;
	int start;
	int wait;
	int finish;
	int tat;
	
	bool operator <(process x)
	{
		if(x.arrival == arrival)
		{
			if(bursts == x.bursts)
			{
				return arrivalFix < x.arrivalFix;
			}
			return bursts < x.bursts;
		}

		return arrival < x.arrival;
	}
};

void printTabHead();
void printArray(vector <int> myTempArray);
void printTable(vector <process> myTempQueue);
//vector <process> mySort (vector <process>);
vector <process> nonPreEmptive (vector <process>);
vector <process> preEmptive (vector <process> myQueue);
void NPEgantt(vector <process> myQueue);

int main (int argc, char const* argv[])
{
	cout<<endl;
	
	// Variables
	int n;
	
	vector <process> proQueue;
	vector <process> finalProQueue;
	// vector <process> :: iterator i;
	
	cout<<"Number of processes? ";
	cin>>n;
	cout<<endl;
	
	for (int i = 0; i < n; i += 1)
	{
		process temp;
	
		temp.id=i;
		temp.arrival=0;
		temp.arrivalFix=0;
		temp.bursts=0;
		temp.burstsFix=0;
		temp.start=0;
		temp.wait=0;
		temp.finish=0;
		temp.tat=0;
		
		proQueue.push_back(temp);
	}
	
	for (int i = 0; i < n; i += 1)
	{
		cout<<"Process "<<i<<" :\n";
		cout<<"Enter arrival time: ";
		cin>>proQueue[i].arrival;
		proQueue[i].arrivalFix=proQueue[i].arrival;
		
		cout<<"Enter bursts: ";
		cin>>proQueue[i].bursts;
		proQueue[i].burstsFix=proQueue[i].bursts;
		cout<<endl;
	}
	
	cout<<endl;
	
	int sel;
	cout<<"1. Non-preemptive\n2. Pre-emptive\n";
	cin>>sel;
	
	cout<<endl;
	if (sel==1)
	{
		finalProQueue=nonPreEmptive(proQueue);
		printTable(finalProQueue);
		cout<<endl;
		NPEgantt(finalProQueue);
	}
	else if (sel==2)
	{
		finalProQueue=preEmptive(proQueue);
		printTable(finalProQueue);
	}
	
	cout<<endl;
	return 0;
}

// ----------- FUNCTIONS ----------

void printTabHead()
{
	cout<<"PID"<<"\t"
		<<"Arrival"<<"\t"
		<<"Bursts"<<"\t"
		<<"Start"<<"\t"
		<<"Wait"<<"\t"
		<<"Finish"<<"\t"
		<<"TAT"<<"\t"
		<<endl;
}

void printTable (vector <process> myTempQueue)
{
	printTabHead();
	for (int i = 0; i < myTempQueue.size(); i += 1)
	{
		cout<<"P"<<myTempQueue[i].id<<"\t"
			<<myTempQueue[i].arrivalFix<<"\t"
			<<myTempQueue[i].burstsFix<<"\t"
			<<myTempQueue[i].start<<"\t"
			<<myTempQueue[i].wait<<"\t"
			<<myTempQueue[i].finish<<"\t"
			<<myTempQueue[i].tat<<"\t"
			<<endl;
	}
	cout<<endl;
	int avgWait=0,avgTat=0;
	for (int i = 0; i < myTempQueue.size(); i += 1)
	{
		avgWait=avgWait+myTempQueue[i].wait;
		avgTat=avgTat+myTempQueue[i].tat;
	}
	
	cout<<"Average Waiting Time = "<<(float)avgWait/(float)myTempQueue.size()<<endl;
	cout<<"Average Turnaround Time = "<<(float)avgTat/(float)myTempQueue.size()<<endl;
	
}

void printArray(vector <int> myTempArray)
{
	for (int i = 0; i < myTempArray.size(); i += 1)
	{
		cout<<myTempArray[i]<<" ";
	}
	cout<<endl;
}

vector <process> nonPreEmptive (vector <process> myQueue)
{
	vector <process> finalQueue;
	vector <process> :: iterator i;
	vector <process> :: iterator myPro;
	
	int time=0;
	int n=myQueue.size();
	
	sort(myQueue.begin(),myQueue.end());
	int tempArr = myQueue.begin()->arrival;
	
	myPro=myQueue.begin();
	
	time=myPro->arrival;
	myPro->start=time;
	myPro->finish= time + myPro->bursts;

	time=time + myPro->bursts;
	
	finalQueue.push_back(*myPro);
	
	for(i = myQueue.begin(); i != myQueue.end(); i++)
	{
		int c = 0;
		while(i->arrival != tempArr && c != myPro->bursts)
		{
			i->arrival = i->arrival -1;
			c++;
		}
	}
	myQueue.erase(myPro);
	
	while (finalQueue.size() != n)
	{
		sort(myQueue.begin(),myQueue.end());
		myPro=myQueue.begin();
		if(time < myPro->arrivalFix)
		{
			time = myPro->arrivalFix;	
		}
		
		myPro->start=time;
		myPro->finish= time + myPro->bursts;
	
		time=time + myPro->bursts;
	
		finalQueue.push_back(*myPro);
	
		for(i = myQueue.begin(); i != myQueue.end(); i++)
		{
			int c = 0;
			while(i->arrival != tempArr && c != myPro->bursts)
			{
				i->arrival = i->arrival -1;
				c++;
			}
		}
		myQueue.erase(myPro);
	}
	
	for (i = finalQueue.begin(); i != finalQueue.end(); i += 1)
	{
		i->wait = i->finish - i->arrivalFix - i->bursts;
		i->tat = i->finish - i->arrivalFix;
	}
	
	return finalQueue;
}

vector <process> preEmptive (vector <process> myQueue)
{
	vector <process> finalQueue;
	vector <process> :: iterator i;
	vector <process> :: iterator myPro;
	
	int time=0;
	int n=myQueue.size();
	
	int totalBursts=0;
	for (i = myQueue.begin(); i != myQueue.end(); i += 1)
	{
		totalBursts=totalBursts + i->bursts;
	}
	
	sort(myQueue.begin(),myQueue.end());
	int tempArr = myQueue.begin()->arrival;
	myPro=myQueue.begin();
	myPro->start=myPro->arrival;
	myPro->bursts = myPro->bursts -1;
	time++;
	
	for (i = myQueue.begin(); i != myQueue.end(); i += 1)
	{
		if (i->arrival != 0)
		{
			i->arrival = i->arrival -1;
		}
	}
	if (myPro->bursts==0)
	{
		myPro->finish = time;
		finalQueue.push_back(*myPro);
		myQueue.erase(myPro);
	}
	
	while (finalQueue.size() != n)
	{
		sort(myQueue.begin(),myQueue.end());
		myPro=myQueue.begin();
		
		if (myPro->bursts == myPro->burstsFix)
		{
			if (time < myPro->arrivalFix)
			{
				time = myPro->arrivalFix;
			}
			myPro->start=time;
		}
		
		myPro->bursts=myPro->bursts -1;
		time++;
		
		for (i = myQueue.begin(); i != myQueue.end(); i += 1)
		{
			if (i->arrival != 0)
			{
				i->arrival = i->arrival -1;
			}
		}
		if (myPro->bursts==0)
		{
			myPro->finish = time;
			finalQueue.push_back(*myPro);
			myQueue.erase(myPro);
		}
	}
	
	for (i = finalQueue.begin(); i != finalQueue.end(); i += 1)
	{
		i->wait = i->finish - i->arrivalFix - i->burstsFix;
		i->tat = i->finish - i->arrivalFix;
	}
	
	return finalQueue;
}

void NPEgantt (vector <process> myQueue)
{
	vector <process> :: iterator i;
	i=myQueue.begin();
	
	for (i = myQueue.begin(); i != myQueue.end(); i += 1)
	{
		if (i!=myQueue.begin() && i->arrivalFix > (i-1)->finish && i->wait==0)
		{
			
			for (int j = 0; j < (i->arrivalFix - (i-1)->arrivalFix)/2; j += 1)
			{
				cout<<" ";
			}
			
		}
		
		for (int j = 0; j < i->burstsFix; j += 1)
		{
			cout<<" ";
		}
		cout<<"P"<<i->id;
		for (int j = 0; j < i->burstsFix; j += 1)
		{
			cout<<" ";
		}
		if (i!=myQueue.begin() && i->arrivalFix > (i-1)->finish && i->wait==0)
		{
			
			for (int j = 0; j < (i->arrivalFix - (i-1)->arrivalFix)/2; j += 1)
			{
				cout<<" ";
			}
			
		}
	}
	cout<<endl;
	cout<<myQueue.begin()->arrivalFix;
	for (i = myQueue.begin(); i != myQueue.end(); i += 1)
	{
		if (i!=myQueue.begin() && (i)->arrivalFix > (i-1)->finish && i->wait==0)
		{
			
			for (int j = 0; j < i->arrivalFix - (i-1)->arrivalFix; j += 1)
			{
				cout<<" ";
			}
			cout<<i->start;
		}
		for (int j = 0; j < i->burstsFix*2; j += 1)
		{
			cout<<"-";
		}
		cout<<i->finish;
	}
}

/*
vector <process> mySort(vector <process> proQueue)
{
	vector <int> tempArrival;
	for (int i = 0; i < proQueue.size(); i += 1)
	{
		tempArrival.push_back(proQueue[i].arrival);
	}
	
	vector <int> tempId;
	for (int i = 0; i < proQueue.size(); i += 1)
	{
		tempId.push_back(proQueue[i].id);
	}
	
	// Sorting of table
	for (int i = 0; i < proQueue.size(); i += 1)
	{
		for (int j = 0; j < proQueue.size()-1; j += 1)
		{
			if (tempArrival[j]>tempArrival[j+1])
			{
				int t;
				t=tempArrival[j];
				tempArrival[j]=tempArrival[j+1];
				tempArrival[j+1]=t;
				
				process temp;
				temp=proQueue[j];
				proQueue[j]=proQueue[j+1];
				proQueue[j+1]=temp;
			}
		}
	}
	
	vector <int> tempBursts;
	for (int i = 0; i < proQueue.size(); i += 1)
	{
		tempBursts.push_back(proQueue[i].bursts);
	}
	
	for (int i = 0; i < proQueue.size(); i += 1)
	{
		int t=0;
		while (proQueue[i].arrival==proQueue[i+1].arrival)
		{
			t++;
			i++;
		}
		if (t!=0)
		{
			for (int x = i-t; x < i+1; x += 1)
			{
				for (int j = i-t; j < i; j += 1)
				{
					if (tempBursts[j]>tempBursts[j+1])
					{
						int t;
						t=tempBursts[j];
						tempBursts[j]=tempBursts[j+1];
						tempBursts[j+1]=t;
				
						process temp;
						temp=proQueue[j];
						proQueue[j]=proQueue[j+1];
						proQueue[j+1]=temp;
					}
				}
			}
		}
	}
	
	for (int i = 0; i < proQueue.size(); i += 1)
	{
		int t=0;
		while ((proQueue[i].arrival==proQueue[i+1].arrival)&&(proQueue[i].bursts==proQueue[i+1].bursts))
		{
			t++;
			i++;
		}
		if (t!=0)
		{
			for (int x = i-t; x < i+1; x += 1)
			{
				for (int j = i-t; j < i; j += 1)
				{
					if (tempId[j]>tempId[j+1])
					{
						int t;
						t=tempId[j];
						tempId[j]=tempId[j+1];
						tempId[j+1]=t;
				
						process temp;
						temp=proQueue[j];
						proQueue[j]=proQueue[j+1];
						proQueue[j+1]=temp;
					}
				}
			}
		}
	}
	
	return proQueue;
}
*/
