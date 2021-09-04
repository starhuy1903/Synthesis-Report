#include "StockItem.h"

int StockItem::adjustStock(int quantity) {
	int newQuantity = this->quantityInStock + quantity;
	if (newQuantity >= 0) {
		this->quantityInStock = newQuantity;
		return quantity;
	}
	return 0;
}

int StockItem::reserveStock(int quantity) {
	if (quantity <= availableQuantity()) {
		reserved += quantity;
		return quantity;
	}
	return 0;
}

int StockItem::unreservedStock(int quantity) {
	if (quantity <= reserved) {
		reserved -= quantity;
		return quantity;
	}
	return 0;
}

int StockItem::finaliseStock(int quantity) {
	if (quantity <= reserved) {
		quantityInStock -= quantity;
		reserved -= quantity;
		return quantity;
	}
	return 0;
}