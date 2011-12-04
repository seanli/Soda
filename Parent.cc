#include "Soda.h"

using namespace std;

Parent::Parent(Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay) : prt ( prt ), bank ( bank ), numStudents ( numStudents ), parentalDelay ( parentalDelay ) {	}

Parent::~Parent() {}

void Parent::main() {	
   for (;;) {
     _Accept( ~Parent ) {
	break;
     } else {
	// calculate random amount between 1 and 3
	int deposit = 1 + (rand() % 3); // fix to not gen 0
	yield(parentalDelay);
	int studentID = rand() % numStudents; // give to a random student
	bank.deposit(studentID, deposit);
    }
   }
}
