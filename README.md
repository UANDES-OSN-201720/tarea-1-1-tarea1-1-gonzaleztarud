## Tarea 1.1

#### Introducción

En el presente informe detallaremos algunas de las funcionalidades de nuestro programa, así como de algunas dificultades que enfrentamos al realizarla.

#### Descripción de las funciones principales del programa, tanto del proceso de casa matriz, como las sucursales.

Nuestro programa implementa las siguientes funciones:
* Permite que, al iniciar una sucursal, el usuario determine el número de cuentas con las cuales desea hacer la simulación, sino, * crea 1000 por defecto con montos entre los rangos descritos en el enunciado al ejecutar el comando “init”.
* Permite listar las sucursales que están activas, así como el número de cuentas asociadas a ellas mediante dos arreglos con el comando “list”.
* Permite generar un archivo CSV con el id de una sucursal, el cual contiene todos los números de sus cuentas y el monto de cada una de ellas con el comando “dump_accs”
* Permite terminar el proceso de una sucursal con el comando “kill”.

#### Problemas encontrados en la implementación  del sistema. En particular, si el programa se cae en algún punto de la ejecución, describir donde está la mayor sospecha del problema que causa la caída.

El programa no reconoce el manejo de errores, solo en el dump_acces. En general, este se queda ejecutando muchas veces sin reconocer el input. Además, tuvimos dificultades en el manejo de acceso a memoria, por ejemplo, tratando de crear un arreglo de 1000 elementos y en el input de elementos por consola que no eran comandos (el número de cuentas que quería el usuario, por ejemplo).

#### Funciones del sistema sin implementar. Describir aquellas funciones que no pudieron implementarse por razones de complejidad y/o tiempo.

Funciones sin implementar:
* En Procesos faltó implementar threads debido a falta de tiempo
* En comunicación entre procesos faltó la implementación de pipes entre sucursal-matriz y matriz-sucursal debido a la complejidad.

* En las operaciones no se implementó:(debido a la complejidad)
  * quit está implementado parcialmente
  * dump 
  * dump_errs

El mayor problema de las funciones que faltaron fue el no haber tenido suficiente conocimiento y práctica en el lenguaje C lo que nos hizo demorar bastante en hacer cosas “sencillas” , entonces esto nos afectó en la efectividad del desarrollo de la tarea.

## Tarea 1.2

#### Descripción de las funciones principales del programa, tanto del proceso de casa matriz, como las sucursales.

Casa Matriz: 
* Crea un thread para gestionar sucursales.

Sucursales:
* Permite que, al iniciar una sucursal, el usuario determine el número de terminales que desea que se ejecuten, con un mínimo de 1 y un máximo de 8.
* Permite listar las sucursales que están activas, así como el número de cuentas y terminales asociadas a ellas mediante dos arreglos con el comando “list”.
* Permite generar un archivo CSV con el id de una sucursal, el cual contiene todos los números de sus cuentas y el monto de cada una de ellas con el comando “dump_accs”
* Permite generar un archivo CSV con el id de una sucursal, el cual contiene todos los números de sus cuentas y el monto de cada una de ellas con el comando “dump”
* Permite terminar el proceso de una sucursal con el comando “kill”.


#### Problemas encontrados en la implementación del sistema, y en particular, problemas de concurrencia y sincronización que se hayan suscitado con el uso de threads. En particular, si el programa se cae en algún punto de la ejecución, describir dónde está la mayor sospecha del problema que causa la caída.

Tuvimos dificultades en cómo generar transacciones, específicamente en el método “MakeTransactions”. También hubo problemas en la implementación para guardar las transacciones con el objetivo de usarlas en el “dump”.

#### Funciones del sistema sin implementar. Describir aquellas funciones que no pudieron implementarse por razones de complejidad y/o tiempo.

Funciones sin implementar:
* En comunicación entre procesos faltó la implementación de pipes entre sucursal-matriz y matriz-sucursal debido a la complejidad.
* En las operaciones no se implementó:(debido a la complejidad)
  * quit está implementado parcialmente
  * dump está implementado parcialmenete
  * dump_errs

El mayor problema de las funciones que faltaron fue el no haber tenido suficiente conocimiento y práctica en el lenguaje C lo que nos hizo demorar bastante en hacer cosas “sencillas” , entonces esto nos afectó en la efectividad del desarrollo de la tarea.

