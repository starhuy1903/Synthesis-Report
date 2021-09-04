#include "Cinema.h"

#include "AdditionalFunctions.h"

void payment(Cinema* cinema, int numTickets, long int amountPay, int point){
	char isMember;
	cout << "\n\tAre you a member of " << cinema->getCinemaName() << " cinema yet? (1.Yes|0.No): ";
	cin >> isMember; cin.ignore();
	
	switch (isMember)
	{
	case '0': {
		cout << "\tDo you want to be a member of " << cinema->getCinemaName() << " cinema? (1.Yes|0.No): ";
		cin >> isMember; cin.ignore();
		// Customer will be become a member
		if (isMember == '1') {
			cinema->createNewMember(point);
			cout << "\tYou have become a member of " << cinema->getCinemaName() << " cinema. Thank you!\n";
		}
		else
			break;
	}
			// Customer is already member
	case '1': {
		int t = 0;
		while (true) {
			string ID = enterID();
			if (cinema->accumulatePoint(ID, point)) {
				amountPay = cinema->discount(ID, amountPay);
				break;
			}
			if (t == 3)
				break;

			cout << "\tYour payment was failed\n\n";
			t++;
		}
		break;
	}
	default:
		cout << "\tYour choice not valid. Please try again.";
		break;
	}
	// finish payment
	cout << "\tPlease pay " << amountPay << " DONG for " << numTickets;
	(numTickets > 1) ? cout << " tickets." : cout << " ticket.";
	cout << endl;

	cout << "\tYour payment was successful.";
	if (isMember == '1') {
		cout << " You have accumulated " << point;
		(point > 1) ? cout << " points." : cout << " point.";
	}
	cout << " Thank you!\n";
}

void printQuantity(Cinema* cinema) {
	cout << "\t\t\t" << cinema->getCinemaName() << " Cinema\n";
	cout << "\tTotal sold ticket is " << cinema->getTotalSoldTickets() << endl;
	cout << "\tRevenue is " << cinema->getRevenue() << " dong." << endl;
}

void runApp(Cinema* cinema) {
	string s;
	string bookedSeat;
	long int amountPay;
	bool continued;
	int numTickets;
	do {
		bookedSeat = "";
		amountPay = 0;
		continued = true;
		numTickets = 0;
		int point = 0;

		while (continued) {
			cout << "\t\t\t\t\t\t" << cinema->getCinemaName() << " CINEMA\n";
			cout << "\t\t Film: " << cinema->getMovieName() << endl;
			cinema->printSeats();
			if (amountPay > 0) {
				cout << "\n\tThe pay process is not completed yet.\n";
				cout << "\tThe booked seats: " << bookedSeat << endl;
			}
				
			cout << "\n\tPlease, make choice your seat (one seat/choice | 0 to exit): ";
			getline(cin, s);
			s = trim(s);
			// finish book seat
			if (s == "0") {
				cinema->storeData();
				system("cls");
				printQuantity(cinema);
				return;
			}
			// uppercase first character 	
			s[0] = toupper(s[0]);

			Seat* seat = cinema->reserveSeat(s);
			if (seat != nullptr) {
				amountPay += seat->getPrice();
				point += seat->getPoint();
				numTickets++;
				bookedSeat += " " + seat->getSeatNumber();

				char choice;
				cout << "\n\t1. Book more\n";
				cout << "\t2. Make payment\n";
				cout << "\t3. Cancel this seat and book more\n";
				cout << "\t4. Cancel this seat and make payment\n\n";
				cout << "\tPlease, Enter: ";
				cin >> choice; cin.ignore();

				switch (choice)
				{
					// book more 
				case '1': break;

					// make payment
				case '2': 
					continued = false;
					cinema->setTotalSoldTickets(numTickets);
					cinema->setRevenue(amountPay);
					break;

					// Cancel this seat and book more
				case '3':
					seat->cancel();
					amountPay -= seat->getPrice();
					point -= seat->getPoint();
					numTickets--;
					bookedSeat = bookedSeat.substr(0, bookedSeat.length() - 3);
					break;

					// Cancel this seat and make payment
				case '4':
					seat->cancel();
					amountPay -= seat->getPrice();
					point -= seat->getPoint();
					numTickets--;
					cinema->setTotalSoldTickets(numTickets);
					cinema->setRevenue(amountPay);
					if (amountPay > 0) {
						continued = false;
					}
					break;

				default:
					cout << "\tYour choice not valid. Please try again.";
					break;
				}
			}
			else {
				cout << "\tSorry, seat already reserved or not exist"; cin.get();
			}
			system("cls");
		}

		payment(cinema, numTickets, amountPay, point);
		cout << "\tPress any key to complete";
		cin.get();
		system("cls");
	} while (true);
}

int main() {
	string filename = "Customers.txt";
	string movieName = "Fast and Furious 9";
	Cinema* cinema = new Cinema("HUY", movieName, 8, 12, filename);
	runApp(cinema);
	return 0;
}