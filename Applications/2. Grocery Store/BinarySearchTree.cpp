#include "BinarySearchTree.h"

// read data from file
void BST::readDatabase(string filename) {
	ifstream ifs(filename);
	if (ifs) {
		string s, text;
		string nameItem;
		long int price;
		int quantity;

		while (!ifs.eof()) {
			getline(ifs, s);
			s = trim(s);

			if (s.empty())
				continue;

			stringstream ss(s);
			// 1. read name item
			getline(ss, nameItem, '|');
			// 2. read price of item
			getline(ss, text, '|');
			price = stol(text);
			// 3. read quantity of item
			getline(ss, text);
			quantity = stoi(text);

			addNewItem(new StockItem(nameItem, price, quantity));
		}
		ifs.close();
	}
	else {
		cout << filename << " could not be opened." << endl;
		exit(EXIT_FAILURE);
	}
}

TreeNode* BST::put(TreeNode* p, StockItem* newItem) {
	if (p == nullptr) {
		TreeNode* temp = createNewNode(newItem);
		return temp;
	}

	if (newItem->getName() < p->item->getName()) {
		p->lchild = put(p->lchild, newItem);
	}
	else if (newItem->getName() > p->item->getName()) {
		p->rchild = put(p->rchild, newItem);
	}
	return p;
}

StockItem* BST::get(TreeNode* p, string nameItem) {
	if (p == nullptr)
		return nullptr;

	if (nameItem == p->item->getName()) {
		return p->item;
	}
	else if (nameItem < p->item->getName()) {
		return get(p->lchild, nameItem);
	}
	else {
		return get(p->rchild, nameItem);
	}
}

TreeNode* BST::createNewNode(StockItem* newItem) {
	TreeNode* newNode = new TreeNode;
	newNode->item = newItem;
	newNode->lchild = newNode->rchild = nullptr;
	return newNode;
}

void BST::inOrder(TreeNode* p, ofstream& ofs) {
	if (p != nullptr) {
		inOrder(p->lchild, ofs);

		ofs << p->item->getName() << "|";
		ofs << p->item->getPrice() << "|";
		ofs << p->item->getQuantityInStock() << endl;

		inOrder(p->rchild, ofs);
	}
}

// store data back to file
void BST::storeData(string filename) {
	ofstream ofs(filename);

	if (ofs) {
		TreeNode* p = root;
		inOrder(p, ofs);

		cout << "\tSuccessfully save data\n";
		ofs.close();
	}
	else {
		cout << filename << " could not be opened." << endl;
		exit(EXIT_FAILURE);
	}
}

void BST::printList() {
	stack<TreeNode*> stk;
	TreeNode* p = root;
	int numOrder = 1;
	int breakLine = 0;

	while (p != nullptr || !stk.empty()) {
		while (p != nullptr) {
			stk.emplace(p);
			p = p->lchild;
		}

		p = stk.top();
		stk.pop();

		if (breakLine % 4 == 0)
			cout << endl;
		breakLine++;
		// output item and price
		string output = to_string(numOrder++) + ". " +
			p->item->getName() + ": " +
			to_string(p->item->getPrice()) + "d";

		cout << "|" << output;

		for (int i = 0; i < (25 - output.length()); i++) {
			cout << " ";
		}
		
		p = p->rchild;

	}
	cout << endl;
}

string* BST::getItemNameList() {
	stack<TreeNode*> stk;

	string* itemNameList = new string[size + 2];
	int numOrder = 0;

	TreeNode* p = root;

	while (p != nullptr || !stk.empty()) {
		if (p != nullptr) {
			stk.emplace(p);
			p = p->lchild;
		}
		else {
			p = stk.top();
			stk.pop();

			itemNameList[numOrder++] = p->item->getName();
		 
			p = p->rchild;
		}
	}
	return itemNameList;
}

int BST::countItem(TreeNode* p) {
	if (p != nullptr)
		return countItem(p->lchild) + countItem(p->rchild) + 1;
	return 0;
}