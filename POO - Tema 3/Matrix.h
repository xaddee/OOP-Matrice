#pragma once

#include <iostream>

template <class T>
class Matrix
{
private:
	int _lines;
	int _columns;
	T **_matrix;

	void matrixAlloc();
	void matrixDealloc();
public:
	Matrix();
	Matrix(int, int);
	~Matrix();
	Matrix(const Matrix&);
	int getLines();
	int getColumns();
	void operator=(Matrix);
	T* operator[](int);
	template <typename T>
	friend std::istream& operator>>(std::istream&, Matrix<T>&);
	template <typename T>
	friend std::ostream& operator<<(std::ostream&, Matrix<T>&);
	Matrix<T> operator+(Matrix<T>);
	Matrix<T> operator-(Matrix<T>);
	Matrix<T> operator*(Matrix);
	Matrix<T> operator*(int);
	T determinant();
	bool isInvertible();
	void lowerRank(int, int, int, int);
	void lowerRank(int, int); 
};