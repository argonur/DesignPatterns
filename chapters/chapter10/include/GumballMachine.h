#ifndef GUMBALLMACHINE_H
#define GUMBALLMACHINE_H

#include <memory>
#include "State.h"
#include <random>

class GumballMachine
{
private:
    State *currentState; // Estado actual
    int count = 0;       // Inventario de chicles

    // Motor y distribucion para numeros aleatorios
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> distribucion;

    // Estados posibles
    std::unique_ptr<State> soldOutState;
    std::unique_ptr<State> noQuarterState;
    std::unique_ptr<State> hasQuarterState;
    std::unique_ptr<State> soldState;
    std::unique_ptr<State> winnerState;

public:
    GumballMachine(int numberGumballs);

    void setState(State &newState);

    // Acciones delegadas al estado actual
    void insertQuarter() { currentState->insertQuarter(); }
    void ejectQuarter() { currentState->ejectQuarter(); }
    void turnCrank()
    {
        currentState->turnCrank();
        currentState->dispense();
    }

    // Getters para modificaciones de estado
    State &getNoQuarterState() { return *noQuarterState; }
    State &getHasQuarterState() { return *hasQuarterState; }
    State &getSoldOutState() { return *soldOutState; }
    State &getSoldState() { return *soldState; }
    // Nuevo estado para el cliente ganador
    State &getWinnerState() { return *winnerState; }

    // Versiones const para cuando se necesiten en modo solo lectura
    const State &getNoQuarterState() const { return *noQuarterState; }
    const State &getHasQuarterState() const { return *hasQuarterState; }
    const State &getSoldOutState() const { return *soldOutState; }
    const State &getSoldState() const { return *soldState; }
    const State &getWinnerState() const { return *winnerState; }

    // Metodos de utilidad
    void releaseBall();                    // Metodo para interaccion Maquina - Usuario
    int getCount() const { return count; } // Metodo para obtener el inventario
    void printStatus() const;              // Metodo para mostrar el estado de la maquina
    int generateRandomNumber();            // Metodo para obtener numero aleatorio
    void refill(int cantidad);
};

#endif