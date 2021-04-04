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

std::vector<std::pair<Sommet*, poids> > Sommet::getSuccesseurs() {
    return m_successeurs;
}

void Sommet::setNom(std::string nom) {
    m_nom = nom;
}

void Sommet::setAlt(int alt) {
    m_alt = alt;
}

void Sommet::ajouterSuccesseurs(Sommet *s, int tps, std::string type) {
    m_successeurs.push_back(std::make_pair(s, poids(tps, type)));
}

void Sommet::afficher() {

}


