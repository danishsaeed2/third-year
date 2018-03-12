// Create a complete binary tree and create linked lists using nodes at the same levels

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

struct node
{
	int data;
	struct node *right = NULL;
	struct node *left = NULL;
	struct node *next = NULL;
};
struct node *root=NULL;

struct listnode
{
	int data;
	struct listnode *next = NULL;
};

void insertnode (struct node *temp);
void createlist (struct node *temp);
int n = 0;
int levels = 0;

struct listnode *gloStartlist;
struct listnode *gloTemplist;

int main()
{
	int check = 1;

	while(1)
	{
		if (root == NULL)
		{
			root = new node;
			insertnode(root);
	        cout << "# Root node."<<endl;
		}
		else
		{
			insertnode(root);
		}

		cout << "\nEnter another level? (0,1) ";
		cin >> check;

				cout<<"/nCheck";
		break;
	}

	cout << endl << endl;
	struct listnode *myTemp = gloStartlist;
	for (int i = 0; myTemp->next != NULL; ++i)
	{
		cout << myTemp->data << " -> ";
		myTemp = myTemp->next;
	}

	return 0;
}

void insertnode (struct node *temp)
{
	struct node *newTemp1 = new node;
	struct node *newTemp2 = new node;
	int myTempData;

	if (temp->left == NULL && temp->right == NULL)
	{
		cout << "\nEnter left value: ";
		cin >> myTempData;
		newTemp1 -> data = myTempData;
		temp -> left = newTemp1;

		cout << "Enter right value: ";
		cin >> myTempData;
		newTemp2 -> data = myTempData;
		temp -> right = newTemp2;

		n = n+2;

		return;
	}
	else
	{
		insertnode(temp->left);
		insertnode(temp->right);
	}
}

void createlist (struct node *temp)
{
	if (temp->left == NULL && temp->right == NULL)
	{
		struct listnode *tempListnode = new listnode;
		tempListnode->data = temp->left->data;

		if (gloStartlist = NULL)
		{
			gloStartlist = tempListnode;
		}
		else
		{
			gloTemplist->next = tempListnode;
		}

		gloTemplist = tempListnode;

		tempListnode = new listnode;
		tempListnode->data = temp->right->data;

		gloTemplist->next = tempListnode;
		gloTemplist = tempListnode;

		return;
	}
	else
	{
		createlist(temp->left);
		createlist(temp->right);
	}
}