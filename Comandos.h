
#ifndef TRABALHO_COMANDOS_H
#define TRABALHO_COMANDOS_H
#include <string>
#include <unistd.h>
#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "Animal.h"
#include "Alimento.h"
#include "Reserva.h"
#include <map>


using namespace std;

class InicioJogo {
        public:
        static int getCoelhoSaude();
        static int getOvelhaSaude();
        static int getLoboSaude();
        static int getCanguruSaude();
        static int getMisterioSaude();
        static int getCoelhoVida();
        static int getOvelhaVida();
        static int getLoboVida();
        static int getCanguruVida();
        static int getMisterioVida();
        static int getCoelhoPeso();
        static int getOvelhaPeso();
        static int getLoboPeso();
        static int getCanguruPeso();
        static int getMisterioPeso();

        static void setCoelhoSaude(int sCoelho);
        static void setOvelhaSaude(int sOvelha);
        static void setLoboSaude(int sLobo);
        static void setCanguruSaude(int sCanguru);
        static void setMisterioSaude(int sMisterio);
        static void setCoelhoVida(int vCoelho);
        static void setOvelhaVida(int vOvelha);
        static void setLoboVida(int vLobo);
        static void setCanguroVida(int vCanguro);
        static void setMisterioVida(int vMisterio);
        static void setCoelhoPeso(int pCoelho);
        static void setOvelhaPeso(int pOvelha);
        static void setLoboPeso(int pLobo);
        static void setCanguruPeso(int pCanguru);
        static void setMisterioPeso(int pMisterio);

        private:
        static int sCoelho;
        static int sOvelha;
        static int sLobo;
        static int sCanguru;
        static int sMisterio;

        static int vCoelho;
        static int vOvelha;
        static int vLobo;
        static int vCanguru;
        static int vMisterio;

        static int pCoelho;
        static int pOvelha;
        static int pLobo;
        static int pCanguru;
        static int pMisterio;

};

class CriarJogo{
        private:

        public:
           bool executarConfig(int &linhas, int &colunas);
};


class Comandos {

public:
    Comandos(Reserva &reserva, map<string, Reserva *> &saveGames); //construtor dos comandos
    void inserirComandos(int linhasReservaInput, int colunasReservaInput);
    bool verificaComando(const string& comando); //refencia para a variável que só consegues ler

    map<string, Reserva *> &getSaveGames() const;

    Reserva & getReserva();



private:

    bool criaAnimal(const string& input);
    bool mataAnimal(const string& input);
    bool mataAnimalId(const string& input);
    bool colocaAlimento(const string& input);
    bool alimentaAnimais(const string& input);
    bool alimentaAnimaisId(const string& input);
    bool removeAlimento(const string& input);
    bool removeEspaco(const string& input);
    bool verEspaco(const string& input);
    bool veInformacao(const string& input);
    bool proximoInstante(const string& input);
    bool listarIDReserva(const string& input);
    bool ListarIDReservaVisivel(const string& input);
    bool ArmazenarEstado(const string& input);
    bool RecuperarEstado(const string& input);
    bool CarregarTxt(const string& input);
    bool MoverVisualizacao(const string& input);

    int linhasReserva, colunasReserva;

    map<string, Reserva *> & saveGames;

    bool adicionaSaveGame(const string& nomeSave, Reserva * reservaSave);

    Reserva &reserva;//referncia para a reserva

    int posicaoZonaVisivelLinhas;
    int posicaoZonaVisivelColunas;
    const int limiteMaximoLinhasColunas;

};


#endif //TRABALHO_COMANDOS_H
