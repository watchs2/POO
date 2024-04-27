//
// Created by biama on 05/11/2022.
//

#include <string>
#include <Windows.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;

#include "Comandos.h"
#include "Reserva.h"


//saude animais
int InicioJogo::sCoelho = 20; //confirmado construtores
int InicioJogo::sOvelha = 30;  //confirmado
int InicioJogo::sLobo = 25;    //confirmado
int InicioJogo::sCanguru = 20;  //confirmado
int InicioJogo::sMisterio = 40; //definido

//vida animais
int InicioJogo::vCoelho = 30; //confirmado
int InicioJogo::vOvelha = 35;  //confirmado
int InicioJogo::vLobo = 40;    //confirmado
int InicioJogo::vCanguru = 70;  //confirmado
int InicioJogo::vMisterio = 20;  //definido

//peso animais
int InicioJogo::pCoelho = 3;
int InicioJogo::pOvelha = 10;
int InicioJogo::pLobo = 15;  //confirmado
int InicioJogo::pCanguru = 10;//confirmado
int InicioJogo::pMisterio = 20; //definido

Comandos::Comandos(Reserva &reserva, map<string, Reserva *> &saveGames) : reserva(reserva),
                                                                          limiteMaximoLinhasColunas(16),
                                                                          posicaoZonaVisivelLinhas(0),
                                                                          posicaoZonaVisivelColunas(0),
                                                                          saveGames(saveGames) {}


//funcoes GET Saude
int InicioJogo::getCoelhoSaude() {
    return sCoelho;
}

int InicioJogo::getOvelhaSaude() {
    return sOvelha;
}

int InicioJogo::getLoboSaude() {
    return sLobo;
}

int InicioJogo::getCanguruSaude() {
    return sCanguru;
}

int InicioJogo::getMisterioSaude() {
    return sMisterio;
}
    //funcoes GET Vida
int InicioJogo::getCoelhoVida() {
    return vCoelho;
}

int InicioJogo::getOvelhaVida() {
    return vOvelha;
}

int InicioJogo::getLoboVida() {
    return vLobo;
}

int InicioJogo::getCanguruVida() {
    return vCanguru;
}

int InicioJogo::getMisterioVida() {
    return vMisterio;
};

//funcoes GET peso
int InicioJogo::getCoelhoPeso() {
    return pCoelho;
}

int InicioJogo::getOvelhaPeso() {
    return pOvelha;
}

int InicioJogo::getLoboPeso() {
    return pLobo;
}

int InicioJogo::getCanguruPeso() {
    return pCanguru;
}

int InicioJogo::getMisterioPeso() {
    return pMisterio;
};


//funcoes SET Saude
void InicioJogo::setCoelhoSaude(int saudeCoelho) {
    InicioJogo::sCoelho = saudeCoelho;
}

void InicioJogo::setOvelhaSaude(int saudeOvelha) {
    InicioJogo::sOvelha = saudeOvelha;
}

void InicioJogo::setLoboSaude(int saudeLobo) {
    InicioJogo::sLobo = saudeLobo;
}

void InicioJogo::setCanguruSaude(int saudeCanguru) {
    InicioJogo::sCanguru = saudeCanguru;
}

void InicioJogo::setMisterioSaude(int saudeMisterio) {
    InicioJogo::sMisterio = saudeMisterio;
}

//funcoes SET vida
void InicioJogo::setCoelhoVida(int vidaCoelho) {
    InicioJogo::vCoelho = vidaCoelho;
}

void InicioJogo::setOvelhaVida(int vidaOvelha) {
    InicioJogo::vOvelha = vidaOvelha;
}

void InicioJogo::setLoboVida(int vidaLobo) {
    InicioJogo::vLobo = vidaLobo;
}

void InicioJogo::setCanguroVida(int vidaCanguru) {
    InicioJogo::vCanguru = vidaCanguru;
}

void InicioJogo::setMisterioVida(int vidaMisterio) {
    InicioJogo::vMisterio = vidaMisterio;
}

//funcoes SET peso
void InicioJogo::setCoelhoPeso(int pesoCoelho) {
    InicioJogo::pCoelho = pesoCoelho;
}

void InicioJogo::setOvelhaPeso(int pesoOvelha) {
    InicioJogo::pOvelha = pesoOvelha;
}

void InicioJogo::setLoboPeso(int pesoLobo) {
    InicioJogo::pLobo = pesoLobo;
}

void InicioJogo::setCanguruPeso(int pesoCanguru) {
    InicioJogo::pCanguru = pesoCanguru;
}

void InicioJogo::setMisterioPeso(int pesoMisterio) {
    InicioJogo::pMisterio = pesoMisterio;
}


/////Alteradooooooooo/////
map<string, Reserva *> &Comandos::getSaveGames() const { return saveGames; }

bool Comandos::adicionaSaveGame(const string &nomeSave, Reserva *reservaSave) {
    return saveGames[nomeSave] = new Reserva(*reservaSave);
}

Reserva &Comandos::getReserva() { return reserva; }


bool CriarJogo::executarConfig(int &linhas, int &colunas) {
    int valor;
    string line;
    string constante;
    ifstream input_file("constantes.txt");
    if (!input_file) {
        //ocorreu um erro
        return -1;
    }

    while (getline(input_file, line)) {
        istringstream iss(line);
        if (!(iss >> constante >> valor)) {
            break;
        }

        if (constante == "sCoelho") {
            InicioJogo::setCoelhoSaude(valor);
        } else if (constante == "sOvelha") {
            InicioJogo::setOvelhaSaude(valor);
        } else if (constante == "sLobo") {
            InicioJogo::setLoboSaude(valor);
        } else if (constante == "sCanguru") {
            InicioJogo::setCanguruSaude(valor);
        } else if (constante == "sMisterio") {
            InicioJogo::setMisterioSaude(valor);
        } else if (constante == "vCoelho") {
            InicioJogo::setCoelhoVida(valor);
        } else if (constante == "vOvelha") {
            InicioJogo::setOvelhaVida(valor);
        } else if (constante == "vLobo") {
            InicioJogo::setLoboVida(valor);
        } else if (constante == "vCanguro") {
            InicioJogo::setCanguroVida(valor);
        } else if (constante == "vMisterio") {
            InicioJogo::setMisterioVida(valor);
        } else if (constante == "pCoelho") {
            InicioJogo::setCoelhoPeso(valor);
        } else if (constante == "pOvelha") {
            InicioJogo::setOvelhaPeso(valor);
        } else if (constante == "pLobo") {
            InicioJogo::setLoboPeso(valor);
        } else if (constante == "pCanguru") {
            InicioJogo::setCanguruPeso(valor);
        } else if (constante == "pMisterio") {
            InicioJogo::setMisterioPeso(valor);
        }

        cout << endl;
        cout << line << endl;
    }

    do {
        cout << endl << "Linhas da reserva: ";
        cin >> linhas;
        fflush(stdin);
        cout << endl << "Colunas da reserva: ";
        cin >> colunas;
        fflush(stdin);


        if ((linhas < 16 || linhas > 500) || (colunas < 16 || colunas > 500)) {
            cout << endl << "Numero invalido! ";

        } else
            break;

        fflush(stdin);

    } while (true);

    return true;
}


void Comandos::inserirComandos(int linhasReservaInput, int colunasReservaInput) {
    linhasReserva = linhasReservaInput;
    colunasReserva = colunasReservaInput;
    string comando;
    bool resComando;

    do {
        reserva.desenhaReserva(posicaoZonaVisivelLinhas, posicaoZonaVisivelColunas, limiteMaximoLinhasColunas);
        cout << endl << "----------------------" << endl;

        cout << "Insira um comando: ";
        getline(cin, comando);

        if (comando == "exit")
            break;

        resComando = verificaComando(comando);
        if (!resComando) {
            cout << "Erro a executar o comando " << comando << endl;
        }
    } while (comando != "exit");
}


bool Comandos::verificaComando(const string &comando) {
//cin les do teclado
// istringstream le de uma varável e vai ler cada palavra

    istringstream iss(comando);
    string tipoComando;
    bool resComando;

    iss >> tipoComando; //receber a primeira palavra

    if (tipoComando == "animal") {
        resComando = criaAnimal(comando);
    } else if (tipoComando == "kill") {
        resComando = mataAnimal(comando);
    } else if (tipoComando == "killid") {
        resComando = mataAnimalId(comando);
    } else if (tipoComando == "food") {
        resComando = colocaAlimento(comando);
    } else if (tipoComando == "feed") {
        resComando = alimentaAnimais(comando);
    } else if (tipoComando == "feedid") {
        resComando = alimentaAnimaisId(comando);
    } else if (tipoComando == "nofood") {
        resComando = removeAlimento(comando);
    } else if (tipoComando == "empty") {
        resComando = removeEspaco(comando);
    } else if (tipoComando == "see") {
        resComando = verEspaco(comando);
    } else if (tipoComando == "info") {
        resComando = veInformacao(comando);
    } else if (tipoComando == "n") {
        resComando = proximoInstante(comando);
    } else if (tipoComando == "anim") {
        resComando = listarIDReserva(comando);
    } else if (tipoComando == "visanim") {
        resComando = ListarIDReservaVisivel(comando);
    } else if (tipoComando == "store") {
        resComando = ArmazenarEstado(comando);
    } else if (tipoComando == "restore") {
        resComando = RecuperarEstado(comando);
    } else if (tipoComando == "load") {
        resComando = CarregarTxt(comando);
    } else if (tipoComando == "slide") {
        resComando = MoverVisualizacao(comando);
    } else
        return false;

    return resComando;
}

bool Comandos::criaAnimal(const string &input) {
    istringstream iss(input);
    string comando;
    char animal;
    int linha = 0, coluna = 0;

    iss >> comando;
    if (iss) {
        iss >> animal >> linha >> coluna;
        if (iss) {
            if (linhasReserva <= linha || linha < 0 || colunasReserva <= coluna || coluna < 0) {
                cout << "linhas ou colunas invalidas" << endl;
                return false;
            }
            if (animal == 'c') {
                cout << "Criou um coelho [id:" << Reserva::getID() << "] " << "na linha " << linha << " e coluna "
                     << coluna << endl;
                reserva.adicionaAnimal(new Coelho(reserva, linha, coluna), linha, coluna);
            } else if (animal == 'o') {
                cout << "Criou uma ovelha [id:" << Reserva::getID() << "] " << "na linha " << linha << " e coluna "
                     << coluna << endl;
                reserva.adicionaAnimal(new Ovelha(reserva, linha, coluna), linha, coluna);
            } else if (animal == 'l') {
                cout << "Criou um lobo [id:" << Reserva::getID() << "] " << "na linha " << linha << " e coluna " << coluna
                     << endl;
                reserva.adicionaAnimal(new Lobo(reserva, linha, coluna), linha, coluna);
            } else if (animal == 'g') {
                cout << "Criou um canguru [id:" << Reserva::getID() << "] " << "na linha " << linha << " e coluna "
                     << coluna << endl;
                reserva.adicionaAnimal(new Canguru(reserva, linha, coluna,nullptr), linha, coluna);
            } else if (animal == 'm') {
                cout << "Criou um animal misterio [id:" << Reserva::getID() << "] " << "na linha " << linha
                     << " e coluna " << coluna << endl;
                reserva.adicionaAnimal(new Misterio(reserva, linha, coluna), linha, coluna);
            } else{
                cout<< "Insira um animal valido"<<endl;
                return false;
            }
        } else if (linha == 0 and coluna == 0) {
            srand((unsigned) time(NULL));
            int randomLinha = rand() % (linhasReserva - 1);
            int randomColuna = rand() % (colunasReserva - 1);

            if (animal == 'c') {
                cout << "Criou um coelho [id:" << Reserva::getID() << "] na linha " << randomLinha << " e coluna "
                     << randomColuna << endl;
                reserva.adicionaAnimal(new Coelho(reserva, randomLinha, randomColuna), randomLinha, randomColuna);
            } else if (animal == 'o') {
                cout << "Criou uma ovelha [id:" << Reserva::getID() << "] na linha " << randomLinha << " e coluna "
                     << randomColuna << endl;
                reserva.adicionaAnimal(new Ovelha(reserva, randomLinha, randomColuna), randomLinha, randomColuna);
            } else if (animal == 'l') {
                cout << "Criou um lobo [id:" << Reserva::getID() << "] na linha " << randomLinha << " e coluna "
                     << randomColuna << endl;
                reserva.adicionaAnimal(new Lobo(reserva, randomLinha, randomColuna), randomLinha, randomColuna);
            } else if (animal == 'g') {
                cout << "Criou um canguru [id:" << Reserva::getID() << "] na linha " << randomLinha << " e coluna "
                     << randomColuna << endl;
                reserva.adicionaAnimal(new Canguru(reserva, randomLinha, randomColuna,nullptr), randomLinha, randomColuna);
            } else if (animal == 'm') {
                cout << "Criou um animal misterio [id:" << Reserva::getID() << "] na linha " << randomLinha
                     << " e coluna " << randomColuna << endl;
                reserva.adicionaAnimal(new Misterio(reserva, randomLinha, randomColuna), randomLinha, randomColuna);
            } else{
                cout<< "Insira um animal valido"<<endl;
                return false;
            }
        } else if(coluna==0){
            cout << "Falta inserir o numero da coluna" << endl;
            return false;
        }
    }
    return true;
}


bool Comandos::mataAnimal(const string &input) {
    istringstream iss(input);
    int linha = 0, coluna = 0;
    string comando;

    iss >> comando;
    if (iss) {
        iss >> linha >> coluna;
        if (iss) {
            if (linhasReserva <= linha || linha < 0 || colunasReserva <= coluna || coluna < 0) {
                cout << "linhas ou colunas invalidas" << endl;
                return false;
            }
            for (auto animal : reserva.getZonas()[linha][coluna]->getAnimais()) {
                reserva.getZonas()[linha][coluna]->removeAnimal(animal->getIdAnimal(), true);
                delete animal;
                cout << "Matou um animal " << endl;

            }
            return true;
        }else{
            cout<<"Deve apresentar o comando no formato kill linha coluna"<<endl;
        }
    }
    return false;
}


bool Comandos::mataAnimalId(const string &input) {
    istringstream iss(input);
    int id;
    string comando;

    iss >> comando;
    if (iss) {
        iss >> id;
        if (iss) {
            for (int i = 0; i < linhasReserva; i++) {
                for (int j = 0; j < colunasReserva; j++) {
                    for (auto animal : reserva.getZonas()[i][j]->getAnimais()) {
                        if (id == animal->getIdAnimal()) {
                            if (reserva.getZonas()[i][j]->removeAnimal(id, true) == true) {
                                delete animal;
                                cout << "Matou um animal com o id " << id << endl;
                                return true;
                            } else
                                return false;
                        }
                    }
                }
            }
            cout << "Animal nao existe" << endl;
        }
        else{
            cout<<"Deve inserir um id"<< endl;
        }

    }
    return false;
}

bool Comandos::colocaAlimento(const string &input) {
    istringstream iss(input);
    string comando;
    char comida;
    iss >> comando;
    int linha = 0, coluna = 0;

    if (iss) {
        iss >> comida >> linha >> coluna;
        if ((linhasReserva <= linha) || (linha < 0) || (colunasReserva <= coluna) || (coluna < 0)) {
            cout << "linhas ou colunas invalidas" << endl;
            return false;
        }
        if (iss) {
            if (comida == 'r') {
                if (reserva.colocaAlimento(new Relva(reserva, linha, coluna), linha, coluna)){
                    cout << "Criou uma comida relva [id: " << (Reserva::getID())-1 << "] na linha " << linha << " e coluna " << coluna << endl;
                }

                else {
                    cout << "Ja existe um alimento nesta posicao";
                    Reserva::idAnterior();
                }
            } else if (comida == 't') {
                if (reserva.colocaAlimento(new Cenoura(linha, coluna), linha, coluna))
                    cout << "Criou uma comida cenoura [id: " << (Reserva::getID())-1 << "] na linha " << linha << " e coluna " << coluna << endl;
                else {
                    cout << "Ja existe um alimento nesta posicao";
                    Reserva::idAnterior();
                }
            } else if (comida == 'p') {
                cout << "Nao e possivel criar um corpo.";

            } else if (comida == 'b') {
                if (reserva.colocaAlimento(new Bife(reserva,linha, coluna), linha, coluna))
                    cout << "Criou uma comida bife [id: " << (Reserva::getID())-1 << "] na linha " << linha << " e coluna " << coluna << endl;
                else {
                    cout << "Ja existe um alimento nesta posicao";
                    Reserva::idAnterior();
                }
            } else if (comida == 'a') {
                if (reserva.colocaAlimento(new AlimentoMisterio(reserva,linha, coluna), linha, coluna))
                    cout << "Criou uma comida misterio [id: " << (Reserva::getID())-1 << "] na linha " << linha << " e coluna " << coluna << endl;
                else {
                    cout << "Ja existe um alimento nesta posicao";
                    Reserva::idAnterior();
                }
            } else{
                cout << "Insira um alimento valido"<<endl;
                return false;
            }
        } else if (linha == 0 and coluna == 0) {
            srand((unsigned) time(NULL));
            int randomLinha = rand() % (linhasReserva - 1);
            int randomColuna = rand() % (colunasReserva - 1);

            while (reserva.getZonas()[randomLinha][randomColuna]->getAlimento() != nullptr) {
                randomLinha = rand() % (linhasReserva - 1);
                randomColuna = rand() % (colunasReserva - 1);
            }

            if (comida == 'r') {
                cout << "Criou uma comida relva [id: " << Reserva::getID() << "] na linha " << randomLinha << " e coluna " << randomColuna << endl;
                reserva.colocaAlimento(new Relva(reserva, randomLinha, randomColuna), randomLinha, randomColuna);
            } else if (comida == 't') {
                cout << "Criou uma comida cenoura [id: " << Reserva::getID() << "] na linha " << randomLinha << " e coluna " << randomColuna << endl;
                reserva.colocaAlimento(new Cenoura(randomLinha, randomColuna), randomLinha, randomColuna);
            }else if (comida == 'p') {
                cout << "Nao e possivel criar um corpo" << endl;
            } else if (comida == 'b') {
                cout << "Criou uma comida bife [id: " << Reserva::getID() << "] na linha " << randomLinha << " e coluna " << randomColuna << endl;
                reserva.colocaAlimento(new Bife(reserva,randomLinha, randomColuna), randomLinha, randomColuna);
            } else if (comida == 'a') {
                cout << "Criou uma comida misterio [id: " << Reserva::getID() << "] na linha " << randomLinha << " e coluna " << randomColuna << endl;
                reserva.colocaAlimento(new AlimentoMisterio(reserva,randomLinha, randomColuna), randomLinha, randomColuna);
            } else{
                cout <<"Insira um alimento valido"<<endl;
                return false;
            }
        } else
            return false;
    }

    //for(auto & i : pAlimento){
    //   cout << endl << "ALIMENTO (" << i.getTipoAlimento() << ") LIDO COM ID: " << i.getIdAlimento();
    //}
    return true;
}



bool Comandos::alimentaAnimais(const string &input) {
    istringstream iss(input);
    int linha = 0, coluna = 0;
    int pontosToxicidade;
    int pontosNutritivos;
    string comando;

    iss >> comando;
    if (iss) {
        iss >> linha >> coluna >> pontosNutritivos >> pontosToxicidade;
        if (iss) {
            if (linhasReserva <= linha || linha < 0 || colunasReserva <= coluna || coluna < 0) {
                cout << "linhas ou colunas invalidas" << endl;
                return false;
            }
            for (auto animal : reserva.getZonas()[linha][coluna]->getAnimais()) {
                if(animal->getTipoAnimal()=='G'){
                    continue;
                }
                animal->diminuiSaude(pontosToxicidade);
                animal->aumentaSaude(pontosNutritivos);
                animal->adicionaAlimentoHistorico("user",pontosNutritivos,pontosToxicidade);
            }
            return true;
        }
    }
    return false;
}


bool Comandos::alimentaAnimaisId(const string &input) {
    istringstream iss(input);
    string comando;
    int pontosToxicidade;
    int pontosNutritivos;
    int id;

    iss >> comando;
    if (iss) {
        iss >> id >> pontosNutritivos >> pontosToxicidade;
        if (iss) {
            for (int i = 0; i < linhasReserva; i++) {
                for (int j = 0; j < colunasReserva; ++j) {
                    for (auto animal : reserva.getZonas()[i][j]->getAnimais()) {
                        if (id == animal->getIdAnimal()) {
                            if(animal->getTipoAnimal()=='G'){
                                return true;
                            }
                            animal->diminuiSaude(pontosToxicidade);
                            animal->aumentaSaude(pontosNutritivos);
                            animal->adicionaAlimentoHistorico("user",pontosNutritivos,pontosToxicidade);
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}


bool Comandos::removeAlimento(const string &input) {
    istringstream iss(input);
    string comando;
    int linha = 0, coluna = 0;
    int id;

    iss >> comando;
    if (iss) {
        iss >> linha >> coluna;
        if (iss) {
            if ((linhasReserva <= linha) || (linha < 0) || (colunasReserva <= coluna) || (coluna < 0)) {
                cout << "linhas ou colunas invalidas" << endl;
                return false;
            }

            if (reserva.getZonas()[linha][coluna]->removeAlimento()) {
                cout << "Remove Alimento na linha " << linha << "e coluna " << coluna << endl;
                return true;
            } else
                cout << "Nao existe altimento nesta posicao"<<endl;
                return false;
        } else if (linha != 0 and coluna == 0) {
            id = linha;
            for (int i = 0; i < linhasReserva; ++i) {
                for (int j = 0; j < colunasReserva; ++j) {
                    auto alimento = reserva.getZonas()[i][j]->getAlimento();

                    if (alimento == nullptr)
                        continue;

                    if (alimento->getIdAlimento() == id){
                        cout << "Remove Alimento com o id " << id << endl;
                        return reserva.getZonas()[i][j]->removeAlimento();
                    }
                }
            }
        }
        cout<< "Digite um id válido ou linha e coluna "<<endl;
    }
    return false;
}


bool Comandos::removeEspaco(const string &input) {
    istringstream iss(input);
    string comando;
    int linha = 0, coluna = 0;
    iss >> comando;
    if (iss) {
        iss >> linha >> coluna;
        if (iss) {
            if ((linhasReserva <= linha) || (linha < 0) || (colunasReserva <= coluna) || (coluna < 0)) {
                cout << "linhas ou colunas invalidas" << endl;
                return false;
            }

            for (auto animal : reserva.getZonas()[linha][coluna]->getAnimais()) {
                reserva.getZonas()[linha][coluna]->removeAnimal(animal->getIdAnimal(), false);
                cout << "Matou um animal com o id " << animal->getIdAnimal() << endl;
                delete animal;
            }
            if (reserva.getZonas()[linha][coluna]->removeAlimento()) {
                cout << "Remove Alimento na linha " << linha << "e coluna " << coluna << endl;
            }
            return true;
        }
    cout<< " Digite o comando no formato empty linha coluna" << endl;
    }
    return false;
}


bool Comandos::verEspaco(const string &input) {
    istringstream iss(input);
    string comando;
    int linha = 0, coluna = 0;

    iss >> comando;
    if (iss) {
        iss >> linha >> coluna;
        if (linhasReserva <= linha || linha < 0 || colunasReserva <= coluna || coluna < 0) {
            cout << "linhas ou colunas invalidas" << endl;
            return false;
        }

        if (iss) {

            cout << "Zona na linha " << linha << " e coluna " << coluna << endl << "Alimentos: " << endl;

            Alimento *alimento = reserva.getZonas()[linha][coluna]->getAlimento();
            if (alimento != nullptr)
                cout << alimento->toString() << endl;

            cout << endl << "Animais:" << endl;

            vector<Animal *> animais = reserva.getZonas()[linha][coluna]->getAnimais();

            for (auto animal : animais) {
                cout << animal->toString() << endl;
            }
        }

    }
    return true;
}


bool Comandos::veInformacao(const string &input) {
    istringstream iss(input);
    string comando;
    int id;

    iss >> comando;
    if (iss) {
        iss >> id;
        if (iss) {
            for (int i = 0; i < linhasReserva; ++i) {
                for (int j = 0; j < colunasReserva; ++j) {
                    for (auto animal : reserva.getZonas()[i][j]->getAnimais()) {
                        if (id == animal->getIdAnimal()) {
                            cout << animal->toString() << endl;
                            return true;
                        }
                    }
                }
            }

            for (int i = 0; i < linhasReserva; ++i) {
                for (int j = 0; j < colunasReserva; ++j) {

                    auto alimento = reserva.getZonas()[i][j]->getAlimento();

                    if (alimento == nullptr) {
                        continue;
                    }

                    if (id == alimento->getIdAlimento()) {
                        cout << alimento->toString()<< endl;

                        return true;
                    }

                }
            }
            cout << "Nao foi possivel encontrar esse elemento" << endl;
            return false;
        }
        cout << "Introduza um id"<<endl;
    }
    return false;
}


bool Comandos::proximoInstante(const string &input) {
    istringstream iss(input);
    string comando;
    int pausa = 0, n = 0;
    iss >> comando;
    if (iss) {
        iss >> n >> pausa;
        if (iss) {
            cout << "Aumenta " << n << " instantes" << endl;
            for (int i = 0; i < n; ++i) {
                Reserva::aumentaInstante();
                for (int j = 0; j < linhasReserva; ++j) {
                    for (int k = 0; k < colunasReserva; ++k) {

                        for (auto animal : reserva.getZonas()[j][k]->getAnimais())
                            animal->setJaAvancouInstante(false);
                    }
                }
                for (int j = 0; j < linhasReserva; ++j) {
                    for (int k = 0; k < colunasReserva; ++k) {
                        auto alimento = reserva.getZonas()[j][k]->getAlimento();

                        if (alimento != nullptr)
                            alimento->avancaInstante();

                        for (int l=0; k < reserva.getZonas()[j][k]->getAnimais().size();k++ )
                            reserva.getZonas()[j][k]->getAnimais()[l]->avancaInstante();
                    }
                }
                if(i<n-1){
                    reserva.desenhaReserva(posicaoZonaVisivelLinhas, posicaoZonaVisivelColunas, limiteMaximoLinhasColunas);
                }
                sleep(pausa);
            }

            return true;

        } else if (n != 0 && pausa == 0) {
            cout << "Aumenta " << n << " instantes" << endl;

            for (int i = 0; i < n; ++i) {
                Reserva::aumentaInstante();
                for (int j = 0; j < linhasReserva; ++j) {
                    for (int k = 0; k < colunasReserva; ++k) {

                        for (auto animal : reserva.getZonas()[j][k]->getAnimais())
                            animal->setJaAvancouInstante(false);
                    }
                }
                for (int j = 0; j < linhasReserva; ++j) {
                    for (int k = 0; k < colunasReserva; ++k) {
                        auto alimento = reserva.getZonas()[j][k]->getAlimento();

                        if (alimento != nullptr)
                            alimento->avancaInstante();

                        for (int l=0; l < reserva.getZonas()[j][k]->getAnimais().size();l++ )
                            reserva.getZonas()[j][k]->getAnimais()[l]->avancaInstante();
                    }
                }
                if(i<n-1){
                    reserva.desenhaReserva(posicaoZonaVisivelLinhas, posicaoZonaVisivelColunas, limiteMaximoLinhasColunas);
                }

            }

            return true;

        } else if (n == 0 && pausa == 0) {
            for (int i = 0; i < linhasReserva; ++i) {
                for (int j = 0; j < colunasReserva; ++j) {

                    for (auto animal : reserva.getZonas()[i][j]->getAnimais())
                        animal->setJaAvancouInstante(false);
                }
            }

            Reserva::aumentaInstante();
            cout << "Aumentou 1 instante" << endl;

            for (int i = 0; i < linhasReserva; ++i) {
                for (int j = 0; j < colunasReserva; ++j) {
                    auto alimento = reserva.getZonas()[i][j]->getAlimento();

                    if (alimento != nullptr)
                        alimento->avancaInstante();

                    for (int k=0; k < reserva.getZonas()[i][j]->getAnimais().size();k++ )
                        reserva.getZonas()[i][j]->getAnimais()[k]->avancaInstante();
                }
            }
            return true;
        }
    }
    cout << endl << "Erro ao executar o comando" << endl;
    return false;
}


bool Comandos::listarIDReserva(const string &input) {
    istringstream iss(input);
    string comando;

    iss >> comando;
    if (iss) {
        for (int i = 0; i < linhasReserva; ++i) {
            for (int j = 0; j < colunasReserva; ++j) {
                for (auto &animal : reserva.getZonas()[i][j]->getAnimais()) {
                    cout << animal->toString() << endl;
                }
            }
        }
        return true;
    } else
        return false;
}


bool Comandos::ListarIDReservaVisivel(const string &input) {
    istringstream iss(input);
    string comando;

    int maxLinhas;
    int maxColunas;
    iss >> comando;
    if (iss) {
        if ((posicaoZonaVisivelLinhas + limiteMaximoLinhasColunas) > linhasReserva)
            maxLinhas = linhasReserva;
        else
            maxLinhas = posicaoZonaVisivelLinhas + limiteMaximoLinhasColunas;
        if ((posicaoZonaVisivelLinhas + limiteMaximoLinhasColunas) > colunasReserva)
            maxColunas = colunasReserva;
        else
            maxColunas = posicaoZonaVisivelColunas + limiteMaximoLinhasColunas;


        for (int i = posicaoZonaVisivelLinhas; i < maxLinhas; ++i) {
            for (int j = posicaoZonaVisivelColunas; j < maxColunas; ++j) {
                for (auto animal:reserva.getZonas()[i][j]->getAnimais()) {
                    cout << animal->toString() << endl;
                }
            }
        }
        return true;
    } else
        return false;
}

bool Comandos::ArmazenarEstado(const string &input) {
    istringstream iss(input);
    string comando, nome;

    iss >> comando >> nome;

    if (iss) {
        for (const auto &saveGame : getSaveGames())
            if (saveGame.first == nome)
                return false;

        return adicionaSaveGame(nome, &getReserva());
    }

    cout << endl << "Prototipo comando: store 'nome store'" << endl << endl;
    return false;
}


bool Comandos::RecuperarEstado(const string &input) {
    istringstream iss(input);
    string comando, nome;

    iss >> comando >> nome;

    if (iss) {
        for (const auto &saveGame : getSaveGames()) {
            if (saveGame.first == nome) {
                reserva = *saveGame.second;
                //reserva->updateDiaStatic();
                verificaComando("list");
                return true;
            }
        }
    }
    return false;
}


bool Comandos::CarregarTxt(const string &input) {
    istringstream iss(input);
    string comando, nomeFicheiro;

    iss >> comando >> nomeFicheiro;
    if (iss) {
        ifstream ficheiro;
        ficheiro.open(nomeFicheiro.c_str());

        if (!ficheiro.is_open())
            return false; // não consegue abrir o ficheiro

        string comandoFicheiro;
        while (getline(ficheiro, comandoFicheiro)) {
            if (!verificaComando(comandoFicheiro))
                cout << "Erro a correr o comando: \"" << comandoFicheiro << "\"" << endl;
            cout << endl;
        }

        ficheiro.close();
        return true;
    }
    cout<<"Digite um ficheiro valido .txt"<<endl;
    return false;
}


bool Comandos::MoverVisualizacao(const string &input) {
    istringstream iss(input);
    string comando;
    string direcao; //up,down,right and left
    int nMovimentos;


    iss >> comando;
    if (iss) {
        iss >> direcao >> nMovimentos;
        if (iss) {
            if (direcao == "up") {
                if (posicaoZonaVisivelLinhas - nMovimentos >= 0)
                    posicaoZonaVisivelLinhas -= nMovimentos;
                else
                    return false;
            } else if (direcao == "down") {
                if (posicaoZonaVisivelLinhas + limiteMaximoLinhasColunas + nMovimentos <= linhasReserva)
                    posicaoZonaVisivelLinhas += nMovimentos;
                else
                    return false;
            } else if (direcao == "right") {
                if (posicaoZonaVisivelColunas + limiteMaximoLinhasColunas + nMovimentos <= colunasReserva)
                    posicaoZonaVisivelColunas += nMovimentos;
                else
                    return false;

            } else if (direcao == "left") {
                if (posicaoZonaVisivelColunas - nMovimentos >= 0) {
                    posicaoZonaVisivelColunas -= nMovimentos;
                } else
                    return false;
            } else
                return false;

            return true;
        }
    }
    return false;

}





