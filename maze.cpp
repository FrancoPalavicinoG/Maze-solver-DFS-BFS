#include "maze.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "node.hpp"
#include "queue.hpp"
#include "stack.hpp"
#include "linkedList.hpp"
#include <vector>
#include <algorithm>
#include <random>

using namespace eda;

namespace maze {

const unsigned char Maze::WALL  = '@';
const unsigned char Maze::EMPTY = '-';
const unsigned char Maze::PATH = '#';
const unsigned char Maze::FINAL = 'X';
const int Maze::NORTH= 0;
const int Maze::SOUTH= 1;
const int Maze::EAST= 2;
const int Maze::WEST= 3;

Maze::Maze(int h, int w):
		height(h),
		width(w),
		grid(nullptr){
	dir[0] = NORTH;
	dir[1] = SOUTH;
	dir[2] = EAST;
	dir[3] = WEST;
	std::srand(time(0));
	generate_maze(h, w);

}

void Maze::reset_maze(int h, int w){
	delete_maze();
	height = h;
	width= w;
	grid = new uchar*[height];
	for (int i = 0; i < height; i++){
		grid[i] = new uchar[width];
		for (int j = 0; j < width; j++){
			grid[i][j] = 1;
		}
	}
}

void Maze::generate_maze(int h, int w){
	reset_maze(h, w);
	visit(0,0);
}

void Maze::delete_maze(){
	if (grid != nullptr){
		for (int i = 0; i < height; i++){
			delete[] grid[i];
		}
		delete[] grid;
	}
}

void Maze::shuffle_dir(){
	for (int i = 0; i < 4; i++){
		int r = std::rand() & 3;
		int aux = dir[r];
		dir[r] = dir[i];
		dir[i] = aux;
	}
}

bool Maze::inRange(int i, int j){
	return ((i >= 0) && (i< height) && (j >= 0) && (j< width));
}

void Maze::visit(int i, int j){
	int dx  = 0;
	int dy = 0;
	int i_next = 0;
	int j_next = 0;
	grid[i][j] = 0;
	shuffle_dir();
	//std::cout << dir[0] << " " << dir[1] << " " << dir[2] << " "<< dir[3] << std::endl;
	for(int k = 0; k <  4; k++){
		//std::cout << dir[k] << std::endl;
		if (dir[k] == NORTH){
			dy = -1;
			dx = 0;
		}
		else if (dir[k] == SOUTH){
			dy = 1;
			dx = 0;
		}
		else if (dir[k] == EAST){
			dy = 0;
			dx = 1;
		}
		else if (dir[k] == WEST){
			dy = 0;
			dx = -1;
		}
		i_next = i + (dy<<1);
		j_next = j + (dx<<1);
		if (inRange(i_next, j_next) && grid[i_next][j_next] == 1){
			grid[i_next - dy][j_next - dx] = 0;
			visit(i_next, j_next);

		}
	}
}

void Maze::print(std::string color){

	const std::string ANSI_RESET = "\x1b[0m";
	const std::string ANSI_FINAL = "\e[1;93m";

	char LIMIT = '=';
	std::cout << " Maze ( "<< height << " x " << width << " ) " << std::endl;
	std::cout << " ";
	for (int j = 0; j < width; j++){
		std::cout << LIMIT;
	}
	std::cout << " ";
	std::cout << std::endl;
	for (int i = 0; i < height; i++){
		std::cout << "|";
		for (int j = 0; j < width; j++){
			if (grid[i][j] == 0) {
				std::cout << EMPTY;
			}
			else if (grid[i][j] == 1) {
				std::cout << WALL;
			}
			else if (grid[i][j] == 2) {
				std::cout << color << PATH << ANSI_RESET;
				grid[i][j] = 0;
			}
			else if (grid[i][j] == 3) {
				std::cout << ANSI_FINAL << FINAL << ANSI_RESET;
				grid[i][j] = 0;
			}
			else if (grid[i][j] == 4) {
				std::cout << ANSI_FINAL << "O" << ANSI_RESET;
				grid[i][j] = 0;
			}
		}
		std::cout << "|";
		std::cout << std::endl;
	}
	std::cout << " ";
	for (int j = 0; j < width; j++){
		std::cout << LIMIT;
	}
	std::cout << " ";
	std::cout << std::endl;
}

LinkedList Maze::solve_pila(int f1, int c1, int f2, int c2){
	std::vector <std::vector <int>> visited(height, std::vector<int>(width, 0));
	Stack stack;
	LinkedList sol;

	// Primer nodo
	stack.push(f1, c1);
	visited[f1][c1] = 1;
	sol.insertLast(f1, c1);

	int foundPath = 0;

	while(!stack.isEmpty()){
		Node * ptr = stack.top();
		int row = ptr->getRow();
		int col = ptr->getCol();

		int found = 0;
		//Camino encontrado
		if (row == f2 && col  == c2){
			sol.insertLast(row, col);
			foundPath = 1;
            break;
		}
		//shuffle aleatorio de direcciones
		shuffle_dir();
    	for(int k = 0; k <  4; k++){
			int dy = 0;
			int dx = 0;
			if (dir[k] == NORTH){
				dy = -1;
				dx = 0;
			}
			else if (dir[k] == SOUTH){
				dy = 1;
				dx = 0;
			}
			else if (dir[k] == EAST){
				dy = 0;
				dx = 1;
			}
			else if (dir[k] == WEST){
				dy = 0;
				dx = -1;
			}
			int row_aux = row + dx;
			int col_aux = col + dy;

			if ((inRange(row_aux, col_aux)) && (grid[row_aux][col_aux] == 0) && (visited[row_aux][col_aux] == 0)){
				stack.push(row_aux, col_aux);
				visited[row_aux][col_aux] = 1;
				sol.insertLast(row_aux, col_aux);
				found = 1;
				break;
			}
		}	

		if (found != 1){
			stack.pop();
			sol.removeAfter(row, col);
		}
	}

	if (foundPath != 1) {
    	std::cout << "No existe solución" << std::endl;
	}

	for (Node* node = sol.head; node != nullptr; node = node->getNext()) {
        int x = node->getRow();
        int y = node->getCol();
        grid[x][y] = 2;
    }
	grid[f1][c1] = 4;
	grid[f2][c2] = 3;

	return sol;
}

LinkedList Maze::solve_cola(int f1, int c1, int f2, int c2){
	std::vector <std::vector <int>> visited(height, std::vector<int>(width, 0));
	Queue queue;
	LinkedList sol;

	// Primer nodo
	queue.push(f1, c1);
	visited[f1][c1] = 1;
	sol.insertLast(f1, c1);

	int foundPath = 0;

	while(!queue.isEmpty()){
		Node * ptr = queue.top();
		int row = ptr->getRow();
		int col = ptr->getCol();

		int found = 0;
		
		//Camino encontrado
		if (row == f2 && col  == c2){
			sol.insertLast(row, col);
			foundPath = 1;
            break;
		}
		//shuffle aleatorio de direcciones
		shuffle_dir();
    	for(int k = 0; k <  4; k++){
			int dy = 0;
			int dx = 0;
			if (dir[k] == NORTH){
				dy = -1;
				dx = 0;
			}
			else if (dir[k] == SOUTH){
				dy = 1;
				dx = 0;
			}
			else if (dir[k] == EAST){
				dy = 0;
				dx = 1;
			}
			else if (dir[k] == WEST){
				dy = 0;
				dx = -1;
			}
			int row_aux = row + dx;
			int col_aux = col + dy;

			if ((inRange(row_aux, col_aux)) && (grid[row_aux][col_aux] == 0) && (visited[row_aux][col_aux] == 0)){
				queue.push(row_aux, col_aux);
				visited[row_aux][col_aux] = 1;
				sol.insertLast(row_aux, col_aux);
				found = 1;
				break;
			}
		}	
		if (found != 1){
			queue.pop();
		}
	}

	if (foundPath == 0) {
    	std::cout << "No existe solución" << std::endl;
	}


	for (Node* node = sol.head; node != nullptr; node = node->getNext()) {
        int x = node->getRow();
        int y = node->getCol();
        grid[x][y] = 2;
    }
	grid[f1][c1] = 4;
	grid[f2][c2] = 3;
	return sol;
}

LinkedList Maze::solve_pila(){
	int c1 = std::rand() % width - 1;
	int f1 = 0;
	int c2 = std::rand() % width - 1;
	int f2 = height - 1;
	std::cout << "Punto de inicio: (" << f1 << "," << c1 << ")" <<std::endl;
	std::cout << "Punto final: (" << f2 << "," << c2 << ")" <<std::endl;
	LinkedList sol = solve_pila(f1, c1, f2, c2);
	return sol;
}
LinkedList Maze::solve_cola(){
	int c1 = std::rand() % width -1;
	int f1 = 0;
	int c2 = std::rand() % width -1;
	int f2 = height -1;
	std::cout << "Punto de inicio: (" << f1 << "," << c1 << ")" <<std::endl;
	std::cout << "Punto final: (" << f2 << "," << c2 << ")" <<std::endl;
	LinkedList sol = solve_cola(f1, c1, f2, c2);
	return sol;
}
}
