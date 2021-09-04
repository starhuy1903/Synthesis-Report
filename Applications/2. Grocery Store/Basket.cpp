#include "Basket.h"

int Basket::addToBasket(StockItem* item, int quantity) {
	if ((item != nullptr) && (quantity > 0)) {
		int inBasket = list->get(item);
		list->put(item, inBasket + quantity);
		return inBasket + quantity;
	}
	return 0;
}

int Basket::removeFromBasket(StockItem* item, int quantity) {
	if ((item != nullptr) && (quantity > 0)) {
		int inBasket = list->get(item);
		int newQuantity = inBasket - quantity;

		if (newQuantity > 0) {
			list->put(item, newQuantity);
			return quantity;
		}
		else if (newQuantity == 0) {
			list->remove(item);
			return quantity;
		}
	}
	return 0;
}

string Basket::toString() {
	int numOrder = 1;
	int size = list->getSize();
	long int totalCost = 0;
	string s = "\n\tShopping basket contains " + to_string(size) + ((size == 1) ? " item" : " items") + "\n";
	ListNode* p = list->getHead();
	while (p != nullptr) {
		s = s + "\t" + to_string(numOrder++) + ". "
			+ p->item->toString()
			+ ". Quantity: " + to_string(p->value) + "\n";

		totalCost += p->item->getPrice() * p->value;
		p = p->next;
	}
	return s + "\t-------------------------------------\n"
		"\tTotal cost " + to_string(totalCost) + " dong";
}

void Basket::clearBasket() {
	delete list;
	list = nullptr;
}