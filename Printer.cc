#include "Soda.h"

using namespace std;

Printer::Printer(unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers) :
	numStudents(numStudents), numVendingMachines(numVendingMachines), numCouriers(numCouriers)
{
    cout << "Parent\tWATOff\tNames\tTruck\tPlant\t";
    for (unsigned int i = 0; i < numStudents; i++)
    {
        cout << "Stud:" << i << '\t';
    }
    for (unsigned int i = 0; i < numVendingMachines; i++)
    {
        cout << "Mach:" << i << '\t';
    }
    for (unsigned int i = 0; i < numCouriers; i++)
    {
        if (i != 0)
        {
            printTab();
        }
        cout << "Cour:" << i;
    }
    cout << endl;
    unsigned int totalUnits = 5 + numStudents + numVendingMachines + numCouriers;
    for (unsigned int i = 0; i < totalUnits; i++)
    {
        if (i != 0)
        {
            printTab();
        }
        cout << "*******";
    }
    cout << endl;
    units.resize(totalUnits);
}

Printer::~Printer()
{
    cout << "***********************" << endl;
}

void Printer::printTab()
{
    cout << '\t';
}

void Printer::printTab(unsigned int times)
{
    for (unsigned int i = 0; i < times; i++)
    {
        printTab();
    }
}

void Printer::printUnit(unsigned int index, char state, int value1, int value2)
{
    if (units[index].state != ' ')
    {
        printFlush();
    }

    if (state == 'F')
    {
        printFinish(state, index);
    }
    else
    {
        units[index].state = state;
        units[index].value1 = value1;
        units[index].value2 = value2;
    }
}

void Printer::printFlush()
{
    int tabsCount = 0;
    for (unsigned int i = 0; i < units.size(); i++)
    {
        if (units[i].state != ' ')
        {
            printTab(tabsCount);
            tabsCount = 1;

            cout << units[i].state;

            if (units[i].value1 != -1)
            {
                cout << ':' << units[i].value1;
            }

            if (units[i].value2 != -1)
            {
                cout << ',' << units[i].value2;
            }

            units[i].state = ' ';
            units[i].value1 = -1;
            units[i].value2 = -1;
        }
        tabsCount++;
    }
    cout << endl;
}

void Printer::printFinish(char state, unsigned int index)
{
    for (unsigned int i = 0; i < index; i++)
    {
        cout << "...";
        printTab();
    }

    cout << state;

    if (index != units.size() - 1)
    {
        printTab();
    }

    for (unsigned int i = index; i < units.size() - 1; i++)
    {
        cout << "...";

        if (i != units.size() - 1)
        {

            printTab();
        }
    }
    cout << endl;
}

unsigned int Printer::getIndex(Kind kind)
{
    switch(kind)
    {
        case Printer::Parent:
            return 0;
        case Printer::WATCardOffice:
            return 1;
        case Printer::NameServer:
            return 2;
        case Printer::Truck:
            return 3;
        case Printer::BottlingPlant:
            return 4;
        case Printer::Student:
            return 5;
        case Printer::Vending:
            return 5;
        case Printer::Courier:
            return 5;
    }
    return -1;
}

unsigned int Printer::getIndex(Kind kind, unsigned int id)
{
    switch(kind)
    {
        case Printer::Student:
            return getIndex(kind) + id;
        case Printer::Vending:
            return getIndex(kind) + numStudents + id;
        case Printer::Courier:
            return getIndex(kind) + numStudents + numVendingMachines + id;
        default:
            return getIndex(kind);
    }
    return -1;
}

void Printer::print(Kind kind, char state)
{
    unsigned int index = getIndex(kind);
    printUnit(index, state, -1, -1);
}

void Printer::print(Kind kind, char state, int value1)
{
    unsigned int index = getIndex(kind);
    printUnit(index, state, value1, -1);
}

void Printer::print(Kind kind, char state, int value1, int value2)
{
    unsigned int index = getIndex(kind);
    printUnit(index, state, value1, value2);
}

void Printer::print(Kind kind, unsigned int lid, char state)
{
    unsigned int index = getIndex(kind, lid);
    printUnit(index, state, -1, -1);
}

void Printer::print(Kind kind, unsigned int lid, char state, int value1)
{
    unsigned int index = getIndex(kind, lid);
    printUnit(index, state, value1, -1);
}

void Printer::print(Kind kind, unsigned int lid, char state, int value1, int value2)
{
    unsigned int index = getIndex(kind, lid);
    printUnit(index, state, value1, value2);
}
