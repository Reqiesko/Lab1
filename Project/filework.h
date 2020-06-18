#pragma once

#include "functions.h"
#include <filesystem>
using namespace std::experimental::filesystem;

void file_work(); 
bool file_name_check(string path);
int same_path();
void file_print_result(string pathFile, string adresFile, int i);
bool check_read_only(string filename);
