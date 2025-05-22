#include <iostream>
#include "GumballMachine.h"

int main()
{
    using std::cout, std::endl;

    GumballMachine *gumballMachine = new GumballMachine(5);
    cout << "---- Estado Inicial de la Maquina ----" << endl;
    gumballMachine->printStatus();

    gumballMachine->insertQuarter();
    gumballMachine->turnCrank();

    cout << "-------------------------------------------" << endl;
    gumballMachine->printStatus();

    gumballMachine->insertQuarter();
    gumballMachine->ejectQuarter();
    gumballMachine->turnCrank();
    cout << "-------------------------------------------" << endl;
    gumballMachine->printStatus();

    gumballMachine->insertQuarter();
    gumballMachine->turnCrank();
    gumballMachine->insertQuarter();
    gumballMachine->turnCrank();
    gumballMachine->ejectQuarter();
    cout << "-------------------------------------------" << endl;
    gumballMachine->printStatus();

    gumballMachine->refill(4);
    gumballMachine->insertQuarter();
    gumballMachine->insertQuarter();
    gumballMachine->turnCrank();
    gumballMachine->insertQuarter();
    gumballMachine->turnCrank();
    gumballMachine->insertQuarter();
    gumballMachine->turnCrank();

    cout << "-------------------------------------------" << endl;
    gumballMachine->printStatus();

    delete gumballMachine;

    return 0;
}