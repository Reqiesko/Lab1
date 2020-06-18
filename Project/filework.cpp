#include "filework.h"
#include "tests.h"
#include "functions.h"
#include <iostream>

using namespace std;

struct filevariable {
  double x0, y0, z0, x, y, z, r, radlenth, dotlenth;
};
filevariable fl;

enum cFile {
  add = 1,
  createF = 2
};

int valpath = 0;
string pathF;
string adresF;
extern string pathc;
extern string adres;
int modout;
int val;
extern int valadres;
extern int way;

void file_work() {
  cout << "Укажите путь к файлу с исходными данными. " << endl;
  cin >> adresF;
  ifstream fin;
  ofstream fout;
  ifstream foutch;
  int count = 0, c_points = 0;
  fin.open(adresF);
  while (file_name_check(adresF)) {
    fin.close();
    cout << "Ошибка! Введен неккоректный путь к файлу! \nВведите путь к файлу: " << endl;
    cin >> adresF;
    fin.open(adresF);
  }
  if (!fin.is_open()) {
    cout << "Ошибка! Не удаётся открыть файл для вывода!" << endl;
    cin.clear();
    cin.ignore(32767, '\n');
    menu();
  }
  else {
    double temp;
    if (file_check_size(adresF) == true) {
      cout << "Ошибка! Файл пуст!" << endl;
      cin.clear();
      cin.ignore(32767, '\n');
      fin.close();
      menu();
    }
    while (fin) {
      fin >> temp;
      if (fin.fail() && !fin.eof()) {
        cout << "Ошибка! Файл содержит некорректные данные. " << endl;
        cin.clear();
        cin.ignore(32767, '\n');
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
      if (i + 1 % 10 == 3 && i + 1 % 100 != 13) {
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
      if (i + 1 % 10 == 3 && i + 1 % 100 != 13) {
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
    result_from_console();
    if (way == 1) {
      cout << "Укажите путь и имя файла вывода. " << endl;
      cin >> pathF;
      foutch.open(pathF, ios::in);
      while (!check_read_only(pathF)) {
        foutch.close();
        cout << "Введите путь к файлу: " << endl;
        cin >> pathF;
        foutch.open(pathF, ios::in);

      }
      if (adresF == pathF) {
        same_path();
        if (val == 2) {
          modout = 1;
          file_print_result(adresF, pathF, i);
          menu();
        }
        else if (val == 2) {
          modout = 1;
          file_print_result(adresF, pathF, i);
          menu();
        }
        else if (val == 1) {
          modout = 2;
          file_print_result(adresF, pathF, i);
          menu();
        }
      }
      while (file_name_check(pathF)) {
        foutch.close();
        cout << "Ошибка! Некорректное путь или имя файла." << endl;
        cout << "Введите путь к файлу: " << endl;;
        cin >> pathF;
        foutch.open(pathF, ios::in);
      }
      if (file_exist(pathF) == false) {
        foutch.close();
        fout.open(pathF);
      }
      else {
        if (file_check_size(pathF) == false) {
          foutch.close();
          wtdw_file();
          if (valadres == 2) {
            modout = 1;
            file_print_result(adresF, pathF, i);
            menu();
          }
          else if (valadres == 1) {
            modout = 2;
            file_print_result(adresF, pathF, i);
            menu();
          }
        }
        modout = 2;
        file_print_result(adresF, pathF, i);
      }
    }
    c_points = 0;
   
  } 
  fin.close();
  fout.close();
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
void file_print_result(string adresFile, string pathFile, int i) {
  ifstream fin;
  ofstream fout;
  if (modout == 1) {
    fin.open(adresFile, ios::app);
    fout.open(pathFile, ios::app);
    fout << " " << endl;
  }
  else if (modout == 2) {
    fin.open(adresFile, ios::in);
    fout.open(pathFile, ios::out);
    fout << " " << endl;
  }
  while (fin >> fl.x0 >> fl.y0 >> fl.z0 >> fl.radlenth >> fl.x >> fl.y >> fl.z) {
   if (i % 10 == 3 && i % 100 != 13) {
      fout << i << "-яя ";
    }
    else {
      fout << i << "-ая ";
    }
    calc();
    if (fl.r == pow(fl.dotlenth, 2) || fl.dotlenth < fl.radlenth) {
      fout << "точка принадлежит сфере." << endl;
    }
    else {
      fout << "точка не принадлежит сфере." << endl;
    }
    if (i % 10 == 3 && i % 100 != 13) {
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

int same_path() {
  ifstream foutcheck;
  
  bool d = true;
  cFile floor = add;
  int del = floor;
  string pfile;
  while (d) {
    cout << "Адреса файлов совпадают! Выберите вариант:." << endl;
    cout << "1. Дописать в конец." << endl;
    cout << "2. Указать другой файл для вывода." << endl;
    cin >> del;
    if (!error_check()) {
      continue;
    }
    cin.ignore(32767, '\n');
    switch (del) {
      case add: {
        val = 2;       
        d = false;
        break;
      }
      case createF: {            
        cout << "Введите путь к файлу. " << endl;
        cin >> pfile;
        pathF = pfile;
        pathc = pfile;
        foutcheck.open(pfile, ios::in);
        if (file_exist(pfile) == true && adresF != pathF) {
          foutcheck.close();
          val = wtdw_file();
        }
        while (!check_read_only(pfile)) {
          foutcheck.close();
          cout << "Введите путь к файлу: " << endl;
          cin >> pfile;
          pathF = pfile;
          pathc = pfile;
          foutcheck.open(pfile, ios::in);
        }
        while (file_name_check(pfile)) {
          foutcheck.close();
          cout << "Ошибка! Некорректный путь или имя файла." << endl;
          cout << "Введите путь к файлу: " << endl;
          cin >> pfile;
          pathF = pfile;
          pathc = pfile;
          foutcheck.open(pfile, ios::in);
        }                   
        if (adresF == pathF) {
          foutcheck.close();
          same_path();
        }

        
        foutcheck.close();        
        d = false;
        break;
      }
      default: {
        cout << "Пожалуйста введите цифру 1 или 2.  " << endl;
      }
    }
  }
  return val;
}

