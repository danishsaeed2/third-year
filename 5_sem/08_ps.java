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
		}	
		
		printTable(proQueue);
		
		System.exit(0);
	}
	
	public static void printTabHead()
	{
		System.out.println("\nPID"+"\t"
			+"Arrival"+"\t"
			+"Priority"+"\t"
			/*+"Bursts"+"\t"
			+"Start"+"\t"
			+"Wait"+"\t"
			+"Finish"+"\t"*/);
	}
	
	public static void printTable (ArrayList <process> myTempQueue)
	{
		printTabHead();
		for (int i = 0; i < myTempQueue.size(); i += 1)
		{
			System.out.println("P"+myTempQueue.get(i).getId()+"\t"
				+myTempQueue.get(i).getArrivalFix()+"\t"
				+myTempQueue.get(i).getPriority()+"\t");
		}
		
		/*
		int avgWait=0,avgTat=0;
		for (int i = 0; i < myTempQueue.size(); i += 1)
		{
			avgWait=avgWait+myTempQueue[i].wait;
			avgTat=avgTat+myTempQueue[i].tat;
		}
	
		cout<<"Average Waiting Time = "<<(float)avgWait/(float)myTempQueue.size()<<endl;
		cout<<"Average Turnaround Time = "<<(float)avgTat/(float)myTempQueue.size()<<endl;
		*/
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
	
	void setArrival(int x)
	{
		arrival=x;
	}
	void setArrivalFix(int x)
	{
		arrivalFix=x;
	}
	void setId(int x)
	{
		id=x;
	}
	void setPriority(int x)
	{
		priority=x;
	}
	
	int getArrival()
	{
		return arrival;
	}
	int getArrivalFix()
	{
		return arrivalFix;
	}
	int getId()
	{
		return id;
	}
	int getPriority()
	{
		return priority;
	}
	
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
				if (p1.arrivalFix > p2.arrivalFix)
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
