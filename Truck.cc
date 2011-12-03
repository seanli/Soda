#include "Soda.h"

using namespace std;

Truck::Truck(Printer &prt, NameServer &nameServer, BottlingPlant &plant, unsigned int numVendingMachines, unsigned int maxStockPerFlavour) :
	prt(prt), nameServer(nameServer), plant(plant), numVendingMachines(numVendingMachines), maxStockPerFlavour(maxStockPerFlavour) {}

void Truck::main()
{
	for(;;)
	{
	    _Accept(~Truck)
	    {
	        break;
	    }
	    else
	    {
            unsigned int timmyTime = r(1, 10);
            yield(timmyTime);
	        unsigned int* cargo = NULL;
            cout << "got here" << endl;
            plant.getShipment(cargo);
            cout << "got shipment" << endl;
            for (unsigned int i = 0; i < (int)VendingMachine::NUM_FLAVOURS; i++)
            {
                cout << cargo[i] << endl;
            }
	    }
	}
}
