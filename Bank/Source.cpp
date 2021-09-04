#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;


#define WAY 3
#define MIN ((WAY - 1)/2)

struct trans
{
	string id;
	string action;
	int amount;
};

typedef struct historyNode
{
	trans data;
	bool color;
	historyNode *left;
	historyNode *right;
	historyNode* parent;
} H;

struct historyList
{
	H* root;
	int count;
};

struct account
{
	string username;
	int amount;
	historyList *history;
};

typedef struct accountnode
{
	account data[WAY - 1];
	accountnode* child[WAY];
	int count;
	accountnode* parent;
	bool isLeaf;
} A;

struct accountList
{
	A* root;
	int count;
};

A* create_A_node()
{
	A* newnode = new A;
	for (int i = 0; i < WAY; i++) newnode->child[i] = NULL;
	newnode->count = 0;
	newnode->parent = NULL;
	newnode->isLeaf = 0;
	return newnode;
}

// Btree

bool search_in_node(account key, A* curr, int& pos)
{
	pos = 0;
	// find the first key in node that is >= key, 
	while ((pos < curr->count) && (key.username > curr->data[pos].username)) pos++;
	// if key > all values in node return 0, pos is position of the last child in node
	if (pos == curr->count) return 0;
	// if key is found, return 1;
	if (key.username == curr->data[pos].username) return 1;
	// else return 0, pos is now position of the child node that might contain key
	return 0;
}

A* Bsearch(account key, A* curr, int& pos)
{
	// reach NULL node mean the key is not found in the tree, return NULL
	if (curr == NULL) return NULL;

	// if key is found in the current node return the current node, pos value will be ignore
	if (search_in_node(key, curr, pos)) return curr;
	// child[pos] is now the possible child to contain key, call recursive to this child
	return Bsearch(key, curr->child[pos], pos);
}

int findChildPos(A* child, A* parent)
{
	// find the position of child in parent's child array
	for (int i = 0; i <= parent->count; i++)
	{
		if (parent->child[i] == child) return i;
	}
	return -1;
}

void insert_in_node(A* curr, account key, A* rightC)
{
	int pos;
	search_in_node(key, curr, pos);

	// shift value > key to the right
	for (int j = curr->count; j > pos; j--)
	{
		curr->data[j] = curr->data[j - 1];
		curr->child[j + 1] = curr->child[j];
	}

	curr->data[pos] = key; // add key

	curr->child[pos + 1] = rightC;
	if (rightC != NULL) rightC->parent = curr;
	curr->count++; // update count value
}

account split_node(A* curr, A*& rightC, A* oldRightC, account key)
{
	rightC = new A;
	rightC->isLeaf = curr->isLeaf;

	if (key.username < curr->data[WAY - MIN - 2].username)
	{
		account midvalue = curr->data[WAY - MIN - 2];
		rightC->count = MIN;
		for (int i = 0; i < MIN; i++)
		{
			rightC->data[i] = curr->data[WAY - MIN - 1 + i];
			rightC->child[i] = curr->child[WAY - MIN - 1 + i];
			if (rightC->child[i] != NULL) rightC->child[i]->parent = rightC;
		}
		rightC->child[rightC->count] = curr->child[curr->count];
		if (rightC->child[rightC->count] != NULL) rightC->child[rightC->count]->parent = rightC;

		curr->count -= (MIN + 1);
		return midvalue;
	}
	else if (key.username > curr->data[WAY - MIN - 1].username)
	{
		account midvalue = curr->data[WAY - MIN - 1];
		rightC->count = MIN - 1;
		for (int i = 0; i < MIN - 1; i++)
		{
			rightC->data[i] = curr->data[WAY - MIN + i];
			rightC->child[i] = curr->child[WAY - MIN + i];
			if (rightC->child[i] != NULL) rightC->child[i]->parent = rightC;
		}
		rightC->child[rightC->count] = curr->child[curr->count];
		if (rightC->child[rightC->count] != NULL) rightC->child[rightC->count]->parent = rightC;

		curr->count -= MIN;
		return midvalue;
	}
	else
	{
		rightC->count = MIN;
		for (int i = 0; i < MIN; i++)
		{
			rightC->data[i] = curr->data[WAY - MIN - 1 + i];
			rightC->child[i + 1] = curr->child[WAY - MIN + i];
			if (rightC->child[i + 1] != NULL) rightC->child[i + 1]->parent = rightC;
		}
		rightC->child[0] = oldRightC;
		if (oldRightC != NULL) oldRightC->parent = rightC;

		curr->count -= MIN;

		return key;
	}
}

A* newRoot(A* leftC, A* rightC, account key)
{
	A* newroot = create_A_node();
	newroot->count = 1;
	newroot->data[0] = key;
	newroot->child[0] = leftC;
	newroot->child[1] = rightC;
	leftC->parent = newroot;
	rightC->parent = newroot;
	return newroot;
}

void insert_at_node(A* curr, account key, A* rightC, accountList *aroot)
{
	if (curr->count < WAY - 1)
	{
		insert_in_node(curr, key, rightC);
	}
	else
	{
		A* oldrightC = rightC;
		account midvalue = split_node(curr, rightC, oldrightC, key);
		if (curr->parent != NULL)
		{
			insert_at_node(curr->parent, midvalue, rightC, aroot);
		}
		else
		{
			aroot->root = newRoot(curr, rightC, midvalue);
		}

		if (key.username < midvalue.username) insert_in_node(curr, key, oldrightC);
		else if (key.username > midvalue.username) insert_in_node(rightC, key, oldrightC);
	}
}

bool Binsert(accountList *aroot, account key)
{
	if (aroot->root == NULL)
	{
		aroot->root = create_A_node();
		aroot->root->isLeaf = 1;
		aroot->root->count = 1;
		aroot->root->data[0] = key;
		aroot->count++;
		return 1;
	}

	A* temp = aroot->root;
	// find a leaf node to insert key
	while (!temp->isLeaf)
	{
		int pos;
		if (search_in_node(key, temp, pos)) return 0;
		else temp = temp->child[pos];
	}

	insert_at_node(temp, key, NULL, aroot);
	aroot->count++;
	return 1;
}

A* left_replace(A* curr, account& replacekey)
{
	// find the largest value in this sub tree
	// get the position of the largest value in current node
	int pos = curr->count - 1;

	// if value[pos] still have right child, it is not the largest value 
	if (curr->child[pos + 1] != NULL)
	{
		return left_replace(curr->child[pos + 1], replacekey);
	}
	else
	{
		// else return the current node
		replacekey = curr->data[pos];
		return curr;
	}
}

A* right_replace(A* curr, account& replacekey)
{
	// the first value is the smallest value in current node 
	// if the first value still have left child, it is not the smallest value 
	if (curr->child[0] != NULL)
	{
		return right_replace(curr->child[0], replacekey);
	}
	else
	{
		// else return the current node
		replacekey = curr->data[0];
		return curr;
	}
}

void fixCase1(A* curr, A* leftsib)
{
	for (int i = curr->count; i > 0; i--)
	{
		curr->data[i] = curr->data[i - 1];
		curr->child[i + 1] = curr->child[i];
	}
	curr->child[1] = curr->child[0];

	curr->data[0] = curr->parent->data[findChildPos(curr, curr->parent) - 1];
	curr->parent->data[findChildPos(curr, curr->parent) - 1] = leftsib->data[leftsib->count - 1];
	curr->child[0] = leftsib->child[leftsib->count];
	if (curr->child[0] != NULL) curr->child[0]->parent = curr;

	curr->count++;
	leftsib->count--;
}

void fixCase2(A* curr, A* rightsib)
{
	curr->data[curr->count] = curr->parent->data[findChildPos(curr, curr->parent)];
	curr->parent->data[findChildPos(curr, curr->parent)] = rightsib->data[0];
	curr->child[curr->count + 1] = rightsib->child[0];
	if (curr->child[curr->count + 1] != NULL) curr->child[curr->count + 1]->parent = curr;

	for (int i = 0; i < rightsib->count - 1; i++)
	{
		rightsib->data[i] = rightsib->data[i + 1];
		rightsib->child[i] = rightsib->child[i + 1];
	}
	rightsib->child[rightsib->count - 1] = rightsib->child[rightsib->count];

	curr->count++;
	rightsib->count--;
}

void fixCase34(A* left, A* right)
{
	left->data[left->count] = left->parent->data[findChildPos(left, left->parent)];
	left->count++;

	A* parent = left->parent;
	int i = findChildPos(left, parent);
	while (i < parent->count - 1)
	{
		parent->data[i] = parent->data[i + 1];
		parent->child[i + 1] = parent->child[i + 2];
		i++;
	}
	parent->count--;

	i = 0;
	while (i < right->count)
	{
		left->data[left->count] = right->data[i];
		left->child[left->count] = right->child[i];
		if (right->child[i] != NULL) right->child[i] = left;
		left->count++;
		i++;
	}
	left->child[left->count] = right->child[i];
	if (right->child[i] != NULL) right->child[i] = left;

	delete right;
}

void deleteFix(A*& curr, accountList *aroot)
{
	bool flag = 0;
	if (!(findChildPos(curr, curr->parent) == 0))
	{
		A* leftsib = curr->parent->child[findChildPos(curr, curr->parent) - 1];
		if (leftsib->count > MIN)
		{
			fixCase1(curr, leftsib);
			flag = 1;
		}
	}
	if ((!flag) && (!(findChildPos(curr, curr->parent) > curr->parent->count)))
	{
		A* rightsib = curr->parent->child[findChildPos(curr, curr->parent) + 1];
		if (rightsib->count > MIN)
		{
			fixCase2(curr, rightsib);
			flag = 1;
		}
	}

	if (!flag)
	{
		if (!(findChildPos(curr, curr->parent) > curr->parent->count))
		{
			A* rightsib = curr->parent->child[findChildPos(curr, curr->parent) + 1];
			fixCase34(curr, rightsib);
			if ((curr->parent != aroot->root) && (curr->parent->count < MIN)) deleteFix(curr->parent, aroot);
		}
		else
		{
			A* leftsib = curr->parent->child[findChildPos(curr, curr->parent) - 1];
			fixCase34(leftsib, curr);
			if ((leftsib->parent != aroot->root) && (leftsib->parent->count < MIN)) deleteFix(leftsib->parent, aroot);
		}
	}

	if (aroot->root->count == 0)
	{
		A* temp = aroot->root;
		aroot->root = aroot->root->child[0];
		delete temp;
	}
}

void delete_in_node(A* curr, account key)
{
	int i = 0;
	while (curr->data[i].username != key.username) i++;
	while (i < curr->count - 1)
	{
		curr->data[i] = curr->data[i + 1];
		i++;
	}
	curr->count--;
}

bool Bdelete(A* curr, accountList *aroot, account key)
{
	if ((curr == NULL) || (aroot->root == NULL)) return 0;
	A* temp = curr;
	int pos;
	while (temp != NULL)
	{
		if (search_in_node(key, temp, pos)) break;
		else temp = temp->child[pos];
	}
	if (temp == NULL) return 0;

	if (temp->child[pos] != NULL)
	{
		account replacekey;
		A* alternode = left_replace(temp->child[pos], replacekey);
		temp->data[pos] = replacekey;
		Bdelete(alternode, aroot, replacekey);
	}
	else if (temp->child[pos + 1] != NULL)
	{
		account replacekey;
		A* alternode = right_replace(temp->child[pos + 1], replacekey);
		temp->data[pos] = replacekey;
		Bdelete(alternode, aroot, replacekey);
	}
	else
	{
		delete_in_node(temp, key);
		if ((temp != aroot->root)&&(temp->count < MIN)) deleteFix(temp, aroot);
	}

	return 1;
}

// RB tree

H* createHNODE(trans data)
{
	H* newNODE = new H;
	newNODE->data = data;
	newNODE->color = 1;
	newNODE->left = NULL;
	newNODE->right = NULL;
	newNODE->parent = NULL;
	return  newNODE;
}

H* BSTsearch(H* curr, trans key)
{
	if (curr == NULL) return NULL;
	if (curr->data.id == key.id) return curr;
	else if (curr->data.id > key.id) return BSTsearch(curr->left, key);
	else return BSTsearch(curr->right, key);
}

void reColoring(H* curr)
{
	curr->color = (curr->color) ? 0 : 1;
}

void leftRotate(historyList *hroot, H* curr)
{
	H* n1 = curr->right;
	H* n2 = n1->left;

	curr->right = n2;
	if (n2 != NULL) n2->parent = curr;
	n1->parent = curr->parent;
	if (n1->parent == NULL) hroot->root = n1;
	else if (curr == curr->parent->left) curr->parent->left = n1;
	else curr->parent->right = n1;
	n1->left = curr;
	curr->parent = n1;
}

void rightRotate(historyList *hroot, H* curr)
{
	H* n1 = curr->left;
	H* n2 = n1->right;

	curr->left = n2;
	if (n2 != NULL) n2->parent = curr;
	n1->parent = curr->parent;
	if (n1->parent == NULL) hroot->root = n1;
	else if (curr == curr->parent->left) curr->parent->left = n1;
	else curr->parent->right = n1;
	n1->right = curr;
	curr->parent = n1;
}

void RBinsertFixing(historyList *hroot, H* curr)
{
	while ((curr->parent != NULL) && (curr->parent->color) && (curr->parent->parent != NULL))
	{
		if (curr->parent == curr->parent->parent->left)
		{
			H* n1 = curr->parent->parent->right;
			if ((n1 == NULL) || (!n1->color))
			{
				if (curr == curr->parent->right)
				{
					curr = curr->parent;
					leftRotate(hroot, curr);

					reColoring(curr->parent);
					reColoring(curr->parent->parent);
					rightRotate(hroot, curr->parent->parent);
				}
				else
				{
					reColoring(curr->parent);
					reColoring(curr->parent->parent);
					rightRotate(hroot, curr->parent->parent);
				}
			}
			else
			{
				reColoring(curr->parent);
				reColoring(curr->parent->parent);
				reColoring(n1);
				curr = curr->parent->parent;
			}
		}
		else
		{
			H* n1 = curr->parent->parent->left;
			if ((n1 == NULL) || (!n1->color))
			{
				if (curr == curr->parent->left)
				{
					curr = curr->parent;
					rightRotate(hroot, curr);

					reColoring(curr->parent);
					reColoring(curr->parent->parent);
					leftRotate(hroot, curr->parent->parent);
				}
				else
				{
					reColoring(curr->parent);
					reColoring(curr->parent->parent);
					leftRotate(hroot, curr->parent->parent);
				}
			}
			else
			{
				reColoring(curr->parent);
				reColoring(curr->parent->parent);
				reColoring(n1);
				curr = curr->parent->parent;
			}
		}
	}
	hroot->root->color = 0;
}

void RBinsert(historyList *hroot, trans data)
{
	H* temp = hroot->root;
	H* temppa = NULL;

	while (temp != NULL)
	{
		temppa = temp;
		if (data.id < temp->data.id) temp = temp->left;
		else temp = temp->right;
	}

	H* newNODE = createHNODE(data);
	newNODE->parent = temppa;

	if (temppa == NULL) hroot->root = newNODE;
	else if (data.id < temppa->data.id) temppa->left = newNODE;
	else temppa->right = newNODE;

	hroot->count++;
	RBinsertFixing(hroot, newNODE);
}

H* findLeftestNODE(H* curr)
{
	if (curr->left == NULL) return curr;
	else return findLeftestNODE(curr->left);
}

H* findSibling(H* curr)
{
	if (curr->parent == NULL) return NULL;
	if (curr == curr->parent->left) return curr->parent->right;
	return curr->parent->left;
}

H* findNODEtoReplace(H* curr)
{
	if ((curr->left != NULL) && (curr->right != NULL))
	{
		return findLeftestNODE(curr->right);
	}

	if ((curr->left == NULL) && (curr->right == NULL)) return NULL;

	if (curr->left != NULL) return curr->left;
	return curr->right;
}

void fixDoubleBlack(historyList *hroot, H* curr)
{
	if (curr->parent == NULL) return;

	H* sibling = findSibling(curr), * parent = curr->parent;

	if (sibling == NULL) fixDoubleBlack(hroot, parent);
	else
	{
		if (sibling->color)
		{
			parent->color = 1;
			sibling->color = 0;
			if (sibling == sibling->parent->left) rightRotate(hroot, parent);
			else leftRotate(hroot, parent);
			fixDoubleBlack(hroot, curr);
		}
		else
		{
			if ((sibling->left != NULL) && (!sibling->left->color))
			{
				if (sibling == sibling->parent->left)
				{
					sibling->left->color = sibling->color;
					sibling->color = parent->color;
					rightRotate(hroot, parent);
				}
				else
				{
					sibling->left->color = parent->color;
					rightRotate(hroot, sibling);
					leftRotate(hroot, parent);
				}
				parent->color = 0;
			}
			else if ((sibling->right != NULL) && (!sibling->right->color))
			{
				if (sibling == sibling->parent->left)
				{
					sibling->right->color = parent->color;
					leftRotate(hroot, sibling);
					rightRotate(hroot, parent);
				}
				else
				{
					sibling->right->color = sibling->color;
					sibling->color = parent->color;
					leftRotate(hroot, parent);
				}
				parent->color = 0;
			}
			else
			{
				sibling->color = 1;
				if (!parent->color)
				{
					fixDoubleBlack(hroot, parent);
				}
				else
				{
					parent->color = 0;
				}
			}
		}
	}
}

void deleteNODE(H* curr, historyList *hroot)
{
	H* replaceN = findNODEtoReplace(curr);

	bool bothNODEareblack = ((!curr->color) && ((replaceN == NULL) || (!replaceN->color)));

	if (replaceN == NULL)
	{
		if (curr == hroot->root) hroot->root == NULL;
		else
		{
			if (bothNODEareblack) fixDoubleBlack(hroot, curr);
			else
			{
				if (findSibling(curr) != NULL) findSibling(curr)->color = 1;
			}
		}

		if (hroot->root != NULL)
		{
			if (curr == curr->parent->left) curr->parent->left = NULL;
			else curr->parent->right = NULL;
		}
		delete curr;
		return;
	}

	if ((curr->left == NULL) || (curr->right == NULL))
	{
		if (curr == hroot->root)
		{
			curr->data = replaceN->data;
			curr->left = NULL;
			curr->right = NULL;
			delete replaceN;
		}
		else
		{
			if (curr == curr->parent->left) curr->parent->left = replaceN;
			else curr->parent->right = replaceN;
			replaceN->parent = curr->parent;
			delete curr;

			if (bothNODEareblack) fixDoubleBlack(hroot, replaceN);
			else replaceN->color = 0;
		}
		return;
	}

	curr->data = replaceN->data;
	deleteNODE(replaceN, hroot);
}

bool RBdelete(historyList *hroot, trans key)
{
	H* temp = hroot->root;

	while (temp != NULL)
	{
		if (temp->data.id == key.id) deleteNODE(temp, hroot);
		else if (temp->data.id > key.id) temp = temp->left;
		else temp = temp->right;
	}

	return 0;
}

//

accountList* readfile(string filename)
{
	ifstream ifs(filename);
	if (ifs)
	{
		accountList* aroot = new accountList;
		aroot->root = NULL;
		aroot->count = 0;

		string s;
		getline(ifs, s);

		int accCOUNT = stoi(s);

		for(int i = 0; i < accCOUNT; i++)
		{
			account newacc;
			string s1,s2;
			getline(ifs, s1);
			stringstream ss1(s1);
			getline(ss1, newacc.username, ' ');
			getline(ss1, s2, ' ');
			newacc.amount = stoi(s2);
			getline(ss1, s2);
			int hisCOUNT = stoi(s2);
			newacc.history = new historyList;
			newacc.history->root = NULL;
			newacc.history->count = 0;

			for (int j = 0; j < hisCOUNT; j++)
			{
				trans newtrans;
				string s3, s4;
				getline(ifs, s3);
				stringstream ss3(s3);
				getline(ss3, newtrans.id, ' ');
				getline(ss3, newtrans.action, ' ');
				getline(ss3, s4);
				newtrans.amount = stoi(s4);

				RBinsert(newacc.history, newtrans);
			}

			Binsert(aroot, newacc);

		}

		return aroot;
	}

	return NULL;
}

void printRBtree(ofstream& ofs, H* root)
{
	if (root == NULL) return;

	printRBtree(ofs, root->left);
	ofs << root->data.id << " " << root->data.action << " " << root->data.amount << endl;
	printRBtree(ofs, root->right);
}

void stdoutRBtree(H* root)
{
	if (root == NULL) return;

	stdoutRBtree(root->left);
	cout << "Id: " << root->data.id << "\taction: " << root->data.action << "\t\tammount: " << root->data.amount << endl;
	stdoutRBtree(root->right);
}

void printBtree(ofstream &ofs,A *root)
{
	if (root == NULL) return;
	int count = 0;
	while (count < root->count)
	{
		printBtree(ofs, root->child[count]);
		ofs << root->data[count].username << " " << root->data[count].amount << " " << root->data[count].history->count << endl;
		printRBtree(ofs, root->data[count].history->root);
		count++;
	}
	printBtree(ofs, root->child[count]);
}

void savefile(accountList *aroot)
{
	string filename;
	cout << "Enter output file name: ";
	cin.ignore(1);
	getline(cin, filename);
	ofstream ofs(filename);
	ofs << aroot->count << endl;
	printBtree(ofs, aroot->root);
}


//


void search_for_account(accountList* aroot)
{
	account user;
	cin.ignore();
	cout << "Enter username: ";
	getline(cin, user.username);
	int pos;
	A* result = Bsearch(user, aroot->root, pos);
	if (result == NULL) cout << "\nUsername not found.";
	else
	{
		char choice;
		cout << "Choose your action :\n1.View profile.\n2.Search for a transaction.\n";
		cin >> choice;
		if (choice == '1')
		{
			cout << "\nUsername: " << result->data[pos].username << "\nBank account amount: " << result->data[pos].amount << "\nHistory :\n";
			stdoutRBtree(result->data[pos].history->root);
		}
		else
		{
			trans tra;
			cout << "Enter transfer id: ";
			cin.ignore(1);
			getline(cin, tra.id);
			H* result1 = BSTsearch(result->data[pos].history->root, tra);
			if (result1 == NULL) cout << "\nTranfer id not found.";
			else
			{
				cout << "\nId: " << result1->data.id << "\taction: " << result1->data.action << "\t\tammount: " << result1->data.amount << endl;
			}
		}
	}
}

void add_account(accountList* aroot)
{
	account newuser;
	cin.ignore(1);
	while (1)
	{
		cout << "Enter new username: ";
		getline(cin, newuser.username);
		int pos;
		if (!Bsearch(newuser, aroot->root, pos)) break;
		cout << "\nUsername is already taken.\n";
	}

	newuser.history = new historyList;
	newuser.history->count = 0;
	newuser.history->root = NULL;
	newuser.amount = 0;
	Binsert(aroot, newuser);
	cout << "Complete!\n";
}

void delete_account(accountList* aroot)
{
	account tobedelete;
	cin.ignore(1);
	cout << "Enter username: ";
	getline(cin, tobedelete.username);
	if (Bdelete(aroot->root, aroot, tobedelete))
	{
		aroot->count--;
		cout << "\nComplete!";
	}
	else cout << "\nUsername not found.";
}

bool menu(accountList *aroot)
{
	char choice = '\0';
	while ((choice < 49) || (choice > 53))
	{
		system("CLS");
		cout << "Choose your action:\n1.Search for profile\n2.Create new profile.\n3.Delete profile.\n4.Save file.\n5.Exit\n";
		cin >> choice;
	}

	system("CLS");
	switch (choice)
	{
	case '1':
		search_for_account(aroot);
		break;
	case '2':
		add_account(aroot);
		break;
	case '3':
		delete_account(aroot);
		break;
	case '4':
		savefile(aroot);
		break;
	case '5': 
		return 0;
	default:
		break;
	}
	return 1;
}



int main()
{
	string filename = "input.txt";
	accountList *root = readfile(filename);

	while (1)
	{
		system("CLS");
		if (!menu(root)) break;;
		char choice;
		cout << "Continue ? (Y/N)";
		cin >> choice;
		if (toupper(choice) == 'N') break;
	}

	return 0;
}




