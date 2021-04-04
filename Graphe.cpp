//
// Created by maxen on 04/04/2021.
//

#include "Graphe.h"

Graphe::Graphe(std::string nomFichier) {
    std::ifstream ifs{ nomFichier };
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    ifs >> m_ordre;
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture ordre du graphe");

    int num1, num3;
    std::string num2;

    for (int i = 0; i < m_ordre; i++)
        m_sommets.push_back(new Sommet{ i+1 });

    for (int i = 0; i < m_ordre; i++){
        ifs >> num1 >> num2 >> num3;

        std::cout << num1 << std::endl;

        if (ifs.fail())
            throw std::runtime_error("Probleme lecture arc");

        m_sommets[i]->setNom(num2);
        m_sommets[i]->setAlt(num3);
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
