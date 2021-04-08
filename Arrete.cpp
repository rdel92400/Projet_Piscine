#include "Arrete.h"

Arrete::Arrete() {

}

Arrete::~Arrete() {

}

int Arrete::getNum() const {
    return m_num;
}

std::string Arrete::getType() const {
    return m_type;
}

std::string Arrete::getNom() const {
    return m_nom;
}

void Arrete::setNum(int num) {
    m_num = num;
}

void Arrete::setType(std::string type) {
    m_type = type;
}

void Arrete::setNom(std::string nom) {
    m_nom = nom;
}

void Arrete::setTps(float tps) {
    m_tps = tps;
}

float Arrete::getTps() const {
    return m_tps;
}

