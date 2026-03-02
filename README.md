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

**Conclusiones:**
* **Velocidad de ejecución:** La resolución es exponencialmente más rápida que la generación. Esto ocurre porque el generador debe recorrer obligatoriamente cada espacio disponible del mapa, mientras que el solucionador se detiene de inmediato al encontrar la meta.
* **El límite de la recursividad:** Al intentar generar un laberinto cuadrado grande (51x51), el programa colapsó. Descubrí que llamar a la función recursiva tantas veces seguidas crea un problema de memoria en el hardware (un desbordamiento de pila o *Stack Overflow*).

**¿Qué haría distinto la próxima vez?**
Para escalar este proyecto y poder generar laberintos masivos sin que el programa explote, reemplazaría el enfoque recursivo por un algoritmo **Iterativo**. Utilizaría una estructura de datos de tipo Pila (*Stack*) manual para gestionar el retroceso, liberando así a la memoria RAM de la carga de las llamadas a funciones anidadas.