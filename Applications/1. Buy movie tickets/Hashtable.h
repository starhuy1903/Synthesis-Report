#pragma once
#include "Library.h"

#include "AdditionalFunctions.h"

#define SIZE 49999

#define PRIME 49993

struct Person {
	string name;
	string ID;
	int point;
};

struct Hashtable {
private:
	string filename;
	Person **customers;
	int size;
	// hash ID card 
	int convertStringToKey(string str);
	int Hash(long key);
	int PrimeHash(long key);
	int DoubleHash(long key);
	string hashID(string ID);

	Person* createNewPerson(string ID, string name, int point);
public:
	Hashtable(string filename) {
		customers = new Person * [SIZE];
		for (int i = 0; i < SIZE; i++) {
			customers[i] = nullptr;
		}
		this->filename = filename;
		int size = 0;
		readDatabase();
	}

	void readDatabase();

	void storeDatabase();

	void createNewPerson(int point);

	void insertNewPerson(Person* newPerson);

	Person* getCustomer(string ID);

	int getSize() {
		return size;
	}
};

