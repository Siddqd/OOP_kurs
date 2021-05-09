#include "MedPatient.h"


MedPatient::MedPatient() {
	this->id = 0;			//конструктор пациента пустой
	this->fio = "";
	this->bday.day = 0;
	this->bday.month = 0;
	this->bday.year = 0;
	this->tel = 0;
	this->res_tel = 0;
	this->polis = 0;
	this->status = -1;
	this->room_id = 0;
	this->doc_id = 0;
}

MedPatient::MedPatient(int idpp) {
	this->id = idpp;			//конструктор пациента ID
	this->fio = "";
	this->bday.day = 0;
	this->bday.month = 0;
	this->bday.year = 0;
	this->tel = 0;
	this->res_tel = 0;
	this->polis = 0;
	this->status = -1;
	this->room_id = 0;
	this->doc_id = 0;
}

MedPatient::MedPatient(std::string fioo,Data bdayy) {
	this->id = 0;			//конструктор пациента фио и ДР
	this->fio = fioo;
	this->bday = bdayy;
	this->tel = 0;
	this->res_tel = 0;
	this->polis = 0;
	this->status = -1;
	this->room_id = 0;
	this->doc_id = 0;
}

MedPatient::MedPatient(int idpp, std::string fioo, Data bdayy,
				int tell, int res_tell, int64_t poliss, int status, int room_id, int doc_id) {

		this->id = idpp;			//конструктор пациента полный
		this->fio = fioo;
		this->bday = bdayy;
		this->tel = tell;
		this->res_tel = res_tell;
		this->polis = poliss;
		this->status = 1;
		this->room_id = 0;
		this->doc_id = 0;
}

/*MedPatient::MedPatient(int idpp, std::string fioo, data bdayy, int tell, int res_tell, int64_t poliss) {
	try {
	this->idp = idpp;			//конструктор пациента
	this->fio = fioo;
	this->bday = bdayy;
	this->tel = tell;
	this->res_tel = res_tell;
	this->polis = poliss;

	}
}*/

int MedPatient::look4(const char* filePat) { //fio2 поиск по фио и ДР, предварительно создаем объект пациент
    int idpp = -1;							// , куда записываем фио и полис
	int foo32;							   //итоговый результат запись всех найденных данных в объект
	int64_t foo64;			 			  //и сравниваем со значениями в файле пациентов
	Data bdres;
	std::string bar;
	std::string foo;

	std::fstream fPat;
	fPat.open(filePat);

    try {									        					
		if (fPat.is_open()) throw "Error_OpenFile";
		if (fPat.eof()) throw "Error_filePatient_is_EMPTY";
	}	catch (const char* err) { std::cout << err; }//{std::cout<< err; fPat.close(); return -1;}

	while (!fPat.eof()) {
			fPat>>bar;                    // считываем первую строку - общее кол-во пациентов
			fPat>>bar;					 // 2ю строку(или 2е число) - номер крайнего пациента
									//просто для пролистывания,хотя можно и вывести
		
			fPat>>bar;							//считываем сигнатуру IDP
			if (bar != "IDP") return -1;		//проверяем сигнатуру IDP //варик ? for(;bar!="IDP";	fPat>>bar)
			fPat >> idpp;						//считали ID текущего пациента
			if (id!=idpp){						//нужный пациент(выполнен поиск по ID) - пропускаем поиск по фио
					fPat>>bar;					//считываем по идее FIO
					if (bar != "FIO") return -1;;
					getchar();
					std::getline(fPat,bar);		//считали фамилию , но с пробелом в начале
					if(" "+fio!=bar) continue; 		//если == , значит фамилия найдена,если != цикл начинаем сначала

					fPat >> bar;											//считываем сигнатуру ДР
					if (bar != "BDAY") return -1;						   //если да, если нет ошибка :[]
					fPat >> bdres.day >> bdres.month >> bdres.year;		  //считываем ДР

					if (bdres.day!=0)	//сравниваем ДР с заданым, если нет идем к след фамилии
						if (bdres.day!=bday.day || bdres.month!=bday.month || bdres.year!=bday.year) continue;
					//если др не задано = 0, то пропускаем сравнение и выводим всех с такой ФИО
										
					//сразу поадаем сюда если bday.day==0 , то есть не задана ДР/ ищет первое совпадение по фио
					//перезаписываем оставшиеся поля класса
			} else {	//сюда попадаем если удачно прошел поиск по ID и 
						fPat >> bar; 
						if (bar == "FIO") { bar = fPat.get(); std::getline(fPat, fio);}
							 	else throw "Oops ... shit happens :|";
						fPat >> bar; 
						if (bar=="BDAY") {fPat>>bday.day; fPat>>bday.month; fPat>>bday.year;}
							 	else throw "Oops ... shit happens :|";
			}		//сюда уходим для проверки совпадения по фио и дате ДР
			id=idpp;
			try {
				fPat >> bar; if (bar=="TEL") fPat>>tel; else throw "Oops ... shit happens :|";
				fPat >> bar; if (bar == "RES_TEL") fPat >> res_tel; else throw "Oops ... shit happens :|";
				fPat >> bar; if (bar == "POLIS") fPat >> polis; else throw "Oops ... shit happens :|";
				fPat >> bar; if (bar == "STATUS") fPat >> status; else throw "Oops ... shit happens :|";
				fPat >> bar; if (bar == "ROOM_ID") fPat >> room_id; else throw "Oops ... shit happens :|";
				fPat >> bar; if (bar == "DOC_ID") fPat >> status; else throw "Oops ... shit happens :|";
				//fPat >> foo32; if (foo=="STATUS") fPat>>status; else throw "Oops ... shit happens :|"
				//возможно вывод данных убрать ? оставить только возврат ID
			} catch (const char* er) { std::cout << er;fPat.close();return -1; }
			
			std::cout<<"		   			  Patient  ID : "<<id<<'\n';
			std::cout<<"						Full name : "<<fio<<'\n';
			std::cout<<"				    Birthday date : "<<bday.day<<' '<<bday.month<<' '<<bday.year<<'\n';
			if (bday.day==0) continue;	//если др не задан в начало цикла - выводим всех с такой фио пока не конец файла
			std::cout<<"		     Patient phone number : "<<tel<<'\n';
			std::cout<<"        Phone number of relatives : "<<res_tel<<'\n';
			std::cout<<"						Polis num : "<<polis<<'\n';
			if (status==0) std::cout<<"Sry, patient is game over ..";
			if (status==2) std::cout<<"Patient was discharged out ..";
			if (status==1) std::cout<<"Patient now in chamber num : " <<room_id<<'\n';
			//if (bday.day == 0) continue;

			fPat.close();
			return id; //возвращаем # id пациента - соответсвует номеру мед карты
	}
	fPat.close();
	std::cout << "You push key .. 4 or push key ... patient with entered data is not detected";
	return -1;
}

int MedPatient::setData(int idpp) {
	int foo32;												//итоговый результат запись всех найденных данных в объект
	int64_t foo64;
	Data bdres;
	std::string bar;
	std::string foo;

	std::fstream fPat("filePatient.txt");


	try {									        					//и сравниваем со значениями в файле пациентов

		if (!fPat.is_open()) throw "Error_OpenFile";
		if (fPat.eof()) throw "Error_filePatient_is_EMPTY";
	}
	catch (const char* er) { std::cout << er; fPat.close(); return 11; }

	//fPat>>bar;                    // считываем первую строку - общее кол-во пациентов
	//fPat>>bar;										// 2ю строку - номер крайнего пациента
																		//просто для пролистывания,хотя можно и вывести
	id = idpp;
	while (!fPat.eof()) {
		fPat >> bar;										//считываем сигнатуру IDP
		if (bar == "IDP") {
			fPat >> foo32;
			if (idpp == foo32) {
				fPat >> bar;
				if (bar == "FIO")
				{	
					try {
						fPat.get();
						getline(fPat, fio);//считали фамилию , но с пробелом в начале
						fPat >> bar;		//считали 
						if (bar == "BDAY") { fPat >> bdres.day >> bdres.month >> bdres.year; }		//если да, если нет ошибка :[]
						else throw "Oops ... shit happens :|";
						fPat >> bar; if (bar == "TEL") fPat >> tel; else throw "Oops ... shit happens :|";
						fPat >> bar; if (bar == "RES_TEL") fPat >> res_tel; else throw "Oops ... shit happens :|";
						fPat >> bar; if (bar == "POLIS") fPat >> polis; else throw "Oops ... shit happens :|";
						fPat >> bar; if (bar == "STATUS") fPat >> status; else throw "Oops ... shit happens :|";
						fPat >> bar; if (bar == "ROOM_ID") fPat >> room_id; else throw "Oops ... shit happens :|";
						fPat >> bar; if (bar == "DOC_ID") fPat >> status; else throw "Oops ... shit happens :|";
						return 0;
					}
					catch (const char* er) { std::cout << er;fPat.close();return 11; }
				}
			}
		}
	}
	return 11;
}
																										//плюс альтернативный поис по ID
int MedPatient::ShowDataScr(const char* filePat) { //fio2 поиск по фио и ДР, предварительно создаем объект пациент
	int idpp = -1;										// , куда записываем фио и полис
	int foo32;												//итоговый результат запись всех найденных данных в объект
	int64_t foo64;
	Data bdres;
	std::string bar;
	std::string foo;

	std::fstream fPat(filePat);
	

	try {									        					//и сравниваем со значениями в файле пациентов
			
			if (!fPat.is_open()) throw "Error_OpenFile";
			if (fPat.eof()) throw "Error_filePatient_is_EMPTY";
	}	catch(const char* er) {std::cout<< er; fPat.close(); return -1;}

	//fPat>>bar;                    // считываем первую строку - общее кол-во пациентов
	//fPat>>bar;										// 2ю строку - номер крайнего пациента
																		//просто для пролистывания,хотя можно и вывести
	while (!fPat.eof()) {
		fPat>>bar;										//считываем сигнатуру IDP
		if (bar != "IDP") continue;		//проверяем сигнатуру IDP, если нет то сначала //варик ? for(;bar!="IDP";	fPat>>bar)
		fPat>>idpp;										//считали ID текущего пациента
		if (id!=idpp){ //нужный пациент(выполнен поиск по ID) - пропускаем поиск по фио
				fPat>>bar;						//считываем по идее FIO
				if(bar!="FIO") continue;
				fPat.get();
				getline(fPat, bar);//считали фамилию , но с пробелом в начале
				
				if(fio!=bar) continue; 		//если == , значит фамилия найдена
				fPat >> bar;										//считываем сигнатуру ДР
				if (bar!="BDAY") return -1;		//если да, если нет ошибка :[]
				fPat >> bdres.day >> bdres.month >> bdres.year;			//считываем ДР

				if (bday.day!=0)
					if (bdres.day!=bday.day || bdres.month!=bday.month || bdres.year!=bday.year) continue;
					//если др не задано = 0, то пропускаем сравнение и выводим всех с такой ФИО
					//сравниваем ДР с заданым, если нет идем к след фамилии
					//если ок полное совпадение фио и др
					//сразу поадаем сюда если bday.day==0 , то есть не задана ДР/ ищет первое совпадение по фио
					//можно сделать вывод текущих данных с запросом дальнейшего поиска совпадений по фио
					//перезаписываем оставшиеся поля класса

		} else {	//сюда попадаем если удачно прошел поиск по ID
			fPat >> bar;
			if (bar == "FIO") { bar = fPat.get(); std::getline(fPat, fio); }
			else throw "Oops ... shit happens :|";
			fPat >> bar;
			if (bar == "BDAY") { fPat >> bday.day; fPat >> bday.month; fPat >> bday.year; }
			else throw "Oops ... shit happens :|";
		}	//сюда уходим после проверки совпадения по фио и дате ДР
			id=idpp;
			try {
				fPat >> bar; if (bar=="TEL") fPat>>tel; else throw "Oops ... shit happens :|";
				fPat >> bar; if (bar == "RES_TEL") fPat >> res_tel; else throw "Oops ... shit happens :|";
				fPat >> bar; if (bar == "POLIS") fPat >> polis; else throw "Oops ... shit happens :|";
				fPat >> bar; if (bar == "STATUS") fPat >> status; else throw "Oops ... shit happens :|";
				fPat >> bar; if (bar == "ROOM_ID") fPat >> room_id; else throw "Oops ... shit happens :|";
				fPat >> bar; if (bar == "DOC_ID") fPat >> status; else throw "Oops ... shit happens :|";
				//fPat >> foo32; if (foo=="STATUS") fPat>>status; else throw "Oops ... shit happens :|"

			} catch (const char* er) { std::cout << er;fPat.close();return -1; }
			
			if (bday.day==0) std::cout<<"Patient  ID : "<<id<<'\n';
			std::cout<<"Full name : "<<fio<<'\n';
			std::cout<<"Birthday date : " << bday.day << ' ' << bday.month << ' ' << bday.year << '\n';
			if (bday.day==0) continue;
			std::cout<<"Patient phone number : "<<tel<<'\n';
			std::cout<<"Phone number of relatives : "<<res_tel<<'\n';
			std::cout<<"Polis num : "<<polis<<'\n';
			if (status==0) std::cout<<"Patient was discharged out ..";
			if (status==2) std::cout<< "Sry, patient is game over ..";
			if (status==1) std::cout<<"Patient now in chamber num : " <<room_id<<'\n';
			
			fPat.close();
			return id; //возвращаем # id пациента - соответсвует номеру мед карты
	}
			
	fPat.close();
	std::cout << "Yo push key .. 4 a push key ... \n patient with entered data is not detected";
	return -1; //если поиск прошел не удачно
}

int MedPatient::AddNewData(const char* filePat) {
	std::string bar;
	int idpp = 0, sum_pat = 0;
	std::fstream fPat("fileID.txt",std::ios::in|std::ios::beg);
	//fPat.close();
	//fPat.open(filePat, std::ios::in );	//открываем файл для чтения
	
	try {
			//проверка открытия файла
		if (fPat.eof()) throw 0;		
		fPat >> sum_pat;						//считали текущее общее количество пациентов
		if (sum_pat >= MaxPatient) throw "sorrY_Clinic_Overflow"; //если больше равно макс - клиника переполнена
		fPat >> idpp;					// считали последний занятый ID пациента
		
	}
	catch (const char* er) { std::cout << er;return -1; }
	catch (int e) { }	//переходим сюда если файл пуст
	++sum_pat;      //если не выкинуло, то места есть, прибавляем +1
	++idpp;			//записываем ID для нового-текущего пациента
		//fPat.seekg(0, std::ios::beg);//встаем в начало файла
	fPat.close();
	fPat.open("fileID.txt", std::ios::out|std::ios::beg); //открываем для файл для записи
	fPat << sum_pat <<" "<< idpp;	//пишем новое значения общего числа пациентов и номер нового крайнего
	fPat.close();
	id = idpp;
	//ввод данных нового пациента
	//std::getline(std::cin , bar);
	std::getchar();//считываем символ /n после cin char из selectItem
	std::cout<<"Enter FIO (throw space) : ";
	std::getline(std::cin, fio);//std::cout <<'\n'<< fio<<'\n';
	std::cout<<"Enter day, month and year of bday(throw space) : " ;
	std::cin>>bday.day>>bday.month>>bday.year;
	try {
				if (bday.day<1||bday.day>31||bday.month<1||bday.month>12||bday.year<1910|| bday.year>2021) throw "Error_bday_input";
	} catch (const char* err) {	std::cout << err << '\n';	return -1;	}	
				
	do  {
		std::cout<<"Enter num cell phone : " ;
		std::cin>>tel;
	} while (tel > 89999999999 || tel < 0);
	std::cout<<"Enter relative num phone  : " ;
	std::cin>>res_tel;
	std::cout<<"Enter POLIS num : ";
	std::cin>>polis;
	status=1;std::cout<<"Status of new patient is set in : 1 - At hospital \n";
	std::cout<<"Enter chamber num : "; //можно выводить список ближайших свободных палат
	std::cin>>room_id;
	std::cout<<"Enter id doc : ";		//можно выводить список врачей
	std::cin>>doc_id;

	fPat.clear();
	fPat.open(filePat,std::ios::app);	//добавляем нового пациента в конец файла
	fPat <<"\nIDP " << id << "\nFIO "<< fio<< "\nBDAY " <<bday.day<<" "<<bday.month<<" "<<
		bday.year<<"\nTEL "<<tel<<"\nRES_TEL "<<res_tel<<"\nPOLIS "<<polis
		<<"\nSTATUS "<<status<<"\nROOM_ID " <<room_id<<"\nDOC_ID "<<doc_id;
	fPat.close();
	return 0;
}

int MedPatient::changeData(const char* filePat) {
	int idpp = -1;										// , куда записываем фио и полис
	int foo32, bar32, old_stat = 0, new_stat = 0;				//итоговый результат запись всех найденных данных в объект
	int len = 1, old_room = 0, new_room = 0, old_room_num = 0, new_room_num = 0;
	int64_t foo64;
	Data bdres;
	std::string bar;
	std::string foo;

	//char* buffer;

	std::fstream fPat(filePat);
	try {									        					//и сравниваем со значениями в файле пациентов

		if (!fPat.is_open()) throw "Error_OpenFile";
		if (fPat.eof()) throw "Error_filePatient_is_EMPTY";
	}
	catch (const char* er) { std::cout << er; fPat.close(); return 11; }

	std::ofstream f2Pat;
	f2Pat.open("buf.txt", std::ofstream::out, std::ofstream::trunc);
	f2Pat.clear();
	f2Pat.close();
	f2Pat.open("buf.txt", std::ofstream::out);
	try {									        					//и сравниваем со значениями в файле пациентов

		if (!f2Pat.is_open()) throw "Error_OpenFile";
		if (fPat.eof()) throw "Error_filePatient_is_EMPTY";
	}
	catch (const char* er) { std::cout << er; f2Pat.close(); return 11; }


	std::cin >> id;					//считали id пациента, данные которого хотим поменять
	//fPat>>bar;                    // считываем первую строку - общее кол-во пациентов
	//fPat>>bar;										// 2ю строку - номер крайнего пациента
																		//просто для пролистывания,хотя можно и вывести
	while (!fPat.eof()) {
		fPat >> bar;		//считываем сигнатуру IDP
		if (bar != "IDP") continue;		//проверяем сигнатуру IDP, если нет то сначала //варик ? for(;bar!="IDP";	fPat>>bar)
		fPat >> idpp;										//считали ID текущего пациента
		if (id == idpp) { //нужный пациент(выполнен поиск по ID) - пропускаем поиск по фио
			len = -1;
			break;
		}
		else continue;
	}
	if (len == 1) {
		std::cerr << "Error 404 ! No Data about entered ID :|";
		return 11;
	}
	//len = fPat.tellg();
	//buffer = new char[len];
	fPat.close();
	fPat.open(filePat);
	for (int i = 0;i < (id - 1) * 9;i++) {
		getline(fPat, foo);
		foo = foo + '\n';
		f2Pat << foo;
	}

	//перед удалением статус должен быть = 0 или 2
	std::cout << "Enter 0 to delete patient, or 1 to make change : ";
	std::cin >> foo32;
	if (foo32 == 0)	//пропускаем 9 строк и начинаем запись во второй файл до конца файла
		for (int i = 0;i < 8;i++) //возможна ошибка при данном способе пролистывания , если появится пустая строка
			getline(fPat, foo);

	else {	//сюда попадаем если нужно изменять даунные пациента
		getline(fPat, foo);
		f2Pat << foo << '\n'; //записали idp ## во второй файл
		fPat >> bar;//считали FIO
		getline(fPat, foo); //записали данные fio в foo
		std::cout << "Current FIO : " << foo;
		std::cout << "\nEnter FIO (throw space; enter 0 to stay without changes) : ";
		std::getchar();
		getline(std::cin, bar); //считали в бар данные FIO 
		if (bar != "0") f2Pat << "FIO " << bar << '\n';
		else f2Pat << "FIO " << foo << '\n';

		fPat >> bar; //считали "BDAY"
		getline(fPat, foo);
		std::cout << "Current BDAY data : " << foo << '\n';
		std::cout << "Enter dd mm yyyy of bday(or enter 0 0 0 to stay w/o changes) : ";
		std::cin >> bdres.day >> bdres.month >> bdres.year;

		if (bdres.day == 0) f2Pat << "BDAY " << foo << '\n';
		else {
			try {
				if (bdres.day < 1 || bdres.day>31 || bdres.month < 1 || bdres.month>12 || bdres.year < 1910 || bdres.year>2021) throw "Error_bday_data_input";
			}
			catch (const char* err) { std::cout << err << '\n';	return -1; }
			f2Pat << "BDAY " << bdres.day << " " << bdres.month << " " << bdres.year << '\n';
		}

		fPat >> bar;
		fPat >> bar32; //переместились
		std::cout << "\nCurrent TEL : " << bar32;
		//do {
		std::cout << "\nEnter num cell phone(0 - stay w/o changes): ";
		std::cin >> tel;
		//} while (tel > 89999999999 || tel < 0);
		if (tel == 0) f2Pat << "TEL " << bar32 << '\n';
		else f2Pat << "TEL " << tel << '\n';


		fPat >> bar;
		fPat >> bar32; //переместились
		std::cout << "\nCurrent RES_TEL : " << bar32;
		std::cout << "\nEnter relative num phone (0 - stay w/o changes): ";
		std::cin >> res_tel;
		if (res_tel == 0) f2Pat << "RES_TEL " << bar32 << '\n';
		else f2Pat << "RES_TEL " << res_tel << '\n';

		fPat >> bar;
		fPat >> foo64; //переместились,в foo64 текущий полис
		std::cout << "Current POLIS : " << foo64;
		std::cout << "\nEnter new POLIS num (0 - stay w/o changes): ";
		std::cin >> polis;
		if (polis == 0) f2Pat << "POLIS " << foo64 << '\n';
		else f2Pat << "POLIS " << polis << '\n';

		fPat >> bar;
		fPat >> old_stat; //переместились, в bar32 текущий статус
		std::cout << "Current status : " << old_stat;
		//old_stat = bar32;
		std::cout << "\nEnter status (0 - Out of hospital, 1 - At hospital, 2 - Dead): ";
		std::cin >> new_stat;
		//если статус изменен, надо убавить общ кол-во пациентов в fileID, и убавить кол-во пациентов в палате fileRoom
		//if (status == -1) f2Pat << "STATUS " << bar32 << '\n';
		f2Pat << "STATUS " << new_stat << '\n';

		fPat >> bar;
		fPat >> old_room; //переместились, в bar32 текущий номер палаты
		if (old_stat == 1 && old_stat != new_stat) { //если пациент был выписан из больницы или умер, меняем номер палаты на 0
			std::cout << "MedRoom # wil autoset in 0 (patient is out) \n";
			f2Pat << "ROOM_ID " << 0 << '\n';
		}
		else {
			std::cout << "Current chamber(room) # : " << old_room;
			std::cout << "\nEnter chamber(room) # (enter 0 to stay w/o changes) : "; //можно выводить список ближайших свободных палат
			std::cin >> new_room;
			f2Pat << "ROOM_ID " << new_room << '\n';
		}


		fPat >> bar;
		fPat >> bar32; //переместились
		std::cout << "Current doc id : " << bar32;
		std::cout << "\nEnter id doc(enter 0 to stay w/o changes)) : ";		//можно выводить список врачей
		std::cin >> doc_id;
		if (doc_id == 0) f2Pat << "DOC_ID " << bar32 << '\n';
		else f2Pat << "DOC_ID " << doc_id << '\n';
	}
	getline(fPat, bar);//считывается пустая строка , хз откуда :D
	while (!fPat.eof()) {
		getline(fPat, bar);
		if (!bar.empty())
			f2Pat << bar << '\n';
	}
	fPat.close();
	f2Pat.close();
	rename(filePat, "1.txt");
	rename("buf.txt", filePat);
	remove("1.txt");

	//перевод пациента в другую палату
	/*if (old_stat == new_stat == 1 && old_room != new_room) {
		std::fstream f4Pat("fileRoom.txt");
		try {
			if (!f4Pat.is_open()) throw "Error_OpenFile fileRoom";
			if (f4Pat.eof()) throw "Error_fileRoom_is_EMPTY";
		}
		catch (const char* er) { std::cout << er; f4Pat.close(); return -1; }
		do {
			f4Pat >> bar >> bar32;//считали idr
			if (bar32 == old_room) {
				f4Pat>>old_room_num;
			}
			if (bar32 == new_room) {
				f4Pat >> new_room_num; //считали текущее колво пациентов в палате из которой убираем/добавляем пациента
				if (new_room_num > 3) {
					std::cerr << " Error removing patient to new med room ! ";	//ошибка палата переполнена
					return -1;
				}
			}
		} while (!f4Pat.eof()||(new_room_num&&old_room_num));
		f4Pat.close();
		f4Pat.open("fileRoom.txt");
		++new_room_num;
		--old_room_num;
		do {
			f4Pat >> bar >> bar32;//считали idr
			if (bar32 == old_room) f4Pat << ' ' << old_room_num;
			else if (bar32 == new_room) f4Pat << ' ' << new_room_num;
			else f4Pat >> bar32;
		} while (!f4Pat.eof());
		f4Pat.close();
	}
	*/
	//начинаем изменять файлы fileID, если статус был изменен определеным значением
	if (old_stat != new_stat) {
		std::fstream f3Pat("fileID.txt");
		try {
			if (!f3Pat.is_open()) throw "Error_OpenFile fileID";
			if (f3Pat.eof()) throw "Error_fileID_is_EMPTY";
		}
		catch (const char* er) { std::cout << er; f3Pat.close(); return 11; }
		/*std::fstream f4Pat("fileRoom.txt");
		try {
			if (!f4Pat.is_open()) throw "Error_OpenFile fileRoom";
			if (f4Pat.eof()) throw "Error_fileRoom_is_EMPTY";
		}
		catch (const char* er) { std::cout << er; f4Pat.close(); f3Pat.close(); return 11; }
		*/
		if (old_stat == 1 || (old_stat == 0 && new_stat == 1)) {
			f3Pat >> bar >> bar32; //меняем значение общ количества пациентов в больнице
			if (old_stat == 1) --bar32; else ++bar32;
			//f3Pat.clear();
			f3Pat.close();
			f3Pat.open("fileID.txt");
			f3Pat << bar << ' ' << bar32;
			f3Pat.close();
		}
	}
	/*
		do {
			f4Pat >> bar >> bar32;//считали idr
			if (bar32 == new_room) {
				f4Pat >> foo32; //считали текущее колво пациентов в палате из которой убираем/добавляем пациента
				if (old_stat == 1) --foo32; else ++foo32;	//изменили кол-во
				break;
			}
			f4Pat >> bar32; //пропускаем для перехода к след палате
		} while (!f4Pat.eof());
		f4Pat.close();
		f4Pat.open("fileRoom.txt");
		do {
			f4Pat >> bar >> bar32;//считали idr
			if (bar32 == new_room) break;
			f4Pat >> bar32; //пропускаем кол-во пациентов в палате для перехода к след палате
		} while (!f4Pat.eof());
		f4Pat << ' ' << foo32; //перезаписали новое уменьшенное количество пациентов*/
		/*
			}
			f4Pat.close();
		}*/
		//fPat.read(buffer, len);
		//f2Pat.write(buffer, len);
		//delete[] buffer;
		//if (old_stat==new_stat)
	return 0;

}
	
int MedPatient::delData(const char* filePat) {
	int idpp = -1;										// , куда записываем фио и полис
	int foo32, bar32, old_stat = 0, new_stat = 0;				//итоговый результат запись всех найденных данных в объект
	int len = 1, old_room = 0, new_room = 0, old_room_num = 0, new_room_num = 0;
	int64_t foo64;
	Data bdres;
	std::string bar;
	std::string foo;
	//char* buffer;

	std::fstream fPat(filePat);
	try {									        					//и сравниваем со значениями в файле пациентов
		if (!fPat.is_open()) throw "Error_OpenFile";
		if (fPat.eof()) throw "Error_filePatient_is_EMPTY";
	}
	catch (const char* er) { std::cout << er; fPat.close(); return 11; }

	std::ofstream f2Pat;
	f2Pat.open("buf.txt", std::ofstream::out, std::ofstream::trunc);
	f2Pat.clear();
	f2Pat.close();
	f2Pat.open("buf.txt", std::ofstream::out);
	try {									        					//и сравниваем со значениями в файле пациентов

		if (!f2Pat.is_open()) throw "Error_OpenFile";
		if (fPat.eof()) throw "Error_filePatient_is_EMPTY";
	}
	catch (const char* er) { std::cout << er; f2Pat.close(); return 11; }

	//std::cin >> id;					//считали id пациента, данные которого хотим поменять
	//fPat>>bar;                    // считываем первую строку - общее кол-во пациентов
	//fPat>>bar;										// 2ю строку - номер крайнего пациента
																		//просто для пролистывания,хотя можно и вывести
	while (!fPat.eof()) {
		fPat >> bar;		//считываем сигнатуру IDP
		if (bar != "IDP") continue;		//проверяем сигнатуру IDP, если нет то сначала //варик ? for(;bar!="IDP";	fPat>>bar)
		fPat >> idpp;										//считали ID текущего пациента
		if (id == idpp) { //нужный пациент(выполнен поиск по ID) - пропускаем поиск по фио
			len = -1;
			break;
		}
		else continue;
	}
	if (len == 1) {
		std::cerr << "Error 404 ! No Data about entered ID :|";
		return 11;
	}
	//len = fPat.tellg();
	//buffer = new char[len];
	fPat.close();
	fPat.open(filePat);
	for (int i = 0;i < (id - 1) * 9;i++) {
		getline(fPat, foo);
		foo = foo + '\n';
		f2Pat << foo;
	}
			//перед удалением статус должен быть = 0 или 2
	std::cout << "Enter 0 to delete patient, or 1 to make change : ";
	std::cin >> foo32;
									//пропускаем 9 строк и начинаем запись во второй файл до конца файла
	for (int i = 0;i < 8;i++) getline(fPat, foo); //возможна ошибка при данном способе пролистывания , если появится пустая строка
	getline(fPat, bar);//считывается пустая строка , хз откуда :D
	while (!fPat.eof()) {
		getline(fPat, bar);
		if (!bar.empty()) f2Pat << bar << '\n';
			
	}
	fPat.close();
	f2Pat.close();
	rename(filePat, "1.txt");
	rename("buf.txt", filePat);
	remove("1.txt");
	//изменить fileID если статус = 1
	if (status == 1) {
		std::fstream f3Pat("fileID.txt");
		try {
			if (!f3Pat.is_open()) throw "Error_OpenFile fileID";
			if (f3Pat.eof()) throw "Error_fileID_is_EMPTY";
		}
		catch (const char* er) { std::cout << er; f3Pat.close(); return 11; }
		f3Pat >> bar >> bar32; //меняем значение общ количества пациентов в больнице
		--bar32;
		//f3Pat.clear();
		f3Pat.close();
		f3Pat.open("fileID.txt");
		f3Pat << bar << ' ' << bar32;
		f3Pat.close();
	}
	return 0;
}