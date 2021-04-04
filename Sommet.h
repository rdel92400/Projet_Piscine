#ifndef PROJET_SOMMET_H
#define PROJET_SOMMET_H
#include <iostream>
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>

#define poids std::pair<int, std::string>

class Sommet {
private:
    int m_num;
    std::string m_nom;
    int m_alt;
    std::vector<std::pair<Sommet*, poids> >m_successeurs;
public:
    Sommet(int num);
    ///Getteur
    int getNum()const;
    int getAlt()const;
    std::string getNom()const;
    std::vector<std::pair<Sommet*, poids> >getSuccesseurs();
    ///Accesseur
    void setNom(std::string nom);
    void setAlt(int alt);
    void ajouterSuccesseurs(Sommet* s, int tps, std::string type);
    ///Autres
    void afficher();
};


#endif //PROJET_SOMMET_H
