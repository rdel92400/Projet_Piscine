#include "Graphe.h"

Graphe::Graphe(std::string nomFichier)
{
    std::ifstream ifs{ nomFichier };
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir le fichier " + nomFichier );
    ifs >> m_ordre;
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture ordre du graphe");

    //Chargement sommets
    int num1, num3;
    std::string num2;
    for (int i = 0; i < m_ordre; i++)
    {
        m_sommets.push_back(new Sommet{ i+1 });
        ifs >> num1 >> num2 >> num3;
        if (ifs.fail())
            throw std::runtime_error("Probleme chargement donnees sommets");
        m_sommets[i]->setNom(num2);
        m_sommets[i]->setAlt(num3);
    }

    //Chargement des types et des temps des arretes
    std::string var1, var2;
    float temp1, temp2, n1, n2, n3;
    ifs >> temp1;
    std::vector<std::pair<std::string, std::pair<int, int>>> tabRemontees (temp1);
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture nb de remontees");
    for (int i = 0; i < temp1; i++)
    {
        ifs >> var1 >> n1 >> n2;
        if (ifs.fail())
            throw std::runtime_error("Probleme chargement remontees");
        tabRemontees[i].first = var1;
        tabRemontees[i].second.first = n1;
        tabRemontees[i].second.second = n2;
    }
    ifs >> temp2;
    std::vector<std::pair<std::string, int>> tabDescentes (temp2);
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture nb de descentes");
    for (int i = 0; i < temp2; i++)
    {
        ifs >> var2 >> n3;
        if (ifs.fail())
            throw std::runtime_error("Probleme chargement descentes");
        tabDescentes[i].first = var2;
        tabDescentes[i].second = n3;
    }

    ifs >> m_taille;
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture taille du graphe");

    //Chargement arretes
    int numArrete, s1, s2;
    std::string nom1, nom2;
    for (int i = 0; i < m_taille; i++)
    {
        ifs >> numArrete >> nom1 >> nom2 >> s1 >> s2;
        std::cout << numArrete << std::endl;
        if (ifs.fail())
            throw std::runtime_error("Probleme chargement donnees arretes");
        m_sommets[s1-1]->ajouterSuccesseurs(m_sommets[s2-1],calculTps(nom2,m_sommets[s1-1],m_sommets[s2-1],tabRemontees,tabDescentes),nom2,numArrete,nom1);
    }
}

Graphe::~Graphe() {}


Sommet* Graphe::getSommet(int num)
{
    for (auto elem : m_sommets)
    {
        if (elem->getNum() == num)
            return elem;
    }
    std::cout << "Ce sommet n'existe pas !\n";
    return nullptr;
}

void Graphe::afficher()
{
    std::cout << "Affichage sommets :\n" << std::endl;
    for (const auto s : m_sommets)
    {
        std::cout << "Sommet " << s->getNum() << " : " << s->getNom() << " altitude : " << s->getAlt() << std::endl;
    }

    int i(1);
    std::cout << std::endl << "Affichage arretes :\n" << std::endl;
    for (const auto s : m_sommets)
    {
        for (const auto& s2 : s->getSuccesseurs())
        {
            std::cout << "Num : " << s2.second->getNum() << std::endl;
            std::cout   << s->getNum() << " -- " << s2.first->getNum() << " : " << std::endl
                        << "Temps : " << s2.second->getTps() << std::endl
                        << "Type : " << s2.second->getType() << std::endl
                        << "Nom : " << s2.second->getNom() << std::endl << std::endl;

        }
        std::cout << std::endl;
    }
}

void Graphe::rechercheCoord() {
    bool test = true;
    std::string trajet;
    std::cout << "Choisissez un trajet pour trouver ses coordonnees d'arrivee et de depart : ";
    std::cin >> trajet;
    for (const auto s : m_sommets)
    {
        for (const auto& s2 : s->getSuccesseurs())
        {
           if (s2.second->getNom() == trajet){
               std::cout << "Le trajet "<< trajet <<" part du sommet " << s->getNum() <<" : "<< s->getNom()
                         << " et arrive au sommet " << s2.first->getNum() << " : " << s2.first->getNom() << std::endl;
               test = false;
           }
        }
    }
    if (test == true){
        std::cout << "Ce trajet n'existe pas" << std::endl;
    }
}

