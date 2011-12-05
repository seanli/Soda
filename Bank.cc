#include "Soda.h"

Bank::Bank(unsigned int numStudents) : numStudents( numStudents ) {
	bankAccounts = new int[numStudents];
	for (unsigned int i = 0; i < numStudents; i++) {
		bankAccounts[i] = 0;
	}
}

Bank::~Bank()
{
    delete[] bankAccounts;
}

void Bank::deposit(unsigned int id, unsigned int amount) {
	bankAccounts[id] += amount;
	sufficientFunds.signal();
}

void Bank::withdraw(unsigned int id, unsigned int amount) {
	while ((unsigned int) bankAccounts[id] < amount) {
		sufficientFunds.wait();
	}
	bankAccounts[id] -= amount;
}

