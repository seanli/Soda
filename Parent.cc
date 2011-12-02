#include "Soda.h"

using namespace std;

PRNG r; // Global random generator

Parent(Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay) : prt ( prt ), bank ( bank ), numStudents ( numStudents ), parentalDelay ( parentalDelay ) {	}

void Parent::main() {	
	// calculate random amount between 1 and 3
	int deposit = rand() % 4; // fix to not gen 0
	yield(parentalDelay);
	int studentID = rand() % numStudents; // give to a random student
	bank.deposit(numStudents, deposit);
	//
	//
	// must keep checking for a call to its destructor to know when to terminate
	// use a terminating else on the _Accept
	// i.e. parent is busy waiting
}

