#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

struct node
{
	string myClass;
	string value;
	struct node *next = NULL;
};

bool checkSize (struct node *);

int main()
{
	char cont;

	struct node *start = NULL;
	struct node *temp = NULL;
	struct node *curr = NULL; 

	cout << "\nCreating linked list" << endl;
	do
	{
		curr = new node;
		cout << "\nEnter class name : ";
		cin >> curr->myClass;
		cout << "Enter value : ";
		cin >> curr->value;

		if (start == NULL)
		{
			start = curr;
			temp = curr;
		}
		else
		{
			temp->next = curr;
			temp = curr;
		}

		cout << "\nAnother node? ";
		cin >> cont;

	} while (cont == 'y' || cont == 'Y');

	cout << "\n\n||||| Linked List Created |||||" << endl;

	temp = start;
	for (int i = 0; temp != NULL ; i++)
	{
		cout << "\n--------\n";
		cout << "Class: " << temp->myClass << endl;
		cout << "Value: " << temp->value;
		temp = temp->next;
	}

	cout << "\n\n||||| Linked List Ends |||||" << endl;

	vector <struct node *> newStarts;

	struct node *temptemp = NULL;
	struct node *last = NULL;
	temp = start;
	while (temp != NULL)
	{
		int flag = 0;
		int i; 
		for (i = 0; i < newStarts.size(); ++i)
		{
			if (temp->myClass == newStarts[i]->myClass)
			{
				flag = 1;
				temptemp = newStarts[i];
				struct node *t = newStarts[i];
				for (int j = 0; t!=NULL ; ++j)
				{
					temptemp = t;
					t=t->next;
				}
				break;
			}
		}
		
		if (flag == 0)
		{
			newStarts.push_back(NULL);
			int i = newStarts.size() - 1;
			newStarts[i] = start;
			temptemp = newStarts[i];
			temp = temp->next;
			start->next = NULL;
			start = temp;
		}

		if (temp == start)
		{
			temptemp->next = temp;
			temptemp = temp;
			temp = temp->next;
			start->next = NULL;
			start = temp;
		}
		else
		{
			temptemp->next = temp;
			temptemp = temp;
			last->next = temp->next;
			temp = temp->next;
			temptemp->next = NULL;
		}
	}

	cout << endl << endl;
	for (int i = 0; i<newStarts.size(); ++i)
	{
		cout << "\n\n||||| CLASS |||||" << endl;
		struct node *myTemp = newStarts[i];
		for (int i = 0; myTemp!=NULL; ++i)
		{
			cout << "\n--------\n";
			cout << "Class: " << myTemp->myClass << endl;
			cout << "Value: " << myTemp->value;
			myTemp = myTemp->next;
		}
	}
	cout << endl << endl;

	return 0;
}

bool checkSize (struct node *myStart)
{
	if (myStart == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
	return false;
}