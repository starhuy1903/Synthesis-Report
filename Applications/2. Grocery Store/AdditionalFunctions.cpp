#include "AdditionalFunctions.h"

void trimLeft(string& s) {
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == ' ') {
			s.erase(s.begin() + i);	// Deletes character at position i
			i--;
		}
		else break;
	}
}

void trimRight(string& s) {
	for (int i = s.length() - 1; i >= 0; i--) {
		if (s[i] == ' ') {
			s.erase(s.begin() + i);
		}
		else break;
	}
}

void trimMidCharacter(string& s) {
	if (s.empty())
		return;
	for (int i = 0; i < s.length() - 1; i++) {
		if (s[i] == ' ' && s[i + 1] == ' ') {
			s.erase(s.begin() + i);
			i--;
		}
	}
}

string trim(string s) {
	trimRight(s);
	trimLeft(s);
	trimMidCharacter(s);
	return s;
}

int makeValidItem(int numItem) {
	string s;
	int item;
	while (true) {
		cout << "\tItem: ";
		getline(cin, s);

		s = trim(s);
		if (s.empty())
			continue;

		item = stoi(s);
		// exit and make payment
		if (item == 0)
			return 0;

		if (item > 0 && item <= numItem) {
			return item;		
		}
		cout << "\tYour choice not valid. Please try again.\n";
	}
}

int makeValidQuantity() {
	string s;
	int quantity;
	while (true) {
		cout << "\tQuantity: ";
		getline(cin, s);

		s = trim(s);
		if (s.empty())
			continue;

		quantity = stoi(s);

		if (quantity > 0 && quantity < 10e6) {
			return quantity;
		}
		cout << "\tYour choice not valid. Please try again.\n";
	}
}

long int makeValidPrice() {
	string s;
	int price;
	while (true) {
		cout << "\tPrice: ";
		getline(cin, s);

		s = trim(s);
		if (s.empty())
			continue;

		price = stol(s);

		if (price >= 1000 && price < 10e9) {
			return price;
		}
		cout << "\tYour choice not valid. Please try again.\n";
	}
}