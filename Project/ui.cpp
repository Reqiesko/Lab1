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
		cout << "�������� �������:" << endl;
		cout << "1. ��������� ���������." << endl;
		cout << "2. ������� ���������� � ��������� � ������." << endl;
		cout << "3. ��������� �����. " << endl;
		cout << "4. ����� �� ���������. " << endl;
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
			cout << "��������� ���������." << endl;
			exit(0);
			break;
		}
		default: {
			cout << "���������� ������� ����� 1, 2 ��� 3." << endl;
		}
		}
		cin.clear();
	}
}

void sub_menu() {
	sub_menu_choice floor = console;
	int var = floor;
	while (true) {
		cout << "�������� �������:" << endl;
		cout << "1. ��������� ��������� ����� �������. " << endl;
		cout << "2. ������������ �������� �� �����. " << endl;
		cout << "3. ������� � ����. " << endl;
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
			cout << "���������� ������� ����� 1, 2 ��� 3." << endl;
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
		cout << "1. �� " << endl;
		cout << "2. ��� " << endl;
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
			cout << "���������� ������� ����� 1 ��� 2. " << endl;
		}
		}
	}
	return way;
}



void greeting() {
	cout << "��� ��������� ���������� �������������� ����� �����." << endl;
	cout << endl;
	cout << "�����: ����������� �������" << endl;
	cout << "������: 494" << endl;
	cout << "������������ ������ �1" << endl;
	cout << "������� 12" << endl;
	cout << endl;
}

