
#include "Zona.h"

Zona::Zona() : alimento(nullptr) {}


void Zona::adicionaAnimal(Animal *animal){
    if(animal->getTipoAnimal()=='L'){
        animais.insert(animais.begin(),animal);
    }
    else
    animais.emplace_back(animal);
}

bool Zona::colocaAlimento(Alimento *alimento) {
    if(this->alimento != nullptr)
        return false;

    this->alimento = alimento;

    return true;
}


bool Zona::removeAnimal(int id,bool deixaCorpo){
    int offset=0;

    for(auto animal :getAnimais()){
        if(animal->getIdAnimal()==id){
            if(deixaCorpo){
                animal->morreAnimal();
                    animais.erase(animais.begin()+offset);
                    return true;

            }else{
                animais.erase(animais.begin()+offset);
                return true;
            }

        }
        offset++;
    }
    return false;
}


bool Zona::removeAlimento(){
    if(alimento == nullptr)
        return false;
    delete alimento;
    alimento = nullptr;
    return true;
}

Alimento * Zona::getAlimento() {return alimento;}
vector<Animal *> Zona::getAnimais() {return animais;}

string Zona::toString() {
    ostringstream oss;

    if(alimento != nullptr)
        oss << alimento->getTipoAlimento();

    for (auto & animal : animais)
        oss << animal->getTipoAnimal();

    return oss.str();
}
