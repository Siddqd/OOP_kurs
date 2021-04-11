#include "MedRoom.h"


MedRoom::MedRoom() {
	id = 0;
	sum = 0;
}

/*void setID(int idrr) {
	id = idrr;
}
void setNum(int numm) {
	sum = numm;
}

int getIDR() {
	return id;
}
int getNum() {
	return sum;
}*/

int MedRoom::lookFreeNum()//���������� � ������� ������ ����� ������ �� ��������� ������� ������ � ���������� ������� ���� � ���
{
	int idr=-1,numr=4, last=0;
	std::string bar;
	//������� ����� ��������� ���� �� ������ ��������� ����� � �������� ( ����� fileID
	int idpp = 0, sum_pat = 0;
	std::fstream fPat("fileID.txt", std::ios::in | std::ios::beg);
	try {
		//�������� �������� �����
		if (fPat.eof()) throw 0;
		fPat >> sum_pat;						//������� ������� ����� ���������� ���������
		if (sum_pat >= MaxPatient) throw "sorrY_Clinic_Overflow"; //���� ������ ����� ���� - ������� �����������
		fPat >> idpp;					// ������� ��������� ������� ID ��������

	}
	catch (const char* er) { std::cout << er;return -1; }
	catch (int e) {
		std::cerr << "fileID.txt ���� - ��������� ������ ";
	}	//��������� ���� ���� ���� ����
	
	std::fstream fRoom("fileRoom.txt");
	while (!fRoom.eof() && numr >= 4)
	{
		fRoom >> bar;
		if (bar == "IDR") {
			++last;
			fRoom >> idr >> numr;
			if (numr < 4) { //����� ������ �� ��������� ������
				setID(idr);
				setSum(numr);
				return 0;
			}
		}
	}
	fRoom.close();
	if (idr == -1) { //���� �� ����� ��������� ������, �� �������(��������������) ����� �������, ���� � ������(���� ���� ����), ���� � �����.
		fRoom.open("fileRoom.txt", std::ios::app);
		(last == 0) ? fRoom << "IDR " : fRoom << "\nIDR ";
		fRoom << ++last << ' ' << 0;
		setID(last);
		setSum(0);
		return 0;
	}
	
	return -1;
}

void MedRoom::showAllFreeNum() {
		int idr = -1, numr = 4, last = 0;
		std::string bar;
		//������� ����� ��������� ���� �� ������ ��������� ����� � �������� ( ����� fileID
		int idpp = 0, sum_pat = 0;
		std::fstream fPat("fileID.txt", std::ios::in | std::ios::beg);
		try {
			//�������� �������� �����
			if (fPat.eof()) throw 0;
			fPat >> sum_pat;						//������� ������� ����� ���������� ���������
			if (sum_pat >= MaxPatient) throw "sorrY_Clinic_Overflow"; //���� ������ ����� ���� - ������� �����������
			fPat >> idpp;					// ������� ��������� ������� ID ��������

		}
		catch (const char* er) { std::cout << er;return ; }
		catch (int e) {
			std::cerr << "fileID.txt ���� - ��������� ������ ";
		}	//��������� ���� ���� ���� ����
		std::cout << "\nfree MedRooms num : \n";
		std::fstream fRoom("fileRoom.txt");
		while (!fRoom.eof())
		{
			fRoom >> bar;
			if (bar == "IDR") {
				++last;
				fRoom >> idr >> numr;
				if (numr < 4) { //����� ������ �� ��������� ������
					std::cout<<idr<<"("<<numr<<")  ";
				}
				if (last % 5 == 0) std::cout << '\n';
			}
		}
		fRoom.close();
		if (idr == -1) { //���� �� ����� ��������� ������, �� �������(��������������) ����� �������, ���� � ������(���� ���� ����), ���� � �����.
			std::cerr << "Hospital hasnt free rooms !";
		}
}

void MedRoom::getRoomNum() {};//���������� ���������� ������� ���� � ������

MedRoom::~MedRoom() {

}
