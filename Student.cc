#include "Soda.h"

Student::Student(Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id, unsigned int maxPurchases) : prt ( prt ), nameServer ( nameServer ), cardOffice ( cardOffice ), id ( id ), maxPurchases ( maxPurchases ) {}

Student::~Student()
{
    prt.print(Printer::Student, id, 'F');
}

void Student::main()
{
    unsigned int purchases = r(1, maxPurchases);
    unsigned int favouriteSoda = r(0, 3);

    prt.print(Printer::Student, id, 'S', favouriteSoda, purchases);

    while (purchases > 0)
    {
        prt.print(Printer::Student, id, 'B');
        purchases--;
        yield();
    }
}
