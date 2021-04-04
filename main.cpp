#include "Sommet.h"
#include "Graphe.h"
#include <iostream>
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>


int main() {
    Graphe g{ "chargement.txt" };
    g.afficher();
    return 0;
}
