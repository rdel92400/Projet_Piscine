#ifndef PROJET_GRAPHE_H
#define PROJET_GRAPHE_H

#include "Bibliotheque.h"
#include "Fonctions.h"
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
    void rechercheCoord();
    void rechercheBFS();
    void affichageBFS(int source, int destination, std::vector<int> parent);
};


#endif //PROJET_GRAPHE_H
