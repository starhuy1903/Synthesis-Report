#include "AdditionalFunctions.h"

#include "StockList.h"

#include "Basket.h"

#define MAX_ITEM 100

int sellItem(StockList* stockList, Basket* basket, string item, int quantity) {
	// retrieve the item from stock list
	StockItem* stockItem = stockList->get(item);

	if (stockItem == nullptr) {
		cout << "\tWe don't sell " << item << endl;
		return 0;
	}
	if (stockList->reserveStock(item, quantity) != 0) {
		return basket->addToBasket(stockItem, quantity);
	}
	return 0;
}

void removeItem(StockList* stockList, Basket* basket, string* selectedItem, int numSelectedItem) {

	int itemNum = makeValidItem(numSelectedItem);
	if (itemNum == 0)
		return;

	int quantity = makeValidQuantity();
	// retrieve the item from stock list
	StockItem* stockItem = stockList->get(selectedItem[itemNum - 1]);

	if (stockItem == nullptr) {
		cout << "\tWe don't sell " << itemNum << endl;
	}
	else if (stockList->unreservedStock(selectedItem[itemNum - 1], quantity) != 0) {
		if (basket->removeFromBasket(stockItem, quantity) != 0) {
			cout << "\tItem removal was successful"; cin.get();
			return;
		}
	}

	cout << "\tItem removal was unsuccessful"; cin.get();
}

int viewBasket(StockList* stockList, Basket* basket, string* selectedItem, int numSelectedItem) {
	char choice;
	while (true) {
		cout << "\t\tYOUR BASKET\n";
		cout << basket->toString() << "\n";

		cout << "\n\t1. Keep Shopping.\n";
		cout << "\t2. Make payment.\n";
		cout << "\t3. Remove item.\n";		
		cout << "\n\tYour choice: ";
		cin >> choice; cin.ignore();
		switch (choice)
		{
		case '1':
			return 1;

		case '2':
			return 2;

		case '3':
			removeItem(stockList, basket, selectedItem, numSelectedItem);
			break;

		default:
			cout << "\tYour choice not valid. Please try again.";
		}

		system("cls");
	}
}

void payment(Basket* basket, StockList* stockList) {
	DLL* itemList = basket->getList();
	ListNode* p = itemList->getHead();
	while (p != nullptr) {
		stockList->sellStock(p->item->getName(), p->value);
		p = p->next;
	}
	basket->clearBasket();
}

void runCustomizeItem(StockList* stockList) {
	
	int itemNum, quantity; // manager choice

	string* itemNameList = stockList->getItemNameList();
	int numItem = stockList->getSize();

	do {

		cout << "\t\t\t\t\t\tGROCERY STORE\n";
		cout << "\t\t\t\t\t\tCUSTOMIZE PRODUCT\n";

		// output all of items
		stockList->printList();
		cout << "\n\tMake choice item you want (one item/choice | 0 to quit)\n";

		// valid value of item information 
		itemNum = makeValidItem(numItem);
		// finish program
		if (itemNum == 0)
			return;

		StockItem* item = stockList->get(itemNameList[itemNum - 1]);
		if (item != nullptr) {
			char choice;
			cout << "\t1. Adjust the price of " << item->getName() << ".\n";
			cout << "\t2. Import more " << item->getName() << ".\n";
			cout << "\t0. Return.\n";
			cout << "\n\tYour choice: ";
			cin >> choice; cin.ignore();

			switch (choice)
			{
			case '1':
				cout << "\tOld price: " << item->getPrice() << "d.\n";
				//long int price = ;
				item->setPrice(makeValidPrice());
				cout << "\tSuccessful price adjustment.";
				break;

			case '2':
				cout << "\tOld quantity: " << item->getQuantityInStock() << endl;
				quantity = makeValidQuantity();
				if (item->adjustStock(quantity) != 0) {
					cout << "\tNew quantity: " << item->getQuantityInStock() << endl;
					cout << "\tSuccessful quantity adjustment.";
				}
				else
					cout << "\tThe quantity adjustment was unsuccessful.";

				break;

			default:
				return;
			}
		}
		else {
			cout << "\tThe adjustment failed."; 
		}
		cout << "(Enter to continue)";
		cin.get();
		system("cls");
	} while (true);
}

void printOptionToPurchase() {
	cout << "\n\t1. Keep Shopping\n";
	cout << "\t2. View Basket\n";
	cout << "\n\tYour choice: ";
}

void runSell(StockList* stockList) {
	string s;

	bool continued;

	string* itemNameList = stockList->getItemNameList();
	int numItem = stockList->getSize();

	int itemNum, quantity; // customer choice
	Basket* basket;
	string* selectedItem;
	int numSI;
	do {

		continued = true;
		basket = new Basket();
		selectedItem = new string[MAX_ITEM];
		numSI = 0; // number of selected item
		while (continued) {
			cout << "\t\t\t\t\t\tGROCERY STORE\n";
			// output all of items
			stockList->printList();

			if (numSI > 0) {
				cout << "\n\tThe pay process is not completed yet.\n";
			}

			cout << "\n\tMake choice item you want (one item/choice | 0 to exit)\n";

			// valid value of item information 
			itemNum = makeValidItem(numItem);
			// finish program
			if (itemNum == 0) {
				if (numSI > 0)
					cout << "\tPayment was unsuccessful."; cin.get();

				return;
			}
				
			
			quantity = makeValidQuantity();

			if (sellItem(stockList, basket, itemNameList[itemNum - 1], quantity) != 0) {
				selectedItem[numSI++] = itemNameList[itemNum - 1];

				// make choices after buying a product
				char choice;
				printOptionToPurchase();
				cin >> choice; cin.ignore();
				// process 
				switch (choice) {
					// 1. Continue Shopping
				case '1':
					break;
					// 2. View basket
				case '2':
					system("cls");

					if (viewBasket(stockList, basket, selectedItem, numSI) != 1)
						continued = false;
					
					break;
				default:
					cout << "\tYour choice not valid. Please try again."; cin.get();
					break;
				}
				
			}
			else {
				cout << "\tWe're sorry, but we only have "
					<< stockList->get(itemNameList[itemNum - 1])->getQuantityInStock()
					<< " " << stockList->get(itemNameList[itemNum - 1])->getName();
				(stockList->get(itemNameList[itemNum - 1])->getQuantityInStock() > 1) ? cout << "s" : cout << "";
				cout << " left.";

				cin.get();
			}

			system("cls");

		}
		payment(basket, stockList);
		cout << "\tPayment was successful.\n";
		cout << "\tPress any key to complete";
		cin.get();
		system("cls");
	} while (true);
}

void runApp(StockList* stockList) {
	char processChoice;
	do {
		cout << "\t\t\t\t\t\tGROCERY STORE\n";
		cout << "\t1. Sell\n";
		cout << "\t2. Customize item\n";
		cout << "\t0. Quit\n";
		cout << "\n\tYour choice: ";
		cin >> processChoice; cin.ignore();

		switch (processChoice)
		{
		case '1': 
			system("cls");
			runSell(stockList);
			break;

		case '2':
			system("cls");
			runCustomizeItem(stockList);
			break;

		case '0': 
			stockList->storeData();
			return;

		default:
			cout << "\tYour choice not valid. Please try again.";
			cin.get();
			break;
		}

		system("cls");
	} while (true);
}

int main() {
	string filename = "Items.txt";

	StockList* stockList = new StockList(filename);

	runApp(stockList);

	return 0;
}