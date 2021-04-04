//
// Created by maxen on 04/04/2021.
//

#include "Graphe.h"

Graphe::Graphe(std::string nomFichier) {
    std::ifstream ifs{ nomFichier };

    ifs >> m_ordre;
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture ordre du graphe");

    int num1, num3;
    std::string num2;

    for (int i = 1; i <= m_ordre; ++i)
        m_sommets.push_back(new Sommet{ i });

    for (int i = 1; i <= m_ordre; ++i){
        ifs >> num1 >> num2 >> num3;
        if (ifs.fail())
            throw std::runtime_error("Probleme lecture arc");
        m_sommets[num1]->setNom(num2);
        m_sommets[num1]->setAlt(num3);
    }
}

Graphe::~Graphe() {

}

void Graphe::afficher() {
    std::cout << "Affichage sommet :" << std::endl;
    for (const auto s : m_sommets){
        std::cout << "Sommet " << s->getNum() << " : " << s->getNom() << " altitude : " << s->getAlt() << std::endl;
    }
}
