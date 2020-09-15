#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <istream>
#include "Windows.h"
#include <filesystem>
#include "ui.h"

using namespace std;
using namespace std::experimental::filesystem;

bool file_check_size(string pFile);
int wtdw_file(string& pfile);
void console_way();
double calc();
double number_check();
bool error_check();
bool file_exist(string path);
void save_source(double** arr, string pathfile, int modout);
void save_results(int* arr, string pathfile, int modout);


enum clearfile {
	rewrite = 1,
	add = 2,
	newfile
};