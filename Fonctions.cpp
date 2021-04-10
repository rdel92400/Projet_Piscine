#include "Fonctions.h"
#include "Graphe.h"

void menu() {

    int depart, arrivee;
    int choix;
    Graphe g{"chargement.txt"};

    do {
        do {
            ///system("cls"); A décommenter si on passe en console
            std::cout << "\n//////////////////// Bienvenue a la borne interactive des Arcs ! \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n" << std::endl;

            std::cout << "Que voulez-vous faire " << g.getNom() << " ?" <<std::endl;
            std::cout << "1 - Connaitre d'ou part et arrive un trajet" << std::endl;
            std::cout << "2 - Connaitre les trajets/chemins complets arrivant et partant d'un sommet " << std::endl;
            std::cout << "3 - Connaitre les chemins les plus courts issus d'un sommet" << std::endl;
            std::cout << "4 - Connaitre le chemin le plus rapide entre deux sommets" << std::endl;
            std::cout << "5 - OPTIMISATION : Connaitre le chemin le plus rapide entre deux sommets avec les preferences" << std::endl;
            std::cout << "6 - EXTENSION : Connaitre le chemin optimiser pour arriver à la pose déjeuner" << std::endl;
            std::cout << "7 - Modifier les temps des trajets" << std::endl;
            std::cout << "8 - Modifier les preferences des trajets" << std::endl;
            std::cout << "9 - Creer un nouveau profil" << std::endl;
            std::cout << "10 - Afficher le graphe" << std::endl;
            std::cout << "0 - Quitter" << std::endl;

            std::cout << "\nChoix : ";
            std::cin >> choix;
        } while (choix>10 || choix<0);


        switch (choix) {
            case 1 :
                g.rechercheCoord();

                std::cout << std::endl;
                std::cout << "0 - Arreter" << std::endl;
                std::cout << "1 - Retour" << std::endl;
                std::cin >> choix;
                break;

            case 2 :
                g.rechercheBFS();

                std::cout << std::endl;
                std::cout << "0 - Arreter" << std::endl;
                std::cout << "1 - Retour" << std::endl;
                std::cin >> choix;
                break;

            case 3 :
                g.rechercheCheminsDijkstra("Tous les plus court chemins");

                std::cout << std::endl;
                std::cout << "0 - Arreter" << std::endl;
                std::cout << "1 - Retour" << std::endl;
                std::cin >> choix;
                break;

            case 4 :
                g.rechercheCheminsDijkstra("Le chemin le plus court");

                std::cout << std::endl;
                std::cout << "0 - Arreter" << std::endl;
                std::cout << "1 - Retour" << std::endl;
                std::cin >> choix;
                break;

            case 5 :
                g.rechercheCheminsDijkstra("Le chemin le plus court avec preferences");

                std::cout << std::endl;
                std::cout << "0 - Arreter" << std::endl;
                std::cout << "1 - Retour" << std::endl;
                std::cin >> choix;
                break;

            case 6 :

                g.extension();
                std::cout << std::endl;
                std::cout << "0 - Arreter" << std::endl;
                std::cout << "1 - Retour" << std::endl;
                std::cin >> choix;
                break;

            case 7 :
                g.modifTemps();

                std::cout << std::endl;
                std::cout << "0 - Arreter" << std::endl;
                std::cout << "1 - Retour" << std::endl;
                std::cin >> choix;
                break;

            case 8 :
                g.modifPrefs();

                std::cout << std::endl;
                std::cout << "0 - Arreter" << std::endl;
                std::cout << "1 - Retour" << std::endl;
                std::cin >> choix;
                break;

            case 9 :
                g.ajoutProfil();
                std::cout << std::endl;
                std::cout << "0 - Pour se reconnecter" << std::endl;
                std::cin >> choix;
                break;

            case 10 :
                g.afficher();
                g.afficherInfosTrajets();

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