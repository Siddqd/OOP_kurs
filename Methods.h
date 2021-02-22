#pragma once
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

  std::cout<<" 2) View med.card info /using Med_Card_ID >> \n";

  std::cout<<" 3) View list of free Med_rooms(chambers) >> \n";
                                                        //сначала добавляем пациента, потом мед карту
  std::cout<<" 4) Add new med.card/patient >> \n";    //если уже существует, изменяем данные(номер палаты, лечящего врача
                                                    //, дописываем историю болезни)
  std::cout<<" 5) Change the patient info(status or add new recs) >> \n";       //выписка пациента - освобождение палаты, смена статуса

  std::cout<<" 6) Change Doc info >> \n";

  std::cout<<" 0) Follow for the white rabbit ... \n";
};

void selectItem(char tmp) {
  MedPatient medP;
  Data bufDat;
  int bufInt;
  std::string bufStr;

    switch(tmp) {
      case '1' :
        system("cls");

        std::cout<< "Введите ID для поиска инфо пациента >> ";
        std::cout<<"(введите ID = 0 для поиска по ФИО и дате рождения) ";
        std::cin >> bufInt;
        medP.setID(bufInt);
        if (medP.getID()==0) {
            std::cout<<"Введите ФИО (через пробел latinicei) : ";
            getchar();
            getline(std::cin,bufStr);
            medP.setFio(bufStr);
  			std::cout<<"Введите день, месяц и год рождения(через пробел) : " ;
            std::cout<<"(возможен поиск только по ФИО , для этого введите день '0' )";
            std::cin >> bufDat.day >> bufDat.month >> bufDat.year;
            medP.setBday(bufDat);
          
        }


        if (medP.ShowDataScr("filePatient.txt") == -1) std::cout << "ErrorrE";
        break;

      case '2' :
        system("cls");
        break;

      case '3' :

        break;
        
      case '4' :
          medP.AddNewData("filePatient.txt");
        break;

      case '5' :

        break;

      case '6' :

        break;

      case '0' :
        rabbit();
        return;
        break;
      default:
        std::cout<<"Oops! Press num baby one more time >> from 1 to 6 or 0 >> ";
        system("cls");
        mainMenu();
    }
  return;
}
