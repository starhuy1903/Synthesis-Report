#include "Hashtable.h"

int Hashtable::convertStringToKey(string str) {
	int key = 0;
	for (int i = 0; i < str.length(); i++) {
		key += (char)str[i];
	}
	return (key > 0) ? key : -key;
}

int Hashtable::Hash(long key) {
	return key % SIZE;
}

int Hashtable::PrimeHash(long key) {
	return PRIME - (key % PRIME);
}

int Hashtable::DoubleHash(long key) {
	int idx = Hash(key);
	int i = 0;
	while (customers[(idx + i * PrimeHash(key)) % SIZE] != nullptr) {
		i++;
	}
	return (idx + i * PrimeHash(key)) % SIZE;
}

void Hashtable::readDatabase() {
	ifstream ifs(filename);
	
	if (ifs) {
		string s, text;
		string ID, name;
		int point;
		while (!ifs.eof()) {
			getline(ifs, s);

			s = trim(s);
			if (s.empty())
				continue;

			stringstream ss(s);
			
			// read ID number
			getline(ss, ID, '|');
			// read name
			getline(ss, name, '|');
			// read number of purchased tickets
			getline(ss, text);
			point = stoi(text);

			insertNewPerson(createNewPerson(ID, name, point));
		}
		ifs.close();
	}
	else {
		cout << filename << " could not be opened." << endl;
		exit(EXIT_FAILURE);
	}
}

void Hashtable::storeDatabase() {
	ofstream ofs(filename);
	if (ofs) {
		for (int i = 0; i < SIZE; i++) {
			if (customers[i] == nullptr)
				continue;

			ofs << customers[i]->ID << "|";
			ofs << customers[i]->name << "|";
			ofs << customers[i]->point << endl;
		}
		ofs.close();
	}
	else {
		cout << filename << " could not be opened." << endl;
		exit(EXIT_FAILURE);
	}	
}

void Hashtable::insertNewPerson(Person* newPerson) {
	int key = convertStringToKey(newPerson->ID);
	int idx = Hash(key);
	if (customers[idx] != nullptr)
		idx = DoubleHash(key);

	customers[idx] = newPerson;
	size++;
}

Person* Hashtable::getCustomer(string ID) {
	int key = convertStringToKey(ID);
	int idx = Hash(key);
	int i = 0;
	while (customers[(idx + i * PrimeHash(key)) % SIZE] != nullptr &&
		customers[(idx + i * PrimeHash(key)) % SIZE]->ID != ID) {
		i++;
	}
	return customers[(idx + i * PrimeHash(key)) % SIZE];
}

void Hashtable::createNewPerson(int point) {
	// input name
	string name = enterName();
	// input ID
	string ID = enterID();
	// insert into hashtable
	insertNewPerson(createNewPerson(ID, name, point));
}

Person* Hashtable::createNewPerson(string ID, string name, int point) {
	Person* temp = new Person();

	temp->ID = ID;
	temp->name = name;
	temp->point = point;
	return temp;
}