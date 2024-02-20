#pragma once
#include <iostream>

class board
{
	int** board_field; // Массив поля
	int size_x; // Ширина поля 
	int size_y; // Высота поля
	int zero_x; // Координаты нуля по x
	int zero_y; // Координаты нуля по y
	board* parent; // Ссылка на родительский узел
	int depth; // глубина поиска 
	int manhatten; // Манхэттенское расстояние

public:
	board(); // Конструктор по умолчанию
	board(int** arrayp, int x, int y); // Конструктор, принимающий массив
	~board(); // Деструктор, осовбождающий память в heap
	board(const board& brd); // Конструктор копирования
private:
	static void create_random(board& brd); // Метод, генерирующий состояние доски
	bool is_solvable(); // Можно ли решить текущую расстановку
	std::string to_string(board& brd);
	int manhattan(const board& goal); // Метод, возвращающий сумму М. расстояний между блоками и целью
	int size(); // Метод, возвращающий размер доски
	int hamming(); // Метод, возвращающий количество блоков не на своих местах
	bool is_goal(const board& goal); // Является ли текущая доска целью
	board& operator = (const board& brd);
	bool operator == (const board& brd) const;
	bool operator != (const board& brd) const;
	friend class Node;
	friend class Solution;
	friend class Solver;
	friend std::ostream& operator<<(std::ostream& os, const board& brd);
};

