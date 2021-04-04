#ifndef PROJET_GRAPHE_H
#define PROJET_GRAPHE_H

#include "Bibliotheque.h"
#include "Sommet.h"

class Graphe {

private:
    int m_ordre;
    int m_taille;
    std::vector<Sommet*> m_sommets;

public:
    Graphe(std::string nomFichier);
    ~Graphe();

    Sommet* getSommet(int num);
    void afficher();
};


#endif //PROJET_GRAPHE_H
