#include "functions.h"
#include "tests.h"
#include "filework.h"



struct Point3D {
	double x0, y0, z0, x, y, z, radlenth;
};
struct number {
	int n;
};
Point3D pt;
number pn;



const int ignor = 32767;
const int c_point = 7;

double number_check() {
	double a;
	while (!(cin >> a) || (cin.peek() != '\n'))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Ошибка! Пожалуйста введите число! " << endl;
	}
	return a;
}

bool error_check() {
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(ignor, '\n');
		cout << "Пожалуйста введите цифру 1, 2 или 3." << endl;
		return 0;
	}
	return 1;
}

bool file_exist(string path) {
	ifstream file(path);
	file.open(path, ios::in);
	if (file.is_open())
		return true;
	else
		return false;
}

void console_way() {
	string pathc, adres;
	ifstream foutcheck;
	cout << "Введите координаты (x, y, z) центра сферы " << endl;
	cout << "X = ";
	pt.x0 = number_check();
	cout << "Y = ";
	pt.y0 = number_check();
	cout << "Z = ";
	pt.z0 = number_check();
	cout << "Введите длину раудиуса. " << endl;
	cout << "Длина = ";
	pt.radlenth = number_check();
	if (pt.radlenth <= 0) {
		cout << "Ошибка! Радиус не может быть отрицательным и нулевым! " << endl;
		sub_menu();
	}
	cout << "Какое количество точек вы хотите проверить? " << endl;
	cin >> pn.n;
	double** arr_source = new double* [pn.n];
	for (int i = 0; i < pn.n; i++) {
		arr_source[i] = new double[c_point];
	}
	int* arr_res = new int[pn.n];
	int i;
	for (i = 0; i < pn.n; i++) {
		arr_source[i][0] = pt.x0;
		arr_source[i][1] = pt.y0;
		arr_source[i][2] = pt.z0;
		arr_source[i][3] = pt.radlenth;
		cout << "Введите координаты " << i + 1 << "-ой точки." << endl;
		cout << "X = ";
		pt.x = number_check();
		cout << "Y = ";
		pt.y = number_check();
		cout << "Z = ";
		pt.z = number_check();
		arr_source[i][4] = pt.x;
		arr_source[i][5] = pt.y;
		arr_source[i][6] = pt.z;
		arr_res[i] = result(pt.x0, pt.y0, pt.z0, pt.x, pt.y, pt.z, pt.radlenth);
	}
	cout << "Исходные данные: " << endl;
	for (i = 0; i < pn.n; i++) {
		for (int j = 0; j < c_point; j++) {
			cout << arr_source[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Выберите вариант:" << endl;
	cout << "Сохранить исходные данные в файл? " << endl;
	if (result_from_console() == 1) {
		cout << "Введите путь к файлу для сохранения исходных данных. " << endl;
		cin >> adres;
		foutcheck.open(adres, ios::in);
		while (!check_read_only(adres)) {
			foutcheck.close();
			cout << "Введите путь к файлу: " << endl;
			cin >> adres;
			foutcheck.open(adres);
		}
		while (file_name_check(adres)) {
			foutcheck.close();
			cout << "Ошибка! Некорректное путь или имя файла." << endl;
			cout << "Введите путь к файлу: " << endl;;
			cin >> adres;
			foutcheck.open(adres, ios::in);
		}
		if (file_exist(adres) == false) {
			foutcheck.close();
			save_source(arr_source, adres, rewrite);
		}
		else {
			foutcheck.close();
			if (file_check_size(adres) == true) {
				save_source(arr_source, adres, rewrite);
			}
			else {
				save_source(arr_source, adres, wtdw_file(adres));
			}
		}
	}
	for (i = 0; i < pn.n; i++) {		
		if (arr_res[i] == 1) {
			cout << i + 1 << " точка принадлежит сфере." << endl;
		}
		else if (arr_res[i] == 0) {
			cout << i + 1 << " точка не принадлежит сфере." << endl;
		}
	}
	cout << "Выберите вариант:" << endl;
	cout << "Сохранить результат в файл? " << endl;

	if (result_from_console() == 1) {
		cout << "Введите путь к файлу для сохранения результата. " << endl;
		cin >> pathc;
		while (adres == pathc) {
			cout << "Адреса файлов совпадают. Введите путь к файлу: " << endl;
			cin >> pathc;
		}		
		foutcheck.open(pathc, ios::in);
		while (!check_read_only(pathc)) {
			foutcheck.close();
			cout << "Введите путь к файлу: " << endl;
			cin >> pathc;
			while (adres == pathc) {
				cout << "Адреса файлов совпадают. Введите путь к файлу: " << endl;
				cin >> pathc;
			}
			foutcheck.open(pathc);
		}
		while (file_name_check(pathc)) {
			foutcheck.close();
			cout << "Ошибка! Некорректное путь или имя файла." << endl;
			cout << "Введите путь к файлу: " << endl;
			cin >> pathc;
			while (adres == pathc) {
				cout << "Адреса файлов совпадают. Введите путь к файлу: " << endl;
				cin >> pathc;
			}
			foutcheck.open(pathc, ios::in);
		}
		if (file_exist(pathc) == false) {
			foutcheck.close();
			save_results(arr_res, pathc, rewrite);
		}
		else {				
			foutcheck.close();
			if (file_check_size(pathc) == true) {
				save_results(arr_res, pathc, rewrite);
			}
			else {	
				save_results(arr_res, pathc, wtdw_file(pathc));
			}
		}	
	}	
	for (i = 0; i < pn.n; i++) {
		delete[] arr_source[i];
	}
	delete[] arr_source;
	delete[] arr_res;
	menu();
}

void save_source(double** arr, string pathfile, int modout) {
	ofstream foutsource;
	if (modout == 1) {
		foutsource.open(pathfile, ios::out);
		foutsource << " " << endl;
	}
	if (modout == 2) {
		foutsource.open(pathfile, ios::app);
		foutsource << " " << endl;
	}
	
	for (int i = 0; i < pn.n; i++) {
		for (int j = 0; j < c_point; j++) {
			foutsource << arr[i][j] << " ";
		}
		foutsource << "\n";
	}
	foutsource.close();
	cout << "Исходные данные успешно сохранены! " << endl;
}

void save_results(int* arr, string pathfile, int modout) {
	ofstream foutcon;
	if (modout == 1) {
		foutcon.open(pathfile, ios::out);
		foutcon << " " << endl;
	}
	if (modout == 2) {
		foutcon.open(pathfile, ios::app);
		foutcon << " " << endl;
	}
	for (int i = 0; i < pn.n; i++) {			
		if (arr[i] == 1) {
			foutcon << i + 1 << " точка принадлежит сфере." << endl;
		}
		else if (arr[i] == 0) {
			foutcon << i + 1 << " точка не принадлежит сфере." << endl;
		}
	}
	foutcon.close();
	system("cls");
	cout << "Результат успешно сохранен! " << endl;
}

double calc() {			

			double dotlenth = abs(sqrt(pow((pt.x - pt.x0), 2) + pow((pt.y - pt.y0), 2) + pow((pt.z - pt.z0), 2)));			

			return dotlenth;
	}



bool file_check_size(string pFile) {
	ifstream file_check_size;
	file_check_size.open(pFile, ios::in);
	file_check_size.seekg(0, ios::end);
	if (file_check_size.tellg() == 0) {
		file_check_size.close();
		return true;
	}
	else {
		file_check_size.close();
		return false;
	}
}

int wtdw_file(string& pFile) {
	bool d = true;
	ifstream foutcheck;
	int del;

	while (d) {
		cout << "Файл не пуст! Выберите вариант." << endl;
		cout << "1. Перезаписать." << endl;
		cout << "2. Дописать в конец." << endl;
		cout << "3. Указать другой файл." << endl;
		cin >> del;

		if (!error_check()) {
			continue;
		}

		cin.ignore(ignor, '\n');

		switch (del) {
		case rewrite: {
			return rewrite;
		}
		case add: {
			return add;
		}
		case newfile: {
			bool trg = true;
			while (trg) {
				string adresF;
				cout << "Введите путь к файлу. " << endl;
				cin >> pFile;

				foutcheck.open(pFile, ios::in);

				while (file_name_check(pFile)) {
					foutcheck.close();
					cout << "Ошибка! Некорректный путь или имя файла." << endl;
					cout << "Введите путь к файлу: " << endl;
					cin >> pFile;
					foutcheck.open(pFile, ios::in);
				}
				while (!check_read_only(pFile)) {
					foutcheck.close();
					cout << "Введите путь к файлу: " << endl;
					cin >> pFile;
					foutcheck.open(pFile);
				}
				if (!foutcheck.is_open()) {
					ifstream newfile(pFile);
					newfile.close();
					return rewrite;
				}
				else {
					bool check = file_check_size(pFile);
					foutcheck.close();
					if (check) {
						return 0;
					}
					else {
						return wtdw_file(pFile);
					}
				}
			}
		}
		default: {
			cout << "Пожалуйста введите цифру 1, 2 или 3." << endl;
		}
		}
	}
}

