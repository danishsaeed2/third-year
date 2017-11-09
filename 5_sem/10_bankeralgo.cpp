#include<iostream>
#include<vector>

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
	vector <int> work;
	bool finish[5];
	void calcState();
	void resourceReq();

	solver (vector <process> x, vector <int> y) {
		tempQueue = x;
		tempAvail = y;
		work = tempAvail;
		for (size_t i = 0; i < 5; i++) {
			finish[i] = false;
		}
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

	cout << "\nEnter available resources:\n";
	for (size_t i = 0; i < m; i++) {
		int t;
		cout << "  R" << i << ": ";
		cin >> t;
		available.push_back(t);
	}

	while (true) {
		int op;
		while (true) {
			cout << "\n Select option:\n  1. Print Process Table\n  2. Show Safe Sequence\n  3. Resource Request\n  4. Exit\n\n# ";
			cin >> op;
			if (op==1) {
				printTable(proQueue,available,m);
				break;
			}
			else if (op==2) {
				solver solve(proQueue,available);
				solve.calcState();
				break;
			}
			else if (op==3) {
				solver solve(proQueue,available);
				solve.resourceReq();
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
	work = tempAvail;
	int m = tempAvail.size();
	cout << "\nSafe Sequence of Processes:\n";
	while (true) {
		int flag = 0;
		for (size_t i = 0; i < tempQueue.size(); i++) {
			if (finish[i] == false) {
				flag = 1;
				bool ntemp = true;
				for (size_t j = 0; j < m; j++) {
					if (tempQueue[i].need[j] > work[j]) {
						ntemp = false;
						break;
					}
				}
				if (finish[i] == false && ntemp == true) {
					for (size_t k = 0; k < m; k++) {
						work[k] = work[k] + tempQueue[i].alloc[k];
					}
					finish[i] = true;
					cout << "P" << i <<" - ";
				}
			}
		}
		if (flag == 0) {
			break;
		}
	}
	cout << endl;
}

void solver::resourceReq() {
	int p;
	int m = tempAvail.size();
	int r[m];

	cout << "Enter additional resource request:\n";
	cout << "Process: ";
	cin >> p;
	for (size_t i = 0; i < m; i++) {
		cout << "R" << i <<": ";
		cin >> r[i];
	}

	bool ntemp = true;
	for (size_t j = 0; j < m; j++) {
		if (tempQueue[p].need[j] < r[j]) {
			ntemp = false;
			break;
		}
	}

	if (ntemp == true) {
		bool atemp = true;
		for (size_t j = 0; j < m; j++) {
			if (tempAvail[j] < r[j]) {
				atemp = false;
				break;
			}
		}
		if (atemp == true) {
			for (size_t i = 0; i < m; i++) {
				tempAvail[i] = tempAvail[i] - r[i];
				tempQueue[p].alloc[i] = tempQueue[p].alloc[i] + r[i];
				tempQueue[p].need[i] = tempQueue[p].need[i] - r[i];
			}

			printTable(tempQueue,tempAvail,m);
			calcState();
		}
		else
			cout << "\nRequest must wait.\n";
	}
	else
		cout << "\nProcess requests resources more than maximum.\n";
}

void printTable(vector <process> tempQueue, vector <int> tempAvail, int m) {
	cout << "\nProcess\tAlloc\t\tMax\t\tNeed\n";

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
	for (size_t i = 0; i < tempQueue.size(); i++) {
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

