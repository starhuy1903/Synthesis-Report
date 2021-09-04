#pragma once
#include "Library.h"

struct Seat {
private:
	string seatNumber;
	long int price;
	int point;
	bool reserved = false;

public:
	Seat(string seatNumber, long int price, int point) {
		this->seatNumber = seatNumber;
		this->price = price;
		this->point = point;
	}

	Seat* reserve();

	bool cancel();

	long int getPrice() {
		return price;
	}

	bool isReserved() {
		return reserved;
	}

	string getSeatNumber() {
		return seatNumber;
	}

	int getPoint() {
		return point;
	}

};



