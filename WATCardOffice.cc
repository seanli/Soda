#include "Soda.h"

using namespace std;

void WATCardOffice::main() {
	// create pool of numCouriers
	Courier *couriers[numCouriers];
	for (unsigned int i = 0; i < numCouriers; i++) {
		couriers[i] = new Courier(bank, this);
	}
	for (;;) { 
		_Accept ( ~WATCardOffice ) {
			for (unsigned int i = 0; i < numCouriers; i++) {
		             jobsAvailable.signalBlock(); 
        		}
			for (unsigned int i = 0; i < numCouriers; i++) {
                             delete couriers[i];
                        }
			break;
		} or _Accept ( create ) {
			jobsAvailable.signal();
		} or _Accept ( transfer ) {
			jobsAvailable.signal();
		} 
	}
}

void WATCardOffice::Courier::main() {
	// infinite loop
	int sid = 0;
	int amount = 0;
	int lostChance = 0;
	int originalBalance = 0;
	for (;;) {	
	   _Accept ( ~Courier ) {
	   	break;	
	   } else {
		// sleep on a cond variable
		office->jobsAvailable.wait();
		if (office->jobQueue.empty()) {
			break;
		}
		Job *newJob = office -> requestWork();	
		sid  = newJob->args.sid;
		amount = newJob->args.depositAmount;
		originalBalance = (newJob->args).card->getBalance();

		bank.withdraw(sid, amount);
		
		// ask bank for moneys, wait till enough moneys is obtained
		WATCard *newCard = newJob->args.card;
		newCard->deposit(amount+originalBalance);
		lostChance = r() % 6;
		if (lostChance == 0) {
			newJob->result.exception(new WATCardOffice::Lost);
		}
		else {
			newJob->result.delivery(newCard);
		}
	   }
	}
}

WATCardOffice::WATCardOffice(Printer &prt, Bank &bank, unsigned int numCouriers) : prt ( prt ), bank ( bank ), numCouriers ( numCouriers ) {} 

WATCardOffice::Courier::Courier(Bank &bank, WATCardOffice *office) : bank ( bank ), office ( office ) {}

FWATCard WATCardOffice::create(unsigned int sid, unsigned int amount, WATCard *&card) {    // need to pass amount from original watcard
	Future_ISM<WATCard *> *fwatCard = new FWATCard();
	Args *args = new Args(sid, amount, card);
	Job *newJob = new Job(*args);
	newJob -> result = *fwatCard;
	jobQueue.push(newJob);

	return *fwatCard; 
}

FWATCard WATCardOffice::transfer(unsigned int sid, unsigned int amount, WATCard *card) {
	Future_ISM<WATCard *> *fwatCard = new FWATCard();
	Args *args = new Args(sid, amount, card);
	Job *newJob = new Job(*args);
        newJob -> result = *fwatCard;
        jobQueue.push(newJob);

	return *fwatCard;
}

WATCardOffice::Job* WATCardOffice::requestWork() {
	// courier should only be here if there is a request
	Job *newJob = jobQueue.front();	
	jobQueue.pop();
	return newJob;
}
