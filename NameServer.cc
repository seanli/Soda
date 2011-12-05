#include "Soda.h"

NameServer::NameServer(Printer &prt, unsigned int numVendingMachines, unsigned int numStudents) :
	prt(prt), numVendingMachines(numVendingMachines), numStudents(numStudents)
{
    machines = new VendingMachine*[numVendingMachines];

	for (unsigned int i = 0; i < numVendingMachines; i++)
	{
		machines[i] = NULL;
	}

	currMachine = 0;
}

NameServer::~NameServer()
{
    delete[] machines;
    prt.print(Printer::NameServer, 'F');
}

void NameServer::main()
{
    prt.print(Printer::NameServer, 'S');
}

void NameServer::VMregister(VendingMachine *vendingmachine)
{
    if (currMachine < numVendingMachines)
    {
        machines[currMachine] = vendingmachine;
        currMachine++;
    }
}

VendingMachine* NameServer::getMachine(unsigned int id)
{
	return NULL;
}

VendingMachine** NameServer::getMachineList()
{
	return machines;
}
