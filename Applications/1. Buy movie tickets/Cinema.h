#pragma once
#include "Seat.h"

#include "Hashtable.h"

#include "AdditionalFunctions.h"

#define LOW 60000
#define NORMAL 80000
#define HIGH 100000

#define DISCOUNT_AMOUNT 50000
#define POINT_MILESTONE 10

struct Cinema {
private:
	string cinemaName;
	string movieName;
	Seat** seats;
	int seatsPerRow;
	int size = 0;
	int totalSoldTickets = 0;
	long int revenue = 0;
	// store information of customers
	Hashtable* HT;
public:
	// constructor 
	Cinema(string cinemaName, string movieName, int numRows, int seatsPerRow, string filename) {
		this->cinemaName = cinemaName;
		this->movieName = movieName;
		this->seats = new Seat * [numRows * seatsPerRow];
		this->seatsPerRow = seatsPerRow;
		
		HT = new Hashtable(filename);

		int lastRow = 'A' + (numRows - 1);
		for (char row = 'A'; row <= lastRow; row++) {
			for (int seatNum = 1; seatNum <= seatsPerRow; seatNum++) {
				long int price = NORMAL;
				int point = 2;
				if ((row < 'D') && (seatNum >= 4 && seatNum <= 9)) {
					price = HIGH;
					point++;
				}
				else if ((row > 'F') || (seatNum < 4 || seatNum > 9)) {
					price = LOW;
					point--;
				}
				string numStr = (seatNum > 9) ? to_string(seatNum) : '0' + to_string(seatNum);
				Seat* seat = new Seat(row + numStr, price, point);
				seats[size++] = seat;
			}
		}
	}

	Seat* reserveSeat(string seatNumber);

	void printSeats();

	void createNewMember(int numTickets);

	bool accumulatePoint(string ID, int point);

	// if customer has bought 
	long int discount(string ID, long int amount);

	void storeData() {
		HT->storeDatabase();
	}

	void setRevenue(long int amount) {
		this->revenue += amount;
	}

	void setTotalSoldTickets(int numTickets) {
		this->totalSoldTickets += numTickets;
	}

	int getSize() {
		return size;
	}

	string getCinemaName() {
		return cinemaName;
	}

	string getMovieName() {
		return movieName;
	}

	long int getRevenue() {
		return revenue;
	}

	int getTotalSoldTickets() {
		return totalSoldTickets;
	}
		
};

