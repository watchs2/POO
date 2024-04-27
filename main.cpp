#include <iostream>
#include "Comandos.h"

using namespace std;
int main() {

    int linhas, colunas;

    CriarJogo criarJogo;

    criarJogo.executarConfig(linhas, colunas);

    Reserva reserva(linhas,colunas);

    map<string, Reserva *> saveGames;

    Comandos comandos(reserva,saveGames);
    comandos.inserirComandos(linhas, colunas);

}
