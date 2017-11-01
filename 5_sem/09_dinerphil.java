import java.util.Scanner;

public class dinerphil
{
	public static void main(String[] args)
	{
		Scanner scan = new Scanner(System.in);
		int n;

		System.out.print("\nEnter number of philosophers: ");
		n=scan.nextInt();

		solver mySolver = new solver();
		mySolver.solve(n);

		System.exit(0);
	}
}

class philosopher implements Runnable
{
	int id;
	int totalTime;
	int eatingTime;
	int thinkingTime;
	int time;

	public philosopher(int i, int total, int eat, int think)
	{
		this.id=i;
		this.totalTime=total;
		this.eatingTime=eat;
		this.thinkingTime=think;
		this.time=0;
	}

	public void run()
	{

	}

	public void eating()
	{

	}

	public void waiting()
	{

	}

	public void thinking()
	{

	}
}

class chopstick
{
	public boolean available;
	public int id;

	public chopstick(int x)
	{
		this.id=x;
	}

	public synchronized void use()
	{
		this.available = false;
	}

	public synchronized void done()
	{
		this.available = true;
	}
}

class solver
{
	public void solve (int n)
	{
		Scanner scan = new Scanner(System.in);

		philosopher[] philosophers = new philosopher[n];
		chopstick[] chopsticks = new chopstick[n];

		for (int i=0; i<chopsticks.length ; i++)
		{
			chopsticks[i] = new chopstick(i);
		}

		System.out.println("\nEnter the details of Philosophers");

		for (int i=0; i<philosophers.length ; i++)
		{
			System.out.print("Philosopher ID: " + i);
			System.out.print("Total Time: ");
			int ttime = scan.nextInt();
			System.out.print("Eating Time: ");
			int etime = scan.nextInt();
			System.out.print("Thinking Time: ");
			int thtime = scan.nextInt();

			philosophers[i] = new philosopher(i,ttime,etime,thtime);
		}
	}
}


/*
int getId()
{return id;}
int getTot()
{return totalTime;}
int getEat()
{return eatingTime;}
int getThink()
{return thinkingTime;}

void setId (int x)
{id=x;}
void setTot (int x)
{totalTime=x;}
void setEat (int x)
{eatingTime=x;}
void setThink (int x)
{thinkingTime=x;}
*/
