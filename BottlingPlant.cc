#include "Soda.h"

using namespace std;

BottlingPlant::BottlingPlant(Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
	unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments) :
    prt(prt), nameServer(nameServer), numVendingMachines(numVendingMachines), maxShippedPerFlavour(maxShippedPerFlavour),
    maxStockPerFlavour(maxStockPerFlavour), timeBetweenShipments(timeBetweenShipments)
{
	numFlavours = (int)VendingMachine::NUM_FLAVOURS;
	produced = new unsigned int[numFlavours];
	for (unsigned int i = 0; i < numFlavours; i++)
	{
		produced[i] = 0;
	}
}

BottlingPlant::~BottlingPlant()
{
	delete[] produced;
}

void BottlingPlant::main()
{
    prt.print(Printer::BottlingPlant, 'S');

    Truck *truck = new Truck(prt, nameServer, *this, numVendingMachines, maxStockPerFlavour);

	for(;;)
  	{
  	    _Accept(~BottlingPlant)
  	    {

  	        break;
  	    }
  	    else
  	    {
  	        cout << "got before loop " << endl;
  	        for (unsigned int i = 0; i < numFlavours; i++)
            {
                produced[i] = r(0, maxShippedPerFlavour);
            } // for
            doneProducing.signalBlock();
            cout << "signaled producing" << endl;
            cout << "blocked" << endl;
            doneShipping.wait();
            yield(timeBetweenShipments);
            cout << "unblocked production" << endl;
  	    }
  	} // for

  	delete truck;
}

bool BottlingPlant::getShipment(unsigned int cargo[])
{
    cout << "blocked waiting for production" << endl;
    doneProducing.wait();
    cout << "unblocked truck" << endl;
    cargo = produced;
    // Nameserver stuff
	doneShipping.signal();
	return (cargo == NULL);
}
