#ifndef _SODA_H_
#define _SODA_H_

#include <uC++.h>
#include <uFuture.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <stdint.h>
#include <cassert>
#include <queue>

#define INT_MAX 1000

struct ConfigParms
{
    unsigned int sodaCost;                      // MSRP per bottle
    unsigned int numStudents;                   // number of students to create
    unsigned int maxPurchases;                  // maximum number of bottles a student purchases
    unsigned int numVendingMachines;            // number of vending machines
    unsigned int maxStockPerFlavour;            // maximum number of bottles of each flavour stocked
    unsigned int maxShippedPerFlavour;          // number of bottles of each flavour in a shipment
    unsigned int timeBetweenShipments;          // length of time between shipment pickup
    unsigned int parentalDelay;                 // length of time between cash deposits
    unsigned int numCouriers;                   // number of couriers in the pool
};

void processConfigFile(const char *configFile, ConfigParms &cparms);

// Forward declare
_Monitor Printer;
_Monitor Bank;
_Task NameServer;
_Task WATCardOffice;
_Task Truck;

_Task Student
{
  Printer &prt;
  NameServer &nameServer;
  WATCardOffice &cardOffice;
  unsigned int id;
  unsigned int maxPurchases;
  void main();
  public:
    Student(Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id, unsigned int maxPurchases);
    ~Student();
};

class WATCard
{
    WATCard(const WATCard &);			// prevent copying
    WATCard &operator=(const WATCard &);
    int balance;
  public:
    WATCard();
    void deposit(unsigned int amount);
    void withdraw(unsigned int amount);
    unsigned int getBalance();
};
typedef Future_ISM<WATCard*> FWATCard;		// future WATCard pointer

_Task WATCardOffice
{
    struct Args
    {
        unsigned int sid;
        unsigned int depositAmount;
        WATCard *&card;
        Args(unsigned int sid, unsigned int depositAmount, WATCard *&card) : sid ( sid ), depositAmount ( depositAmount ), card ( card ) {}
    };

    struct Job // marshalled arguments and return future
    {
		Args args;					// call arguments (YOU DEFINE "Args")
		FWATCard result;			// return future
		Job(Args args) : args(args) {}
    };

    std::queue<Job *> jobQueue;
    uCondition jobsAvailable;
    Printer &prt;
    Bank &bank;
    unsigned int numCouriers;
    void main();

    _Task Courier
    {
        Bank &bank;
        WATCardOffice *office;
	Printer &prt;
        void main();
        public:
            Courier(Bank &bank, WATCardOffice* office, Printer &prt);
    };

  public:
    _Event Lost {};
    WATCardOffice(Printer &prt, Bank &bank, unsigned int numCouriers);
    ~WATCardOffice();
    FWATCard create(unsigned int sid, unsigned int amount, WATCard *&card);
    FWATCard transfer(unsigned int sid, unsigned int amount, WATCard *card);
    Job *requestWork();
};

_Monitor Bank
{
    uCondition sufficientFunds;
    unsigned int numStudents;
    int *bankAccounts;
  public:
    Bank(unsigned int numStudents);
    ~Bank();
    void deposit(unsigned int id, unsigned int amount);
    void withdraw(unsigned int id, unsigned int amount);
};

_Task Parent
{
    Printer &prt;
    Bank &bank;
    unsigned int numStudents;
    unsigned int parentalDelay;
    void main();
  public:
    Parent(Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay);
    ~Parent();
};

_Task VendingMachine
{
    Printer &prt;
    NameServer &nameServer;
    unsigned int id;
    unsigned int sodaCost;
    unsigned int maxStockPerFlavour;
    unsigned int numFlavours;
    unsigned int* stock;
    void main();
  public:
    enum Flavours {BLUES, CLASSICAL, ROCK, JAZZ, NUM_FLAVOURS}; 	// flavours of soda (YOU DEFINE)
    enum Status {BUY, STOCK, FUNDS};								// purchase status: successful buy, out of stock, insufficient funds
    VendingMachine(Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour);
    ~VendingMachine();
    Status buy(Flavours flavour, WATCard &card);
    unsigned int* inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
};

_Task NameServer
{
	Printer &prt;
	unsigned int numVendingMachines;
	unsigned int numStudents;
	VendingMachine** machines;
	unsigned int currMachine;
	unsigned int* studentCurrMachine;

    void main();
  public:
    NameServer(Printer &prt, unsigned int numVendingMachines, unsigned int numStudents);
    ~NameServer();
    void VMregister(VendingMachine *vendingmachine);
    VendingMachine* getMachine(unsigned int id);
    VendingMachine** getMachineList();
};

_Task BottlingPlant
{
	Printer &prt;
	NameServer &nameServer;
	unsigned int numVendingMachines;
	unsigned int maxShippedPerFlavour;
	unsigned int maxStockPerFlavour;
	unsigned int timeBetweenShipments;

	unsigned int numFlavours;
	unsigned int* shipment;
	Truck* truck;

	uCondition producedShipment;

	bool plantClosing;
	uCondition closing;

    void main();
  public:
    BottlingPlant(Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
    	unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments);
    ~BottlingPlant();
    bool getShipment(unsigned int cargo[]);
};

_Task Truck
{
	Printer &prt;
	NameServer &nameServer;
	BottlingPlant &plant;
	unsigned int numVendingMachines;
	unsigned int maxStockPerFlavour;

    unsigned int numFlavours;
    unsigned int* cargo;
    bool gotCargo;

    VendingMachine** destMachines;
    unsigned int* machineInventory;

    void main();
  public:
    Truck(Printer &prt, NameServer &nameServer, BottlingPlant &plant, unsigned int numVendingMachines, unsigned int maxStockPerFlavour);
    ~Truck();
};

/*_Monitor Printer {

  public:
    enum Kind { Parent, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
    Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
    ~Printer();
    void print( Kind kind, char state );
    void print( Kind kind, char state, int value1 );
    void print( Kind kind, char state, int value1, int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, int value1 );
    void print( Kind kind, unsigned int lid, char state, int value1, int value2 );

  private:

    char* allStates;

    int* value_one;
    int* value_two;

    unsigned int numStudent;
    unsigned int numMachine;
    unsigned int numCourier;

    unsigned int student_start_index;
    unsigned int machine_start_index;
    unsigned int courier_start_index;

    unsigned int totalTasks;

    void flush();
    void setState( Kind kind, char state, unsigned int value1, unsigned int value2 );
    void setState( Kind kind, char state, unsigned int id, unsigned int value1, unsigned int value2 );
    void printFinish( char state, unsigned int id );
};*/

_Monitor Printer
{
	unsigned int numStudents;
	unsigned int numVendingMachines;
	unsigned int numCouriers;

	struct Unit
	{
        char state;
        int value1;
        int value2;
        Unit() : state(' '), value1(-1), value2(-1) {}
	}; // Unit
	std::vector<Unit> units;

	void printTab();
	void printTab(unsigned int times);
	void printUnit(unsigned int index, char state, int value1, int value2);
	void printFlush();
	void printFinish(char state, unsigned int index);

  public:
    enum Kind {Parent, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier};
    Printer(unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers);
    ~Printer();
    void print(Kind kind, char state);
    void print(Kind kind, char state, int value1);
    void print(Kind kind, char state, int value1, int value2);
    void print(Kind kind, unsigned int lid, char state);
    void print(Kind kind, unsigned int lid, char state, int value1);
    void print(Kind kind, unsigned int lid, char state, int value1, int value2);

  private:
    _Nomutex unsigned int getIndex(Kind kind);
	_Nomutex unsigned int getIndex(Kind kind, unsigned int id);
};

class PRNG
{
    uint32_t seed_;	// same results on 32/64-bit architectures

  public:
    PRNG(uint32_t s = 362436069)
    {
        seed_ = s;					// set seed
        assert(((void)"invalid seed", seed_ != 0));
    }

    uint32_t seed() // read seed
    {
        return seed_;
    }

    void seed(uint32_t s) // reset seed
    {
        seed_ = s;					// set seed
        assert(((void)"invalid seed", seed_ != 0));
    }

    uint32_t operator()() // [0,UINT_MAX]
    {
        seed_ = 36969 * (seed_ & 65535) + (seed_ >> 16); // scramble bits
        return seed_;
    }

    uint32_t operator()(uint32_t u) // [0,u]
    {
        assert(((void)"invalid random range", u < (uint32_t)-1));
        return operator()() % (u + 1);			// call operator()()
    }

    uint32_t operator()(uint32_t l, uint32_t u) // [l,u]
    {
        assert(((void)"invalid random range", l <= u));
        return operator()( u - l ) + l;			// call operator()( uint32_t )
    }
};

_Monitor MPRNG : private PRNG
{
  public:
    MPRNG(uint32_t seed = 1009) { PRNG(seed); }
    uint32_t seed() { return PRNG::seed(); }
    void seed(uint32_t s) { PRNG::seed(s); }
    uint32_t operator()() { return PRNG::operator()(); }
    uint32_t operator()(uint32_t u) { return PRNG::operator()(u); }
    uint32_t operator()(uint32_t l, uint32_t u) { return PRNG::operator()(l, u); }
}; // _Monitor MPRNG

extern MPRNG r; // Global random generator

#endif // _SODA_H_
