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
    ///Constructeur
    Graphe(std::string nomFichier);
    ~Graphe();
    Sommet* getSommet(int num);

    ///Autres
    void afficher();
    void rechercheCoord();
    void rechercheBFS();
    void BFS(std::string sommet, std::string arrivee, std::string type);
    void affichageBFS(int source, int destination, std::vector<int> parent);
    void dijkstra(Sommet* depart, Sommet* arrivee);
};


#endif //PROJET_GRAPHE_H
