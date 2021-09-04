#pragma once
#include "StockItem.h"

#include "AdditionalFunctions.h"

struct ListNode {
	StockItem* item;
	int value;
	ListNode* next;
	ListNode* prev;
};
struct DLL {
	
private:
	ListNode* head, * tail;

	ListNode* createNewNode(StockItem* item, int value);
	
public:
	DLL() {
		head = tail = nullptr;
	}

	void put(StockItem* item, int value);

	int get(StockItem* item);

	void remove(StockItem* item);

	int getSize();

	ListNode* getHead() {
		return head;
	}

};

