#pragma once

#include "AdditionalFunctions.h"

#include "StockItem.h"

struct TreeNode {
	TreeNode* lchild;
	StockItem* item;
	TreeNode* rchild;
};

struct BST{
private:
	TreeNode* root;

	int size;

	string filename;

	TreeNode* createNewNode(StockItem* newItem);

	TreeNode* put(TreeNode* p, StockItem* newNode);

	StockItem* get(TreeNode* p, string nameItem);

	void readDatabase(string filename);

	void inOrder(TreeNode* p, ofstream& ofs);

public:
	BST(string filename){
		root = nullptr;
		this->filename = filename;
		readDatabase(filename);
		size = countItem(root);
	}

	void addNewItem(StockItem* newItem) {
		root = put(root, newItem);
	}
	
	StockItem* get(StockItem* item) {
		return get(root, item->getName());
	}
	StockItem* get(string nameItem) {
		return get(root, nameItem);
	}

	string* getItemNameList();
	
	void storeData(string filename);

	void printList();

	int countItem(TreeNode* p);
	
	TreeNode* getRoot() {
		return root;
	}

	int getSize() {
		return size;
	}
};

