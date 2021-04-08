#ifndef PROJET_GRAPHE_H
#define PROJET_GRAPHE_H

#include "Bibliotheque.h"
#include "Fonctions.h"
#include "Sommet.h"
#include "TempsTrajets.h"


class Graphe {

private:
    int m_ordre;
    int m_taille;
    std::vector<Sommet*> m_sommets;
    int getOrdre();
    TempsTrajets m_tempsTrajets;

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
    void dijkstra(Sommet* depart, Sommet* arrivee, std::string type);
    void rechercheCheminsDijkstra(std::string type);

    ///Setters
    void setTempsTrajets(TempsTrajets trajetTempo);

    ///Getters

    TempsTrajets getTempsTrajets();

};


#endif //PROJET_GRAPHE_H
