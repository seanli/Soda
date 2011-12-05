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
            tabsCount = 0;

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

_Nomutex unsigned int Printer::getIndex(Kind kind)
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

_Nomutex unsigned int Printer::getIndex(Kind kind, unsigned int id)
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
    cout << index << endl;
    printUnit(index, state, value1, value2);
}

/*#include "Soda.h"

using namespace std;


Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers )
{

    numStudent = numStudents;
    numMachine = numVendingMachines;
    numCourier = numCouriers;

    student_start_index = 5;
    machine_start_index = 5 + numStudent;
    courier_start_index = machine_start_index + numCourier;

    totalTasks = numStudent + numMachine + numCourier + 5;

    allStates = new char[totalTasks];
    value_one = new int[totalTasks];
    value_two = new int[totalTasks];

    for(unsigned int i = 0; i < totalTasks; i++)
    {
        allStates[i] = ' ';
        value_one[i] = INT_MAX;
        value_two[i] = INT_MAX;
    }

    cout << "Parent\tWATOff\tNames\tTruck\tPlant\t";

    for(unsigned int i = 0; i < numStudent; i++)
    {
        cout << "Stud:" << i << "\t";
    }

    for(unsigned int i = 0; i < numMachine; i++)
    {
        cout << "Mach:" << i << "\t";
    }

    for(unsigned int i = 0; i < numCourier; i++)
    {
        cout << "Cour:" << i;
        if(i != numCourier - 1)
        {
            cout << "\t";
        }
    }

    cout << endl;

    for(unsigned int i = 0; i < 5 + numStudents + numMachine + numCouriers; i++)
    {
        cout << "*******";
        if(i != (totalTasks - 1))
        {
            cout << "\t";
        }
    }

    cout << endl;
}

Printer::~Printer()
{
    cout << "***********************" << endl;

    delete allStates;
    delete value_one;
    delete value_two;
}

void Printer::print( Kind kind, char state )
{
    setState(kind, state, INT_MAX, INT_MAX);
}

void Printer::print( Kind kind, char state, int value1 )
{
    setState(kind, state, value1, INT_MAX);
}

void Printer::print( Kind kind, char state, int value1, int value2 )
{
    setState(kind, state, value1, value2);
}

void Printer::print( Kind kind, unsigned int lid, char state )
{
    setState(kind, state, lid, INT_MAX, INT_MAX);
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1 )
{
    setState(kind, state, lid, value1, INT_MAX);
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 )
{
    setState(kind, state, lid, value1, value2);

}

void Printer::flush()
{
    int tabcounter = 0;

    for( unsigned int i = 0; i < totalTasks; i++ )
    {
        // if state exist for element i, print, otherwise hold tab.
        if(allStates[i] != ' ')
        {
            for( ; tabcounter > 0; tabcounter--)
            {
                cout << '\t';
            }

            cout << allStates[i];

            if(value_one[i] != INT_MAX)
            {
                cout << ':' << value_one[i];
            }

            if(value_two[i] != INT_MAX)
            {
                cout << ',' << value_two[i];
            }


            allStates[i] = ' ';
            value_one[i] = INT_MAX;
            value_two[i] = INT_MAX;
        }

        tabcounter++;
    }

    cout << endl;
}

void Printer::setState(Kind kind, char state, unsigned int value1, unsigned int value2)
{
    unsigned int index = (unsigned int)kind;

    if(allStates[index] != ' ')
    {
        flush();
    }

    if(state == 'F')
    {
        printFinish(state, index);
    }
    else
    {
        //assign new values to buffer

        allStates[index] = state;
        value_one[index] = value1;
        value_two[index] = value2;
    }

}

void Printer::setState(Kind kind, char state, unsigned int id, unsigned int value1, unsigned int value2)
{
    unsigned int index;

    if(kind == Student)
    {
        index = student_start_index + id;
    }
    else if(kind == Vending)
    {
        index = machine_start_index + id;
    }
    else if(kind == Courier)
    {
        index = courier_start_index + id;
    }
    else
    {
        cout << "You're calling the wrong print function." << endl;
        assert(false);
    }

    if(allStates[index] != ' ')
    {
        flush();
    }

    if(state == 'F')
    {
        printFinish(state, index);
    }
    else
    {
        //assign new values to buffer

        allStates[index] = state;
        value_one[index] = value1;
        value_two[index] = value2;
    }
}

void Printer::printFinish(char state, unsigned int id)
{
    for(unsigned int i = 0; i < id; i++)
    {
        cout << "..." << '\t';
    }

    cout << state;

    if(id != totalTasks - 1)
    {
        cout << '\t';
    }

    for(unsigned int i = id; i < totalTasks - 1; i++)
    {
        cout << "...";

        if(i != totalTasks - 1)
        {
            cout << '\t';
        }
    }

    cout << endl;
}*/


