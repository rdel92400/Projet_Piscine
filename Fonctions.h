#ifndef PROJET_FONCTIONS_H
#define PROJET_FONCTIONS_H
#include "Bibliotheque.h"

#include "Sommet.h"


float calculTps(std::string type, Sommet* s1, Sommet* s2, std::vector<std::pair<std::string, std::pair<float, float>>> tabRemontees, std::vector<std::pair<std::string, float>> tabDescentes);

void menu();


#endif //PROJET_FONCTIONS_H