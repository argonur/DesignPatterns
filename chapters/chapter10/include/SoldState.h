#ifndef SOLDSTATE_H
#define SOLDSTATE_H

#include "State.h"
#include "GumballMachine.h"
#include <iostream>

class SoldState : public State
{
private:
    GumballMachine &machine;

public:
    explicit SoldState(GumballMachine &machine) : machine(machine) {}
    ~SoldState() override = default;

    void insertQuarter() override
    {
        std::cout << "Porfavor espera, ya te estamos dando un chicle" << std::endl;
    }

    void ejectQuarter() override
    {
        std::cout << "Lo siento, ya giraste la manivela" << std::endl;
    }

    void turnCrank() override
    {
        std::cout << "Girarla 2 veces no te dara otro chicle" << std::endl;
    }

    void dispense() override
    {
        machine.releaseBall();
        if (machine.getCount() > 0)
        {
            machine.setState(machine.getNoQuarterState());
        }
        else
        {
            std::cout << "Oops, nos quedamos sin chicles" << std::endl;
            machine.setState(machine.getSoldOutState());
        }
    }

    void refill() override
    {
        // No hace nada pero esta obligado a implementarse
    }

    const char *getName() const override
    {
        return "Despachando chicle";
    }
};

#endif