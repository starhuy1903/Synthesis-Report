#include "Cinema.h"

Seat* Cinema::reserveSeat(string seatNumber) {
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

void Cinema::printSeats() {
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

bool Cinema::accumulatePoint(string ID, int point) {
	Person* temp = HT->getCustomer(ID);
	if (temp != nullptr) {
		temp->point += point;
		return true;
	}
	return false;	
}

long int Cinema::discount(string ID, long int amount) {
	Person* temp = HT->getCustomer(ID);
	if (temp->point >= POINT_MILESTONE) {
		temp->point -= POINT_MILESTONE;
		revenue -= DISCOUNT_AMOUNT;
		cout << "\tYou got a " << DISCOUNT_AMOUNT << " dong discount.\n";
		return amount - DISCOUNT_AMOUNT;
	}
	return amount;
}

void Cinema::createNewMember(int point) {
	HT->createNewPerson(point);
}