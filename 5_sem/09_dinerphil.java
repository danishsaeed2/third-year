// Dining philosophers problem
// Rename file to main class name

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

		System.out.println();
		System.exit(0);
	}
}

class philosopher extends Thread
{
	int finishEat=0;
	int id;
	int totalTime;
	int eatingTime;
	int thinkingTime;
	int time;
	int serves;
	int waitTime;
	chopstick leftChop;
	chopstick rightChop;

	public philosopher(int i, int total, int eat, int think, chopstick left, chopstick right )
	{
		this.id=i;
		this.totalTime=total;
		this.eatingTime=eat;
		this.thinkingTime=think;
		this.time=0;
		this.serves=0;
		this.waitTime=0;
		leftChop=left;
		rightChop=right;
	}

	public void run()
	{
		while (time <= totalTime)
		{
			thinking();
			while (!pickChopsticks() && time<totalTime)
			{
				waiting();
				if (time >= totalTime)
				{
					finishEat = 1;
					break;
				}
			}

			if (finishEat == 1)
			{
				System.out.print("\n"+time+" - - - Philosopher "+id+" has finished eating. Serves: "+serves);
				return;
			}

			if (time > totalTime)
			{
				break;
			}
			else
			{
				eating();
				keepChopsticks();
			}
		}

		System.out.print("\n"+time+" - - - Philosopher "+id+" has finished eating. Serves: "+serves);
		return;
	}

	public void eating()
	{
		try
		{
			sleep(eatingTime);
		}
		catch (Exception e)
		{
			e.printStackTrace();
		}
		time = time + eatingTime;
		serves++;
	}

	public void waiting()
	{
		try
		{
			sleep(1);
		}
		catch (Exception e)
		{
			e.printStackTrace();
		}
		time++;
		waitTime++;
	}

	public void thinking()
	{
		try
		{
			sleep(thinkingTime);
		}
		catch (Exception e)
		{
			e.printStackTrace();
		}
		time = time + thinkingTime;
	}

	public boolean pickChopsticks()
	{
		if (leftChop.isAvailable() && rightChop.isAvailable())
		{
			leftChop.use();
			rightChop.use();
			System.out.print("\n"+time+" - p - Philosopher "+id+" picks "+leftChop.id+" "+rightChop.id);
			return true;
		}
		return false;
	}

	public void keepChopsticks()
	{
		leftChop.done();
		rightChop.done();
		System.out.print("\n"+time+" - r - Philosopher "+id+" releases "+leftChop.id+" "+rightChop.id);
	}
}

class chopstick
{
	private boolean available;
	public int id;

	public chopstick(int x)
	{
		this.id=x;
		this.available=true;
	}

	public void use()
	{
		this.available = false;
	}

	public void done()
	{
		this.available = true;
	}

	public boolean isAvailable()
	{
		if (this.available==true)
			return true;
		return false;
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
			System.out.print("\nPhilosopher ID: " + i);
			System.out.print("\nTotal Time: ");
			int ttime = scan.nextInt();
			System.out.print("Eating Time: ");
			int etime = scan.nextInt();
			System.out.print("Thinking Time: ");
			int thtime = scan.nextInt();

			if (i == (philosophers.length)-1)
			{
				philosophers[i] = new philosopher(i,ttime,etime,thtime,chopsticks[i],chopsticks[0]);
			}
			else
			{
				philosophers[i] = new philosopher(i,ttime,etime,thtime,chopsticks[i],chopsticks[i+1]);
			}
		}

		for (int j=0; j<philosophers.length ; j++)
		{
			philosophers[j].start();
		}

		for (int j=0; j<philosophers.length ; j++)
		{
			try
			{
				philosophers[j].join();
			}
			catch (InterruptedException e)
			{
		        e.printStackTrace();
		    }
		}
	}
}
