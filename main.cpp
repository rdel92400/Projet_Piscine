#include "Bibliotheque.h"
#include "Fonctions.h"
#include "Graphe.h"

void menu(Graphe g);


int main()
{
    Graphe g{"chargement.txt"};
    menu(g);
    return 0;
}

