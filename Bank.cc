#include "Soda.h"

using namespace std;

Bank::Bank(unsigned int numStudents) : numStudents( numStudents ) {
	bankAccounts = new int[numStudents];
	for (unsigned int i = 0; i < numStudents; i++) {
		bankAccounts[i] = 0;
	}
}

void Bank::deposit(unsigned int id, unsigned int amount) {
	bankAccounts[id - 5] += amount;
	sufficientFunds.signal();
}

void Bank::withdraw(unsigned int id, unsigned int amount) {
	while ((unsigned int) bankAccounts[id - 5] < amount) {
		sufficientFunds.wait();
	}
	bankAccounts[id - 5] -= amount;
}

