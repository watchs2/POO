
#ifndef TRABALHO_ALIMENTO_H
#define TRABALHO_ALIMENTO_H
#include <algorithm>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Reserva;
class Alimento {

public:
    Alimento(char typeAlimento, int vNutritivo, int toxi, int duration, initializer_list<string> cheiro, int x, int y);
    virtual ~Alimento();

    int getIdAlimento() const;
    virtual char getTipoAlimento()const =0;
    virtual string getNomeAlimento()const =0;
   // virtual bool desapareceAlimento() const= 0;


    int getToxicidade() const;
    int getvalorNutritivo() const;
    int getDuracao() const;
    vector<string> getCheiro();
    int getLinhaAlimento();
    int getColunaAlimento();



    virtual void avancaInstante() = 0;

    void aumentaToxicidade();
    void diminuiValorNutritivo();
    void diminuiValorDuracao();
    void aumentaValorNutritivo();


    virtual string toString() const;

private:
    char tipoAlimento;
    int valorNutritivo;
    int idAlimento;
    int toxicidade;
    int duracao;
    int linha;
    int coluna;
    vector<string> cheiro;
};


class Relva : public Alimento{
public:
    Reserva &reserva;

    ~Relva() override;

      char getTipoAlimento() const override;
      string getNomeAlimento() const override;
      void apareceRelva();//5
      void avancaInstante() override;
      bool desapareceAlimento();

    Relva(Reserva &reserva,int x, int y);
private:
bool gerou=false;

};

class Cenoura: public Alimento{
public:
    Cenoura(int x,int y);
    ~Cenoura() override;

    string getNomeAlimento() const override;
    char getTipoAlimento() const override;
    void avancaInstante() override;

};

class Corpo: public Alimento{
public:
    Corpo(int x, int y, int vNutritivo, int toxi);
    Corpo(int x, int y);
    ~Corpo() override;

    string getNomeAlimento() const override;
    char getTipoAlimento() const override;
    void avancaInstante() override;
    //bool desapareceAlimento() override;

private:
    int instanteInicial;
    bool geraValorNutritivo=false;
    int valorNutritivoInicial;
};

class Bife: public Alimento{
public:
    Reserva &reserva;
    Bife(Reserva &reserva,int x, int y);
    ~Bife() override;

    string getNomeAlimento() const override;
    char getTipoAlimento() const override;
    void avancaInstante() override;
    bool desapareceAlimento();
};

class AlimentoMisterio: public Alimento{
public:
   Reserva &reserva;
   AlimentoMisterio(Reserva &reserva,int x,int y);
    ~AlimentoMisterio() override;

    string getNomeAlimento() const override;
    char getTipoAlimento() const override;
    void avancaInstante()override;
    bool desapareceAlimento();

};

#endif //TRABALHO_ALIMENTO_H
