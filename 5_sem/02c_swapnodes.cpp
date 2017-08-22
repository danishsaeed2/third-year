#include<iostream>
using namespace std;

struct node
{
	int data;
	struct node *next;
};

int main ()
{
	int i;
	int length;
	cout<<"\nCreating linked list";
	cout<<"\nLength of linked list: ";
	cin>>length;
	
	struct node *curr=NULL;
	struct node *temp=NULL;
	struct node *firstnode=NULL;
	struct node *check=NULL;
	struct node *a=NULL;
	struct node *b=NULL;
	struct node *c=NULL;
	struct node *d=NULL;
	
	for(i=0;i<length;i++)
	{
		curr=new node;
		curr->data=i+1;
		
		if (temp==NULL)
		{
			firstnode=curr;
			temp=curr;
		}
		else
		{
			temp->next=curr;
			temp=curr;
		}
	}
	
	cout<<endl;
	temp=firstnode;
	while (temp!=NULL)
	{
		cout<<temp->data<<" ";
		temp=temp->next;
	}
	
	cout<<endl;
	
	temp=firstnode;
	
	if (length%2==0)
	{
		while (temp!=NULL)
		{
			if (a==NULL)
			{
				a=temp;
				b=temp->next;
				c=b->next;
				firstnode=b;
				a->next=c;
				b->next=a;
			}
			else
			{
				b=temp;
				c=temp->next;
				d=c->next;
			
				a->next=c;
				c->next=b;
				b->next=d;
			}
			a=temp;
			temp=temp->next;		
		}
	}
	else
	{
		while (temp->next!=NULL)
		{
			if (a==NULL)
			{
				a=temp;
				b=temp->next;
				c=b->next;
				firstnode=b;
				a->next=c;
				b->next=a;
			}
			else
			{
				b=temp;
				c=temp->next;
				d=c->next;
			
				a->next=c;
				c->next=b;
				b->next=d;
			}
			a=temp;
			temp=temp->next;		
		}
	}
	
	
	cout<<endl;
	temp=firstnode;
	while (temp!=NULL)
	{
		cout<<temp->data<<" ";
		temp=temp->next;
	}
	
	return 0;
}
