#include "GumballMachine.h"
#include "NoQuarterState.h"
#include "HasQuarterState.h"
#include "SoldState.h"
#include "SoldOutState.h"
#include "WinnerState.h"

GumballMachine::GumballMachine(int numberOfGumballs) : gen(rd()), count(numberOfGumballs), distribucion(1, 10)
{
    // Inicializamos todos los estados

    noQuarterState = std::make_unique<NoQuarterState>(*this);
    hasQuarterState = std::make_unique<HasQuarterState>(*this);
    soldOutState = std::make_unique<SoldOutState>(*this);
    soldState = std::make_unique<SoldState>(*this);
    winnerState = std::make_unique<WinnerState>(*this);

    // Estado actual
    currentState = (count > 0) ? noQuarterState.get() : soldOutState.get();
}

void GumballMachine::setState(State &newState)
{
    currentState = &newState;
}

void GumballMachine::releaseBall()
{
    if (count > 0)
    {
        std::cout << "Un chicle sale rodando...." << std::endl;
        count--;
    }
}

int GumballMachine::generateRandomNumber()
{
    return distribucion(gen);
}

void GumballMachine::refill(int count)
{
    this->count += count;
    std::cout << "---- La maquina de chicles ha sido rellenada. el nuevo inventario es: "
              << this->count << " ----"
              << std::endl;
    currentState->refill();
}

void GumballMachine::printStatus() const
{
    using std::cout, std::endl;

    cout << "Mighty Gumball, Inc.\n"
         << "C++-enabled Standing Gumball Model #2004" << endl;
    if (GumballMachine::getCount() > 0)
    {
        cout << "\033[32mInventario: \033[0m" << GumballMachine::getCount() << " gumballs" << endl;
    }
    else
    {
        cout << "\033[31mInventario: \033[0m" << GumballMachine::getCount() << " gumballs" << endl;
    }
    cout << "\033[33mEstado: \033[0m" << currentState->getName() << endl;
    cout << "----------------------------" << endl;
}
