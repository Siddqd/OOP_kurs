#pragma once
#include "Med.h"
//const char* fileRoom = "fileRoom.txt"; //файл палат (IDR Num_room Num_taked_places   (предположим все палаты по 4 места),


class MedRoom : public Med {
//private:
//	int idr;
//	int num;	//количество занятых мест в палате
	//int* list_patient_id; //список id пациентов в палате (можно и не писать, искать инфу в MedHistory)
public:
	MedRoom();
	//int getIDR(); - объявлены в базовом классе Med
	//int getNum();
	//void setIDR(int);
	//void setNum(int);
					  //0 - удачно , -1 - переполнено
	int lookFreeNum();//уст-ет значения класса номер и кол-во занятых мест первой не заполненой полностью палаты(не требует входных данных)
	void getRoomNum();//возвращает количество занятых мест в палате (требует заполненное значение ID)
	void showAllFreeNum();
	int chgFileRoom();
	~MedRoom();
};
