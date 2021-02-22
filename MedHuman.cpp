#include "MedHuman.h"

std::string MedHuman::getFio() {
    return fio;
}
void MedHuman::setFio(std::string fio2) {
    fio=fio2;
}

Data MedHuman::getBday() {
  return  bday;
}

void MedHuman::setBday(Data bdayy) {
  bday=bdayy;
}

int64_t MedHuman::getTel() {
  return tel;
}
void MedHuman::setTel(int64_t tell) {
  tel=tell;
}

int64_t MedHuman::getRes_tel() {
  return res_tel;
}
void MedHuman::setRes_tel(int64_t res_tell) {
  res_tel=res_tell;
}

int64_t MedHuman::getPolis() {
  return polis;
}
void MedHuman::setPolis(int64_t poliss) {
  polis=poliss;
}
