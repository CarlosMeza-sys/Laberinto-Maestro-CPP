# El Laberinto Maestro en C++
**Autor:** Carlos Daniel Meza Herrera

Un generador y solucionador automático de laberintos desarrollado en C++, creado como parte del reto "Penguin Academy". Este proyecto demuestra el uso de matrices dinámicas bidimensionales, validación de entradas por consola y algoritmos de búsqueda recursiva.

---

## 1. Generación del Laberinto
Para construir el escenario de manera aleatoria y asegurar que siempre exista un camino válido, implementé el algoritmo **Recursive Backtracker** (Algoritmo de Excavación por Túneles).

**Lógica de implementación:**
* El laberinto se inicializa como una matriz sólida de muros (`#`).
* El algoritmo simula un agente que avanza dando saltos de dos en dos casillas dentro del marco de seguridad de la matriz.
* Al encontrar una casilla válida, "cava" tanto la casilla de destino como la casilla intermedia, transformándolas en caminos transitables (`*`).
* Las direcciones se eligen de forma completamente aleatoria en cada paso. Si el agente llega a un punto sin salida, utiliza la recursividad para retroceder sobre sus propios pasos hasta encontrar una nueva ruta disponible, esculpiendo así todo el mapa.

## 2. Resolución Automática
Para la resolución automática, utilicé el algoritmo de **Backtracking** (Búsqueda con Retroceso), el cual evalúa los caminos disponibles para encontrar la salida sin caer en bucles infinitos.

**Lógica de implementación:**
* A medida que el algoritmo avanza por un camino válido, va tallando su rastro con el carácter `O` mayúscula.
* Si el agente llega a un callejón sin salida, reconoce que esa ruta es incorrecta. En ese momento, retrocede y reescribe esa `O` por un espacio en blanco (` `).
* Este cambio a espacio en blanco es crucial: le indica al algoritmo que ese camino ya fue explorado y descartado, evitando volver a entrar. 
* Al finalizar, el mapa impreso muestra únicamente el camino correcto marcado con `O`.

## 3. Descubrimientos y Análisis de Tiempos
Durante el desarrollo, realicé pruebas de estrés para medir el rendimiento de la CPU y la memoria utilizando la librería `<chrono>`:

| Tamaño de Matriz | Tiempo Generación | Tiempo Resolución | Estado Final |
| :--- | :--- | :--- | :--- |
| 11 x 11 | ~2.4 ms | ~0.01 ms | Éxito |
| 51 x 25 | ~4.59 ms | ~0.06 ms | Éxito |
| 51 x 51 | - | - | Fallo (Exit Code 127) |

## 4. Instrucciones de Ejecución
Este programa está diseñado para ejecutarse nativamente desde la terminal, utilizando **argumentos de línea de comandos** (parámetros que le entregamos al programa en el momento exacto de su arranque para definir su comportamiento).

### Requisitos Previos
Asegúrate de tener un compilador de C++ instalado en tu sistema (como `g++`, estándar en entornos Linux y WSL).

### Pasos para probar el código:

**Paso 1: Compilación**
Abre tu terminal, navega hasta el directorio donde se encuentra el archivo fuente y traduce el código a un archivo ejecutable utilizando el siguiente comando:
```bash
g++ laberinto.cpp -o laberinto
```
*(Este comando genera un nuevo archivo ejecutable llamado `laberinto` listo para ser utilizado).*

**Paso 2: Ejecución**
Para arrancar el programa, debes indicarle las dimensiones deseadas directamente en la terminal. Por reglas de diseño y para evitar errores estructurales, el tamaño mínimo permitido es de 5x5.
**Sintaxis correcta:**
```bash
./laberinto <ancho> <alto>
```
**Ejemplo de uso:**
Para generar y resolver automáticamente un laberinto de 21 columnas por 21 filas, ejecuta:
```bash
./laberinto 21 21
```
Si omites los parámetros o ingresas caracteres no válidos, el programa interceptará el error de forma segura y te mostrará las instrucciones de uso en pantalla sin colapsar.

## 5. Conclusiones y Mejoras Futuras
* **Velocidad de ejecución:** La resolución es exponencialmente más rápida que la generación. Esto ocurre porque el generador debe recorrer obligatoriamente cada espacio disponible del mapa, mientras que el solucionador se detiene de inmediato al encontrar la meta.
* **El límite de la recursividad:** Al intentar generar un laberinto cuadrado grande (51x51), el programa colapsó. Descubrí que llamar a la función recursiva tantas veces seguidas crea un problema de memoria en el hardware (un desbordamiento de pila o *Stack Overflow*).

**¿Qué haría distinto la próxima vez?**
Para escalar este proyecto y poder generar laberintos masivos sin que el programa explote, reemplazaría el enfoque recursivo por un algoritmo **Iterativo**. Utilizaría una estructura de datos de tipo Pila (*Stack*) manual para gestionar el retroceso, liberando así a la memoria RAM de la carga de las llamadas a funciones anidadas.