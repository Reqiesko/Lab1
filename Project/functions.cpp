#include "functions.h"
#include "tests.h"
#include "filework.h"

extern string pathF;
extern string adresF;
extern int val;
string adres;
string pathc;
int way = 0;

int valadres;

struct Point3D {
	double x0, y0, z0, x, y, z, r, radlenth, dotlenth;
};
struct number {
	int n;
};
Point3D pt;
number pn;

enum menu_choice { 
	perform = 1,
	info = 2,
	tests = 3,
	out = 4
};
enum sub_menu_choice {
	console = 1,
	file = 2,
	back = 3
};
enum saveinfile {
	yes = 1,
	no = 2
};
enum clearfile {
	rewrite = 1,
	add = 2,
	newfile
};

void greeting() {
	cout << "Эта программа определяет принадлежность точки сфере." << endl;
	cout << endl;
	cout << "Автор: Нерадовский Артемий" << endl;
	cout << "Группа: 494" << endl;
	cout << "Лабораторная работа №1" << endl;
	cout << "Вариант 12" << endl;
	cout << endl;
}

void menu() {
	menu_choice floor = perform;
	int variant = floor;
	cout << endl;
	while (true) {
		cout << "Menu" << endl;
		cout << "Выберите вариант:" << endl;
		cout << "1. Выполнить программу." << endl;
		cout << "2. Вывести информацию о программе и авторе." << endl;
		cout << "3. Выполнить тесты. " << endl;
		cout << "4. Выйти из программы. " << endl;
		cout << endl;
		cin >> variant;
	
		if (!error_check()) {
			continue;
		}
		cin.ignore(32767, '\n');
		switch (variant) {
			case perform: {
			sub_menu();
			break;
			}
			case info: {
				cout << endl;
				greeting();
				menu();
				break;
			}
			case tests: {
				system("cls");
				test();
				menu();
				break;
			}
			case out: {
				cout << "Программа завершена." << endl;
				exit(0);
				break;
			}
			default: {
				cout << "Пожалуйста введите цифру 1, 2 или 3." << endl;				
			}
		}
		cin.clear();
	}
}

void sub_menu() {
	sub_menu_choice floor = console;
	int var = floor;
	while (true) {
		cout << "Выберите вариант:" << endl;
		cout << "1. Выполнить программу через консоль. " << endl;
		cout << "2. Использовать значения из файла. " << endl;
		cout << "3. Обратно в меню. " << endl;
		cin >> var;
		if (!error_check()) {			
			continue;
		}
		cin.ignore(32767, '\n');
		switch (var) {
			case console: {
				console_way();
				break;
			}
			case file: {
				file_work();
			}
			case back: {
				menu();
			}
			default: {
				cout << "Пожалуйста введите цифру 1, 2 или 3." << endl;
				sub_menu();
			}
		}
		cin.clear();
	}
}

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
		cin.ignore(32767, '\n');
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

int console_way() {
	way = 0;
	ifstream foutcheck;
	ofstream foutcon;
	ofstream foutsource;
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
		arr_source[i] = new double[7];
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
	for (i = 0; i < pn.n; i++) {
		for (int j = 0; j < 7; j++) {
			cout << arr_source[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Выберите вариант:" << endl;
	cout << "Сохранить исходные данные в файл? " << endl;
	result_from_console();
	if (way == 1) {
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
			foutcon.open(adres);
		}
		else {
			foutcheck.close();
			if (file_check_size(adres) == true) {
				foutsource.open(adres);
			}
			else {
				wtdw_file();
				if (valadres == 1) {
					foutsource.open(adres, ios::out);
				}
				else if (valadres == 2) {
					foutsource.open(adres, ios::app);
				}
				else {
					foutsource.open(adres);
				}
			}
		}
		for (i = 0; i < pn.n; i++) {
			if (i + 1 % 10 == 3 && i + 1 % 100 != 13) {
				for (int j = 0; j < 7; j++) {
					foutsource << arr_source[i][j] << " ";
				}
				foutsource << "\n";
			}
			else {
				for (int j = 0; j < 7; j++) {
					foutsource << arr_source[i][j] << " ";
				}
				foutsource << "\n";
			}
		}
		cout << "Исходные данные успешно сохранены! " << endl;
		way = 0;
	}
	for (i = 0; i < pn.n; i++) {		
		if (i + 1 % 10 == 3 && i + 1 % 100 != 13) {
			cout << '\n' << i + 1 << "-яя ";
		}
		else {
			cout << '\n' << i + 1 << "-ая ";
		}
		if (arr_res[i] == 1) {
			cout << "точка принадлежит сфере." << endl;
		}
		else if (arr_res[i] == 0) {
			cout << "точка не принадлежит сфере." << endl;
		}
	}
	cout << "Выберите вариант:" << endl;
	cout << "Сохранить результат в файл? " << endl;
	result_from_console();
	if (way == 1) {
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
			foutcheck.open(pathc);
		}
		while (file_name_check(pathc)) {
			foutcheck.close();
			cout << "Ошибка! Некорректное путь или имя файла." << endl;
			cout << "Введите путь к файлу: " << endl;
			cin >> pathc;
			foutcheck.open(pathc, ios::in);
		}
		if (file_exist(pathc) == false) {
			foutcheck.close();
			foutcon.open(pathc);
		}
		else {				
			foutcheck.close();
			if (file_check_size(pathc) == true) {
				foutcon.open(pathc);
			}
			else {
				wtdw_file();
				if (valadres == 1) {
					foutcon.open(pathc, ios::out);
				}
				else if (valadres == 2) {
					foutcon.open(pathc, ios::app);
				}
				else {
					foutcon.open(pathc);
				}
			}
		}
		for (i = 0; i < pn.n; i++) {			
			if (i + 1 % 10 == 3 && i + 1 % 100 != 13) {
				foutcon << '\n' << i + 1 << "-яя ";
			}
			else {
				foutcon << '\n' << i + 1 << "-ая ";
			}
			if (arr_res[i] == 1) {
				foutcon << "точка принадлежит сфере." << endl;
			}
			else if (arr_res[i] == 0) {
				foutcon << "точка не принадлежит сфере." << endl;
			}
		}
		way = 0;
		system("cls");
		cout << "Результат успешно сохранен! " << endl;
	}	
	foutsource.close();
	foutcon.close();
	for (i = 0; i < pn.n; i++) {
		delete[] arr_source[i];
	}
	delete[] arr_source;
	delete[] arr_res;
	menu();
	return 1;
}




double calc() {			

			pt.dotlenth = abs(sqrt(pow((pt.x - pt.x0), 2) + pow((pt.y - pt.y0), 2) + pow((pt.z - pt.z0), 2)));			

			return pt.dotlenth;
	}



void result_from_console() {
	saveinfile floor = yes;
	int var = floor;
	bool sw = true;
	while (sw) {
		cout << "1. Да " << endl;
		cout << "2. Нет " << endl;
		cin >> var;
		if (!error_check()) {
			continue;
		}
		cin.ignore(32767, '\n');
		switch (var) {
			case yes: {
				way = 1;
				sw = false;
				break;
			}
			case no: {
				sw = false;
				break;			
			}
			default: {
				cout << "Пожалуйста введите цифру 1 или 2. " << endl;				
			}	
		}	
	}
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

int wtdw_file() {
	bool d = true;
	ifstream foutcheck;
	clearfile floor = rewrite;
	int del = floor;
	string pfile;
	while (d) {
		cout << "Файл с таким именем уже существует! Выберите вариант." << endl;
		cout << "1. Перезаписать." << endl;
		cout << "2. Дописать в конец." << endl;
		cout << "3. Указать другой файл." << endl;
		cin >> del;
		if (!error_check()) {
			continue;
		}
		cin.ignore(32767, '\n');
		switch (del) {
			case rewrite: {	
				valadres = 1;
				d = false;
				break;
			}
			case add: {
				valadres = 2;						
				d = false;
				break;
			}
			case newfile: {	
				cout << "Введите путь к файлу. " << endl;
				cin >> pfile;
				pathc = pfile;
				pathF = pfile;
				foutcheck.open(pfile, ios::in);
				while (!check_read_only(pfile)) {
					foutcheck.close();
					cout << "Введите путь к файлу: " << endl;
					cin >> pfile;
					pathc = pfile;
					foutcheck.open(pfile, ios::in);
				}
				while (file_name_check(pfile)) {
				foutcheck.close();
				cout << "Ошибка! Некорректный путь или имя файла." << endl;
				cout << "Введите путь к файлу: " << endl;
				cin >> pfile;
				pathc = pfile;
				pathF = pfile;
				foutcheck.open(pfile, ios::in);
				}
				
				if (adresF == pathF) {
					foutcheck.close();
					same_path();
				}
				if (file_exist(pfile) == true) {
					foutcheck.close();
					wtdw_file();
				}
				foutcheck.close();				
				d = false;		
				break;
			}
			default: {
				cout << "Пожалуйста введите цифру 1, 2 или 3.  " << endl;
			}
		}
	}
	return valadres;
}