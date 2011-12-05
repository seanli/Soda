#include "Soda.h"

VendingMachine::VendingMachine(Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour) :
	prt(prt), nameServer(nameServer), id(id), sodaCost(sodaCost), maxStockPerFlavour(maxStockPerFlavour)
{
    numFlavours = (int)VendingMachine::NUM_FLAVOURS;

    stock = new unsigned int[numFlavours];

	for (unsigned int i = 0; i < numFlavours; i++)
	{
		stock[i] = 0;
	}
}

VendingMachine::~VendingMachine()
{
    delete[] stock;
    prt.print(Printer::Vending, 'F');
}

void VendingMachine::main()
{
    prt.print(Printer::Vending, 'S', sodaCost);
}

unsigned int* VendingMachine::inventory()
{
    return stock;
}

void VendingMachine::restocked()
{

}

_Nomutex unsigned int VendingMachine::cost()
{
    return sodaCost;
}

_Nomutex unsigned int VendingMachine::getId()
{
    return id;
}
