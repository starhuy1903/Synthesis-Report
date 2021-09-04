#pragma once

#include "StockItem.h"

#include "DoubleLinkedList.h"

struct Basket {

private:
	DLL* list;

public:
	Basket() {
		list = new DLL();
	}

	int addToBasket(StockItem* item, int quantity);

	int removeFromBasket(StockItem* item, int quantity);

	void clearBasket();

	string toString();

	DLL* getList() {
		return list;
	}
};

