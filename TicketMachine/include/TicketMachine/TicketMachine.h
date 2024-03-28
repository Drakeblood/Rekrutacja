#pragma once

#include <string>

enum class ETicketMachineState
{
	HOME,
	TICKET_SELECTION,
	TICKET_PRINTING,
	CHANGE,
	TRANSACTION_CANCELED
};

class TicketMachine
{
public:
	TicketMachine();

	void run();

	void home();
	void ticketSelection();
	void ticketTransactionFail(const std::string&& message);
	void ticketPrinting();
	void transactionCanceled();
	void change();

	bool isRunning() { return running; }
private:
	bool running;
	ETicketMachineState state;

	int balance;
	int selectedTicket;

	static constexpr int availableTicketsCost[] = { 3, 4, 8, 10, 15 };
	static constexpr int availableTicketsCostLength = sizeof(availableTicketsCost) / sizeof(availableTicketsCost[0]);
	static constexpr int changeDenominations[] = { 5, 2, 1 };
};