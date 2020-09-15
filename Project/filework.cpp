#include "filework.h"
#include "tests.h"
#include "functions.h"
#include "ui.h"
#include <iostream>

using namespace std;

struct file_var {
  double x0, y0, z0, x, y, z, radlenth;
};

file_var fl;
const int rem_1 = 3;
const int rem_2 = 13;
const int ten = 10;
const int hundred = 100;
const int ignor = 32767;
void file_work() {
  string pathF;
  string adresF;
  cout << "Укажите путь к файлу с исходными данными. " << endl;
  cin >> adresF;
  ifstream fin;
  ifstream foutch;
  int count = 0, c_points = 0, modout = 0;
  fin.open(adresF);
  while (file_name_check(adresF)) {
    fin.close();
    cout << "Ошибка! Введен некорректный путь к файлу! \nВведите путь к файлу: " << endl;
    cin >> adresF;
    fin.open(adresF);
  }
  if (!fin.is_open()) {
    cout << "Ошибка! Не удаётся открыть файл!" << endl;
    cin.clear();
    cin.ignore(ignor, '\n');
    menu();
  }
  else {
    double temp;
    if (file_check_size(adresF) == true) {
      cout << "Ошибка! Файл пуст!" << endl;
      cin.clear();
      cin.ignore(ignor, '\n');
      fin.close();
      menu();
    }
    while (fin) {
      fin >> temp;
      if (fin.fail() && !fin.eof()) {
        cout << "Ошибка! Файл содержит некорректные данные. " << endl;
        cin.clear();
        cin.ignore(ignor, '\n');
        fin.close();
        menu();
      }
      count++;
    }
    fin.close();
    c_points = (count - 1) / 7;
    int* arr_res = new int[c_points];
    int i = 0;
    fin.open(adresF, ios::in);
    while (fin >> fl.x0 >> fl.y0 >> fl.z0 >> fl.radlenth >> fl.x >> fl.y >> fl.z) {
      if (i + 1 % ten == rem_1 && i + 1 % hundred != rem_2) {
        cout << "Исходные данные " << i + 1 << " -ей точки: " << endl;
        cout << fl.x0 << " " << fl.y0 << " " << fl.z0 << " " << fl.radlenth << " " << fl.x << " " << fl.y << " " << fl.z << endl;
      }
      else {
        cout << "Исходные данные " << i + 1 << " -ой точки: " << endl;
        cout << fl.x0 << " " << fl.y0 << " " << fl.z0 << " " << fl.radlenth << " " << fl.x << " " << fl.y << " " << fl.z << endl;
      }
      i++;
    }
    
    fin.close();
    fin.open(adresF, ios::in);
    i = 0;
    while (fin >> fl.x0 >> fl.y0 >> fl.z0 >> fl.radlenth >> fl.x >> fl.y >> fl.z) {
      if (i + 1 % ten == rem_1 && i + 1 % hundred != rem_2) {
        cout << i + 1 << "-яя ";
      }
      else {
        cout << i + 1 << "-ая ";
      }
      arr_res[i] = result(fl.x0, fl.y0, fl.z0, fl.x, fl.y, fl.z, fl.radlenth);
      if (arr_res[i] == 1) {
        cout << "точка принадлежит сфере." << endl;
      }
      else if (arr_res[i] == 0) {
        cout << "точка не принадлежит сфере." << endl;
      }
      if (i < c_points)i++;
    } 
    fin.close();
    delete[] arr_res;
    i = 1;
    cout << "Выберите вариант:" << endl;
    cout << "Сохранить результат в файл? " << endl;
    
    if (result_from_console() == 1) {
      cout << "Укажите путь и имя файла вывода. " << endl;
      cin >> pathF;
      foutch.open(pathF, ios::in);
      while (!check_read_only(pathF)) {
        foutch.close();
        cout << "Введите путь к файлу: " << endl;
        cin >> pathF;
        foutch.open(pathF, ios::in);

      }
      while (adresF == pathF) {
        cout << "Ошибка! Адрес файла вывода совпадает с файлом ввода!" << endl;
        cout << "Введите путь к файлу: " << endl;
        cin >> pathF;
      }
      while (file_name_check(pathF)) {
        foutch.close();
        cout << "Ошибка! Некорректное путь или имя файла." << endl;
        cout << "Введите путь к файлу: " << endl;;
        cin >> pathF;
        while (adresF == pathF) {
          cout << "Ошибка! Адрес файла вывода совпадает с файлом ввода!" << endl;
          cout << "Введите путь к файлу: " << endl;
          cin >> pathF;
        }
        foutch.open(pathF, ios::in);
      }
      if (file_exist(pathF) == false) {
        foutch.close();
        file_print_result(adresF, pathF, rewrite);
      }
      else {
        foutch.close(); 
        if (file_check_size(pathF) == true) {                 
          file_print_result(adresF, pathF, rewrite);
        }
        else {
          file_print_result(adresF, pathF, wtdw_file(pathF));
        }
      }
    }
    c_points = 0;
   
  } 
  fin.close();
}

bool check_read_only(string filename) {
  ofstream file(filename, ios::in);
  LPCSTR name = filename.c_str();
  WIN32_FIND_DATAA findData;
  FindFirstFileA(name, &findData);
  if (findData.dwFileAttributes & FILE_ATTRIBUTE_READONLY) {
    cerr << "Ошибка! Невозможно сохранить данные в файл, предназначенный только для чтения! " << endl;
    return false;
  }
  else {
    return true;
  }
}

bool file_name_check(string filename) { 
  size_t found = filename.find_last_of("\\");
  size_t point = filename.find_last_of(".");
  size_t base = point - found - 1;
  string basefilenameStr = filename.substr(found + 1, base);
  const char* basefilenameChar = basefilenameStr.c_str();
  ofstream file(filename, ios::app);
  if (!_strcmpi(basefilenameChar, "con")) return true;
  if (!std::filesystem::is_regular_file(filename)) return true;
  file.close();
  return false;
}

void file_print_result(string adresFile, string pathFile, int modout) {
  ifstream fin;
  ofstream fout;
  int i = 1;
  if (modout == 1) {
    fin.open(adresFile, ios::in);
    fout.open(pathFile, ios::out);
    fout << " " << endl;
  }
  else if (modout == 2) {
    fin.open(adresFile, ios::app);
    fout.open(pathFile, ios::app);
    fout << " " << endl;
  }
  
  while (fin >> fl.x0 >> fl.y0 >> fl.z0 >> fl.radlenth >> fl.x >> fl.y >> fl.z) {
    if (i + 1 % ten == rem_1 && i + 1 % hundred != rem_2) {
      fout << i << "-яя ";
    }
    else {
      fout << i << "-ая ";
    }
    double dotlenth = calc();
    double r = pow(dotlenth, 2);
    if (r == pow(dotlenth, 2) || dotlenth < fl.radlenth) {
      fout << "точка принадлежит сфере." << endl;
    }
    else {
      fout << "точка не принадлежит сфере." << endl;
    }
    if (i + 1 % ten == rem_1 && i + 1 % hundred != rem_2) {
      cout << "Результат по " << i << "-ей точке записан в указанном для вывода файле. " << endl;
    }
    else {
      cout << "Результат по " << i << "-ой точке записан в указанном для вывода файле. " << endl;
    }
    i++;
  }
  fin.close();
  fout.close();
}