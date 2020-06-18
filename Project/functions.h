#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <istream>
#include "Windows.h"
#include <filesystem>


using namespace std;
using namespace std::experimental::filesystem;

bool file_check_size(string pFile);
int wtdw_file();
int console_way();
double calc();
void greeting();
void menu();
void sub_menu();
double number_check();
bool error_check();
void result_from_console();
bool file_exist(string path);
