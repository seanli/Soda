#include "Soda.h"

Parent::Parent(Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay) : prt ( prt ), bank ( bank ), numStudents ( numStudents ), parentalDelay ( parentalDelay ) {	}

Parent::~Parent()
{
    prt.print(Printer::Parent, 'F');
}

void Parent::main() {
    prt.print(Printer::Parent, 'S');
	int deposit = 0;
	int studentID = 0;
    for (;;)
    {
        _Accept( ~Parent )
        {
            break;
        }
        else
        {
            // calculate random amount between 1 and 3
            deposit = r(1, 3); // fix to not gen 0
            yield(parentalDelay);
            studentID = r() % numStudents; // give to a random student
            prt.print(Printer::Parent, 'D', studentID, deposit);
            bank.deposit(studentID, deposit);
        }
   }
}
