// First Come First Serve scheduling algorithm for CPU processes

#include<iostream>
#include<algorithm>

using namespace std;

struct process
{
	int process;
	int arrival;
	int burst;
};

int main (int argc, char const* argv[])
{
	int n;

	cout<<"Number of processes: ";
	cin>>n;
	
	process processList[n];
	
	int arrivalTemp[n];
	int burstTemp[n];
	int processTemp[n];
	
	for (unsigned int i = 0; i < n; i += 1)
	{
		processList[i].process=i+1;	
		
		cout<<"\nProcess "<<i+1<<endl;
		cout<<"   Enter arrival time: ";
		cin>>processList[i].arrival;
		
		cout<<"   Enter burst time: ";
		cin>>processList[i].burst;
		
	}
	
	for (unsigned int i = 0; i < n; i += 1)
	{
		processTemp[i]=processList[i].process;
	}
	for (unsigned int i = 0; i < n; i += 1)
	{
		arrivalTemp[i]=processList[i].arrival;
	}
	for (unsigned int i = 0; i < n; i += 1)
	{
		burstTemp[i]=processList[i].burst;
	}
	
	cout<<"\n\nArrival times	";
	for (unsigned int i = 0; i < n; i += 1)
	{
		cout<<arrivalTemp[i]<<" ";
	}
	cout<<"\n\nBurst times	";
	for (unsigned int i = 0; i < n; i += 1)
	{
		cout<<burstTemp[i]<<" ";
	}
	
	cout<<endl;
	
	for (int i = 0; i < n; i += 1)
	{
		for (int j = 0; j < n-1; j += 1)
		{
			if (arrivalTemp[j]>=arrivalTemp[j+1])
			{
				int temp;
				temp=arrivalTemp[j];
				arrivalTemp[j]=arrivalTemp[j+1];
				arrivalTemp[j+1]=temp;
				
				temp=burstTemp[j];
				burstTemp[j]=burstTemp[j+1];
				burstTemp[j+1]=temp;
				
				temp=processTemp[j];
				processTemp[j]=processTemp[j+1];
				processTemp[j+1]=temp;
			}
		}
	}
	
	cout<<"\n\nSorted Arrival times	";
	for (int i = 0; i < n; i += 1)
	{
		cout<<arrivalTemp[i]<<" ";
	}
	cout<<"\n\nSorted Burst times	";
	for (int i = 0; i < n; i += 1)
	{
		cout<<burstTemp[i]<<" ";
	}
	
	int ganttChart[n+1];
	int tempx=0;
	ganttChart[0]=arrivalTemp[0];
	tempx=ganttChart[0];
	
	for (int i = 1; i < n+1; i += 1)
	{
		for (int j = 1; j <=i; j += 1)
		{
			ganttChart[i]=ganttChart[i-1]+burstTemp[i-1];
		}
	}
	
	cout<<"\n\nGantt Chart		";
	for (int i = 0; i < n+1; i += 1)
	{
		cout<<ganttChart[i]<<" ";
	}
	
	cout<<"\n\nProcess Number		";
	for (int i = 0; i < n; i += 1)
	{
		cout<<processTemp[i]<<" ";
	}
	
	int turnTime[n];
	for (int i = 0; i < n; i += 1)
	{
		turnTime[i]=arrivalTemp[i]+ganttChart[i];
	}
	cout<<"\n\nTurnaround Time		";
	for (int i = 0; i < n; i += 1)
	{
		cout<<turnTime[i]<<" ";
	}
	
	float avgWaitTime;
	int temp=0;
	for (int i =0; i < n-1; i += 1)
	{
		temp=ganttChart[i]+temp;
	}
	avgWaitTime=(float)temp/(float)n;
	
	//cout<<"\n\nAverage Waiting Time: "<<avgWaitTime;
	/*
	float avgTurnTime;
	temp=0;
	for (int i =0; i < n-1; i += 1)
	{
		temp=turnTime[i]+temp;
	}
	avgTurnTime=(float)temp/(float)n;
	*/
	//cout<<"\n\nAverage Turnaround Time: "<<avgTurnTime;
	
	return 0;
}
