#include <iostream>
#include <string>
using namespace std;

int main()
{
	cout.setf(ios::fixed);
	cout.precision(2);

	cout << "Age of rider: ";
	int age;
	cin >> age; 
	cin.ignore(10000, '\n'); //ignore rest of line

	cout << "Student? (y/n): ";
	string studentID;
	getline(cin, studentID);

	cout << "Destination: ";
	string destination;
	getline(cin, destination);

	cout << "Number of zone boundaries crosses: ";
	int zonesCrossed;
	cin >> zonesCrossed;
	cin.ignore(10000, '\n'); //ignore rest of line

	double fare = 1.35;
	double fareZoneRate = .55;
	if (age >= 65) { // if the passenger is older than 65 they will pay .45 for zero boundary trip and .65 for a 1 boundary trip if a student
		if (studentID == "y" && zonesCrossed == 1){ //non student seniors pay normal senior price for 1+ boundary trips and student seniors pay normal senior price for
			fare = .65;                              //2+ boundary trips

		}
		else if (zonesCrossed == 0){
			fare = .45;

		}
		else {
			fareZoneRate = .25;
			fare = .55;
			fare = fare + fareZoneRate *zonesCrossed;

		}
		
		
	}
	else if (age > 18) { //18-65 passengers with pay the normal fair unless they are a student and then get a discount on 0-1 boundary trips 
		if (studentID == "y" && zonesCrossed <= 1)
			fare = .65;
		else {
			fareZoneRate = .55;
			fare = 1.35 + fareZoneRate * zonesCrossed;
		}
		
	}
	else { // 0-18 age passengers pay normal fair for 2+ boundary trips and discount on 0-1 boundary trips no matter their student status
		if (zonesCrossed <= 1)
			fare = .65;
		else {
			fareZoneRate = .55;
			fare = 1.35 + fareZoneRate * zonesCrossed;
		}

	}
	
		


	cout << "---" << endl;

	if (age < 0)
		cout << "The age must not be negative" << endl;
	else if (studentID != "y" && studentID != "n")
		cout << "You must enter y or n" << endl;
	else if (destination == "")
		cout << "You must enter a destination" << endl;
	else if (zonesCrossed < 0)
		cout << "The number of zone boundaries crossed must not be negative" << endl;
	else
		cout << "The fare to " << destination << " is $" << fare << endl;

	






}