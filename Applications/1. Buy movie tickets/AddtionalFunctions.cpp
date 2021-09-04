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

bool validID(string& ID) {
	ID = trim(ID);
	if (ID.empty())
		return false;

	for (int i = 0; i < ID.length(); i++) {
		if (!isdigit(ID[i]))
			return false;
	}
	return true;
}

bool validName(string& name) {
	name = trim(name);
	if (name.empty())
		return false;

	bool upper = true;
	for (int i = 0; i < name.length(); i++) {
		if (!isalpha(name[i])) {
			if (!isspace(name[i]))
				return false;
			upper = true;
			continue;
		}
		if (upper) {
			name[i] = toupper(name[i]);
			upper = false;
		}
	}
	return true;
}

string enterID() {
	string ID;
	string mess = "";
	while (true) {
		cout << "\tPlease enter " << mess << "your ID: ";
		getline(cin, ID);
		if (validID(ID))
			break;

		mess = "again ";
	}
	return ID;
}

string enterName() {
	string name, mess = "";
	while (true) {
		cout << "\tPlease enter " << mess << "your name: ";
		getline(cin, name);
		if (validName(name))
			break;

		mess = "again ";
	}
	return name;
}