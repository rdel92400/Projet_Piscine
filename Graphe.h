#ifndef PROJET_GRAPHE_H
#define PROJET_GRAPHE_H
#include "Bibliotheque.h"
#include "Sommet.h"
#include <iostream>
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>

class Graphe {
private:
    int m_ordre;
    int m_taille;
    std::vector<Sommet*> m_sommets;
public:
    Graphe(std::string nomFichier);
    ~Graphe();
    void afficher();
};


#endif //PROJET_GRAPHE_H
