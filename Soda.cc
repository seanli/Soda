#include "Soda.h"

using namespace std;

MPRNG r; // Global random generator

void uMain::main()
{
    ConfigParms cparam;
    string filePath = "Config.txt";
    processConfigFile(filePath.c_str(), cparam);

    Printer *printer = new Printer(cparam.numStudents, cparam.numVendingMachines, cparam.numCouriers);
    Bank *bank = new Bank(cparam.numStudents);
    Parent *parent = new Parent(*printer, *bank, cparam.numStudents, cparam.parentalDelay);
    NameServer *nameServer = new NameServer(*printer, cparam.numVendingMachines, cparam.numStudents);
    BottlingPlant *plant = new BottlingPlant(*printer, *nameServer, cparam.numVendingMachines, cparam.maxShippedPerFlavour, cparam.maxStockPerFlavour, cparam.timeBetweenShipments);

    delete plant;
    delete nameServer;
    delete parent;
    delete bank;
    delete printer;
}
