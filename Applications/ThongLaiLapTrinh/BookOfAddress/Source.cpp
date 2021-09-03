#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Address
{
	string fname, lname;
	int num;
};
void readFromFile(Address*& Book, int& n, string filename)
{
	ifstream fin(filename, ios::in);

	fin >> n; fin.ignore();
	Book = new Address[n];

	for (int i = 0; i < n; i++)
	{
		getline(fin, Book[i].fname, ' ');
		getline(fin, Book[i].lname, ' ');
		fin >> Book[i].num; fin.ignore();
	}

	fin.close();
}
void listByFirstName(Address*& Book, int n)
{
	for (int i = 1; i < n; i++)
	{
		Address v = Book[i];
		int j = i - 1;
		while (j >= 0 && Book[j].fname > v.fname)
		{
			Book[j + 1] = Book[j];
			j--;
		}
		Book[j + 1] = v;
	}
}
void listByLastName(Address*& Book, int n)
{
	for (int i = 1; i < n; i++)
	{
		Address v = Book[i];
		int j = i - 1;
		while (j >= 0 && Book[j].lname > v.lname)
		{
			Book[j + 1] = Book[j];
			j--;
		}
		Book[j + 1] = v;
	}
}

void printAddress(Address* Book, int n)
{
	for (int i = 0; i < n; i++)
		cout << Book[i].fname << " " << Book[i].lname << " " << Book[i].num << endl;
}

int main()
{
	Address* Book = NULL;
	int n = 0;
	readFromFile(Book, n, "address.txt");

	listByFirstName(Book, n);
	printAddress(Book, n);

	cout << endl;

	listByLastName(Book, n);
	printAddress(Book, n);

	delete[]Book;
	return 0;
}