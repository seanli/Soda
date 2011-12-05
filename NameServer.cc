#include "Soda.h"

NameServer::NameServer(Printer &prt, unsigned int numVendingMachines, unsigned int numStudents) :
	prt(prt), numVendingMachines(numVendingMachines), numStudents(numStudents)
{
    machines = new VendingMachine*[numVendingMachines];

	for (unsigned int i = 0; i < numVendingMachines; i++)
	{
		machines[i] = NULL;
	}

    studentCurrMachine = new unsigned int[numStudents];
    for (unsigned int i = 0; i < numStudents; i++)
    {
        studentCurrMachine[i] = i % numVendingMachines;
    }

	currMachine = 0;
}

NameServer::~NameServer()
{
    delete[] machines;
    delete[] studentCurrMachine;
    prt.print(Printer::NameServer, 'F');
}

void NameServer::main()
{
    prt.print(Printer::NameServer, 'S');

    for (;;)
    {
        _Accept(~NameServer)
        {
            break;
        }
        or _Accept(VMregister) {}
        or _Accept(getMachine) {}
        or _Accept(getMachineList) {}
    }
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
    VendingMachine* vm = machines[studentCurrMachine[id]];
    studentCurrMachine[id] = (studentCurrMachine[id] + 1) % numVendingMachines;
    prt.print(Printer::NameServer, 'N', id, vm->getId());
	return vm;
}

VendingMachine** NameServer::getMachineList()
{
	return machines;
}
