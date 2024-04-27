
#ifndef TRABALHO_ZONAS_H
#define TRABALHO_ZONAS_H


#include <vector>
#include <string>
#include "Alimento.h"
#include "Animal.h"

using namespace std;

class Zona {

public:
    Zona();
    void adicionaAnimal(Animal *animal);
    bool colocaAlimento(Alimento *alimento);
    bool removeAnimal(int id,bool deixaCorpo);
    bool removeAlimento();


    Alimento* getAlimento();
    vector<Animal*> getAnimais();

    string toString();
private:
    Alimento* alimento;

    vector<Animal*> animais;
};


#endif //TRABALHO_ZONAS_H
