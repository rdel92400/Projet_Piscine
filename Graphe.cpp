#include "Graphe.h"

Graphe::Graphe(std::string nomFichier)
{
    std::string fichierPerso;
    bool condition = false;
    bool conditionMdp = false;

    std::cout << "\n///Bienvenue sur la borne interactive des Arcs !\\\\\\" << std::endl << std::endl;
    std::cout << "Connectez-vous, saisissez vos identifiants : " << std::endl << std::endl;

    ///Saisie du login
    do {
        std::cout << "Login : ";
        std::cin >> fichierPerso;
        fichierPerso += ".txt";
        m_nom = fichierPerso;

        std::ifstream ifsTemp{ fichierPerso };
        if (!ifsTemp)
            std::cout << "L'utilisateur " << fichierPerso << " n'existe pas." << std::endl;
        else
            condition = true;

    } while (!condition);

    ///Ouverture fichier perso
    std::ifstream ifs2{ fichierPerso };
    std::string mdpBon, mdp;

    ///Verification MDP
    do {
        ifs2.seekg(0, std::ios::beg);
        ifs2 >> mdpBon;
        m_mdp = mdpBon;

        std::cout << "Mot de passe : ";
        std::cin >> mdp;
        if (mdp != mdpBon)
            std::cout << "le mot de passe " << mdp << " n'est pas bon." << std::endl;
        else
            conditionMdp = true;

    } while (!conditionMdp);

    ///Chargement des types et des temps des arretes
    std::string var1, var2;
    float temp1, temp2, n1, n2, n3;
    ifs2 >> temp1;
    if (ifs2.fail())
        throw std::runtime_error("Probleme lecture nb de remontees");
    for (int i = 0; i < temp1; i++)
        m_tabRemontees.push_back(std::make_pair("",std::make_pair(0,0)));
    for (int i = 0; i < temp1; i++)
    {
        ifs2 >> var1 >> n1 >> n2;
        if (ifs2.fail())
            throw std::runtime_error("Probleme chargement remontees");
        m_tabRemontees[i].first = var1;
        m_tabRemontees[i].second.first = n1;
        m_tabRemontees[i].second.second = n2;
    }
    ifs2 >> temp2;
    if (ifs2.fail())
        throw std::runtime_error("Probleme lecture nb de descentes");
    for (int i = 0; i < temp2; i++)
        m_tabDescentes.push_back(std::make_pair("",0));
    for (int i = 0; i < temp2; i++)
    {
        ifs2 >> var2 >> n3;
        if (ifs2.fail())
            throw std::runtime_error("Probleme chargement descentes");
        m_tabDescentes[i].first = var2;
        m_tabDescentes[i].second = n3;
    }

    ///Chargement preferences skieur
    std::string p1,p2,p3;
    ifs2 >> p1 >> p2 >> p3;
    if (ifs2.fail())
        throw std::runtime_error("Probleme lecture preferences");
    m_pref.push_back(p1);
    m_pref.push_back(p2);
    m_pref.push_back(p3);

    ifs2.close();

    ///Chargement sommets et arretes
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
        m_sommets[s1-1]->ajouterSuccesseurs(m_sommets[s2-1],calculTps(nom2,m_sommets[s1-1],m_sommets[s2-1],m_tabRemontees,m_tabDescentes),nom2,numArrete,nom1);
    }

    //afficherInfosTrajets();
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

    for (int i=0; i<m_sommets.size(); i++){
        std::cout << "Sommet: " << m_sommets[i]->getNum() << " \t Nom : " << m_sommets[i]->getNom() << " \t Altitude : " << m_sommets[i]->getAlt() << std::endl;
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
    if (type == "Le chemin le plus court" || type == "Le chemin le plus court avec preferences")
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
    if (type == "Le chemin le plus court avec preferences")
        dijkstraPref(sDepart,sArrivee);
}

void Graphe::dijkstra(Sommet* depart, Sommet* arrivee, std::string type)
{
    int bl = 0;
    int tpm;
    std::priority_queue<std::pair<int, float>> file; //numSommet, distance
    std::vector<float> distance (m_ordre+1, 1000);
    std::vector<int> parent (m_ordre+1, -1);
    std::vector<std::pair <int, int>> parent2;
    std::string stringTempo;
    float floatTempo;

    for (int i = 0; i < m_ordre+1; i++)
        distance.push_back(1000);

    file.push(std::make_pair(depart->getNum(),0));
    distance[depart->getNum()] = 0;

    while (!file.empty())
    {
        int currentSommetV = file.top().first;
        float currentNum = file.top().second;
        file.pop();

        if (currentNum  <= distance[currentSommetV]){
            for (auto succ : m_sommets[currentSommetV-1]->getSuccesseurs())
            {
                int numSuccV2 = succ.first->getNum();
                float poidsSuccW2 = succ.second->getTps();

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
        std::cout << std::endl << "Voici tous les chemins les plus courts issu du sommet " << depart->getNom() << " :\n" << std::endl;
        for (int k = 1; k <= m_ordre; k++)
        {
            parent2.clear();
            bl = 0;

            std::cout << "De " << depart->getNom() << " a " << m_sommets[k-1]->getNom() << " (Temps : " << distance[k] << " min) : ";
            std::cout << k;
            for (auto p = parent[k]; p!= -1; p = parent[p])
            {
                if (bl == 0)
                    parent2.push_back(std::make_pair(p, k));
                else
                    parent2.push_back(std::make_pair(p, tpm));

                std::cout << " <- " << p;
                tpm = p;
                bl = 1;
            }

            std::reverse(parent2.begin(),parent2.end());

            std::cout   << "\nOrdre des pistes et des remontees a emprunter : " << std::endl
                        << "Depart (" << depart->getNom() << ")";
            for (auto elem : parent2)
            {
                stringTempo = "";
                for (auto elem2 : m_sommets[elem.first-1]->getSuccesseurs())
                {
                    if (elem2.first->getNum() == elem.second)
                    {
                        if (stringTempo.empty())
                        {
                            stringTempo = elem2.second->getNom();
                            floatTempo = elem2.second->getTps();
                        }
                        if (!stringTempo.empty() && elem2.second->getTps() < floatTempo)
                            stringTempo = elem2.second->getNom();
                    }
                }
                std::cout << " -> " << stringTempo;
            }
            std::cout << " -> Arrivee (" << m_sommets[k-1]->getNom() << ")" << std::endl;

            std::cout << std::endl;
        }
    }
    if (type == "Le chemin le plus court")
    {
        std::cout << "\nTemps du chemin le plus rapide de " << depart->getNom() << " a " << arrivee->getNom() << " : "
                  << distance[arrivee->getNum()] << " min" << std::endl;
        std::cout << "Chemin : " << arrivee->getNum();

        for (auto p = parent[arrivee->getNum()]; p != -1; p = parent[p])
        {
            if (bl == 0)
                parent2.push_back(std::make_pair(p, arrivee->getNum()));
            else
                parent2.push_back(std::make_pair(p, tpm));

            std::cout << " <- " << p;
            tpm = p;
            bl = 1;
        }

        std::reverse(parent2.begin(),parent2.end());

        std::cout   << std::endl << "\nOrdre des pistes et des remontees a emprunter : " << std::endl
                    << "Depart (" << depart->getNom() << ")";
        for (auto elem : parent2)
        {
            stringTempo = "";
            for (auto elem2 : m_sommets[elem.first-1]->getSuccesseurs())
            {
                if (elem2.first->getNum() == elem.second)
                {
                    if (stringTempo.empty())
                    {
                        stringTempo = elem2.second->getNom();
                        floatTempo = elem2.second->getTps();
                    }
                    if (!stringTempo.empty() && elem2.second->getTps() < floatTempo)
                        stringTempo = elem2.second->getNom();
                }
            }
            std::cout << " -> " << stringTempo;
        }
        std::cout << " -> Arrivee (" << arrivee->getNom() << ")" << std::endl;
    }
}

void Graphe::dijkstraPref(Sommet* depart, Sommet* arrivee)
{
    int bl = 0;
    int tpm;
    std::priority_queue<std::pair<int, float>> file; //numSommet, distance
    std::vector<float> distance (m_ordre+1, 1000);
    std::vector<int> parent (m_ordre+1, -1);
    std::vector<std::pair <int, int>> parent2;
    std::string stringTempo;
    float floatTempo;

    for (int i = 0; i < m_ordre+1; i++)
        distance.push_back(1000);

    file.push(std::make_pair(depart->getNum(),0));
    distance[depart->getNum()] = 0;

    while (!file.empty())
    {
        int currentSommetV = file.top().first;
        float currentNum = file.top().second;
        file.pop();

        if (currentNum  <= distance[currentSommetV]){
            for (auto succ : m_sommets[currentSommetV-1]->getSuccesseurs())
            {
                int numSuccV2 = succ.first->getNum();
                float poidsSuccW2 = succ.second->getTps();

                if (distance[numSuccV2] > distance[currentSommetV] + poidsSuccW2 && succ.second->getType() != m_pref[0] && succ.second->getType() != m_pref[1] && succ.second->getType() != m_pref[2])
                {
                    distance[numSuccV2] = distance[currentSommetV] + poidsSuccW2;
                    parent[numSuccV2] = currentSommetV;
                    file.push(std::make_pair(numSuccV2, distance[numSuccV2]));
                }
            }
        }
    }

        std::cout << "\nTemps du chemin le plus rapide de " << depart->getNom() << " a " << arrivee->getNom() << " : "
                  << distance[arrivee->getNum()] << " min" << std::endl;
        std::cout << "Chemin : " << arrivee->getNum();

        for (auto p = parent[arrivee->getNum()]; p != -1; p = parent[p])
        {
            if (bl == 0)
                parent2.push_back(std::make_pair(p, arrivee->getNum()));
            else
                parent2.push_back(std::make_pair(p, tpm));

            std::cout << " <- " << p;
            tpm = p;
            bl = 1;
        }
        std::reverse(parent2.begin(),parent2.end());
        std::cout   << std::endl << "\nOrdre des pistes et des remontees a emprunter : " << std::endl
                    << "Depart (" << depart->getNom() << ")";
        for (auto elem : parent2)
        {
            stringTempo = "";
            for (auto elem2 : m_sommets[elem.first-1]->getSuccesseurs())
            {
                if (elem2.first->getNum() == elem.second)
                {
                    if (stringTempo.empty())
                    {
                        stringTempo = elem2.second->getNom();
                        floatTempo = elem2.second->getTps();
                    }
                    if (!stringTempo.empty() && elem2.second->getTps() < floatTempo)
                        stringTempo = elem2.second->getNom();
                }
            }
            std::cout << " -> " << stringTempo;
        }
        std::cout << " -> Arrivee (" << arrivee->getNom() << ")" << std::endl;

}

int Graphe::getOrdre() {
    return m_ordre;
}

void Graphe::modifTemps()
{
    std::string typeTrajet;
    float nouveauTemps;
    bool condition = false;
    int i = 0, j = 0;
    std::string typeModif;

    ///Choix type de trajet à modifier
    do {
        std::cout << "Entrez le type de trajet que vous voulez modifier : ";
        std::cin >> typeTrajet;

        for (const auto s : m_tabDescentes)
            if (s.first == typeTrajet)
                condition = true;

        for (const auto s : m_tabRemontees)
            if (s.first == typeTrajet)
                condition = true;

        if (!condition)
            std::cout << std::endl << "Ce trajet n'existe pas, veuillez en choisir un autre." << std::endl;

    } while (!condition);

    ///Choix du nouveau temps si c'est une descente
    for (auto s : m_tabDescentes) {
        if (s.first == typeTrajet) {
            std::cout << "Quelle nouvelle duree en minutes par 100 metres voulez-vous ?";
            std::cin >> nouveauTemps;

            m_tabDescentes[i].second = nouveauTemps;
        }
        i++;
    }

    ///Choix du nouveau temps si c'est une remontee
    for (auto s : m_tabRemontees) {
        if (s.first == typeTrajet) {
            std::cout
                    << "Voulez vous modifier la partie fixe ou la partie proportionnelle au denivele ('f' ou 'p') : ";
            std::cin >> typeModif;

            if (typeModif == "f") {
                std::cout << "Quelle nouvelle duree de la partie fixe voulez vous ?";
                std::cin >> nouveauTemps;
                m_tabRemontees[j].second.first = nouveauTemps;
            }
            if (typeModif == "p") {
                std::cout << "Quelle nouvelle duree en minutes par 100 metres voulez-vous ?";
                std::cin >> nouveauTemps;
                m_tabRemontees[j].second.second = nouveauTemps;
            }
        }
        j++;
    }

    std::ofstream ifs(m_nom.c_str());
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir le fichier " + m_nom );

    ifs << m_mdp << std::endl << std::endl;
    ifs << m_tabRemontees.size() << std::endl;
    for (auto elem : m_tabRemontees)
        ifs << elem.first << "\t" << elem.second.first << "\t" << elem.second.second << std::endl;

    ifs << std::endl << m_tabDescentes.size() << std::endl;
    for (auto elem : m_tabDescentes)
        ifs << elem.first << "\t" << elem.second << std::endl;

    ifs << std::endl << m_pref[0]  << " " << m_pref[1] << " " <<m_pref[2];

    ifs.close();

    Graphe{"chargement.txt"};
}

void Graphe::modifPrefs()
{
    std::string typeTrajet;
    float nouveauTemps;
    bool condition = false;
    int i = 0, j = 0;
    std::string p1, p2, p3;

    ///Choix des prefs
    std::cout << "Nouvelle pref 1 : ";
    std::cin >> p1;
    std::cout << "Nouvelle pref 2 : ";
    std::cin >> p2;
    std::cout << "Nouvelle pref 3 : ";
    std::cin >> p3;

    m_pref[0] = p1;
    m_pref[1] = p2;
    m_pref[2] = p3;

    std::ofstream ifs(m_nom.c_str());
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir le fichier " + m_nom );

    ifs << m_mdp << std::endl << std::endl;
    ifs << m_tabRemontees.size() << std::endl;
    for (auto elem : m_tabRemontees)
        ifs << elem.first << "\t" << elem.second.first << "\t" << elem.second.second << std::endl;

    ifs << std::endl << m_tabDescentes.size() << std::endl;
    for (auto elem : m_tabDescentes)
        ifs << elem.first << "\t" << elem.second << std::endl;

    ifs << std::endl << m_pref[0]  << " " << m_pref[1] << " " <<m_pref[2];

    ifs.close();

    Graphe{"chargement.txt"};
}

void Graphe::afficherInfosTrajets()
{
    std::cout << std::endl;
    for (auto elem : m_tabRemontees)
        std::cout << elem.first << "\t" << elem.second.first << "\t" << elem.second.second << std::endl;

    for (auto elem : m_tabDescentes)
        std::cout << elem.first << "\t" << elem.second << std::endl;
    std::cout << std::endl;

    std::cout << m_pref[0] << " " << m_pref[1] << " " << m_pref[2] << std::endl;

}

std::string Graphe::getNom() {
    return m_nom;
}

