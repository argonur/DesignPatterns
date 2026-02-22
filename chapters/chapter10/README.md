# State Desing Pattern
Este ejemplo implementa el patrón de diseño **`State`**, el cual permite que un objeto altere su comportamiento cuando cambia su estado interno.
Dicho objeto parecera cambiar de clase.

## ¿Como funciona?
Este patrón de diseño encapsula el estado en clases separadas y delega al objeto que representa el estado actual.

## Ejemplo: Maquina de chicles
En este ejercicio de ejemplo, cuando la maquina de chicles se encuentra en un estado `NoQuarterState` y se inserta una moneda, el comportamiento es *Acepta la moneda*, muy diferente a cuando esta en un estado `HasQuarterState` en donde la maquina *rechaza la moneda*.

## Ejecución del programa
Se espera que el comportamiento del programa sea el siguiente:
```bash
/chapter10/build$ ./main

---- Estado Inicial de la Maquina ----
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2004
Inventario: 5 gumballs
Estado: Esperando Moneda
----------------------------
Insertaste una moneda
Giraste la manivela
Un chicle sale rodando....
-------------------------------------------
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2004
Inventario: 4 gumballs
Estado: Esperando Moneda
----------------------------
Insertaste una moneda
Moneda devuelta
Giraste la manivela pero no insertaste la moneda
Necesitas pagar primero
-------------------------------------------
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2004
Inventario: 4 gumballs
Estado: Esperando Moneda
----------------------------
Insertaste una moneda
Giraste la manivela
Un chicle sale rodando....
Insertaste una moneda
Giraste la manivela
Un chicle sale rodando....
--------------------------------
ERES EL GANADOR!! Te llevas 2 chicles por el precio de 1
--------------------------------
Un chicle sale rodando....
No has insertado una moneda
-------------------------------------------
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2004
Inventario: 1 gumballs
Estado: Esperando Moneda
----------------------------
---- La maquina de chicles ha sido rellenada. el nuevo inventario es: 5 ----
Insertaste una moneda
No puedes insertar otra moneda
Giraste la manivela
Un chicle sale rodando....
Insertaste una moneda
Giraste la manivela
Un chicle sale rodando....
Insertaste una moneda
Giraste la manivela
Un chicle sale rodando....
-------------------------------------------
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2004
Inventario: 2 gumballs
Estado: Esperando Moneda
----------------------------
```