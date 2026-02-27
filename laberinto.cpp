#include <iostream>
#include <string>
#include <vector>

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
    std::cout << "Listo para generar la matriz de " <<ancho << "x" << alto << std::endl;

    // Creación de la matriz dinámica.
    std::vector<std::vector<char>> laberinto(alto, std::vector<char>(ancho, '#'));


    for (int fila = 0; fila < alto; fila++) {
        for (int columna = 0; columna < ancho; columna++) {
            std::cout << laberinto[fila][columna];
        }
        std::cout<<std::endl;
    }
    return 0;
}