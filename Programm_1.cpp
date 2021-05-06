#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <windows.h>

using namespace std;

bool check(bool *vect, int);
void out_matrix(double**, int, int);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	srand(time(0));
	int order_i, order_j, index_i, index_j, index_f, k;
	double min, min_ab, date, target_function;
	bool fl;
	ifstream f_m;

	f_m.open("c://matrix3.txt");

	if (!f_m.is_open()) {
		cout << "Файл не открыт;\n\n";
		exit(1);
	}
	else
		cout << "Файл открыт;\n\n";

	f_m >> order_i;
	f_m >> order_j;

	double **matrix = new double*[order_i];
	for (int i = 0; i < order_i; i++)
		matrix[i] = new double[order_j];

	double **find_matrix = new double*[order_i];
	for (int i = 0; i < order_i; i++)
		find_matrix[i] = new double[order_j];

	for (int i = 0; i < order_i; i++)
		for (int j = 0; j < order_j; j++)
			find_matrix[i][j] = 0;

	int *vect_a = new int[order_i];
	int *vect_b = new int[order_j];
	bool *vect_delete = new bool[order_j];

	//f_m.seekg(1, ios::cur);
	for (int i = 0; i < order_i; i++)
		for (int j = 0; j < order_j; j++)
			f_m >> matrix[i][j];

	f_m.seekg(1, ios::cur);

	for (int i = 0; i < order_i; i++)
		f_m >> vect_a[i];
	for (int j = 0; j < order_j; j++)
		f_m >> vect_b[j];

	f_m.close();

	for (int i = 0; i < order_j; i++)
		vect_delete[i] = false;

	for (int i = 0; i < order_i; i++) {
		for (int j = 0; j < order_j; j++)
			cout << matrix[i][j] << " ";
		cout << "\n";
	}
	cout << "\n";

	cout << "vect_a:\n";
	for (int i = 0; i < order_i; i++)
		cout << vect_a[i] << " ";
	cout << "\n\n";

	cout << "vect_b:\n";
	for (int j = 0; j < order_j; j++)
		cout << vect_b[j] << " ";
	cout << "\n\n";

	if (vect_a[0] < vect_b[0])
		min = vect_a[0] * matrix[0][0];
	else
		min = vect_b[0] * matrix[0][0];
	
	index_i = 0;
	index_j = 0;
	k = 0;
	target_function = 0;
	do {
		cout << "k: " << k << "\n\n";

		for (int index = 0;;) {
			for (index = 0; index < order_j; index++)
				if (!vect_delete[index])
					break;
			min = vect_a[0] * matrix[0][index];
			break;
		}

		for (int i = 0; i < order_i; i++)
			for (int j = 0; j < order_j; j++) {
				if (!vect_delete[j]) {
					if (vect_a[i] < vect_b[j])
						min_ab = vect_a[i];
					else
						min_ab = vect_b[j];
					if (min > min_ab * matrix[i][j]) {
						min = min_ab * matrix[i][j];
						index_i = i;
						index_j = j;
						date = min_ab;
					}


					/*cout << "i: " << i << " j: " << j << "\n\n";
					cout << "min: " << min << "\n\n";
					cout << "matrix:\n";
					out_matrix(matrix, order_i, order_j);
					cout << "\n\n";
					cout << "vect_a:\n";
					for (int i = 0; i < order_i; i++)
						cout << vect_a[i] << " ";
					cout << "\n\n";
					cout << "vect_b:\n";
					for (int i = 0; i < order_j; i++)
						cout << vect_b[i] << " ";
					cout << "\n_______________________________\n\n"; */
				}
				//cin.get();
			}
		find_matrix[index_i][index_j] = date;
		cout << "date: " << date << " " << "matrix[" << index_i << "][" << index_j << "]: " << matrix[index_i][index_j] << "\n\n";
		target_function += date * matrix[index_i][index_j];
		vect_a[index_i] -= date;
		vect_b[index_j] -= date;
		vect_delete[index_j] = true;

		fl = check(vect_delete, order_j);
		k++;
	} while (fl);

	for (int i = 0; i < order_j; i++)
		if (!vect_delete[i]) {
			index_f = i;
			break;
		}

	for (int i = 0; i < order_i; i++)
		if (vect_a[i] < vect_b[index_f]) {
			find_matrix[i][index_f] = vect_a[i];
			target_function += vect_a[i] * matrix[i][index_f];
		}
		else {
			find_matrix[i][index_f] = vect_b[index_f];
			target_function += vect_b[i] * matrix[i][index_f];
		}

	cout << "Искомая матрица:\n";
	out_matrix(find_matrix, order_i, order_j);
	cout << "\n\n";

	cout << "vect_a:\n";
	for (int i = 0; i < order_i; i++)
		cout << vect_a[i] << " ";
	cout << "\n\n";

	cout << "vect_b:\n";
	for (int i = 0; i < order_j; i++)
		cout << vect_b[i] << " ";
	cout << "\n\n";

	cout << "Значение целевой функции: " << target_function << "\n\n";

	system("pause");
	return 0;
}

bool check(bool *vect, int order)
{
	int date;

	date = 0;
	for (int i = 0; i < order; i++) {
		if (!vect[i])
			date++;
		if (date > 1)
			break;
	}

	if (date == 1)
		date = 0;

	return (bool)date;
}

void out_matrix(double **matrix, int order_i, int order_j)
{
	for (int i = 0; i < order_i; i++) {
		for (int j = 0; j < order_j; j++)
			cout << setw(3) << matrix[i][j] << " ";
		cout << "\n";
	}
}