#include "Fonctions.h"
#include "Graphe.h"

void modifTemps(Graphe g);

void menu(Graphe g) {

    int depart, arrivee;
    int choix;
    //g.afficher();

    do {
        std::cout << " //////////////////// Bienvenue a la borne interactive des Arcs ! \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << std::endl;

        std::cout << "Que voulez-vous faire ?" << std::endl;

        std::cout << "0 - Quitter" << std::endl;
        std::cout << "1 - Connaitre d'ou part et arrive un trajet" << std::endl;
        std::cout << "2 - Connaitre les trajets/chemins complets arrivant et partant d'un sommet " << std::endl;
        std::cout << "3 - Connaitre les chemins les plus courts issus d'un sommet" << std::endl;
        std::cout << "4 - Connaitre le chemin le plus rapide entre deux sommets" << std::endl;
        std::cout << "5 - Modifier temps trajets" << std::endl;

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
                modifTemps(g);
                g.getTempsTrajets().affichageTemps();
                break;
        }
    } while (choix != 0);
}



float calculTps(std::string type, Sommet* s1, Sommet* s2, std::vector<std::pair<std::string, std::pair<int, int>>> tabRemontees, std::vector<std::pair<std::string, float>> tabDescentes)
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

void modifTemps(Graphe g) {
    std::string typeTrajet;
    float nouveauTemps;
    bool condition = false;
    int i = 1, j = 1;
    std::string typeModif;

    TempsTrajets temps;

    std::vector<std::pair<std::string, float>> tabTempsDescentes = g.getTempsTrajets().getTabDescente();
    std::vector<std::pair<std::string, std::pair<int, int>>> tabTempsRemontees = g.getTempsTrajets().getTabRemontees();

    do {
        std::cout << "Entrez le type de trajet que vous voulez modifier : ";
        std::cin >> typeTrajet;

        for (const auto s : g.getTempsTrajets().getTabDescente())
            if (s.first == typeTrajet)
                condition = true;

        for (const auto s :g.getTempsTrajets().getTabRemontees())
            if (s.first == typeTrajet)
                condition = true;

        if (!condition)
            std::cout << std::endl << "Ce trajet n'existe pas, veuillez en choisir un autre." << std::endl;

    } while (!condition);

    for (const auto s : g.getTempsTrajets().getTabDescente()) {
        if (s.first == typeTrajet) {
            std::cout << "Quelle nouvelle duree en minutes par 100 metres voulez-vous ?";
            std::cin >> nouveauTemps;

            tabTempsDescentes[i].second = nouveauTemps;
            temps.setTabDescentes(tabTempsDescentes);
            temps.setTabRemontees(g.getTempsTrajets().getTabRemontees());
            i++;
            g.setTempsTrajets(temps);
        }
    }

    for (const auto s : g.getTempsTrajets().getTabRemontees()) {
        if (s.first == typeTrajet) {
            std::cout
                    << "Voulez vous modifier la partie fixe ou la partie proportionnelle au denivele ('fixe' ou 'proportionnelle') : ";
            std::cin >> typeModif;

            if (typeModif == "fixe") {
                std::cout << "Quelle nouvelle duree de la partie fixe voulez vous ?";
                std::cin >> nouveauTemps;

                tabTempsRemontees[j].second.first = nouveauTemps;
                temps.setTabRemontees(tabTempsRemontees);
                temps.setTabDescentes(g.getTempsTrajets().getTabDescente());
                j++;
                g.setTempsTrajets(temps);
            }
            if (typeModif == "proportionnelle") {
                std::cout << "Quelle nouvelle duree en minutes par 100 metres voulez-vous ?";
                std::cin >> nouveauTemps;

                tabTempsRemontees[j].second.second = nouveauTemps;
                temps.setTabRemontees(tabTempsRemontees);
                temps.setTabDescentes(g.getTempsTrajets().getTabDescente());
                j++;
                g.setTempsTrajets(temps);
            }
        }
    }
    g.getTempsTrajets().affichageTemps();
}
