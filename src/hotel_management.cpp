#include<iostream>
#include<fstream>
#ifdef _WIN32
#include <Windows.h>
#else
#include <chrono>
#include <thread>
void Sleep(unsigned long milliseconds) { std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds)); }
#endif
#include <cstdlib>
void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#endif
}
#include<string>
using namespace std;
int choice;
int roomnumber;
string password = "1234";
string temp;

enum type_bed {
	king,
	queen,
	single
};
struct room {
	int room_number = 0;
	int beds = 0;
	int start[3] = { 0 };///array that 0 is the index of days 1 month and 2 is year
	int end[3] = { 0 };
	int price = 0;
	type_bed bedtype = single;
	int bookingid = -1;//not booked: -1 , booked: 1 , checked in: 2 
};
room rooms[100];
int currentRoom = 0;

void SYSTEM();///el function el asasia el fi el main
void INVENTORY_TASK();//fiha switch case btaat el inventory task
void HOTEL_RESRVATIONS();//fiha el switch case btaat el hotel reservations
bool ADD_ROOM(room& r);//tzwd room fi el array
bool DELETE_ROOM(room r);//btms7 el room mn el array w bt shift 3lshan el current room
bool SAVE_INVENTORY();//output file
int CALCULATE_BILL(room& r);//bt7sb el s3r related to el type and the number of beds and el period
void ADD_ROOM_INFO(room& x);//sub function lazmtha enk tdkhl el info btaat el function abl el add
bool BOOKING(room& r);//bt7ot fiha el start date w el end date w btghir el booking id b 1
int SEARCH_INDEX(int targetRoomNumber);//btdwr 3la el index btaat el room mn el room number
bool CHECK_OUT(room& r);//btshil el start date w el end date w btkhli el booking id b -1 tani
bool CHECK_IN(room& r);//btshof lw el room already booked w btghir el booking id b 2
void LOAD_ROOM();//input file
bool PASSWORD();
void loading(int length, int duration);
const int monthDays[12] = { 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
///check for the leap year
int countLeapYearDays(int d[]) {
	int years = d[2];
	if (d[1] <= 2)
		years--;
	return ((years / 4) - (years / 100) + (years / 400));
}
//calculate the difference between 2 days
int countNoOfDays(int date1[], int date2[]) {
	long int dayCount1 = (date1[2] * 365);
	dayCount1 += date1[1] > 1 ? monthDays[date1[1] - 2] : 0;
	dayCount1 += date1[0];
	dayCount1 += countLeapYearDays(date1);
	long int dayCount2 = (date2[2] * 365);
	dayCount2 += date2[1] > 1 ? monthDays[date2[1] - 2] : 0;
	dayCount2 += date2[0];
	dayCount2 += countLeapYearDays(date2);
	return (abs(dayCount1 - dayCount2));
}



int main() {
	loading(50, 100);
	LOAD_ROOM();
	for (;;) {

		SYSTEM();
	}

}

void SYSTEM() {

	do {
		cout << "********************************" << endl;
		cout << "Welcome Back!" << endl;
		cout << "1)Inventory Task" << endl;
		cout << "2)Hotel Reservations" << endl;
		cout << "0)exit" << endl;
		cout << "********************************" << endl;

		cin >> choice;
		switch (choice) {
		case 1:
			clearScreen();
			INVENTORY_TASK();
			break;
		case 2:
			clearScreen();
			HOTEL_RESRVATIONS();
			break;
		case 0:
			exit(0);
		default:
			clearScreen();
			cout << "ERROR:choose a number(1,2)" << endl;

		}
	} while (choice != 1 && choice != 2);

}

void INVENTORY_TASK() {
	///if the password is correct it will enter the function and if not for 3 times you will get blocked
	if (PASSWORD()) {
		clearScreen();
		do
		{
			cout << "********************************" << endl;
			cout << "1)add room" << endl;
			cout << "2)delete room" << endl;
			cout << "3)save inventory to file" << endl;
			cout << "4)change password" << endl;
			cout << "5)back" << endl;
			cout << "********************************" << endl;
			cin >> choice;
			room r;
			switch (choice) {
			case 1:
				clearScreen();
				//it asks the user to enter the info of the room
				ADD_ROOM_INFO(r);
				//enter the info to the array and checks if its added
				if (ADD_ROOM(r)) {
					cout << "the room is added successfully" << endl;
				}
				else {
					cout << "ERROR:the room is not added" << endl;
				}
				Sleep(2000);
				clearScreen();
				break;
			case 2:
				clearScreen();
				cout << "enter the number of the room" << endl;
				cin >> roomnumber;
            if (SEARCH_INDEX(roomnumber) < 0) {
                cout << "Room not found." << endl;
                break;
            }
				//check if the room exist and if it exists it deletes the room
				if (DELETE_ROOM(rooms[SEARCH_INDEX(roomnumber)])) {
					cout << "the room is deleted successfully" << endl;
				}
				else {
					cout << "ERROR:the room is not deleted" << endl;
				}
				Sleep(1000);
				clearScreen();
				break;
			case 3:
				clearScreen();
				if (SAVE_INVENTORY()) {
					cout << "saved successfully" << endl;
				}
				else {
					cout << "ERROR:failed to save" << endl;
				}
				Sleep(1000);
				clearScreen();
				break;
			case 4:

				clearScreen();

				cout << "enter the new password" << endl;
				cin >> temp;
				//checks if the new password equal to the new password or not and it cannot be the same as the old password
				if (temp != password) {
					clearScreen();
					password = temp;
					cout << "password has been changed successufully" << endl;
					Sleep(2000);
					clearScreen();
				}
				else {
					while (temp == password) {
						clearScreen();
						cout << "old password cannot be the new password" << endl;
						cout << "enter the new password" << endl;
						cin >> temp;
						if (temp != password) {
							clearScreen();
							password = temp;
							temp = "0";
							cout << "password has been changed successufully" << endl;
							Sleep(2000);
							clearScreen();
						}
					}
				}


				break;
			case 5:
				clearScreen();
				SYSTEM();
				break;
			default:
				clearScreen();
				cout << "ERROR:enter a number (1,2,3)" << endl;
			}
		} while (choice != 1 && choice != 2 && choice != 3);
	}
	else {
		cout << "you are blocked" << endl;
		exit(0);
	}


}

void HOTEL_RESRVATIONS() {
	string cont;
	do {
		cout << "********************************" << endl;
		cout << "1)booking" << endl;
		cout << "2)check in" << endl;
		cout << "3)check out" << endl;
		cout << "4)calculate bill" << endl;
		cout << "5)back" << endl;
		cout << "********************************" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			clearScreen();
			cout << "enter the number of the room" << endl;
			cin >> roomnumber;
            if (SEARCH_INDEX(roomnumber) < 0) {
                cout << "Room not found." << endl;
                break;
            }
			//check if the room is either booked or checked in and it its neither it book it
			if (BOOKING((rooms[SEARCH_INDEX(roomnumber)]))) {
				cout << "room is booked successfully" << endl;
			}
			else {
				cout << "failed to book the room" << endl;
			}
			Sleep(2000);
			clearScreen();
			break;
		case 2:
			clearScreen();
			cout << "enter the number of the room" << endl;
			cin >> roomnumber;
            if (SEARCH_INDEX(roomnumber) < 0) {
                cout << "Room not found." << endl;
                break;
            }
			if (CHECK_IN(rooms[SEARCH_INDEX(roomnumber)])) {
				cout << "check in successfully" << endl;
			}
			else {
				cout << "failed to check in" << endl;
			}
			Sleep(2000);
			clearScreen();
			break;
		case 3:
			clearScreen();
			cout << "enter the room number" << endl;
			cin >> roomnumber;
            if (SEARCH_INDEX(roomnumber) < 0) {
                cout << "Room not found." << endl;
                break;
            }
			if (CHECK_OUT((rooms[SEARCH_INDEX(roomnumber)]))) {
				cout << "checked out successfully" << endl;
			}
			else {
				cout << "failed to check out" << endl;
			}
			Sleep(2000);
			clearScreen();

			break;
		case 4:
			clearScreen();
			cout << "enter the room number" << endl;
			cin >> roomnumber;
            if (SEARCH_INDEX(roomnumber) < 0) {
                cout << "Room not found." << endl;
                break;
            }
			cout << "the price of the given room: $" << CALCULATE_BILL((rooms[SEARCH_INDEX(roomnumber)])) << endl;
			cout << "enter any key to continue" << endl;
			cin >> cont;
			clearScreen();
			break;
		case 5:
			clearScreen();
			SYSTEM();
			break;
		default:
			clearScreen();

			cout << "ERROR:enter a number(1,2,3,4)" << endl;

		}
	} while (choice != 1 && choice != 2 && choice != 3 && choice != 4);

}
bool ADD_ROOM(room& r) {
	////3lshan a3rf wslt el maximum rooms number wla laa
	if (currentRoom < 100 && r.room_number > 0 && r.beds >= 1 && r.beds <= 3 && SEARCH_INDEX(r.room_number) == -1) {

		rooms[currentRoom] = r;
		currentRoom++;
		return 1;
	}
	else
		return 0;


}
bool DELETE_ROOM(room r) {
	if (r.beds != 0) {
		r.beds = 0;
		r.bookingid = -1;
		r.end[0] = 0;
		r.end[1] = 0;
		r.end[2] = 0;
		r.start[0] = 0;
		r.start[1] = 0;
		r.start[2] = 0;
		r.price = 0;
		for (int i = SEARCH_INDEX(r.room_number) + 1; i < 100; i++) {
			//shifts the room to adjust the current room variable
			rooms[i - 1] = rooms[i];

		}
		for (int i = 0; i < 100; i++) {
			if (rooms[i].beds == 0) {
				//the first room that got no beds will put the current room at it
				currentRoom = i;
				break;
			}
		}
		r.room_number = 0;
		return 1;

	}
	else {
		return 0;
	}

}

int CALCULATE_BILL(room& r) {

	int period = countNoOfDays(r.start, r.end);
	int bed = 0, type = 0;
	if (r.beds == 1) {
		bed = 20;
	}
	else if (r.beds == 2) {
		bed = 25;
	}
	else if (r.beds == 3) {
		bed = 30;
	}
	if (r.bedtype == king) {
		type = 20;
	}
	else if (r.bedtype == queen) {
		type = 10;
	}
	else if (r.bedtype == single) {
		type = 5;
	}
	r.price = bed * type;
	return r.price * period;



}
void ADD_ROOM_INFO(room& x) {
	int num;
	cout << "enter the room number" << endl;
	cin >> x.room_number;
	cout << "enter the number of bed" << endl;
	cin >> x.beds;
	cout << "enter the type of the beds(0=king,1=queen,2=single)" << endl;
	cin >> num;
	if (num < 0 || num > 2) { x.beds = 0; return; }
	if (num == 0)
	{
		x.bedtype = king;
	}
	else if (num == 1) {
		x.bedtype = queen;
	}
	else if (num == 2) {
		x.bedtype = single;
	}


}
bool BOOKING(room& r) {
	if (r.start[0] == 0 && r.end[0] == 0 && r.room_number != 0) {
		r.bookingid = 1;
		cout << "enter the start date" << endl;
		cout << "(dd) ";
		cin >> r.start[0];
		cout << "(mm) ";
		cin >> r.start[1];
		cout << "(yy) ";
		cin >> r.start[2];
		cout << "enter the end date" << endl;
		cout << "(dd) ";
		cin >> r.end[0];
		cout << "(mm) ";
		cin >> r.end[1];
		cout << "(yy) ";
		cin >> r.end[2];

        auto validDate = [](int date[]) {
            if (date[2] < 1 || date[1] < 1 || date[1] > 12) return false;
            int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
            bool leap = date[2] % 400 == 0 || (date[2] % 4 == 0 && date[2] % 100 != 0);
            if (leap) days[1] = 29;
            return date[0] >= 1 && date[0] <= days[date[1]-1];
        };
        bool ordered = r.end[2] > r.start[2] || (r.end[2] == r.start[2] &&
            (r.end[1] > r.start[1] || (r.end[1] == r.start[1] && r.end[0] > r.start[0])));
        if (!validDate(r.start) || !validDate(r.end) || !ordered) {
            for (int i = 0; i < 3; ++i) r.start[i] = r.end[i] = 0;
            r.bookingid = -1;
            return false;
        }
        r.bookingid = 1;
        return 1;
	}
	else {
		return 0;
	}
}
bool CHECK_OUT(room& r) {
	if (r.bookingid == 1 || r.bookingid == 2) {
		r.bookingid = -1;
		r.end[0] = 0;
		r.end[1] = 0;
		r.end[2] = 0;
		r.start[0] = 0;
		r.start[1] = 0;
		r.start[2] = 0;
		return 1;
	}
	else {

		return 0;
	}
}
int SEARCH_INDEX(int targetRoomNumber) {

	for (int i = 0; i < currentRoom; i++) {
		if (rooms[i].room_number == targetRoomNumber) {
			return i;
		}
	}
	return -1;
}
bool CHECK_IN(room& r) {
	if (r.start[0] == 0 || r.end[0] == 0) {

		return 0;
	}
	else {

		r.bookingid = 2;
		return 1;
	}
}
bool SAVE_INVENTORY() {
	//save data
	ofstream output;
	output.open("INVENTORY.txt");
	for (int i = 0; i < currentRoom; i++) {
		output << "number of beds: " << rooms[i].beds << endl << "booking id: " << rooms[i].bookingid << endl << "price of the room: " << rooms[i].price << endl << "room number: " << rooms[i].room_number << endl << "bed type: " << rooms[i].bedtype << endl << "start date: " << rooms[i].start[0] << " / " << rooms[i].start[1] << " / " << rooms[i].start[2] << endl << "end date: " << rooms[i].end[0] << " / " << rooms[i].end[1] << " / " << rooms[i].end[2] << endl << endl;
	}
	output.close();
	//save currentroom
	ofstream currentoutput;
	currentoutput.open("CUURENT.txt");
	currentoutput << currentRoom;
	currentoutput.close();
	//save password
	ofstream passwordoutput;
	passwordoutput.open("PASSWORD.txt");
	if (passwordoutput.fail()) {
		cout << "cannot open the file password.txt" << endl;
	}
	else {
		passwordoutput << password;
	}

	return 1;
}
void LOAD_ROOM() {
	///load password
	ifstream passwordinput;
	passwordinput.open("PASSWORD.txt");
	if (passwordinput.fail()) {
		cout << "cannot open the file password.txt" << endl;
	}
	else {
		passwordinput >> password;
	}
	passwordinput.close();


	/////////////////load currentroom
	ifstream currentinput;
	currentinput.open("CUURENT.txt");
	if (currentinput.fail()) {
		cout << "cannot open file current" << endl;
	}
	if (!(currentinput >> currentRoom) || currentRoom < 0 || currentRoom > 100) currentRoom = 0;
	currentinput.close();
	/////////////load all data
	ifstream input;
	string s;
	input.open("INVENTORY.txt");
	if (input.fail()) {
		cout << "cannot open file inventory" << endl;
	}
	int num = 2;

	for (int i = 0; i < currentRoom; i++) {
		input >> s >> s >> s >> rooms[i].beds >> s >> s >> rooms[i].bookingid >> s >> s >> s >> s >> rooms[i].price >> s >> s >> rooms[i].room_number >> s >> s >> num >> s >> s >> rooms[i].start[0] >> s >> rooms[i].start[1] >> s >> rooms[i].start[2] >> s >> s >> rooms[i].end[0] >> s >> rooms[i].end[1] >> s >> rooms[i].end[2];

		if (num == 0)
		{
			rooms[i].bedtype = king;
		}
		else if (num == 1) {
			rooms[i].bedtype = queen;
		}
		else if (num == 2) {
			rooms[i].bedtype = single;
		}
	}

	input.close();

}
bool PASSWORD() {
	int counter = 2;
	string check;


	cout << "enter the password" << endl;
	cin >> check;
	if (check == password) {
		return 1;
	}
	do {
		cout << "wrong try again ,you have got " << counter << " trials left " << endl;
		cin >> check;
		counter--;
		if (check == password) {
			return 1;
		}
	} while (counter > 0 && check != password);

	return 0;

}

void loading(int length, int duration) {
	for (int i = 0; i <= length; i++) {
		cout << "loading[";
		for (int j = 0; j < i; j++) {
			cout << "#";
		}
		for (int j = i; j <= length; j++) {
			cout << " ";
		}
		cout << "]" << (i * 100) / length << "%";
		Sleep(duration);
	}

	cout << "loading complete" << endl;
	Sleep(1900);
	clearScreen();
}
