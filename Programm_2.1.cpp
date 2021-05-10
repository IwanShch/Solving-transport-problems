#include <iostream>
#include <climits>
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

	int order_i, order_j, index_i, index_j, index_f, k, order_i_d, order_j_d;
	double min, min_ab, date, target_function, target_function_i;
	bool fl1, fl2;
	ifstream f_m;

	f_m.open("c://matrix4.txt");

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

	double **matrix_c = new double*[order_i];
	for (int i = 0; i < order_i; i++)
		matrix_c[i] = new double[order_j];

	double **find_matrix = new double*[order_i];
	for (int i = 0; i < order_i; i++)
		find_matrix[i] = new double[order_j];

	for (int i = 0; i < order_i; i++)
		for (int j = 0; j < order_j; j++)
			find_matrix[i][j] = 0;

	int *vect_a = new int[order_i];
	int *vect_b = new int[order_j];
	bool *vect_delete_b = new bool[order_j];
	bool *vect_delete_a = new bool[order_i];

	for (int i = 0; i < order_i; i++)
		for (int j = 0; j < order_j; j++)
			f_m >> matrix[i][j];

	for (int i = 0; i < order_i; i++)
		for (int j = 0; j < order_j; j++)
			matrix_c[i][j] = matrix[i][j];

	f_m.seekg(1, ios::cur);

	for (int i = 0; i < order_i; i++)
		f_m >> vect_a[i];
	for (int j = 0; j < order_j; j++)
		f_m >> vect_b[j];

	f_m.close();

	for (int i = 0; i < order_j; i++)
		vect_delete_b[i] = false;

	for (int i = 0; i < order_i; i++)
		vect_delete_a[i] = false;

	for (int i = 0; i < order_i; i++) {
		for (int j = 0; j < order_j; j++)
			cout << matrix[i][j] << " ";
		cout << "\n";
	}
	cout << "\n";

	f_m.open("c://matrix_d.txt");
	f_m >> order_i_d;
	f_m >> order_j_d;

	double **matrix_d = new double*[order_i_d];
	for (int i = 0; i < order_i_d; i++)
		matrix_d[i] = new double[order_j];

	for (int i = 0; i < order_i_d; i++)
		for (int j = 0; j < order_j_d; j++)
			f_m >> matrix_d[i][j];

	f_m.close();

	for (int i = 0; i < order_i; i++)
		for (int j = 0; j < order_j; j++) {
			if (vect_a[i] < vect_b[j])
				min_ab = vect_a[i];
			else
				min_ab = vect_b[j];
			matrix[i][j] = matrix[i][j] + ((1.0*matrix_d[i][j]) / min_ab);
		}
	cout << "matrix v 2:\n";
	out_matrix(matrix, order_i, order_j);
	cout << "\n\n";

	cout << "vect_a:\n";
	for (int i = 0; i < order_i; i++)
		cout << vect_a[i] << " ";
	cout << "\n\n";

	cout << "vect_b:\n";
	for (int j = 0; j < order_j; j++)
		cout << vect_b[j] << " ";
	cout << "\n\n";

	index_i = 0;
	index_j = 0;
	k = 0;
	target_function = target_function_i = 0;
	do {
		//cout << "k: " << k << "\n\n";

		for (int i = 0; i < order_i; i++)
			if (!vect_delete_a[i]) {
				for (int j = 0; j < order_j; j++)
					if (!vect_delete_b[j]) {
						if (vect_a[i] < vect_b[j])
							min_ab = vect_a[i];
						else
							min_ab = vect_b[j];
						min = min_ab * matrix[i][j];
						index_i = i;
						index_j = j;
						date = min_ab;
						break;
					}
				break;
			}

		for (int i = 0; i < order_i; i++)
			if (!vect_delete_a[i]) {
				for (int j = 0; j < order_j; j++) {
					if (!vect_delete_b[j]) {
						if (vect_a[i] < vect_b[j])
							min_ab = vect_a[i];
						else
							min_ab = vect_b[j];
						if (min > min_ab * matrix[i][j]) {
							min = min_ab * matrix[i][j];
							index_i = i;
							index_j = j;
							date = min_ab;
							cout << "date: " << date << "\n\n";
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
					/*cout << "date: " << date << "\n\n";
					cin.get();*/
				}
			}
		//cout << "date: " << date << " " << "matrix[" << index_i << "][" << index_j << "]: " << matrix[index_i][index_j] << "\n\n";
		find_matrix[index_i][index_j] = date;

		//cout << "matrix_c[index_i][index_j]: " << matrix_c[index_i][index_j] << " matrix_d[index_i][index_j]: " << matrix_d[index_i][index_j] << "\n\n";
		//cout << "matrix[index_i][index_j]: " << matrix[index_i][index_j] << " date: " << date << "\n\n";
		target_function += date * matrix_c[index_i][index_j] + matrix_d[index_i][index_j];
		target_function_i += date * matrix[index_i][index_j];
		//cout << "target_function: " << target_function << "\n";
		//cout << "target_function_i: " << target_function_i << "\n\n";
		vect_a[index_i] -= date;
		vect_b[index_j] -= date;
		if (vect_b[index_j] == 0)
			vect_delete_b[index_j] = true;
		else
			vect_delete_a[index_i] = true;

		fl1 = check(vect_delete_b, order_j);
		fl2 = check(vect_delete_a, order_i);

		k++;
	} while (fl1 && fl2);

	for (int i = 0; i < order_i; i++)
		if (!vect_delete_a[i]) {
			for (int j = 0; j < order_j; j++)
				if (!vect_delete_b[j]) {
					if (vect_a[i] < vect_b[j]) {
						find_matrix[i][j] = vect_a[i];
						target_function += vect_a[i] * matrix_c[i][j] + matrix_d[i][j];
						//cout << "vect_a[i]: " << vect_a[i] << " matrix_c[i][j]: " << matrix_c[i][j] << " matrix_d[i][j]: " << matrix_d[i][j] << "\n";
						target_function_i += vect_a[i] * matrix[i][j];
						//cout << "matrix[i][j]: " << matrix[i][j] << "\n\n";
					}
					else {
						find_matrix[i][j] = vect_b[j];
						target_function += vect_b[j] * matrix_c[i][j] + matrix_d[i][j];
						//cout << "vect_b[i]: " << vect_b[j] << " matrix_c[i][j]: " << matrix_c[i][j] << " matrix_d[i][j]: " << matrix_d[i][j] << "\n";
						target_function_i += vect_b[j] * matrix[i][j];
						//cout << "matrix[i][j]: " << matrix[i][j] << "\n\n";
					}
				}
		}
	cout << "\n\n_______________________________________________\n\n";
	cout << "После вычислений: \n\n";
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

	cout << "Значение целефой функции в модифицированной транспортной задаче: " << target_function_i << "\n\n";

        delete[]vect_a;
        delete[]vect_b;
        delete[]matrix;
        delete[]matrix_c;
        delete[]find_matrix;
        delete[]vect_delete_b;
        delete[]vect_delete_a;
        delete[]matrix_d;
	
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
