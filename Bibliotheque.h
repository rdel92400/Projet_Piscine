#ifndef PROJET_BIBLIOTHEQUE_H
#define PROJET_BIBLIOTHEQUE_H

#include <iostream>
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>
#include <windows.h>

#include "Graphe.h"
#include "Sommet.h"
#include "Arrete.h"

int calculTps(std::string type, Sommet* s1, Sommet* s2, std::vector<std::pair<std::string, std::pair<int, int>>> tabRemontees, std::vector<std::pair<std::string, int>> tabDescentes);

void menu();
#endif //PROJET_BIBLIOTHEQUE_H
