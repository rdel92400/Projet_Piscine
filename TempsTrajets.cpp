//
// Created by Romain on 08/04/2021.
//

#include "TempsTrajets.h"

void TempsTrajets::setTabDescentes(std::vector<std::pair<std::string, float>> tabTempo) {
    m_tabDescentes = tabTempo;
}

void TempsTrajets::setTabRemontees(std::vector<std::pair<std::string, std::pair<int, int>>> tabTempo) {
    m_tabRemontees = tabTempo;
}

void TempsTrajets::affichageTemps() {
    std::cout << "Temps remontee : " << std::endl;

    for (auto it:m_tabRemontees) {
        std::cout << "Type : " << it.first << "Temps : " << it.second.first << "temps 2 : " << it.second.second
                  << std::endl;
    }

    std::cout << "Temps descente :  : " << std::endl;

    for (auto it:m_tabDescentes) {
        std::cout << "Type : " << it.first << "Temps : " << it.second << std::endl;
    }

}

std::vector<std::pair<std::string, std::pair<int, int>>> TempsTrajets::getTabRemontees() {
    return m_tabRemontees;
}

std::vector<std::pair<std::string, float>> TempsTrajets::getTabDescente() {
    return m_tabDescentes;
}

