#include "Soda.h"

using namespace std;

void WATCardOffice::main() {
    prt.print( Printer::WATCardOffice, 'S' );
	// create pool of numCouriers
	Courier **couriers = new Courier*[numCouriers];
	for (unsigned int i = 0; i < numCouriers; i++) {
		couriers[i] = new Courier(bank, this, prt);
	}
	for (;;) {
		_Accept ( ~WATCardOffice ) {
			for( unsigned int i = 0; i < numCouriers; i++ ){
				_Accept(requestWork) {}
			}
			break;
		} or _Accept ( create, transfer ) {
			_Accept(requestWork) {}
		}
//			jobsAvailable.signal();

	}
	for(unsigned int i = 0 ; i < numCouriers ; i++) {
                delete couriers[i];
        }
	delete couriers;
	prt.print( Printer::WATCardOffice, 'F' );
}

void WATCardOffice::Courier::main() {
	// infinite loop
	int sid = 0;
	int amount = 0;
	int lostChance = 0;
	int originalBalance = 0;
	prt.print( Printer::Courier, sid, 'S' );
	for (;;) {
	   _Accept ( ~Courier ) {
	   	break;
	   } else {
		// sleep on a cond variable
	//	office->jobsAvailable.wait();
		if (office->jobQueue.empty()) {
			prt.print( Printer::Courier, sid, 'F' );
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
		delete newJob;
	   }
	}
}

WATCardOffice::WATCardOffice(Printer &prt, Bank &bank, unsigned int numCouriers) : prt ( prt ), bank ( bank ), numCouriers ( numCouriers ) {}

WATCardOffice::~WATCardOffice() {
	prt.print( Printer::WATCardOffice, 'F' );

}

WATCardOffice::Courier::Courier(Bank &bank, WATCardOffice *office, Printer &prt) : bank ( bank ), office ( office ), prt ( prt ) {}

FWATCard WATCardOffice::create(unsigned int sid, unsigned int amount, WATCard *&card) {    // need to pass amount from original watcard
	Future_ISM<WATCard *> *fwatCard = new FWATCard();
	Args *args = new Args(sid, amount, card);
	Job *newJob = new Job(*args);
	newJob -> result = *fwatCard;
	jobQueue.push(newJob);
	prt.print( Printer::WATCardOffice, 'C', sid, amount );
	return *fwatCard;
}

FWATCard WATCardOffice::transfer(unsigned int sid, unsigned int amount, WATCard *card) {
	Future_ISM<WATCard *> *fwatCard = new FWATCard();
	Args *args = new Args(sid, amount, card);
	Job *newJob = new Job(*args);
        newJob -> result = *fwatCard;
        jobQueue.push(newJob);
	prt.print( Printer::WATCardOffice, 'T', sid, amount );

	return *fwatCard;
}

WATCardOffice::Job* WATCardOffice::requestWork() {
	// courier should only be here if there is a request
	Job *newJob = jobQueue.front();
	jobQueue.pop();
	prt.print( Printer::WATCardOffice, 'W' );
	return newJob;
}
