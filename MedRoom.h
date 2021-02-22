#pragma once
#include "Med.h"
//const char* fileRoom = "fileRoom.txt"; //файл палат (1 1 строка - общ кол-во палат (предположим все палаты по 4 места),


class MedRoom : public Med
{
private:
	int id;
	int taked_cham;	//количество занятых мест в палате
	int* list_patient_id; //список id пациентов в палате (можно и не писать, искать инфу в MedHistory)
public:
	MedRoom();

	~MedRoom();
};
