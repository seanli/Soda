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
    prt.print(Printer::Vending, id, 'F');
}

void VendingMachine::main()
{
    prt.print(Printer::Vending, id, 'S', sodaCost);
    for (;;)
    {
        _Accept(~VendingMachine)
        {
            break;
        }
        or _Accept(buy) {}
        or _Accept(inventory)
        {
            _Accept(restocked);
        }
    }
}

VendingMachine::Status VendingMachine::buy(Flavours flavour, WATCard &card)
{
	if(this->inventoryList[(int) flavour] < 1){
		return VendingMachine::STOCK;
	}
	if(	card.getBalance() < this->sodaCost){
		return VendingMachine::FUNDS;
	}
	prt->print( Printer::Vending,id, 'B', (int)flavour, inventoryList[(int) flavour]);
	card.withdraw( this->sodaCost );
	return VendingMachine::BUY;
}

unsigned int* VendingMachine::inventory()
{
    prt.print(Printer::Vending, id, 'r');
    return stock;
}

void VendingMachine::restocked()
{
    prt.print(Printer::Vending, id, 'R');
}

_Nomutex unsigned int VendingMachine::cost()
{
    return sodaCost;
}

_Nomutex unsigned int VendingMachine::getId()
{
    return id;
}
