#include "Matrix.h"
#include "Matrix.cpp"

#include <fstream>

// am testat functiile pt float si int, nu am suprascris functiile pt char, variabilele sunt denumite de forma 'nume_variabila', variabiele membre in clase au '_' in fata, functiile sunt de forma 'numeleFunctiei'
int main()
{
	std::ifstream f("datein.txt");
	Matrix<float> m1, m2, m3;
	int x = 5;
	float *v; 
	v = new float[4]; // vector folosit pt a returna linia specifica (operatorul [])
	f >> m1;
	f >> m2;
	std::cout << "Suma:\n";
	m3 = m1 + m2;
	std::cout << m3;
	std::cout << "Diferenta:\n";
	m3 = m1 - m2;
	std::cout << m3;
	std::cout << "Inmultirea a 2 matrice:\n";
	m3 = m1 * m2;
	std::cout << m3;
	std::cout << "Inmultirea cu scalar(m1 *5):\n";
	m3 = m1 * 5;
	std::cout << m3;
	std::cout << "Test pt operatorul [] (am facut m1[2]):\n";
	v = m1[2];
	for (int i = 0; i<4; i++) std::cout << v[i] << " ";
	std::cout << std::endl;
	x = m2.determinant();
	std::cout << "Determinantul matricei m2 este: " << x << "\n";
	if (m2.isInvertible()) std::cout << "-matricea este inversabila";
	else std::cout << "-matricea nu este inversabila;\n";
	x = m1.determinant();
	std::cout << "Determinantul matricei m1 este: " << x << "\n";
	if (m1.isInvertible()) std::cout << "-matricea este inversabila\n";
	else std::cout << "-matricea nu este inversabila;\n";
	std::cout << "Nr de coloane al matricei m1: " << m1.getColumns() << "\n";
	std::cout << "Nr de linii al matricei m1: " << m1.getLines() << "\n";
	system("pause");
	return 0;
}