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
    bool condition = false;
    std::string trajet;

    do {
        std::cout << std::endl << "Choisissez un trajet : ";
        std::cin >> trajet;

        for (const auto s : m_sommets)
            for (const auto& s2 : s->getSuccesseurs())
                if (s2.second->getNom() == trajet)
                    condition = true;

        if (!condition)
            std::cout << std::endl << "Ce trajet n'existe pas, veuillez en choisir un autre." << std::endl;

    } while (!condition);

    for (const auto s : m_sommets)
    {
        for (const auto& s2 : s->getSuccesseurs())
        {
           if (s2.second->getNom() == trajet)
           {
               std::cout << std::endl << "Ce trajet est de type " << s2.second->getType() << " et dure " << s2.second->getTps() << " min" << std::endl;
               std::cout << "Le trajet " << trajet << " part du sommet " << s->getNom() << " (Altitude : " << s->getAlt() << ", Num : " << s->getNum() << ") " << std::endl
                         << "Le trajet " << trajet << " arrive au sommet " << s2.first->getNom() << " (Altitude : " << s2.first->getAlt() << ", Num : " << s2.first->getNum() << ") " << std::endl;
               test = false;
           }
        }
    }
    if (test){
        std::cout << "Ce trajet n'existe pas" << std::endl;
    }
}

void Graphe::rechercheBFS()
{
    bool condition = false;
    std::string sommet;

    do {
        std::cout << std::endl << "Choisissez un sommet : ";
        std::cin >> sommet;

        for (const auto s : m_sommets)
                if (s->getNom() == sommet)
                    condition = true;

        if (!condition)
            std::cout << std::endl << "Ce sommet n'existe pas, veuillez en choisir un autre." << std::endl;

    } while (!condition);

    //Recherche des arretes qui partent du sommet
    std::cout << std::endl << "Trajets qui partent du sommet " << sommet << " : " << std::endl;
    for (const auto s : m_sommets)
    {
        if (s->getNom() == sommet)
        {
            for (const auto& s2 : s->getSuccesseurs())
            {
                if (s->getAlt() > s2.first->getAlt())
                    std::cout << "Descente : " << s2.second->getNom() << " (type : " << s2.second->getType() << ", temps : " << s2.second->getTps() << ", num : " << s2.second->getNum() << ")\n";
                if (s->getAlt() < s2.first->getAlt())
                    std::cout << "Remontee : " << s2.second->getNom() << " (type : " << s2.second->getType() << ", temps : " << s2.second->getTps() << ", num : " << s2.second->getNum() << ")\n";
            }
        }
    }

    //Recherche des arretes qui arrivent au sommet
    std::cout << std::endl << "Trajets qui arrivent au sommet " << sommet << " : " << std::endl;
    for (const auto s : m_sommets)
    {
        for (const auto& s2 : s->getSuccesseurs())
        {
            if (s2.first->getNom() == sommet)
            {
                if (s->getAlt() > s2.first->getAlt())
                    std::cout << "Descente : " << s2.second->getNom() << " (type : " << s2.second->getType() << ", temps : " << s2.second->getTps() << ", num : " << s2.second->getNum() << ")\n";
                if (s->getAlt() < s2.first->getAlt())
                    std::cout << "Remontee : " << s2.second->getNom() << " (type : " << s2.second->getType() << ", temps : " << s2.second->getTps() << ", num : " << s2.second->getNum() << ")\n";
            }
        }
    }

    //Algo BFS pour les chemins partant du sommet vers tous les autres
    std::cout << std::endl << "Chemins partant du sommet " << sommet << " vers tous les autres :" << std::endl;
    BFS(sommet,sommet, "vers les autres sommets");

    //Algo BFS pour les chemins arrivant au sommet depuis tous les autres
    std::cout << std::endl << "Chemins arrivant au sommet " << sommet << " depuis tous les autres :" << std::endl;
    for (const auto s :m_sommets)
        BFS(s->getNom(),sommet,"depuis les autres sommets");

}

void Graphe::BFS(std::string sommet, std::string arrivee, std::string type)
{
    int src, dest, srcTemp;
    for (const auto s :m_sommets)
    {
        if (s->getNom() == sommet)
            src = s->getNum();
        if (s->getNom() == arrivee)
            dest = s->getNum();
    }
    srcTemp = src;

    std::vector<int> parent(m_ordre+1);
    bool *visited = new bool[m_ordre];
    std::list<int> queue;

    for (int i = 0; i < m_ordre; i++)
    {
        visited[i] = false;
        parent[i] = -1;
    }
    visited[srcTemp] = true;
    queue.push_back(srcTemp);

    while (!queue.empty())
    {
        srcTemp = queue.front();
        queue.pop_front();

        for (auto elem : m_sommets[srcTemp-1]->getSuccesseurs())
        {
            if (!visited[elem.first->getNum()])
            {
                visited[elem.first->getNum()] = true;
                parent[elem.first->getNum()] = srcTemp;
                queue.push_back(elem.first->getNum());
            }
        }
    }

    //Affichage BFS pour les deux cas de figure
    if (type == "vers les autres sommets")
    {
        for (int i = 1; i <= m_ordre; i++)
        {
            std::cout << "De " << sommet << " vers " << m_sommets[i-1]->getNom() << " : ";
            affichageBFS(src, i, parent);
            std::cout << std::endl;
        }
    }
    else if (type == "depuis les autres sommets")
    {
        std::cout << "De " << sommet << " vers " << arrivee << " : ";
        affichageBFS(src, dest, parent);
        std::cout << std::endl;
    }
}

void Graphe::affichageBFS(int source, int destination, std::vector<int> parent)
{
    if (source == destination)
        std::cout << source;

    else if (parent[destination] == -1)
        std::cout << "Il n'y a pas de chemin de " << source << " vers " << destination;

    else
    {
        affichageBFS(source, parent[destination],parent);
        std::cout << " -> " << destination;
    }
}

void Graphe::rechercheCheminsDijkstra(std::string type)
{
    Sommet *sDepart, *sArrivee;
    std::string depart, arrivee;
    bool condition = false;

    if (type == "Tous les plus court chemins")
    {
        do {
            std::cout << std::endl << "Choisissez un sommet : ";
            std::cin >> depart;

            for (const auto s : m_sommets)
                if (s->getNom() == depart)
                    condition = true;

            if (!condition)
                std::cout << std::endl << "Ce sommet n'existe pas, veuillez en choisir un autre." << std::endl;

        } while (!condition);
    }
    if (type == "Le chemin le plus court")
    {
        do {
            std::cout << std::endl << "Choisissez le sommet de depart : ";
            std::cin >> depart;

            for (const auto s : m_sommets)
                if (s->getNom() == depart)
                    condition = true;

            if (!condition)
                std::cout << std::endl << "Ce sommet n'existe pas, veuillez en choisir un autre." << std::endl;

        } while (!condition);

        condition = false;

        do {
            std::cout << std::endl << "Choisissez le sommet d'arrivee : ";
            std::cin >> arrivee;

            for (const auto s : m_sommets)
                if (s->getNom() == arrivee)
                    condition = true;

            if (!condition)
                std::cout << std::endl << "Ce sommet n'existe pas, veuillez en choisir un autre." << std::endl;

        } while (!condition);
    }

    for (const auto elem : m_sommets)
    {
        if (elem->getNom() == depart)
            sDepart = elem;
        if (elem->getNom() == arrivee)
            sArrivee = elem;
    }

    if (type == "Tous les plus court chemins")
        dijkstra(sDepart,sDepart,"Tous les plus court chemins");
    if (type == "Le chemin le plus court")
        dijkstra(sDepart,sArrivee,"Le chemin le plus court");
}

void Graphe::dijkstra(Sommet* depart, Sommet* arrivee, std::string type)
{
    int bl = 0;
    int tpm;
    std::priority_queue<std::pair<int, int>> file; //numSommet, distance
    std::vector<int> distance (m_ordre+1, 1000);
    std::vector<int> parent (m_ordre+1, -1);
    std::vector<std::pair <int, int>> parent2;

    for (int i = 0; i < m_ordre+1; i++)
        distance.push_back(1000);

    file.push(std::make_pair(depart->getNum(),0));
    distance[depart->getNum()] = 0;

    while (!file.empty())
    {
        int currentSommetV = file.top().first;
        int currentNum = file.top().second;
        file.pop();

        if (currentNum  <= distance[currentSommetV]){
            for (auto succ : m_sommets[currentSommetV-1]->getSuccesseurs())
            {
                int numSuccV2 = succ.first->getNum();
                int poidsSuccW2 = succ.second->getTps();

                if (distance[numSuccV2] > distance[currentSommetV] + poidsSuccW2)
                {
                    distance[numSuccV2] = distance[currentSommetV] + poidsSuccW2;
                    parent[numSuccV2] = currentSommetV;
                    file.push(std::make_pair(numSuccV2, distance[numSuccV2]));
                }
            }
        }
    }

    //Affichage Dijkstra
    if (type == "Tous les plus court chemins")
    {
        std::cout << std::endl << "Voici tous les chemins les plus courts issu du sommet " << depart->getNom() << " :" << std::endl;
        for (int k = 1; k <= m_ordre; k++)
        {
            std::cout << "De " << depart->getNom() << " a " << k << " (Temps : " << distance[k] << " min) : ";
            std::cout << k;
            for (auto p = parent[k]; p!= -1; p = parent[p])
                std::cout << " <- " << p;
            std::cout << std::endl;
        }
    }
    if (type == "Le chemin le plus court")
    {
        std::cout << "\nTemps du chemin le plus rapide de " << depart->getNom() << " a " << arrivee->getNom() << " : " << distance[arrivee->getNum()] << " min" << std::endl;
        std::cout << "Chemin : " << arrivee->getNum();

        for (auto p = parent[arrivee->getNum()]; p!= -1; p = parent[p])
        {
            if (bl != 0)
            {
                //parent2.push_back(std::make_pair(tpm, p));
            }
            std::cout << " <- " << p;
            //tpm = p;
            //bl++;
        }
        /*
        std::cout << "\nChemin 2: " << arrivee->getNom();
        for (auto elem : parent2)
        {
            std::cout << " <- " <<m_sommets[elem.first]->getSuccesseurs()[elem.second].second->getNom();
        }
         */

        std::cout << std::endl;
    }
}

int Graphe::getOrdre() {
    return m_ordre;
}

void Graphe::modifTemps(std::string nomFichier, std::string typeTransport, int newTemps) {
    std::ofstream ifs(nomFichier.c_str(), std::ios::app);
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir le fichier " + nomFichier );
    ifs << m_ordre;
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture ordre du graphe");

    //Chargement sommets
    int num1, num3;
    std::string num2;
    for (int i = 0; i < m_ordre; i++)
    {
        m_sommets.push_back(new Sommet{ i+1});
        ifs << num1 << num2 << num3;
        if (ifs.fail())
            throw std::runtime_error("Probleme chargement donnees sommets");
        m_sommets[i]->setNom(num2);
        m_sommets[i]->setAlt(num3);
    }

    //Chargement des types et des temps des arretes
    std::string var1, var2;
    float temp1, temp2, n1, n2, n3;
    ifs << temp1;
    std::vector<std::pair<std::string, std::pair<int, int>>> tabRemontees (temp1);
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture nb de remontees");
    for (int i = 0; i < temp1; i++)
    {
        ifs << var1 << n1 << n2;
        if (ifs.fail())
            throw std::runtime_error("Probleme chargement remontees");
        tabRemontees[i].first = var1;
        tabRemontees[i].second.first = n1;
        tabRemontees[i].second.second = n2;
    }
    ifs << temp2;
    std::vector<std::pair<std::string, int>> tabDescentes (temp2);
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture nb de descentes");
    for (int i = 0; i < temp2; i++)
    {
        ifs << var2 << n3;
        if (ifs.fail())
            throw std::runtime_error("Probleme chargement descentes");
        tabDescentes[i].first = var2;
        tabDescentes[i].second = n3;
    }

    ifs << m_taille;
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture taille du graphe");

    //Chargement arretes
    int numArrete, s1, s2;
    std::string nom1, nom2;
    for (int i = 0; i < m_taille; i++)
    {
        ifs << numArrete << nom1 << nom2 << s1 << s2;
        if (ifs.fail())
            throw std::runtime_error("Probleme chargement donnees arretes");
        m_sommets[s1-1]->ajouterSuccesseurs(m_sommets[s2-1],calculTps(nom2,m_sommets[s1-1],m_sommets[s2-1],tabRemontees,tabDescentes),nom2,numArrete,nom1);
    }
}
