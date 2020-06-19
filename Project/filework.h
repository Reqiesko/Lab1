#pragma once

#include "functions.h"
#include <filesystem>
using namespace std::experimental::filesystem;

void file_work(); 
bool file_name_check(string path);
void file_print_result(string adresFile, string pathFile, int modout);
bool check_read_only(string filename);
