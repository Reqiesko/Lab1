#pragma once
#include "functions.h"


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

void menu();

void sub_menu();

int result_from_console();

void greeting();
