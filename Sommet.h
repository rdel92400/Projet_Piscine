#ifndef PROJET_SOMMET_H
#define PROJET_SOMMET_H

//Ici il faudrait mettre #include "Bibliotheque.h" a la place de tous les define mais jsp pourquoi ca marche pas

#include "Bibliotheque.h"
#include "Arrete.h"

class Sommet {

private:
    int m_num;
    std::string m_nom;
    int m_alt;
    std::vector<std::pair<Sommet*, Arrete*>> m_successeurs;
    Sommet* m_predecesseur;
    int m_bool;

public:
    Sommet(int num, int b);

    ///Getteur
    int getNum()const;
    int getAlt()const;
    std::string getNom()const;
    std::vector<std::pair<Sommet*, Arrete*>> getSuccesseurs();
    Sommet* getPred()const { return m_predecesseur; }
    int getBool()const { return m_bool; }

    ///Accesseur
    void setNom(std::string nom);
    void setAlt(int alt);
    void ajouterSuccesseurs(Sommet* s, int tps, std::string type, int num, std::string nom);
    ///Autres

    ///Fonction pour dijkstra
    int getDistSucc(Sommet* sommet);
    void reset();
    void setPassage(Sommet* pred);
    void setPred(Sommet* pred);
};


#endif //PROJET_SOMMET_H
