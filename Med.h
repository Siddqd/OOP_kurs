#pragma once
#include <iostream>
#include <string>
#include <fstream>
//#include <sstream>
#include <cstdio>


const int MaxRooms = 25;
const int MaxPatient = 4*MaxRooms;
//файл пациентов (1 строка 1 число - текущее количество пациентов, 2 число - номер последнего пациента)
//перед записью нового пациента тест на оставшееся количество мест в больнице и в палате начиная с  1, IDcham, list IDpat(список ID_пациентов в палате)

struct Data {	//для упрощения , 12 месяцев по 30 дней + - ~
	int day;
	int month;
	int year;
};

class Med	{
	protected:
		int sum;
		int id;
		
	public:
		int getID() { return id; }
		void setID(int idd) { id = idd; }

		//virtual int ShowDataScr(const char*) ;
		//virtual int AddNewData(const char*);
		//virtual int DeleteData(const char*);
		//virtual int RewriteData(const char*);
		//virtual int PrintDataFile(const char*);
};
