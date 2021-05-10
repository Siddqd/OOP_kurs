// OOP_kurs.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//#include <iostream>
//#include <string>

#include "Methods.h"

using namespace std;

int main() {
  char tmpp;
  setlocale(LC_ALL, "rus");
  
  do {
    mainMenu();
    std::cout << "\nEnter the num of menu_item >>> ";
    std::cin>>tmpp;
    selectItem(tmpp);
    system("cls");
  } while (tmpp != '0');
  return 0;
}

