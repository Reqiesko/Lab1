#include "tests.h"



const int count_of_tests = 5;


int result(double x0, double y0, double z0, double x, double y, double z, double radlenth) {
	double r; 
	double dotlenth;
	r = pow(radlenth, 2);
	dotlenth = abs(sqrt(pow((x - x0), 2) + pow((y - y0), 2) + pow((z - z0), 2)));
	if (r == pow(dotlenth, 2) || dotlenth < radlenth) {
		return 1;
	}
	else {
		return 0;
	}
}

void test() {
	double x0, y0, z0, x, y, z, radlenth;
	int count = 0;
	string expected_res_str;
	string actual_res_str;
	int expected_res;
	int actual_res;

	int result_test[count_of_tests] = {0, 1, 1, 0, 0};
	double coordinates[count_of_tests][7] = { {0, 0, 0, -10, 10, 10, 10}, {0, 0, 0, 2, 2, 2, 5}, {6, 0, -11, 12, 5, -9, 15}, {-5.5, 4.5, -2, 7, 1, 0, 11}, {2.4, -7.28, 3.51, -5.7, 11, 3.84, 9} };
	for (int i = 0, j = 0; i < count_of_tests;) {
		expected_res = result_test[i];
		x0 = coordinates[i][j];
		j++;
		y0 = coordinates[i][j];
		j++;
		z0 = coordinates[i][j];
		j++;
		x = coordinates[i][j];
		j++;
		y = coordinates[i][j];
		j++;
		z = coordinates[i][j];
		j++;
		radlenth = coordinates[i][j];
		j++;		
		actual_res = result(x0, y0, z0, x, y, z, radlenth);
		if (expected_res == 1) {
			expected_res_str = "Точка принадлежит сфере. ";
		}
		if (expected_res == 0) {
			expected_res_str = "Точка не принадлежит сфере. ";
		}
		if (actual_res == 1) {
			actual_res_str = "Точка принадлежит сфере. ";
		}
		if (actual_res == 0) {
			actual_res_str = "Точка не принадлежит сфере. ";
		}
		if (actual_res == expected_res) { 
			count++;
		}
		else if (actual_res != expected_res) {
			cout << "Тест №" << i + 1 << " провалился." << endl;
			cout << "Ожидался результат: " << expected_res_str << endl;
			cout << "Полученный результат: " << actual_res_str << endl;
			cout << endl;
		}
		i++;
		j = 0;
	}
	if (count == count_of_tests) { 
		cout << "Тестирование прошло успешно." << endl;
		cout << endl;
	}
	else {
		cout << "Тестирование провалилось." << endl;
		cout << endl;
	}
}