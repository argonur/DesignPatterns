#pragma once
// #ifndef WINNERSTATE_H
// #define WINNERSTATE_H

#include "State.h"
#include "GumballMachine.h"
#include <iostream>

class WinnerState : public State
{
private:
    GumballMachine &machine;

public:
    explicit WinnerState(GumballMachine &machine) : machine(machine) {}
    ~WinnerState() override = default;

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
        if (machine.getCount() == 0)
        {
            machine.setState(machine.getSoldOutState());
        }
        else
        {
            std::cout << "--------------------------------" << std::endl;
            std::cout << "\033[1;32mERES EL GANADOR!! Te llevas 2 chicles por el precio de 1\033[0m" << std::endl;
            std::cout << "--------------------------------" << std::endl;
            machine.releaseBall();

            if (machine.getCount() > 0)
            {
                machine.setState(machine.getNoQuarterState());
            }
            else
            {
                machine.setState(machine.getSoldOutState());
                std::cout << "Vaya... Nos quedamos sin inventario" << std::endl;
            }
        }
    }

    void refill() override
    {
        // No hace nada
    }

    const char *getName() const override
    {
        return "Usuario Ganador";
    }
};

// #endif