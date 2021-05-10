#pragma once
#include <cstdio>
#include "MedPatient.h"
#include "MedCard.h"
#include "MedDoc.h"
#include "MedRoom.h"


void rabbit() {
    system("cls");
    std::string os2 = "",os1 = "";
    for(int i=1;i<300;i++){
        if(!(i%50)) {
            os1 =" ";
            os2 = os2 + "\n\n\n";
        }
        std::cout<<os2;
        std::cout<<os1<<"(V)\n";
        std::cout<<os1<<"(..)\n";
        std::cout<<os1<<"(\")(\")\n";
        os1 = os1 + "  ";
        system("cls");
        
    }
}
void mainMenu() {
  std::cout<<" Main menU  "<<'\n';

  std::cout<<" 1) View patient info /using fio & bday or ID >> \n";

  //std::cout<<" 2) !@#$%^&*()_+ >> \n";

  std::cout<<" 2) View list of free Med_rooms(chambers) >> \n";
                                                        //сначала добавляем пациента, потом мед карту
  std::cout<<" 3) Add new med.card/patient >> \n";    //если уже существует, изменяем данные(номер палаты, лечящего врача
                                                    //, дописываем историю болезни)
  std::cout<<" 4) Change the patient info(status or add new recs) >> \n";       //выписка пациента - освобождение палаты, смена статуса

  std::cout<<" 5) Del the patient info (by ID) >> \n";

  std::cout<<" 0) Fast Exit >> \n";

  std::cout<<" r) Follow for the white rabbit ... \n";
};

void selectItem(char tmp) {
  MedRoom medR;
  MedPatient medP;
  Data bufDat;
  int bufInt;
  int oldSt,newSt,oldRoom,newRoom;
  std::string bufStr;

    switch(tmp) {
      case '1' :
        system("cls");

        std::cout<< "Ender ID to search patient info  ";
        std::cout<<"(Enter ID = 0 to search by FIO and  bday date) >> ";
        std::cin >> bufInt;
        medP.setID(bufInt);
        if (bufInt==0) {
            std::cout<<"Enter FIO(throw space) : ";
            getchar();
            getline(std::cin,bufStr);
            medP.setFio(bufStr);
  			std::cout<<"Enter day month year of bday(throw space) " ;
            std::cout<<"(to search just by FIO, enter the bday day = 0)";
            std::cin >> bufDat.day >> bufDat.month >> bufDat.year;
            medP.setBday(bufDat);
        }


        if (medP.ShowDataScr("D:\\wrk\\OOP_kurs\\filePatient.txt") == -1) std::cout <<'\n'<< "ErrorrE";
        system("pause");
        break;

      case '11' :
          std::cerr << "Crya! sistem failed !";
          system("pause");
        break;

      case '2' :
          medR.showAllFreeNum();
          std::cout << "\nPress Enter to continue";
          getchar();getchar();
          break;
        
      case '3' :
          medR.lookFreeNum(); //находим номер первой свободной палаты
          std::cout << "Nearest free room # : " << medR.getID() << " and " << medR.getSum() << " places are taked\n";
          //не совсем правильно, нужно было ввод сделать здесь в переменные , потом через setter положить в класс medP и потом записать в файл :)
          medP.AddNewData("filePatient.txt");
          if (medP.getStatus() == 1) {
              medR.setID(medP.getRoom_id());
              medR.chgFileRoom(1);
          }
          break;

      case '4' :
          medR.lookFreeNum(); //находим номер первой свободной палаты
          std::cout << "Nearest free room # : " << medR.getID() << " and " << medR.getSum() << " places are taked\n";
          std::cout << "Enter ID patient to change info : ";
          std::cin >> bufInt;
          medP.setData(bufInt); //запись в элемент класса всех данных о текущем пацинете
          oldRoom=medP.getRoom_id();
          oldSt=medP.getStatus();
          medP.changeData("D:\\wrk\\OOP_kurs\\filePatient.txt");
          newSt = medP.getStatus();
          newRoom = medP.getRoom_id();      //
          if (oldSt == 0 && newSt == 1) {                   //возврат пациента в клинику
              medR.setID(newRoom); medR.chgFileRoom(1);
          }
          if (oldSt == newSt == 1 && oldRoom != newRoom) { //перевод в другую палату
              medR.setID(oldRoom); medR.chgFileRoom(-1);
              medR.setID(newRoom); medR.chgFileRoom(1);
          }
          if (oldSt==1 && (newSt==0 || newSt==2)) { medR.setID(oldRoom); medR.chgFileRoom(-1); } //изм статуса пациента на вне больниц/умер
          break;
        
      case '5':
          std::cout << "Enter ID patient to delete info : ";
          std::cin >> bufInt;
          medP.setData(bufInt);
          if (medP.getStatus() == 1) {
              medR.setID(medP.getRoom_id());
              medR.chgFileRoom(-1);
          }
          medP.delData("D:\\wrk\\OOP_kurs\\filePatient.txt");
          break;

      case '0' :
        return;
        break;

      case 'r' :
        rabbit();
        return;
        break;
      default:
        std::cout<<"Oops! Press num baby one more time >> from 1 to 6 or 0 >> ";
        system("pause");
        system("cls");
        mainMenu();
    }
  return;
}
