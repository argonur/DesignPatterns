#ifndef SOLDOUTSTATE_H
#define SOLDOUTSTATE_H

#include "State.h"
#include "GumballMachine.h"
#include <iostream>

class SoldOutState : public State
{
private:
    GumballMachine &machine;

public:
    explicit SoldOutState(GumballMachine &machine) : machine(machine) {}
    ~SoldOutState() override = default;

    void insertQuarter() override
    {
        std::cout << "No puedes insertar una moneda, la maquina esta vacia" << std::endl;
    }

    void ejectQuarter() override
    {
        std::cout << "No has insertado una moneda" << std::endl;
    }

    void turnCrank() override
    {
        std::cout << "Debes pagar primreo" << std::endl;
    }

    void dispense() override
    {
        std::cout << "No se dispenso ningun chicle. Inventario vacio" << std::endl;
    }

    void refill() override
    {
        machine.setState(machine.getNoQuarterState());
    }

    const char *getName() const override
    {
        return "\033[31mInventario Agotado\033[0m";
    }
};

#endif