#ifndef HASCUARTERSTATE_H
#define HASQUARTERSTATE_H

#include "State.h"
#include "GumballMachine.h"
#include <iostream>
#include <random>

class HasQuarterState : public State
{
private:
    GumballMachine &machine;

public:
    explicit HasQuarterState(GumballMachine &machine) : machine(machine) {}
    ~HasQuarterState() override = default;

    void insertQuarter() override
    {
        std::cout << "No puedes insertar otra moneda" << std::endl;
    }

    void ejectQuarter() override
    {
        std::cout << "Moneda devuelta" << std::endl;
        machine.setState(machine.getNoQuarterState());
    }
    void turnCrank() override
    {
        int numeroAleatorio = machine.generateRandomNumber();
        std::cout << "Giraste la manivela" << std::endl;
        if (numeroAleatorio == 10 && machine.getCount() > 0)
        {
            machine.setState(machine.getWinnerState());
        }
        else
        {
            machine.setState(machine.getSoldState());
        }
    }

    void dispense() override
    {
        std::cout << "No se despacha ningun chicle" << std::endl;
    }

    void refill() override
    {
        // No hace nada pero esta obligado a implementarse
    }

    const char *getName() const override
    {
        return "Moneda Insertada";
    }
};
#endif