#include "Bibliotheque.h"

int main()
{
    //Graphe g{"chargement.txt"};
    //g.afficher();
    menu();
    return 0;
}

int calculTps(std::string type, Sommet* s1, Sommet* s2, std::vector<std::pair<std::string, std::pair<int, int>>> tabRemontees, std::vector<std::pair<std::string, int>> tabDescentes)
{
    int alt, tpsprop(0), tps(0), tpsTot;

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

    std::cout << tps << " + ( " << alt << " /100 ) * " << tpsprop << std::endl;
    tpsTot = tps + (alt/100)*tpsprop;

    return tpsTot;
}