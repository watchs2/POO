


#include "Animal.h"
#include "Reserva.h"

#include <iomanip>

int Reserva::id = 1;
int Reserva::getNextId() {
    return id++;
}
int Reserva::getID() {
    return id;
}
int Reserva::idAnterior(){
    return id--;
}
int Reserva::instante = 1;
int Reserva::aumentaInstante(){
    return instante++;
}

int Reserva::getInstante() {return instante;}

Reserva::Reserva( int nLinhas,int nColunas) : nLinhas(nLinhas), nColunas(nColunas){


    for (int i = 0; i < nLinhas; ++i) {
        vector<Zona*> linha;
        for (int j = 0; j < nColunas; ++j) {
            linha.emplace_back(new Zona());
        }
        reservaGeral.emplace_back(linha);
    }
}

void Reserva::adicionaAnimal(Animal *animal, int linha, int coluna){
    reservaGeral[linha][coluna]->adicionaAnimal(animal);
}

bool Reserva::colocaAlimento(Alimento *alimento, int linha, int coluna) {
    return reservaGeral[linha][coluna]->colocaAlimento(alimento);
}

void Reserva::desenhaReserva(int posicaoLinha, int posicaoColuna, int limiteMaximo){
    cout << endl;

    int maxLinhas;
    int maxColunas;

    if((posicaoLinha + limiteMaximo) > nLinhas)
        maxLinhas = nLinhas;
    else
        maxLinhas = posicaoLinha + limiteMaximo;

    if((posicaoLinha + limiteMaximo) > nColunas)
        maxColunas = nColunas;
    else
        maxColunas = posicaoColuna + limiteMaximo;

    cout << left << setw(4) << " ";
    for (int i = posicaoColuna; i < maxColunas; ++i) {
        cout << left << setw(3) << i << " ";
    }
    cout << endl;

    for (int i = posicaoLinha; i < maxLinhas; ++i) {
        cout << left << setw(3) << i << "|";
        for (int j = posicaoColuna; j < maxColunas; ++j) {
            cout << left << setw(3) << reservaGeral[i][j]->toString() << "|";
        }
        cout << endl;
    }
}

vector<vector<Zona*>> Reserva::getZonas(){return reservaGeral;}

Reserva::~Reserva() {
    int i,j;
    for(i=0;i<nLinhas;i++){
        for(j=0;j<nColunas;j++){
            delete reservaGeral[i][j];
        }
    }
}

int Reserva::getNLinhas() const {
    return nLinhas;
}

int Reserva::getNColunas() const {
    return nColunas;
}


