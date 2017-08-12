// To find the data of the node where two linked lists merge

#include<iostream>
using namespace std;

struct node
{
	int data;
	struct node *next;
};

int findJoin(struct node *, struct node *);

int main ()
{
	int i,x,lenA,lenB,connect;
	struct node *curra=NULL;
	struct node *currb=NULL;
	struct node *tempa=NULL;
	struct node *tempb=NULL;
	struct node *firstnodea=NULL;
	struct node *firstnodeb=NULL;
	struct node *lasta=NULL;
	struct node *lastb=NULL;
	struct node *conna=NULL;
	
	cout<<"\n\nCreating linked list A";
	cout<<"\nLength of linked list A: ";
	cin>>lenA;
	
	for(i=0;i<lenA;i++)
	{
		curra=new node;
		curra->data=100+i+1;
		
		if (tempa==NULL)
		{
			firstnodea=curra;
			tempa=curra;
		}
		else
		{
			tempa->next=curra;
			tempa=curra;
			lasta=curra;
		}
	}
	
	cout<<endl;
	tempa=firstnodea;
	while (tempa!=NULL)
	{
		cout<<tempa->data<<" -> ";
		tempa=tempa->next;
	}
	
	cout<<"\n\nCreating linked list B";
	cout<<"\nLength of linked list B: ";
	cin>>lenB;
	
	for(i=0;i<lenB;i++)
	{
		currb=new node;
		currb->data=200+i+1;
		
		if (tempb==NULL)
		{
			firstnodeb=currb;
			tempb=currb;
		}
		else
		{
			tempb->next=currb;
			tempb=currb;
			lastb=currb;
		}
	}
	
	cout<<endl;
	tempb=firstnodeb;
	while (tempb!=NULL)
	{
		cout<<tempb->data<<" -> ";
		tempb=tempb->next;
	}
	
	cout<<"\n\nConnect last node of list B with which node of list A? ";
	cin>>x;
	
	tempa=firstnodea;
	for(i=0;i<x;i++)
	{
		conna=tempa;
		tempa=tempa->next;
	}
	
	cout<<"\nResultant A\n";
	tempa=firstnodea;
	for(i=0;tempa!=NULL;i++)
	{
		cout<<tempa->data<<" -> ";
		tempa=tempa->next;
	}
	cout<<"\n\nResultant B\n";
	
	lastb->next=conna;		//
	
	tempb=firstnodeb;
	for(i=0;tempb!=NULL;i++)
	{
		cout<<tempb->data<<" -> ";
		tempb=tempb->next;
	}
	
	
	
	connect=findJoin(firstnodea,firstnodeb);
	cout<<"\n\nConnecting Node value: "<<connect;
	
	cout<<endl<<endl;
	return 0;	
}

int findJoin(struct node *a, struct node *b)
{
	int x;
	struct node *ta=NULL;
	struct node *tb=NULL;
	tb=b;
	while (tb!=NULL)
	{
		ta=a;
		while (ta!=NULL)
		{
			if (tb==ta)
			{
				x=tb->data;
				return x;
			}
			ta=ta->next;
		}
		tb=tb->next;		
	}
	return -1;
}
