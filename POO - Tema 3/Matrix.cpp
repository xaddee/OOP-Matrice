#include "Matrix.h"

template <class T>
Matrix<T>::Matrix()
{
	_lines = 0;
	_columns = 0;
	_matrix = new T*;

}

template <typename T>
Matrix<T>::Matrix(int n, int m)
{
	_lines = n;
	_columns = m;
	matrixAlloc();
	for (int i = 0; i< _lines; i++)
	{
		for (int j = 0; j < _columns; j++)
		{
			_matrix[i][j] = 0;
		}
	}
}

template <typename T>
Matrix<T>::~Matrix()
{
	matrixDealloc();
}

template <typename T>
void Matrix<T>::matrixAlloc()
{
	_matrix = new T*[_lines];

	for (int i = 0; i < _lines; i++)
		_matrix[i] = new T[_columns];

}

template <typename T>
void Matrix<T>::matrixDealloc()
{
	for (int i = 0; i < _lines; i++)
		delete[] _matrix[i];
	delete[] _matrix;
}

template <typename T>
Matrix<T>::Matrix(const Matrix &m2)
{
	_lines = m2._lines;
	_columns = m2._columns;
	matrixAlloc();

	for (int i = 0; i < _lines; i++)
		for (int j = 0; j < _columns; j++)
			_matrix[i][j] = m2._matrix[i][j];
}

template <typename T>
int Matrix<T>::getLines()
{
	return _lines;
}

template <typename T>
int Matrix<T>::getColumns()
{
	return _columns;
}

template <typename T>
void Matrix<T>::operator=(Matrix m2)
{
	matrixDealloc();
	_lines = m2._lines;
	_columns = m2._columns;
	matrixAlloc();
	for (int i = 0; i < _lines; i++)
	{
		for (int j = 0; j < _columns; j++)
		{
			_matrix[i][j] = m2._matrix[i][j];  
		}
	}
}

template <typename T>
T* Matrix<T>::operator[] (int line)
{
	T *tmp; 
	tmp = new T [_columns];
	for (int i = 0; i < _columns; i++)
		tmp[i] = _matrix[line][i];
	return tmp;
}

template <typename T>
std::istream& operator>>(std::istream& input, Matrix<T> &m)
{
	int i, j;
	input >> m._lines;
	input >> m._columns;
	m.matrixAlloc();
	for (i = 0; i < m._lines; i++)
	{
		for (j = 0; j < m._columns; j++)
		{
			input >> m._matrix[i][j];
		}

	}
	return input;
}

template <typename T>
std::ostream& operator<<(std::ostream& output, Matrix<T>& m)
{
	int i, j;
	for (i = 0; i < m._lines; i++)
	{
		for (j = 0; j < m._columns; j++)
		{
			output << m._matrix[i][j] << " ";
		}
		output << std::endl;
	}

	return output;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(Matrix<T> m2)
{
	Matrix<T> tmp(_lines, _columns);
	if (_lines == m2._lines && _columns == m2._columns)
	{

		for (int i = 0; i < _lines; i++)
		{
			for (int j = 0; j < _columns; j++)
			{
				tmp._matrix[i][j] = _matrix[i][j] + m2._matrix[i][j];
			}
		}
	}
	return tmp;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(Matrix<T> m2)
{
	Matrix<T> tmp(_lines, _columns);
	if (_lines == m2._lines && _columns == m2._columns)
	{

		for (int i = 0; i < _lines; i++)
		{
			for (int j = 0; j < _columns; j++)
			{
				tmp._matrix[i][j] = _matrix[i][j] - m2._matrix[i][j];
			}
		}
	}
	return tmp;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T> m2)
{

	Matrix<T> tmp(_lines, m2._columns);
	if (_columns == m2._lines)
	{
		for (int i = 0; i < _lines; i++)
			for (int j = 0; j < m2._columns; j++)
			{
				tmp._matrix[i][j] = 0;
				for (int k = 0; k <  _columns; k++)
				{
					tmp._matrix[i][j] += _matrix[i][k] * m2._matrix[k][j];  // aici am folosit contorul k pt a putea inmulti linia cu coloana
				}
			}
	}
	return tmp;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(int number)
{
	Matrix<T> tmp(_lines, _columns);
	for (int i = 0; i < _lines; i++)
	{
		for (int j = 0; j < _columns; j++)
		{
			tmp._matrix[i][j] = _matrix[i][j] * number;
		}
	}
	return tmp;
}

template <typename T>
void Matrix<T>::lowerRank(int line, int column)
{
	Matrix<T> tmp(_lines - 1, _columns - 1); 
	int k = 0, m = 0;
	for (int i = 0; i < _lines; i++)
	{
		k = 0;
		if (i == line) continue;
		for (int j = 0; j < _columns; j++)
		{
			if (j == column) continue;
			tmp._matrix[m][k] = _matrix[i][j];
			k++;
		}
		m++;
	}
	matrixDealloc();
	_lines--;
	_columns--;
	matrixAlloc();
	for (int i = 0; i < _lines; i++)
	{
		for (int j = 0; j < _columns; j++)
		{
			_matrix[i][j] = tmp._matrix[i][j];
		}
	}
}

template <typename T>
void Matrix<T>::lowerRank(int newI, int newL, int newJ, int newC)  // functia sa creaza o matrice inferioara la parametrii primiti
{

	Matrix<T> tmp(newL - newI + 1, newC - newJ + 1); // am incrementat cu 1 pt ca mi ar fi alocat cu un spatiu mai putin , apelul facandu se pt linii si coloane numarate de la 0
	_lines = newL - newI + 1;                       // la fel ca mai sus
	_columns = newC - newJ + 1;
	int k = 0, m = 0; // contori pt matricea temporara, ea avand elementele de la 0 la newL si newC
	for (int i = newI; i < newL + 1; i++)
	{
		m = 0;
		for (int j = newJ; j < newC + 1; j++)
		{
			tmp._matrix[k][m] = _matrix[i][j];
			m++;
		}
		k++;
	}
	matrixDealloc();
	matrixAlloc();
	for (int i = 0; i < _lines; i++)
	{
		for (int j = 0; j < _columns; j++)
			_matrix[i][j] = tmp._matrix[i][j];
	}
}

template <typename T>
T Matrix<T>::determinant() // parametrul este matricea in sine, functie care o sa se apeleze recursiv
{

	if (_lines == _columns) // cand ajunge la un det pt o matrice de grad 2 returneaza rezultatul
	{
		T det = 0;
		int i = 0, j;
		if (_lines == 2)
		{
			det = _matrix[0][0] *_matrix[1][1] - _matrix[0][1] * _matrix[1][0];
			return det;
		}

		for (j = 0; j < _columns; j++)
		{
			Matrix<T> tmp(_lines, _columns);  // creem o matrice temporara pt a salva matricea initiala
			tmp = *this;                     // o copiem pe cea initiala in cea tmp
			tmp.lowerRank(i, j);            // transformam matricea temporara intr una inferioara fara linia i si coloana j
			int sign;
			if ((i + j) % 2 == 0) sign = 1; // ne formam (-1)^(i+j) pt a l folosi in formula
			else sign = -1;
			det += sign * _matrix[i][j] * tmp.determinant(); // reapelam functia pt matricea obtinuta

		}
		return det; // nu returneaza nimic daca este apelata cu un nr inegal de linii si coloane
	}
}


template<typename T>
bool Matrix<T>::isInvertible()
{
	if (determinant())
		return true;
	
        return false;
}
