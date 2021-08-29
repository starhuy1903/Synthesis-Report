#include <iostream>

#include <fstream>

#include <string>

#include <sstream>

#include <iomanip>

#include <stack>

using namespace std;

#pragma warning(disable:4996)

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

struct Seat {
private:
	string seatNumber;
	double price;
	bool reserved = false;
public:
	Seat(string seatNumber, double price) {
		this->seatNumber = seatNumber;
		this->price = price;
	}

	Seat* reserve() {
		if (!this->reserved) {
			this->reserved = true;
			cout << "\tSeat " << seatNumber << " reserved\n";
			return this;
		}
		return nullptr;
	}

	bool cancel() {
		if (this->reserved) {
			this->reserved = false;
			cout << "Reservation of seat " << seatNumber << " cancelled\n";
			return true;
		}
		return false;
	}

	string getSeatNumber() {
		return seatNumber;
	}

	double getPrice() {
		return price;
	}

	bool isReserved() {
		return reserved;
	}
};

struct Theatre {
private:
	string theatreName;
	Seat** seats;
	int seatsPerRow;
	int size = 0;

public:
	Theatre(string theatreName, int numRows, int seatsPerRow) {
		this->seats = new Seat * [numRows * seatsPerRow];
		this->seatsPerRow = seatsPerRow;
		this->theatreName = theatreName;

		int lastRow = 'A' + (numRows - 1);
		for (char row = 'A'; row <= lastRow; row++) {
			for (int seatNum = 1; seatNum <= seatsPerRow; seatNum++) {
				double price = 12.00;

				if ((row < 'D') && (seatNum >= 4 && seatNum <= 9)) {
					price = 14.00;
				}
				else if ((row > 'F') || (seatNum < 4 || seatNum > 9)) {
					price = 7.00;
				}
				string numStr = (seatNum > 9) ? to_string(seatNum) : '0' + to_string(seatNum);
				Seat* seat = new Seat(row + numStr, price);
				seats[size++] = seat;
			}
		}
	}

	string getTheatreName() {
		return theatreName;
	}

	Seat* reserveSeat(string seatNumber) {
		// apply binary search
		int low = 0;
		int high = size - 1;

		while (low <= high) {
			int mid = (low + high) / 2;
			Seat* midVal = seats[mid];
			int cmp = midVal->getSeatNumber().compare(seatNumber);
			if (cmp < 0) {
				low = mid + 1;
			}
			else if (cmp > 0) {
				high = mid - 1;
			}
			else {
				return seats[mid]->reserve();
			}
		}
		cout << "\tThere is no seat " << seatNumber << endl;
		return nullptr;
	}

	void printSeats() {
		for (int i = 0; i < size; i++) {
			if (i % seatsPerRow == 0)
				cout << endl;
			if (!seats[i]->isReserved())
				cout << "\t" << seats[i]->getSeatNumber();
			else
				cout << "\t   ";
		}
		cout << endl;
	}

	int getSize() {
		return size;
	}

};

void runApp(Theatre* huy) {
	do {
		string s;
		double total = 0;
		bool continued = true;
		while (continued) {
			cout << "\t\t\t\t\t\t" << huy->getTheatreName() << " CINEMA\n";
			huy->printSeats();
			if (total != 0)
				cout << "\n\tThe pay process is not completed yet.\n";

			cout << "\n\tPlease, make choice your seat (one seat/choice | 0 to exit): ";
			getline(cin, s);
			s = trim(s);
			if (s == "0")
				return;
			s[0] = toupper(s[0]);

			Seat* seat = huy->reserveSeat(s);
			if (seat != nullptr) {

				total += seat->getPrice();

				char choice;
				cout << "\t1. Make payment\n";
				cout << "\t2. Book more\n";
				cout << "\t3. Cancel this seat and book more\n";
				cout << "\t4. Cancel this seat\n";
				cout << "\tPlease, Enter: ";
				cin >> choice; cin.ignore();
				switch (choice)
				{
				case '1': continued = false; break;

				case '2': break;

				case '3':
					seat->cancel();
					total -= seat->getPrice();
					break;

				default:
					seat->cancel();
					total -= seat->getPrice();
					if (total > 0) {
						continued = false;
						break;
					}
				}
			}
			else {
				cout << "\tSorry, seat already reserved or not exist"; cin.get();
			}
			system("cls");
		}

		cout << "\tPlease pay $" << setprecision(2) << fixed << total << "\n";
		do cout << "\tPress any key to complete";
		while (cin.get() != '\n');
		system("cls");
	} while (true);
}

int main() {
	Theatre* huy = new Theatre("HUY", 8, 12);
	runApp(huy);
	return 0;
}