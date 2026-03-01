#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

// Función para crear laberinto
void generarLaberinto(std::vector<std::vector<char>>& laberinto, int filaActual, int columnaActual, int alto, int ancho) {
    // La celda actual se marca en camino
    laberinto[filaActual][columnaActual] = '*';
    // Definición de las 4 direcciones
    std::vector<std::pair<int, int>> direcciones = {{-2, 0}, {2, 0}, {0, -2}, {0, 2}};

    // Mezclamos las direcciones aleatoriamente
    std::random_device rd;  // Obtiene un numero aleatorio del hardware
    std::mt19937 g(rd());   // Generador de números pseudoaleatorios
    std::shuffle(direcciones.begin(), direcciones.end(), g);

    // Intentamos cavar en cada una de las 4 direcciones mezcladas
    for (auto dir : direcciones) {
        int destinoFila = filaActual + dir.first;
        int destinoColumna = columnaActual + dir.second;

        // Validamos que el destino esté dentro de los límites del mapa y sea un '#'
        if (destinoFila > 0 && destinoFila < alto - 1 && destinoColumna > 0 && destinoColumna < ancho - 1 && laberinto[destinoFila][destinoColumna] == '#') {
            // Calcular la pared intermedia a demoler
            int paredFila = filaActual + (dir.first / 2);
            int paredColumna = columnaActual + (dir.second / 2);
            // Demoler la pared intermedia
            laberinto[paredFila][paredColumna] = '*';
            // Recursividad: Se repite el proceso
            generarLaberinto(laberinto, destinoFila, destinoColumna, alto, ancho);
        }
    }
}

// Función para resolver el laberinto
bool resolverLaberinto(std::vector<std::vector<char>>& laberinto, int filaActual, int columnaActual, int destinoFila, int destinoColumna) {
    // Caso base
    if (filaActual == destinoFila && columnaActual == destinoColumna) {
        laberinto[filaActual][columnaActual] = 'O';
        return true;
    }

    // Validación de límites y obstáculos
    if (filaActual < 0 || filaActual >= (int)laberinto.size() ||
        columnaActual < 0 || columnaActual >= (int)laberinto[0].size()||
        laberinto[filaActual][columnaActual] != '*') {
        return false;
        }
    
    // Camino potencial
    laberinto[filaActual][columnaActual] = 'O';
    // Recursividad para determinar si es que se mantiene el camino potencial
    if (resolverLaberinto(laberinto, filaActual - 1, columnaActual, destinoFila, destinoColumna) ||
        resolverLaberinto(laberinto, filaActual + 1, columnaActual, destinoFila, destinoColumna) ||
        resolverLaberinto(laberinto, filaActual, columnaActual - 1, destinoFila, destinoColumna) ||
        resolverLaberinto(laberinto, filaActual, columnaActual + 1, destinoFila, destinoColumna)) {
        return true;
        }
    
    // Backtracking - para determinar que no hay salida en este punto
    laberinto[filaActual][columnaActual] = ' ';
    return false;
}

int main(int argc, char* argv[]) {
    // Validación de entrada
    if (argc != 3) {
        std::cerr << "Error: Faltan parametros." << std::endl;
        std::cerr << "Uso correcto: ./laberinto <ancho> <alto>" << std::endl;
        return 1;
    }
    // Conversión de tipo de datos --- "IMPLEMENTAR ALGUNA LOGICA DE VALIDACION DE NUMEROS ENTEROS"
    int ancho = std::stoi(argv[1]);
    int alto = std::stoi(argv[2]);
    // Imprimir para confirmar datos correctos
    std::cout << "Matriz de " <<ancho << " x " << alto << std::endl;

    // Creación de la matriz dinámica
    std::vector<std::vector<char>> laberinto(alto, std::vector<char>(ancho, '#'));

    // Inicio de la medición del tiempo
    auto inicioGeneracion = std::chrono::high_resolution_clock::now();

    // Función para crear laberinto
    generarLaberinto(laberinto, 1, 1, alto, ancho);
    laberinto[1][0] = '*';
    laberinto[alto - 2][ancho - 1] = '*';

    // Fin de la medición del tiempo
    auto finGeneracion = std::chrono::high_resolution_clock::now();
    // Calcular y guardar el tiempo de generación del laberinto
    std::chrono::duration<double, std::milli> tiempo_generacion_ms = finGeneracion - inicioGeneracion;

    // Impresión de la matriz dinámica
    for (int fila = 0; fila < alto; fila++) {
        for (int columna = 0; columna < ancho; columna++) {
            std::cout << laberinto[fila][columna];
        }
        std::cout<<std::endl;
    }
    // Reporte del tiempo de generación del laberinto
    std::cout << "Tiempo de generacion: " << tiempo_generacion_ms.count() << " ms\n";

    // Definición de la entrada y salida del algoritmo solucionadaor del laberinto
    int inicioFila = 1;
    int inicioColumna = 0;
    int metaFila = alto - 2;
    int metaColumna = ancho - 1;

    // Inicio de medición del tiempo
    auto inicioResolucion = std::chrono::high_resolution_clock::now();

    // Guardar resultado de la resolución del laberinto
    bool resuelto = resolverLaberinto(laberinto, inicioFila, inicioColumna, metaFila, metaColumna);

    // Fin de la medición del tiempo y guardamos el tiempo de resolución el laberinto
    auto finResolucion = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tiempo_resolucion_ms = finResolucion - inicioResolucion;

    //Impresion del laberinto ya resuelto
    for (int fila = 0; fila < alto; fila++) {
        for (int columna = 0; columna < ancho; columna++) {
            std::cout << laberinto[fila][columna];
        }
        std::cout << std::endl;
    }
    // Reporte final del estado de resolución
    if (resuelto) {
        std::cout << "Estado: RESUELTO\n";
    } else {
        std::cout << "Estado: FAIL\n";
    }
    // Reporte del tiempo de resolución del laberinto
    std::cout << "Tiempo de resolucion: " << tiempo_resolucion_ms.count() << " ms\n";

    return 0;
}