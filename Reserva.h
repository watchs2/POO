#ifndef TRABALHO_RESERVA_H
#define TRABALHO_RESERVA_H

#include <vector>
#include <iostream>
#include "Zona.h"

using namespace std;

class Reserva {
public:
    static int getNextId();
    static int getID();
    static int aumentaInstante();
    static int getInstante();
    static int idAnterior();
    Reserva(int novasLinhas, int novasColunas);

    void adicionaAnimal(Animal *animal, int linha, int coluna);

    bool colocaAlimento(Alimento *alimento, int linha, int coluna);

    void desenhaReserva(int posicaoLinha, int posicaoColuna, int limiteMaximo);

    int getNLinhas() const;

    int getNColunas() const;

    ~Reserva();

    //Funções que retornam os vetores
    vector<vector<Zona *>> getZonas();


private:
    vector<vector<Zona *>> reservaGeral;
    static int id;
    int nLinhas;
    int nColunas;

    static int instante;

};


#endif //TRABALHO_RESERVA_H
