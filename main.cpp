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
    Graphe g{ "chargementss.txt" };
    g.afficher();
    return 0;
}
