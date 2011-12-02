#include "Soda.h"

using namespace std;

PRNG r; // Global random generator

Bank::Bank(unsigned int numStudents) : numStudents( numStudents ) {
	bankAccounts = new int[numStudents];
	for (int i = 0; i < numStudents; i++) {
		bankAccounts[i] = 0;
	}
}

void Bank::deposit(unsigned int id, unsigned int amount) {
	bankAccounts[id - 5] += amount;
}

void Bank::withdraw(unsigned int id, unsigned int amount) {
	bankAccounts[id - 5] -= amount;
}

