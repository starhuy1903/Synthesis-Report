#include "Seat.h"

Seat* Seat::reserve() {
	if (!this->reserved) {
		this->reserved = true;
		cout << "\tSeat " << seatNumber << " reserved\n";
		return this;
	}
	return nullptr;
}

bool Seat::cancel() {
	if (this->reserved) {
		this->reserved = false;
		cout << "Reservation of seat " << seatNumber << " cancelled\n";
		return true;
	}
	return false;
}