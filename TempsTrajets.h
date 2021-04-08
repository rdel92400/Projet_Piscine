//
// Created by Romain on 08/04/2021.
//

#ifndef PROJET_TEMPSTRAJETS_H
#define PROJET_TEMPSTRAJETS_H

#include "Bibliotheque.h"

class TempsTrajets {
private :
    std::vector <std::pair<std::string, std::pair<int, int>>> m_tabRemontees;
    std::vector<std::pair<std::string, float>> m_tabDescentes;

public :

    ///Setters
    void setTabDescentes(std::vector<std::pair<std::string, float>> tabTempo);
    void setTabRemontees(std::vector <std::pair<std::string, std::pair<int, int>>> tabTempo);

    ///Getters

    std::vector <std::pair<std::string, std::pair<int, int>>> getTabRemontees();
    std::vector<std::pair<std::string, float>> getTabDescente();

    ///Affichage
    void affichageTemps();

    ///Fonctions


};


#endif //PROJET_TEMPSTRAJETS_H
