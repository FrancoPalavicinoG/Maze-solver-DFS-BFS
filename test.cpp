#include <iostream>
#include "maze.hpp"

int main(int nargs, char** vargs){
	maze::Maze laberinto(21,21);
	eda::LinkedList sol = laberinto.solve_pila();
    std::string red = "\e[1;91m";
    std::string green = "\e[1;92m";
    laberinto.print(green);
    eda::LinkedList sol2 = laberinto.solve_cola();
    laberinto.print(red);
    // Imprime la solución
    std::cout << "Sol:" << std::endl;
    //sol.print();

    return 0;
}