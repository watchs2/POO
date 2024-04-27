
#ifndef TRABALHO_ANIMAL_H
#define TRABALHO_ANIMAL_H

#include <string>
#include <vector>
#include "Alimento.h"

using namespace std;
class Reserva;


class HistoricoAlimentacao{
public:
    HistoricoAlimentacao(string nome, int valorNutritivo, int valorToxicidade);


    HistoricoAlimentacao *getProximo() const;

    void setProximo(HistoricoAlimentacao *proximo);
    string toString() const;

private:
    string nome;
    int valorNutritivo;
    int toxicidade;
    HistoricoAlimentacao *proximo;


};

class Animal {

public:
    Animal(Reserva &reserva, char typeAnimal, int health, int weight, int duration, int x, int y);
    ~Animal();
    Reserva &reserva;
    virtual void morreAnimal() = 0;
    virtual bool verificamorreAnimal() = 0;
    virtual void avancaInstante() = 0;


    int getIdAnimal() const;
    int getSaudeAnimal() const;
    int getPesoAnimal() const;
    char getTipoAnimal() const;
    int getDuracao() const;
    int getFomeAnimal() const;
    int getLinhaAnimal() const;
    int getColunaAnimal() const;
    void setPesoAnimal(int novoPeso);
    void setLinhaAnimal(int linhanova);
    void setColunaAnimal(int novaColuna);
    void diminuiSaude(int toxicidade);
    void aumentaSaude(int vNutritivo);
    void aumentaFome(int n);
    void diminuiSaudeA(int n);
    void diminuiDuracao();
    string toString() const;
    static int randomPesoC();
    static int randomPesoO();



    HistoricoAlimentacao *getHistoricoAlimentacao();

    void adicionaAlimentoHistorico(string nome, int valorNutritivo, int valorToxicidade);

    bool isJaAvancouInstante() const;

    void setJaAvancouInstante(bool jaAvancouInstante);

    void setHistorico(HistoricoAlimentacao *historico);

private:
    HistoricoAlimentacao *historico;
    char tipoAnimal;
    int saude;
    int idA;
    int duracao;
    int peso;
    int fome;
    int linha;
    int coluna;
    bool jaAvancouInstante;

};


class Coelho: public Animal{
public:
    Coelho(Reserva &reserva, int x,int y);
    ~Coelho();

    void avancaInstante() override;
    void morreAnimal() override;
    bool verificamorreAnimal() override;
};

class Ovelha: public Animal{
public:
    Ovelha(Reserva &reserva, int x, int y);
    ~Ovelha();

    void avancaInstante() override;
    void morreAnimal() override;
    bool verificamorreAnimal() override;
};

class Lobo: public Animal{
public:
    Lobo(Reserva &reserva, int x, int y);
    ~Lobo();
    bool verificamorreAnimal() override;

    void avancaInstante() override;
    void morreAnimal() override;
    void geraInstanteNascimento();
    int getInstanteNascimento();
private:
    int instanteNascimento;
    bool gerouFilho = false;

};

class Canguru: public Animal{
public:
    Canguru(Reserva &reserva, int x, int y);
    Canguru(Reserva &reserva, int x, int y, Canguru* progenitor);
    ~Canguru();

    void avancaInstante() override;
    void morreAnimal() override;
    Canguru* getProgenitor() const;
    bool verificamorreAnimal() override;
    void adicionaCanguruBolsa(Canguru* canguru);
    int getTempoNaBolsa() const;
    void setTempoNaBolsa(int novoTempo);
private:
    vector<Canguru*> bolsa;
    Canguru* progenitor;
    int tempoNaBolsa;

};
class Misterio: public Animal{
public:
    Misterio(Reserva &reserva, int x, int y);
    ~Misterio();

    void avancaInstante() override;
    void morreAnimal() override;
    bool verificamorreAnimal() override;
};


#endif //TRABALHO_ANIMAL_H
