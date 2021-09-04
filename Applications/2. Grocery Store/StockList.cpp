#include "StockList.h"

int StockList::addStock(StockItem* item) {
	if (item != nullptr) {

		//check if already have quantities of this item
		StockItem* inStock = list->get(item);
		// If there are already stocks on this item, adjust the quantity
		if (inStock != nullptr) {
			item->adjustStock(inStock->availableQuantity());
		}
		list->addNewItem(item);
		return item->availableQuantity();
	}
	return 0;
}

int StockList::sellStock(string item, int quantity) {
	StockItem* inStock = list->get(item);

	if ((inStock != nullptr) && (quantity > 0)) {
		return inStock->finaliseStock(quantity);
	}
	return 0;
}

int StockList::reserveStock(string item, int quantity) {
	StockItem* inStock = list->get(item);
	if ((inStock != nullptr) && (quantity > 0)) {
		return inStock->reserveStock(quantity);
	}
	return 0;
}

int StockList::unreservedStock(string item, int quantity){
	StockItem* inStock = list->get(item);
	if ((inStock != nullptr) && (quantity > 0)) {
		return inStock->unreservedStock(quantity);
	}
	return 0;
}

void StockList::printList() {
	list->printList();
}

 

