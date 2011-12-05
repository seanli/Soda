include "Soda.h"

using namespace std;

Student::Student(Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id, unsigned int maxPurchases) : prt ( prt ), nameServer ( nameServer ), cardOffice ( cardOffice ), id ( id ), maxPurchases ( maxPurchases ) {}

void Student::main() {

}
