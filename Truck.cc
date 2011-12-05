#include "Soda.h"

Truck::Truck(Printer &prt, NameServer &nameServer, BottlingPlant &plant, unsigned int numVendingMachines, unsigned int maxStockPerFlavour) :
	prt(prt), nameServer(nameServer), plant(plant), numVendingMachines(numVendingMachines), maxStockPerFlavour(maxStockPerFlavour)
{
    numFlavours = (int)VendingMachine::NUM_FLAVOURS;

    cargo = new unsigned int[numFlavours];

	for (unsigned int i = 0; i < numFlavours; i++)
	{
		cargo[i] = 0;
	}
}

Truck::~Truck()
{
    delete[] cargo;
    prt.print(Printer::Truck, 'F');
}

void Truck::main()
{
    prt.print(Printer::Truck, 'S');

    for(;;)
    {
        unsigned int timmyTime = r(1, 10);
        yield(timmyTime);

        gotCargo = !(plant.getShipment(cargo));

        if(gotCargo)
        {
            unsigned int sum = 0;

            for(unsigned int i = 0; i < numFlavours; i++)
            {
                sum += cargo[i];
            }

            prt.print(Printer::Truck, 'P', sum);

            destMachines = nameServer.getMachineList();

            bool isChanged = false;
            unsigned int i = 0;

            while(sum > 0 && i < numVendingMachines)
            {
                prt.print(Printer::Truck, 'd', destMachines[i]->getId(), sum);

                machineInventory = destMachines[i]->inventory();

                int numUnreplenished = 0;

                for(unsigned int j = 0; j < numFlavours; j++)
                {
                    if(cargo[j] > 0 && machineInventory[j] < maxStockPerFlavour)
                    {
                        isChanged = true;

                        unsigned int numMissing = maxStockPerFlavour - machineInventory[j];

                        if(numMissing > cargo[j])
                        {
                            machineInventory[j] += cargo[j];
                            sum -= cargo[j];
                            cargo[j] = 0;
                        }
                        else
                        {
                            machineInventory[j] = maxStockPerFlavour;
                            sum -= numMissing;
                            cargo[j] -= numMissing;
                        }
                    }

                    numUnreplenished += (maxStockPerFlavour - machineInventory[j]);

                }

                if(numUnreplenished > 0)
                {
                    prt.print(Printer::Truck, 'U', destMachines[i]->getId(), numUnreplenished);
                    numUnreplenished = 0;
                }

                prt.print(Printer::Truck, 'D', destMachines[i]->getId(), sum);

                if(isChanged)
                {
                    destMachines[i]->restocked();
                }

                i++;
            }

            for(unsigned int i = 0; i < numFlavours; i++)
            {
                cargo[i] = 0;
            }

        }
        else
        {
            break;
        }
    }
}
