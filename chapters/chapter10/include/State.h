/*
> Aqui definiremos la interfaz State de la cual heredaran los estados de GumballMachine
*/

#ifndef STATE_H
#define STATE_H
// Declaración anticipada de GumballMachine para evitar problemas de memoria y punteros.
class GumballMachine;

class State
{

public:
    virtual ~State() = default;       // Destructor que se puede heredar. | debe implementarse por defecto
    virtual void insertQuarter() = 0; // Insertar moneda
    virtual void ejectQuarter() = 0;  // Expulsar moneda
    virtual void turnCrank() = 0;     // Girar manivela
    virtual void dispense() = 0;      // Depachar
    virtual void refill() = 0;        // Para rellenar la maquina

    virtual const char *getName() const = 0; // Para obtener el nombre en cada Estado
};

#endif