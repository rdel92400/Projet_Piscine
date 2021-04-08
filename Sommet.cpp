#include "Sommet.h"

Sommet::Sommet(int num) {
    m_num = num;
}

int Sommet::getNum() const {
    return m_num;
}

std::string Sommet::getNom() const {
    return m_nom;
}

int Sommet::getAlt() const {
    return m_alt;
}

std::vector<std::pair<Sommet*, Arrete*> > Sommet::getSuccesseurs() {
    return m_successeurs;
}

void Sommet::setNom(std::string nom) {
    m_nom = nom;
}

void Sommet::setAlt(int alt) {
    m_alt = alt;
}

void Sommet::ajouterSuccesseurs(Sommet *s, float tps, std::string type, int num, std::string nom) {
    Arrete* tpm = new Arrete;
    tpm->setNum(num);
    tpm->setNom(nom);
    tpm->setTps(tps);
    tpm->setType(type);
    m_successeurs.push_back(std::make_pair(s, tpm));
}
