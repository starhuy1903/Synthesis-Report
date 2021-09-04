#pragma once
#include "StockItem.h"

#include "BinarySearchTree.h"

struct StockList{
private:
	BST* list;

	string filename;

public:
	StockList(string filename) {
		this->filename = filename;
		list = new BST(filename);
	}

	int addStock(StockItem* item);

	int sellStock(string item, int quantity);

	int reserveStock(string item, int quantity);

	int unreservedStock(string item, int quantity);

	void printList();

	void storeData() {
		list->storeData(filename);
	}

	StockItem* get(string nameItem) {
		return list->get(nameItem);
	}

	string* getItemNameList() {
		return list->getItemNameList();
	}

	int getSize() {
		return list->getSize();
	}
};

