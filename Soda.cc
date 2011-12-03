#include "Soda.h"

using namespace std;

MPRNG r; // Global random generator

void uMain::main()
{
  ConfigParms cparam;
  string filePath = "Config.txt";
  processConfigFile(filePath.c_str(), cparam);

  Printer *prt = new Printer(cparam.numStudents, cparam.numVendingMachines, cparam.numCouriers);
  NameServer *ns = new NameServer(*prt, cparam.numVendingMachines, cparam.numStudents);
  BottlingPlant *bp = new BottlingPlant(*prt, *ns, cparam.numVendingMachines, cparam.maxShippedPerFlavour, cparam.maxStockPerFlavour, cparam.timeBetweenShipments);

  delete bp;
  delete ns;
  delete prt;
}
