#include<iostream>
#include<vector>
#include<string>

using namespace std;

class process {
public:
	int id;
	vector<int> alloc;
	vector<int> max;
	vector<int> need;

	process (int x) {
		id = x;
	}
	int getId ();
};

class solver {
public:
	vector <process> tempQueue;
	vector <int> tempAvail;
	void calcState();
	void resourceReq();

	solver (vector <process> x, vector <int> y) {
		tempQueue = x;
		tempAvail = y;
	}
};

void printTable(vector <process>, vector <int>, int);

int main(int argc, char const *argv[]) {


	int n,m;

	cout << "Enter number of processes: ";
	cin >> n;
	cout << "Enter number of resources: ";
	cin >> m;

	vector <process> proQueue;
	vector <int> available;

	for (size_t i = 0; i < n; i++) {

		process temp(i);
		vector <int> talloc;
		vector <int> tmax;
		vector <int> tneed;

		cout << "\n--------\nProcess " << i << '\n';
		for (size_t j = 0; j < m; j++) {
			int t1,t2,t3;
			cout << "  R" << j << '\n';
			cout << "    Alloc: ";
			cin >> t1;
			cout << "    Max: ";
			cin >> t2;
			t3 = t2 - t1;

			temp.alloc.push_back(t1);
			temp.max.push_back(t2);
			temp.need.push_back(t3);
		}

		proQueue.push_back(temp);
	}

	while (true) {
		int op;
		while (true) {
			cout << "\n Select option:\n  1. Print Process Table\n  2. Show State\n  3. Resource Request\n  4. Exit\n\n# ";
			cin >> op;
			if (op==1) {
				printTable(proQueue,available,m);
				break;
			}
			else if (op==2) {
				break;
			}
			else if (op==3) {
				break;
			}
			else if (op==4) {
				cout << "\nTerminated successfully\n";
				return 0;
			}
			else {
				cout << "\nTry Again!\n";
			}
		}
	}

	return 0;
}

void solver::calcState() {
	
}

void solver::resourceReq() {

}

void printTable(vector <process> tempQueue, vector <int> tempAvail, int m) {
	cout << "\nProcess\tAlloc\tMax\tNeed\n";

	for (size_t l = 0; l < 3; l++) {
		cout << "\t";
		for (size_t i = 0; i < m; i++) {
			if (i==0)
				cout << "R" << i;
			else
				cout << " R" << i;
		}
	}

	cout << "\n";
	for (size_t i = 0; i < m; i++) {
		cout << "\n";
		cout << "P" << i << "\t";
		for (size_t j = 0; j < m; j++) {
			cout << tempQueue[i].alloc[j] << "  ";
		}
		cout << "\t";
		for (size_t j = 0; j < m; j++) {
			cout << tempQueue[i].max[j] << "  ";
		}
		cout << "\t";
		for (size_t j = 0; j < m; j++) {
			cout << tempQueue[i].need[j] << "  ";
		}
	}
	cout << "\n\n";
}
