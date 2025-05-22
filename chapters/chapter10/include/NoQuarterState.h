#ifndef NOQUARTERSTATE_H
#define NOQUARTERSTATE_H

#include "State.h"
#include "GumballMachine.h"
#include <iostream>

class NoQuarterState : public State
{
private:
    GumballMachine &machine; // Referencia a la maquina

public:
    explicit NoQuarterState(GumballMachine &machine) : machine(machine) {}
    ~NoQuarterState() override = default; // Destructor explicito

    void insertQuarter() override
    {
        std::cout << "Insertaste una moneda" << "\n";
        machine.setState(machine.getHasQuarterState());
    }
    void ejectQuarter() override
    {
        using std::cout, std::endl;
        cout << "No has insertado una moneda" << endl;
    }
    void turnCrank() override
    {
        std::cout << "Giraste la manivela pero no insertaste la moneda" << std::endl;
    }
    void dispense() override
    {
        std::cout << "Necesitas pagar primero" << std::endl;
    }

    void refill() override
    {
        // No hace nada pero esta obligado a implementarse
    }

    const char *getName() const override
    {
        return "Esperando Moneda"; // Nombre legible y obtenible
    }
};

#endif