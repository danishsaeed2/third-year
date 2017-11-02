// Non pre-emptive and pre-emptive (faulty) Shortest Job First scheduling algorithm for CPU processes
// Rename file to main class name

import java.util.Collections;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Scanner;

public class ps
{
	public static void main(String[] args)
	{
		Scanner scan = new Scanner(System.in);
	
		ArrayList <process> proQueue = new ArrayList<process>();
		int n;
		
		System.out.print("\nNumber of processes: ");
		n=scan.nextInt();
		
		for (int i = 0; i < n; i += 1)
		{
			process temp = new process();
	
			temp.id=i;
			temp.arrival=0;
			temp.arrivalFix=0;
			temp.bursts=0;
			temp.burstsFix=0;
			temp.start=0;
			temp.wait=0;
			temp.finish=0;
			temp.priority=0;
		
			proQueue.add(temp);
		}	
		
		for (int i = 0; i < n; i += 1)
		{
			System.out.println("\nProcess "+i+" :");
			System.out.print("Enter arrival time: ");
			int a_temp;
			a_temp=scan.nextInt();
			proQueue.get(i).setArrival(a_temp);
			proQueue.get(i).setArrivalFix(a_temp);
		
			System.out.print("Enter priority: ");
			proQueue.get(i).setPriority(scan.nextInt());
			
			System.out.print("Enter bursts time: ");
			int b_temp;
			b_temp=scan.nextInt();
			proQueue.get(i).setBursts(b_temp);
			proQueue.get(i).setBurstsFix(b_temp);
		}
		
		printTable(proQueue);
		
		int d;
		System.out.println("\n1. Non Pre-emptive\n2. Pre-emptive");
		d=scan.nextInt();
		
		if (d==1) { // 
		   nonPreEmptive(proQueue);
		}
		else if (d==2) { // 
		   preEmptive(proQueue);
		}
		else {
		
		}
		System.exit(0);
	}
	
	public static void nonPreEmptive (ArrayList <process> myQueue)
	{
		ArrayList <process> finalQueue = new ArrayList<process>();
		
		int time=0, myPro=0;
		int n=myQueue.size();
		
		Collections.sort(myQueue, new processCompare());
		
		time = myQueue.get(myPro).getArrivalFix();
		int firstTime = time;
		
		myQueue.get(myPro).setStart(time);
		myQueue.get(myPro).setFinish(time+myQueue.get(myPro).getBursts());
		time=time+myQueue.get(myPro).getBursts();
		finalQueue.add(myQueue.get(myPro));
		
		for(int i=0 ; i<myQueue.size() ; i++)
		{
			int count=0;
			while(myQueue.get(i).getArrival()!=firstTime && count!=myQueue.get(myPro).getBursts())
			{
				myQueue.get(i).decArrival();
				count++;
			}
		}
		myQueue.remove(myPro);
		
		while (finalQueue.size() != n)
		{
			Collections.sort(myQueue, new processCompare());
		
			if (time<myQueue.get(myPro).getArrivalFix())
			{
				time=myQueue.get(myPro).getArrivalFix();
			}
		
			myQueue.get(myPro).setStart(time);
			myQueue.get(myPro).setFinish(time+myQueue.get(myPro).getBursts());
			time=time+myQueue.get(myPro).getBursts();
			finalQueue.add(myQueue.get(myPro));
		
			for(int i=0 ; i<myQueue.size() ; i++)
			{
				int count=0;
				while(myQueue.get(i).getArrival()!=firstTime && count!=myQueue.get(myPro).getBursts())
				{
					myQueue.get(i).decArrival();
					count++;
				}
			}
			myQueue.remove(myPro);
		}
		
		for(int i=0 ; i< finalQueue.size() ; i++)
		{
			finalQueue.get(i).setWait(finalQueue.get(i).getFinish()-finalQueue.get(i).getArrivalFix()-finalQueue.get(i).getBursts());
			finalQueue.get(i).setTat(finalQueue.get(i).getFinish()-finalQueue.get(i).getArrivalFix());
		}
		
		printTable(finalQueue);
		NPEgantt(finalQueue);
	}
	
	public static void preEmptive (ArrayList <process> myQueue)
	{
		ArrayList <process> finalQueue = new ArrayList<process>();
		
		int time=0, myPro=0;
		int n=myQueue.size();
		
		Collections.sort(myQueue, new processCompare());
		time = myQueue.get(myPro).getArrivalFix();
		int firstTime = time;
		
		myQueue.get(myPro).setStart(time);
		myQueue.get(myPro).decBursts();
		time++;
		
		for (int i=0 ; i<myQueue.size() ; i++)
		{
			if(myQueue.get(i).getArrival() != firstTime)
			{
				myQueue.get(i).decArrival();
			}
		}
		if (myQueue.get(myPro).getBursts()==0)
		{
			myQueue.get(myPro).setFinish(time);
			finalQueue.add(myQueue.get(myPro));
			myQueue.remove(myPro);
		}
		
		while (finalQueue.size() != n)
		{
			Collections.sort(myQueue, new processCompare());
			
			if (myQueue.get(myPro).getBursts()==myQueue.get(myPro).getBurstsFix())
			{
				if (time<myQueue.get(myPro).getArrivalFix())
				{
					time=myQueue.get(myPro).getArrivalFix();
				}
				myQueue.get(myPro).setStart(time);
			}
			
			myQueue.get(myPro).decBursts();
			time++;
			
			for (int i=0 ; i<myQueue.size() ; i++)
			{
				if(myQueue.get(i).getArrival() != firstTime)
				{
					myQueue.get(i).decArrival();
				}
			}
			if (myQueue.get(myPro).getBursts()==0)
			{
				myQueue.get(myPro).setFinish(time);
				finalQueue.add(myQueue.get(myPro));
				myQueue.remove(myPro);
			}
		}
		
		/*
		for(int i=0 ; i< finalQueue.size() ; i++)
		{
			finalQueue.get(i).setWait(finalQueue.get(i).getFinish()-finalQueue.get(i).getArrivalFix()-finalQueue.get(i).getBursts());
			finalQueue.get(i).setTat(finalQueue.get(i).getFinish()-finalQueue.get(i).getArrivalFix());
		}
		*/
		
		printTable(finalQueue);
		
	}
	
	public static void printTabHead()
	{
		System.out.println("\nPID"+"\t"
			+"Arrival"+"\t"
			+"Prty"+"\t"
			+"Bursts"+"\t"
			+"Start"+"\t"
			+"Wait"+"\t"
			+"Finish"+"\t"
			+"TAT"+"\t");
	}
	
	public static void printTable (ArrayList <process> myTempQueue)
	{
		printTabHead();
		for (int i = 0; i < myTempQueue.size(); i += 1)
		{
			System.out.println("P"+myTempQueue.get(i).getId()+"\t"
				+myTempQueue.get(i).getArrivalFix()+"\t"
				+myTempQueue.get(i).getPriority()+"\t"
				+myTempQueue.get(i).getBurstsFix()+"\t"
				+myTempQueue.get(i).getStart()+"\t"
				+myTempQueue.get(i).getWait()+"\t"
				+myTempQueue.get(i).getFinish()+"\t"
				+myTempQueue.get(i).getTat()+"\t");
		}
		
		
		int avgWait=0,avgTat=0;
		for (int i = 0; i < myTempQueue.size(); i += 1)
		{
			avgWait=avgWait+myTempQueue.get(i).getWait();
			avgTat=avgTat+myTempQueue.get(i).getTat();
		}
	
		System.out.print("Average Waiting Time = "+(float)avgWait/(float)myTempQueue.size()+"\n");
		System.out.print("Average Turnaround Time = "+(float)avgTat/(float)myTempQueue.size()+"\n");
	}
	
	public static void NPEgantt (ArrayList <process> myQueue)
	{
		int i=0;
		System.out.print("\n");
		for (i = 0; i < myQueue.size(); i += 1)
		{
			if (i!=0 && myQueue.get(i).getArrivalFix() > myQueue.get(i-1).getFinish() && myQueue.get(i).getWait()==0)
			{
				for (int j = 0; j < (myQueue.get(i).getArrivalFix() - myQueue.get(i-1).getArrivalFix())/2; j += 1)
				{
					System.out.print(" ");
				}
			
			}
		
			for (int j = 0; j < myQueue.get(i).getBurstsFix(); j += 1)
			{
				System.out.print(" ");
			}
			System.out.print("P"+myQueue.get(i).getId());
			for (int j = 0; j < myQueue.get(i).getBurstsFix(); j += 1)
			{
				System.out.print(" ");
			}
			if (i!=0 && myQueue.get(i).getArrivalFix() > myQueue.get(i-1).getFinish() && myQueue.get(i).getWait()==0)
			{
			
				for (int j = 0; j < (myQueue.get(i).getArrivalFix() - myQueue.get(i-1).getArrivalFix())/2; j += 1)
				{
					System.out.print(" ");
				}
			}
		}
		System.out.print("\n"+myQueue.get(0).getArrivalFix());
		for (i = 0; i < myQueue.size(); i += 1)
		{
			if (i!=0 && myQueue.get(i).getArrivalFix() > myQueue.get(i-1).getFinish() && myQueue.get(i).getWait()==0)
			{
			
				for (int j = 0; j < myQueue.get(i).getArrivalFix() - myQueue.get(i-1).getArrivalFix(); j += 1)
				{
					System.out.print(" ");
				}
				System.out.print(myQueue.get(i).getStart());
			}
			for (int j = 0; j < myQueue.get(i).getBurstsFix()*2; j += 1)
			{
				System.out.print("-");
			}
			System.out.print(myQueue.get(i).getFinish());
		}
		System.out.println();
	}
}
	
class process
{
	int id;
	int arrival;
	int arrivalFix;
	int bursts;
	int burstsFix;
	int start;
	int wait;
	int finish;
	int priority;
	int tat;
	
	void setArrival(int x)
	{arrival=x;}
	void setArrivalFix(int x)
	{arrivalFix=x;}
	void setId(int x)
	{id=x;}
	void setPriority(int x)
	{priority=x;}
	void setBursts(int x)
	{bursts=x;}
	void setBurstsFix(int x)
	{burstsFix=x;}
	void setStart(int x)
	{start=x;}
	void setWait(int x)
	{wait=x;}
	void setFinish(int x)
	{finish=x;}
	void setTat(int x)
	{tat=x;}
	
	void decArrival()
	{arrival--;}
	void decBursts()
	{bursts--;}
	
	int getArrival()
	{return arrival;}
	int getArrivalFix()
	{return arrivalFix;}
	int getId()
	{return id;}
	int getPriority()
	{return priority;}
	int getBursts()
	{return bursts;}
	int getBurstsFix()
	{return burstsFix;}
	int getStart()
	{return start;}
	int getWait()
	{return wait;}
	int getFinish()
	{return finish;}
	int getTat()
	{return tat;}
}

class processCompare implements Comparator<process>
{
	public int compare (process p1, process p2)
	{
		if (p1.arrival > p2.arrival)
		{
			return 1;
		}
		else if (p1.arrival < p2.arrival)
		{
			return -1;
		}
		else
		{
			if (p1.priority > p2.priority)
			{
				return 1;
			}
			else if (p1.priority < p2.priority)
			{
				return -1;
			}
			else
			{
				if(p1.arrivalFix > p2.arrivalFix)
 				{
 					return 1;
 				}
 				else if (p1.arrivalFix < p2.arrivalFix)
 				{
 					return -1;
 				}
			}
		}
		return 0;
	}
}
