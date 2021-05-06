#include <iostream>
#include <climits>
#include <iomanip>
#include <ctime>
#include <fstream>

using namespace std;

bool check(bool *vect, int);
void out_matrix(double**, int, int);

int main()
{

	int order_i, order_j, index_i, index_j, index_f, k, order_i_d, order_j_d;
	double min, min_ab, date, target_function, target_function_i;
	bool fl1, fl2;
	ofstream f_m;

	srand(time(0));

	order_i = rand();
	order_j = rand();

	cout << "order_i: " << order_i << "\n";
	cout << "order_j: " << order_j << "\n\n";

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
	bool *vect_delete = new bool[order_j];
	bool *vect_delete_a = new bool[order_i];
	
	for (int i = 0; i < order_i; i++)
		for (int j = 0; j < order_j; j++)
			matrix[i][j] = rand() % 10;

	for (int i = 0; i < order_i; i++)
		for (int j = 0; j < order_j; j++)
			matrix_c[i][j] = matrix[i][j];


	for (int i = 0; i < order_i; i++)
		vect_a[i] = rand() % 10;
	for (int j = 0; j < order_j; j++)
		vect_b[j] = rand() % 10;


	for (int i = 0; i < order_j; i++)
		vect_delete[i] = false;

	for (int i = 0; i < order_i; i++)
		vect_delete_a[i] = false;


	double **matrix_d = new double*[order_i_d];
	for (int i = 0; i < order_i_d; i++)
		matrix_d[i] = new double[order_j];

	for (int i = 0; i < order_i_d; i++)
		for (int j = 0; j < order_j_d; j++)
			matrix_d[i][j] = rand();

	for (int i = 0; i < order_i; i++)
		for (int j = 0; j < order_j; j++) {
			if (vect_a[i] < vect_b[j])
				min_ab = vect_a[i];
			else
				min_ab = vect_b[j];
			matrix[i][j] = matrix[i][j] + ((1.0*matrix_d[i][j]) / min_ab);
		}


	if (vect_a[0] < vect_b[0]) {
		min = vect_a[0] * matrix[0][0];
		index_i = 0;
		index_j = 0;
		date = vect_a[0];
	}
	else {
		min = vect_b[0] * matrix[0][0];
		index_i = 0;
		index_j = 0;
		date = vect_b[0];
	}

	index_i = 0;
	index_j = 0;
	k = 0;
	target_function = target_function_i = 0;
	do {
		cout << "k: " << k << "\n\n";

		min = INT_MAX;

		for (int i = 0; i < order_i; i++)
			if (!vect_delete_a[i]) {
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

					}
				}
			}
	
		find_matrix[index_i][index_j] = date;


		
		target_function += date * matrix_c[index_i][index_j] + matrix_d[index_i][index_j];
		target_function_i += date * matrix[index_i][index_j];

		vect_a[index_i] -= date;
		vect_b[index_j] -= date;
		if (vect_b[index_j] == 0)
			vect_delete[index_j] = true;
		else
			vect_delete_a[index_i] = true;

		fl1 = check(vect_delete, order_j);
		fl2 = check(vect_delete_a, order_i);

		k++;
	} while (fl1 && fl2);

	for (int i = 0; i < order_i; i++)
		if (!vect_delete_a[i]) {
			for (int j = 0; j < order_j; j++)
				if (!vect_delete[j]) {
					if (vect_a[i] < vect_b[j]) {
						find_matrix[i][j] = vect_a[i];
						target_function += vect_a[i] * matrix_c[i][j] + matrix_d[i][j];
						target_function_i += vect_a[i] * matrix[i][j];
					}
					else {
						find_matrix[i][j] = vect_b[j];
						target_function += vect_b[j] * matrix_c[i][j] + matrix_d[i][j];
				
						target_function_i += vect_b[j] * matrix[i][j];
				
					}
				}
		}

	f_m.open("res.txt");

	for (int i = 0; i < order_i; i++) {
		for (int j = 0; j < order_j; j++)
			f_m << find_matrix[i][j] << " ";
		f_m << "\n";
	}
	f_m << "\n\n";
	f_m << "vect_a:\n";

	for (int i = 0; i < order_i; i++)
		f_m << vect_a[i] << " ";
	f_m << "\n\n";

	f_m << "vect_b:\n";
	for (int i = 0; i < order_j; i++)
		f_m << vect_b[i] << " ";
	f_m << "\n\n";

	f_m << "Значение целевой функции: " << target_function << "\n\n";
	f_m << "Значение целевой функции от модифицированной матрицы: " << target_function_i << "\n\n";

	f_m.close();

	/*cout << "Искомая матрица:\n";
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

	cout << "Значение целефой функции в модифицированной транспортной задаче: " << target_function_i << "\n\n"; */

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