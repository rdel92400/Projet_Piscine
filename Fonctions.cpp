#include "Fonctions.h"
#include "Graphe.h"

void menu() {

    int depart, arrivee;
    int choix;
    Graphe g{"chargement.txt"};
    //g.afficher();

    do {
        std::cout << " //////////////////// Bienvenue a la borne interactive des Arcs ! \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << std::endl;

        std::cout << "Que voulez-vous faire ?" << std::endl;

        std::cout << "0 - Quitter" << std::endl;
        std::cout << "1 - Connaitre d'ou part et arrive un trajet" << std::endl;
        std::cout << "2 - Connaitre les trajets/chemins complets arrivant et partant d'un sommet " << std::endl;
        std::cout << "3 - Connaitre les chemins les plus courts issus d'un sommet" << std::endl;
        std::cout << "4 - Connaitre le chemin le plus rapide entre deux sommets" << std::endl;
        std::cout << "5 - OPTIMISATION : Connaitre le chemin le plus rapide entre deux sommets avec les preferences" << std::endl;
        std::cout << "6 - Modifier les temps des trajets" << std::endl;
        std::cout << "7 - Modifier les preferences des trajets" << std::endl;

        std::cout << "\nChoix : ";
        std::cin >> choix;

        switch (choix) {
            case 1 :
                //system("cls");
                g.rechercheCoord();

                std::cout << std::endl;
                std::cout << "0 - Arreter" << std::endl;
                std::cout << "1 - Retour" << std::endl;
                std::cin >> choix;
                break;

            case 2 :
                //system("cls");
                g.rechercheBFS();

                std::cout << std::endl;
                std::cout << "0 - Arreter" << std::endl;
                std::cout << "1 - Retour" << std::endl;
                std::cin >> choix;
                break;

            case 3 :
                //system("cls");
                g.rechercheCheminsDijkstra("Tous les plus court chemins");

                std::cout << std::endl;
                std::cout << "0 - Arreter" << std::endl;
                std::cout << "1 - Retour" << std::endl;
                std::cin >> choix;
                break;

            case 4 :
                //system("cls");
                g.rechercheCheminsDijkstra("Le chemin le plus court");

                std::cout << std::endl;
                std::cout << "0 - Arreter" << std::endl;
                std::cout << "1 - Retour" << std::endl;
                std::cin >> choix;
                break;

            case 5 :
                //system("cls");
                g.rechercheCheminsDijkstra("Le chemin le plus court avec preferences");

                std::cout << std::endl;
                std::cout << "0 - Arreter" << std::endl;
                std::cout << "1 - Retour" << std::endl;
                std::cin >> choix;
                break;

            case 6 :
                //system("cls");
                g.modifTemps();

                std::cout << std::endl;
                std::cout << "0 - Arreter" << std::endl;
                std::cout << "1 - Retour" << std::endl;
                std::cin >> choix;
                break;

            case 7 :
                //system("cls");
                g.modifPrefs();

                std::cout << std::endl;
                std::cout << "0 - Arreter" << std::endl;
                std::cout << "1 - Retour" << std::endl;
                std::cin >> choix;
                break;
        }
    } while (choix != 0);


}



float calculTps(std::string type, Sommet* s1, Sommet* s2, std::vector<std::pair<std::string, std::pair<float, float>>> tabRemontees, std::vector<std::pair<std::string, float>> tabDescentes)
{
    float alt, tpsprop(0), tps(0), tpsTot;

    alt = s2->getAlt() - s1->getAlt();

    for (const auto& elem : tabRemontees)
    {
        if (type == elem.first)
        {
            if (type == "BUS" && (s1->getNum() == 36 || s2->getNum() == 36))
            {
                for (auto index : tabRemontees)
                    if (index.second.second == 1800)
                        tps = index.second.first;
            }
            if (type == "BUS" && (s1->getNum() == 7 || s2->getNum() == 7))
            {
                for (auto index : tabRemontees)
                    if (index.second.second == 2000)
                        tps = index.second.first;
            }
            else if (type != "BUS")
            {
                tps = elem.second.first;
                tpsprop = elem.second.second;
            }
        }
    }

    for (const auto& elem : tabDescentes)
        if (type == elem.first)
            tpsprop = elem.second;

    if (alt < 0)
        alt = -alt;

    tpsTot = tps + (alt*tpsprop)/100;

    return tpsTot;
}