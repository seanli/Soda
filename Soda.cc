#include "Soda.h"

using namespace std;

MPRNG r; // Global random generator

// Parses command line argument into integer
bool parseArg(int *num, char *arg)
{
    stringstream ss(arg);		 // declares stringstream with argument
    ss >> dec >> *num;           // parses argument as an integer to num
    // check if the process failed
    return !ss.fail();
} // parsesArg

void uMain::main()
{
    string exec_name = argv[0];
    string usage("Usage: " + exec_name + " [ config-file [ random-seed (> 0) ] ]");

    if (argc > 3)
    {
        cout << usage << endl;
        return;
    }

    string configFilePath = "soda.config";
    int seed = time(NULL);

    if (argc == 3)
    {
        configFilePath = argv[1];
        if (!parseArg(&seed, argv[2]) || seed <= 0)
        {
            cout << usage << endl;
            return;
        }
    }
    else if (argc == 2)
    {
        configFilePath = argv[1];
    }

    ConfigParms cparam;
    processConfigFile(configFilePath.c_str(), cparam);

    r.seed(seed);

    Printer *printer = new Printer(cparam.numStudents, cparam.numVendingMachines, cparam.numCouriers);
    Bank *bank = new Bank(cparam.numStudents);
    WATCardOffice *office = new WATCardOffice(*printer, *bank, cparam.numCouriers);
    Parent *parent = new Parent(*printer, *bank, cparam.numStudents, cparam.parentalDelay);
    NameServer *nameServer = new NameServer(*printer, cparam.numVendingMachines, cparam.numStudents);

    VendingMachine **vm = new VendingMachine*[cparam.numVendingMachines];
    for (unsigned int i = 0; i < cparam.numVendingMachines; i++)
    {
        vm[i] = new VendingMachine(*printer, *nameServer, i, cparam.sodaCost, cparam.maxStockPerFlavour);
        nameServer->VMregister(vm[i]);
    }

    BottlingPlant *plant = new BottlingPlant(*printer, *nameServer, cparam.numVendingMachines, cparam.maxShippedPerFlavour, cparam.maxStockPerFlavour, cparam.timeBetweenShipments);

    Student **stu = new Student*[cparam.numStudents];
    for (unsigned int i = 0; i < cparam.numStudents; i++)
    {
        stu[i] = new Student(*printer, *nameServer, *office, i, cparam.maxPurchases);
    }

    for (unsigned int i = 0; i < cparam.numStudents; i++)
    {
        delete stu[i];
    }
    delete plant;
    for (unsigned int i = 0; i < cparam.numVendingMachines; i++)
    {
        delete vm[i];
    }
    delete nameServer;
    delete parent;
    delete office;
    delete bank;
    delete printer;
}
