// Binary Search Tree 
// Data Structure Project
// Poorya Mohammadi Nasab  9621160025

//#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

class Node {
private :
	int value;
	Node* Right;
	Node* Left;

public:
	Node(int t) {
		value = t;
		Left = NULL;
		Right = NULL;
	}
	bool add(int t) {
		if (t==value)
		{
			return false;
		}
		else if (t < value)
		{
			if (Left == NULL) {
				Left = new Node(t);
				return true;
			}
			else
			{
				Left->add(t);
			}
		}
		else if (t > value){
			if (Right == NULL) {
				Right = new Node(t);
				return true;
			}
			else
			{
				return Right->add(t);
			}
		}
		return false;
	}
	int get_value() {
		return value;
	}
	void set_left(Node* tmp) {
		Left = tmp;
	}
	void set_right(Node* tmp) {
		Right = tmp;
	}
	Node* get_left() {
		return Left;
	}
	Node* get_right() {
		return Right;
	}
	void set_value(int t) {
		value = t;
	}
};

void postorder(Node* Root);
void preorder(Node* Root);
void inorder(Node* Root);
void levelorder(Node* Root);
int get_height(Node* Root);
void printlevel(Node* Root, int level);
void deleteNode(int t,Node* Root,Node* father);
int minimun(Node* Root);
void minorder(Node* Root);
static bool flag;
static int arr[10000];
static int count;
bool delete_only_root;

class BST {
private : 

	Node* Root;

public:

	// Constractor

	BST() {
		Root = NULL;
	}

	// Add Node
	bool insert(int value) {
		if (Root==NULL)
		{
			Root = new Node(value);
			return true;
		}
		else
		{
			return Root->add(value);
		}
	}
	// survey Delete node
	void remove(int t) {
		Node* tmp;
		tmp = Root;
		deleteNode(t, tmp,NULL);
		if (delete_only_root==true)
		{
			Root = NULL;
		}
		delete_only_root = false;
	}
	// Level Order
	void LEVEL() {
		Node* tmp;
		tmp = Root;
		flag = false;
		levelorder(tmp);
		cout << endl;
	}
	// In Order
	void IN() {
		Node* tmp;
		tmp = Root;
		flag = false;
		inorder(tmp);
		cout << endl;
	}
	// Pre Order
	void PRE() {
		Node* tmp;
		tmp = Root;
		flag = false;
		preorder(tmp);
		cout << endl;
	}
	// Post Order
	void POST() {
		Node* tmp;
		tmp = Root;
		flag = false;
		postorder(tmp);
		cout << endl;
	}
	//minVal

};

void postorder(Node* Root) {
	if (Root==NULL)
	{
		return;
	}
	postorder(Root->get_left());
	postorder(Root->get_right());
	//if (flag == true)
	{
	//	cout << ",";//cout << ", ";
	}
	flag = true;
	cout << Root->get_value()<<",";
	
}

void preorder(Node* Root) {
	if (Root==NULL)
	{
		return;
	}
	//if (flag == true)
	{
	//	cout << ",";//	cout << ", ";
	}
	flag = true;
	cout << Root->get_value()<<",";
	preorder(Root->get_left());
	preorder(Root->get_right());
}

void inorder(Node* Root) {
	if (Root==NULL)
	{
		return;
	}
	inorder(Root->get_left());
	//if (flag == true)
	{
	//	cout << ",";//cout << ", ";
	}
	flag = true;
	cout << Root->get_value()<<",";
	inorder(Root->get_right());
}

void levelorder(Node* Root) {
	if (Root == NULL)
	{
		return;
	}
	Node* tmp = Root;
	int H=	get_height(tmp);
	for (int i = 1; i <= H; i++)
	{
		printlevel(Root, i);
	}
}

void printlevel(Node* Root, int level) {
	if (Root==NULL)
	{
		return;
	}
	if (level==1)
	{
	//	if (flag == true)
		{
			//cout << ",";//	cout << ", ";
		}
		flag = true;
		cout << Root->get_value()<<",";
	}
	if (level>1)
	{
		printlevel(Root->get_left(), level - 1);
		printlevel(Root->get_right(), level - 1);
	}
}

int get_height(Node* Root) {
	if (Root==NULL)
	{
		return 0;
	}
	int Lh = get_height(Root->get_left());
	int Rh = get_height(Root->get_right());
	if (Lh > Rh)
	{
		return Lh + 1;
	}
	else
	{
		return Rh + 1;
	}
}


void deleteNode(int t, Node* Root,Node* father) {
	if (Root == NULL)
	{
		return;
	}
	if (t < Root->get_value())
	{
		deleteNode(t, Root->get_left(), Root);
	}
	else if (t > Root->get_value())
	{
		deleteNode(t, Root->get_right(), Root);
	}
	else
	{
		if (Root->get_left()==NULL && Root->get_right()==NULL)
		{
			if (father==NULL)
			{
				/*int remove_val = minimun(Root);
				deleteNode(remove_val, Root, father);
				Root->set_value(remove_val);*/
				delete_only_root = true;
				return;
			}
			if ( father->get_right()!=NULL && Root->get_value() == father->get_right()->get_value())
			{
				father->set_right(NULL);
			}
			else if (father->get_left()!=NULL && Root->get_value() == father->get_left()->get_value())
			{
				father->set_left(NULL);
			}
		}
		else if ( Root->get_left() == NULL && Root->get_right() != NULL)//chap khali
		{
			if (father == NULL)
			{
				int remove_val = minimun(Root);
				deleteNode(remove_val, Root, father);
				Root->set_value(remove_val);
				return;
			}
			if ( father->get_left()!=NULL && Root->get_value()==father->get_left()->get_value())
			{
				father->set_left(Root->get_right());
				delete Root;
			}
			else if (father->get_right()!=NULL && Root->get_value() == father->get_right()->get_value())
			{
				father->set_right(Root->get_right());
				delete Root;
			}
		}
		else if (Root->get_left() != NULL && Root->get_right() == NULL)//rast khali
		{
			if (father == NULL)
			{
				int remove_val = minimun(Root);
				deleteNode(remove_val, Root, father);
				Root->set_value(remove_val);
				return;
			}
			if (father->get_left() != NULL && Root->get_value() == father->get_left()->get_value())
			{
				father->set_left(Root->get_left());
				delete Root;
			}
			else if (father->get_right() != NULL && Root->get_value() == father->get_right()->get_value())
			{
				father->set_right(Root->get_left());
				delete Root;
			}
		}
		else //joft por
		{
			int remove_val = minimun(Root);
			deleteNode(remove_val, Root, father);
			Root->set_value(remove_val);
		}
	}
}

int minimun(Node* Root) {
	::count = 0;
	Node* tmp = Root;
	minorder(tmp);
	for (int i = 0; i < ::count; i++)
	{
		if (arr[i]==Root->get_value() && i!=::count-1)
		{
			return arr[i + 1];
		}
		else if (arr[i] == Root->get_value() && i == ::count - 1)
		{
			return arr[i - 1];
		}
	}
}

void minorder(Node* Root) {
	if (Root == NULL)
	{
		return;
	}
	minorder(Root->get_left());
	arr[::count] = Root->get_value();
	::count++;
	minorder(Root->get_right());
}

int main()
{
	BST MY_BST;
	while (1)
	{
		string a;
		string b;
		cin >> a;
		if (a=="insert")
		{
			bool sign = false;
			cin >> b;
			int k = 1;
			int input = 0;
			int p;
			for (int i = 0; b[i] ; i++)
			{
				if (b[i]=='-')
				{
					sign = true;
					continue;
				}
				p = b[i] - 48;
				input = input * 10 + p;
			}
			if (sign==true)
			{
				input = input*-1;
			}
			MY_BST.insert(input);
			continue;
		}
		else if (a=="delete")
		{
			bool sign = false;
			cin >> b;
			int k = 1;
			int input = 0;
			int p;
			for (int i = 0; b[i]; i++)
			{
				if (b[i]=='-')
				{
					sign = true;
					continue;
				}
				p = b[i] - 48;
				input = input * 10 + p;
			}
			if (sign==true)
			{
				input = input*-1;
			}
			MY_BST.remove(input);
			continue;
		}
		else if (a=="levelorder")
		{
			MY_BST.LEVEL();
			continue;
		}
		else if (a=="inorder")
		{
			MY_BST.IN();
			continue;
		}
		else if (a=="preorder")
		{
			MY_BST.PRE();
			continue;
		}
		else if (a=="postorder")
		{
			MY_BST.POST();
			continue;
		}
		else if (a=="end")
		{
			break;
		}
		else
		{
			continue;
		}
	}
    return 0;
}

