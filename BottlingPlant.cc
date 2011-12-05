#include "Soda.h"

BottlingPlant::BottlingPlant(Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
	unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments) :
    prt(prt), nameServer(nameServer), numVendingMachines(numVendingMachines), maxShippedPerFlavour(maxShippedPerFlavour),
    maxStockPerFlavour(maxStockPerFlavour), timeBetweenShipments(timeBetweenShipments), plantClosing(false)
{
	numFlavours = (int)VendingMachine::NUM_FLAVOURS;
	shipment = new unsigned int[numFlavours];

	for (unsigned int i = 0; i < numFlavours; i++)
	{
		shipment[i] = 0;
	}
}

BottlingPlant::~BottlingPlant()
{
    closing.wait();
    delete truck;
	delete[] shipment;
	prt.print(Printer::BottlingPlant, 'F');
}

void BottlingPlant::main()
{
    prt.print(Printer::BottlingPlant, 'S');

    truck = new Truck(prt, nameServer, *this, numVendingMachines, maxStockPerFlavour);
    _Accept(getShipment);

	for(;;)
  	{
  	    _Accept(~BottlingPlant)
  	    {

            plantClosing = true;
  	        break;
  	    }
  	    else
  	    {
  	        int totalSodaProduced = 0;

            for(unsigned int i = 0; i < numFlavours; i++)
            {
                shipment[i] = r(0, maxShippedPerFlavour);
                totalSodaProduced += shipment[i];
            }

            prt.print(Printer::BottlingPlant, 'G', totalSodaProduced);
            producedShipment.signalBlock();
            prt.print(Printer::BottlingPlant, 'P');

            yield(timeBetweenShipments);
  	    }
  	} // for
}

bool BottlingPlant::getShipment(unsigned int cargo[])
{
    if(!plantClosing)
    {
        producedShipment.wait();

        for(unsigned int i = 0; i < numFlavours; i++)
        {
            cargo[i] = shipment[i];
        }

        producedShipment.signal();
        return false;
    }
    else
    {
        closing.signal();
        return true;
    }
}
