#pragma once
#include "Med.h"
//const char* fileCard = "fileCard.txt"; 
//файл историй (основной) : IDpat, status(0-dead,1-на лечении,2-выписан),IDcham(номер палаты) , IDdoc, data priema, data vipiski, string History в текстовом виде

class MedRec : public virtual Med
{

private:
	
	int id;
	Data data_in;
	Data data_out;
	int status;
	std::string recs;

};
