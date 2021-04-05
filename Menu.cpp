//
// Created by Romain on 05/04/2021.
//

#include "bibliotheque.h"

void menu() {

    int choix;

    do {
        std::cout << " //////////////////// Bienvenue a la borne interactive des Arcs ! \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << std::endl;

        std::cout << "Que voulez-vous faire ?" << std::endl;

        std::cout << "1 - Connaitre d'ou part et arrive un chemin (Pas fait)" << std::endl;
        std::cout << "2 - Connaitre les trajets permettant d'arriver a un point (Pas fait)" << std::endl;
        std::cout << "3 - Connaitre les chemins les plus courts a partir d'un point choisi (Pas fait)" << std::endl;
        std::cout << "4 - Connaitre l'itineraire le plus rapide entre deux points (Pas fait)" << std::endl;

        std::cin >> choix;

        switch (choix) {
            case 1 :
                //system("cls");
                std::cout << "Pas encore implemente" << std::endl;
                std::cout << "0 - Arreter" << std::endl;
                std::cout << "1 - Retour" << std::endl;
                std::cin >> choix;
                break;

            case 2 :
                //system("cls");
                std::cout << "Pas encore implemente" << std::endl;
                std::cout << "0 - Arreter" << std::endl;
                std::cout << "1 - Retour" << std::endl;
                std::cin >> choix;
                break;

            case 3 :
                //system("cls");
                std::cout << "Pas encore implemente" << std::endl;
                std::cout << "0 - Arreter" << std::endl;
                std::cout << "1 - Retour" << std::endl;
                std::cin >> choix;
                break;

            case 4 :
                //system("cls");
                std::cout << "Pas encore implemente" << std::endl;
                std::cout << "0 - Arreter" << std::endl;
                std::cout << "1 - Retour" << std::endl;
                std::cin >> choix;
                break;
        }
    } while (choix != 0);


}

