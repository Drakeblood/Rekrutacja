#include "TicketMachine.h"
#include <iostream>
#include "StringHelper.h"

TicketMachine::TicketMachine()
	: running(true)
	, state(ETicketMachineState::HOME)
	, balance(0)
{

}

void TicketMachine::run()
{
	if (state == ETicketMachineState::HOME) home();
	else if (state == ETicketMachineState::TICKET_SELECTION) ticketSelection();
	else if (state == ETicketMachineState::TICKET_PRINTING) ticketPrinting();
	else if (state == ETicketMachineState::CHANGE) change();
	else if (state == ETicketMachineState::TRANSACTION_CANCELED) transactionCanceled();
}

void TicketMachine::home()
{
	std::cout << "Witaj, z tej strony automat biletowy miasta Kraków, oczekujê wrzucenia do mnie pieniêdzy\n";

	std::string inputCash;
	std::getline(std::cin >> std::ws, inputCash);
	
	auto separated = StringHelper::split(inputCash, ",");

	for (int i = 0; i < separated.size(); i++)
	{
		balance += atoi(separated[i].c_str());
	}

	state = ETicketMachineState::TICKET_SELECTION;
}

void TicketMachine::change()
{
	int change[3]{ 0 };
	for (int i = 0; i < 3; i++)
	{
		while (balance - changeDenominations[i] >= 0)
		{
			balance -= changeDenominations[i];
			change[i] += 1;
		}
	}

	std::cout << "Bilet zosta³ wydrukowany oto Twoja reszta: ";
	for (int i = 0; i < 3; i++)
	{
		std::cout << change[i] << "*" << changeDenominations[i] << " z³ ";
	}
	std::cout << "\n¯yczê mi³ego dnia Twój bilecik " << selectedTicket << " oczekuje na odbiór\n";

	state = ETicketMachineState::HOME;
}

void TicketMachine::ticketSelection()
{
	std::cout << "Twoje saldo wynosi: " << balance << ", wybierz bilet który chcesz kupiæ lub \"0\" aby anulowaæ: ";

	for (int i = 0; i < availableTicketsCostLength; i++)
	{
		std::cout << availableTicketsCost[i];
		if (i < availableTicketsCostLength - 1) std::cout << ", ";
	}
	std::cout << std::endl;

	std::cin >> selectedTicket;

	if (selectedTicket == 0)
	{
		state = ETicketMachineState::TRANSACTION_CANCELED;
		return;
	}

	bool bFound = false;
	for (int i = 0; i < availableTicketsCostLength; i++)
	{
		if (availableTicketsCost[i] == selectedTicket)
		{
			bFound = true;
			break;
		}
	}

	if (!bFound)
	{
		ticketTransactionFail("Wybrano nieistniej¹ct bilet. Czy chcesz kontynuowaæ operacjê? (Y/n) ");
		return;
	}
	if (selectedTicket > balance)
	{
		ticketTransactionFail("Nie masz wystarczaj¹cych œrodków do zakupu tego biletu. Czy chcesz kontynuowaæ operacjê? (Y/n) ");
		return;
	}

	balance -= selectedTicket;
	state = ETicketMachineState::TICKET_PRINTING;
}

void TicketMachine::ticketTransactionFail(const std::string&& message)
{
	std::cout << message;

	std::string option;
	std::cin >> option;

	if (option == "Y" || option == "y")
	{
		state = ETicketMachineState::TICKET_SELECTION;
	}
	else
	{
		state = ETicketMachineState::TRANSACTION_CANCELED;
	}
}

void TicketMachine::ticketPrinting()
{
	std::cout << "Drukowanie biletu...\n";
	state = ETicketMachineState::CHANGE;
}

void TicketMachine::transactionCanceled()
{
	std::cout << "Oddajê Twoje monety\n";
	balance = 0;
	state = ETicketMachineState::HOME;
}