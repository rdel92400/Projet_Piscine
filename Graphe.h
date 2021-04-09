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
    int getOrdre();
    std::string m_nom;
    std::string m_mdp;
    std::vector<std::string> m_pref;
    std::vector<std::pair<std::string, std::pair<float, float>>> m_tabRemontees;
    std::vector<std::pair<std::string, float>> m_tabDescentes;

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
    void dijkstraPref(Sommet* depart, Sommet* arrivee);
    void modifTemps();
    void modifPrefs();
    void rechercheCheminsDijkstra(std::string type);
    void afficherInfosTrajets();
};


#endif //PROJET_GRAPHE_H
