#pragma once
#include "Library.h"

struct StockItem {
private:
	string name;
	long int price;
	int quantityInStock = 0;
	int reserved = 0;

public:
	StockItem(string name, long int price, int quantityStock) {
		this->name = name;
		this->price = price;
		this->quantityInStock = quantityStock;
	}

	string getName() {
		return name;
	}

	long int getPrice() {
		return price;
	}

	int getQuantityInStock() {
		return quantityInStock;
	}

	int availableQuantity() {
		return quantityInStock - reserved;
	}

	void setPrice(long int price) {
		if (price > 0) {
			this->price = price;
		}
	}

	int adjustStock(int quantity);

	int reserveStock(int quantity);

	int unreservedStock(int quantity);

	int finaliseStock(int quantity);

	string toString() {
		return this->name + " : price " + to_string(this->price);
	}
};

