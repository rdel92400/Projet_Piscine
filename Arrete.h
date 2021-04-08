#ifndef PROJET_ARRETE_H
#define PROJET_ARRETE_H
#include "Bibliotheque.h"


class Arrete {
private:
    int m_num;
    float m_tps;
    std::string m_type;
    std::string m_nom;
public:
    Arrete();
    ~Arrete();
    ///Getteur
    int getNum()const;
    std::string getType()const;
    std::string getNom()const;
    float getTps()const;
    ///Acesseur
    void setNum(int num);
    void setType(std::string type);
    void setNom(std::string nom);
    void setTps(float tps);
};


#endif //PROJET_ARRETE_H
