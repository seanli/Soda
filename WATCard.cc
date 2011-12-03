#include "Soda.h"

using namespace std;

PRNG r; // Global random generator

WATCard::WATCard() {
	balance = 0;
}
WATCard::WATCard(const WATCard &) {
	
} // prevent copying

WATCard::WATCard &operator=(const WATCard &) {
	return *this;
}

void WATCard::deposit(unsigned int amount) {
	balance += amount;
}

void WATCard::withdraw(unsigned int amount) {
	balance -= amount;
}

unsigned int WATCard::getBalance() {
	return balance;
}
