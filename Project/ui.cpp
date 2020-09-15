#include "ui.h"
#include "tests.h"
#include "filework.h"

const int ignor = 32767;

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
		cin.ignore(ignor, '\n');
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
		cin.ignore(ignor, '\n');
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

int result_from_console() {
	saveinfile floor = yes;
	int var = floor;
	int way = 0;
	bool sw = true;
	while (sw) {
		cout << "1. Да " << endl;
		cout << "2. Нет " << endl;
		cin >> var;
		if (!error_check()) {
			continue;
		}
		cin.ignore(ignor, '\n');
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
	return way;
}



void greeting() {
	cout << "Эта программа определяет принадлежность точки сфере." << endl;
	cout << endl;
	cout << "Автор: Нерадовский Артемий" << endl;
	cout << "Группа: 494" << endl;
	cout << "Лабораторная работа №1" << endl;
	cout << "Вариант 12" << endl;
	cout << endl;
}

