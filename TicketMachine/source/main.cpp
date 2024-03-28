#include <iostream>
#include <locale>
#include "TicketMachine.h"

int main()
{
    setlocale(LC_CTYPE, "Polish");

    std::unique_ptr<TicketMachine> automat(new TicketMachine);

    while(automat->isRunning()) automat->run();

    return 0;
}