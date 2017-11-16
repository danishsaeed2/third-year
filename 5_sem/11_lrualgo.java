import java.util.Scanner;
import java.util.ArrayList;

class lrualgo {
	public static void main(String[] args) {

		Scanner scan = new Scanner(System.in);
		ArrayList<Integer> myQueue = new ArrayList<Integer>();

		int n,c;

		System.out.print("\nEnter number of pages: ");
		n = scan.nextInt();

		System.out.println();
		for (int i=0; i<n; i++ ) {
			System.out.print("Page Call: ");
			int temp;
			temp = scan.nextInt();
			myQueue.add(temp);
		}

		System.out.print("\nEnter capacity of cache: ");
		c = scan.nextInt();

		solver(myQueue,c);

		System.out.print("\nTerminated.\n");
	}

	public static void solve(ArrayList<Integer> myTempCache, int capacity) {
		Scanner x = new Scanner(System.in);
		int n = myTempCache.size();
		int check;

		System.out.print("\nAdditional Request? (1 for yes) ");
		check = x.nextInt();
		while (check==1) {
			System.out.print("\nPage Call: ");
			int t = x.nextInt();

			if (myTempCache.size() < capacity) {
				if (myTempCache.contains(t) == false) {
					myTempCache.add(0,t);
					System.out.println("PAGE FAULT");
				}
				else {
					int temp = myTempCache.indexOf(t);
					myTempCache.remove(temp);
					myTempCache.add(0,t);
					System.out.println("PAGE HIT");
				}
			}
			else {
				if (myTempCache.contains(t) == false) {
					myTempCache.remove(myTempCache.size()-1);
					myTempCache.add(0,t);
					System.out.println("PAGE FAULT");
				}
				else {
					int temp = myTempCache.indexOf(t);
					myTempCache.remove(temp);
					myTempCache.add(0,t);
					System.out.println("PAGE HIT");
				}
			}

			for (int j=0; j<myTempCache.size(); j++ ) {
				System.out.print(myTempCache.get(j)+" ");
			}
			System.out.println();

			System.out.print("\nAdditional Request? (1 for yes) ");
			check = x.nextInt();
			
		}
	}

	public static void solver(ArrayList<Integer> myTempQueue, int capacity) {
		int n = myTempQueue.size();
		int faults = 0;
		int hits = 0;

		ArrayList<Integer> cache = new ArrayList<Integer>(capacity);

		for (int i=0; i<n; i++ ) {
			int t = myTempQueue.get(i);

			if (cache.size() < capacity) {
				if (cache.contains(t) == false) {
					cache.add(0,t);
					faults++;
					System.out.print("Page faulted: "+t);
					System.out.print(" F |");
				}
				else {
					int temp = cache.indexOf(t);
					cache.remove(temp);
					cache.add(0,t);
					hits++;
					System.out.print("H ");
				}
			}
			else {
				if (cache.contains(t) == false) {
					cache.remove(cache.size()-1);
					cache.add(0,t);
					faults++;
					System.out.print("Page faulted: "+t);
					System.out.print(" F |");
					
				}
				else {
					int temp = cache.indexOf(t);
					cache.remove(temp);
					cache.add(0,t);
					hits++;
					System.out.print("H ");
				}
			}

			for (int j=0; j<cache.size(); j++ ) {
				System.out.print(cache.get(j)+" ");
			}
			System.out.println();
		}
		System.out.println();
		System.out.println("Total Page Faults: "+faults);
		System.out.println("Total Page Hits: "+hits);

		solve(cache,capacity);
	}
}