#include "Alimento.h"
#include "Comandos.h"

using namespace std;

Alimento::Alimento(char typeAlimento, int vNutritivo, int toxi, int duration, initializer_list<string> cheiro, int x,
                   int y) :
        tipoAlimento(typeAlimento), idAlimento(Reserva::getNextId()), valorNutritivo(vNutritivo), toxicidade(toxi),
        duracao(duration), cheiro(cheiro), linha(x), coluna(y) {}

Alimento::~Alimento() noexcept {}

int Alimento::getIdAlimento() const {
    return idAlimento;
}

int Alimento::getToxicidade() const {
    return toxicidade;
}

int Alimento::getvalorNutritivo() const {
    return valorNutritivo;
}

int Alimento::getDuracao() const {
    return duracao;
}

vector<string> Alimento::getCheiro() {
    return cheiro;
}

int Alimento::getLinhaAlimento() {
    return linha;
}

int Alimento::getColunaAlimento() {
    return coluna;
}

void Alimento::aumentaToxicidade() {
    toxicidade++;
}

void Alimento::diminuiValorNutritivo() {
    valorNutritivo--;
}

void Alimento::diminuiValorDuracao() {
    duracao--;
}
void Alimento::aumentaValorNutritivo() {
    valorNutritivo++;
}


Relva::Relva(Reserva &reserva, int x, int y) : Alimento('r', 3, 0, 20, {"erva", "verdura"}, x, y), reserva(reserva) {}

Relva::~Relva() noexcept {}

Cenoura::Cenoura(int x, int y) : Alimento('t', 4, 0, -1, {"verdura"}, x, y) {}

Cenoura::~Cenoura() noexcept {}

Corpo::Corpo(int x, int y) : Alimento('p', 10, 0, -1, {"carne"}, x, y), instanteInicial(Reserva::getInstante()) {}
Corpo::Corpo(int x, int y,int vNutritivo, int toxi) : Alimento('p', vNutritivo, toxi, -1, {"carne"}, x, y), instanteInicial(Reserva::getInstante()) {}

Corpo::~Corpo() noexcept {}

Bife::Bife(Reserva &reserva,int x, int y) : Alimento('b', 10, 2, 30, {"carne", "ketchup"}, x, y),reserva(reserva) {}

Bife::~Bife() noexcept {}

AlimentoMisterio::AlimentoMisterio(Reserva &reserva,int x, int y) : Alimento('a', 5, 1, 20, {"rosas"}, x, y),reserva(reserva) {}

AlimentoMisterio::~AlimentoMisterio() noexcept {}

char Relva::getTipoAlimento() const { return 'r'; }

string Relva::getNomeAlimento() const {return "relva";}

char Cenoura::getTipoAlimento() const { return 't'; }

string Cenoura::getNomeAlimento() const {return "cenoura" ;}

char Corpo::getTipoAlimento() const { return 'p'; }
string Corpo::getNomeAlimento() const {return "corpo" ;}

char Bife::getTipoAlimento() const { return 'b'; }
string Bife::getNomeAlimento() const {return "bife" ;}

char AlimentoMisterio::getTipoAlimento() const { return 'a'; }
string AlimentoMisterio::getNomeAlimento() const {return "alimento misterio" ;}


//Acabar
void Relva::apareceRelva() {
    srand((unsigned) time(NULL));
    int numRandLinha;
    int numRandColuna;
    int linha;
    int coluna;
    do {
        numRandColuna = -8 + rand() % (8 - (-8) + 1); //para obter um valor entre -8 e 8
    } while (numRandColuna <= 3 && numRandColuna >= -3);

    do {
        numRandLinha = -8 + rand() % (8 - (-8) + 1);
    } while (numRandLinha <= 3 && numRandLinha >= -3);;
    linha=getLinhaAlimento() + numRandLinha;
    coluna=getColunaAlimento() + numRandColuna;//mudar a linha de 16 para o valor maximo
    if(linha>=0 && coluna>=0 && linha<=reserva.getNLinhas() && coluna<=reserva.getNColunas() && gerou==false){
        if(reserva.getZonas()[linha][coluna]->getAlimento() ==nullptr)
            if (reserva.colocaAlimento(new Relva(reserva, linha, coluna), linha, coluna)){
                gerou=true;
                cout << "Nasceu uma comida relva na linha " << linha << " e coluna " << coluna << endl;
            }
    }

}

void Relva::avancaInstante() {
    diminuiValorDuracao();desapareceAlimento();
    if(getDuracao() < 20 / 4)
        apareceRelva();

}

void Cenoura::avancaInstante() {
    if (getToxicidade() < 3) {
        if (Reserva::getInstante() % 10 == 0) {
            aumentaToxicidade();
        }
    }
}

void Corpo::avancaInstante() {
    if(geraValorNutritivo==false){
        valorNutritivoInicial=getvalorNutritivo();
        geraValorNutritivo=true;
    }
    if (getvalorNutritivo() > 0)
        diminuiValorNutritivo();
    if (Reserva::getInstante() - instanteInicial <= 2 *valorNutritivoInicial) {
        aumentaToxicidade();

    }
}

void Bife::avancaInstante() {
    diminuiValorDuracao();
    desapareceAlimento();
    if(getvalorNutritivo() > 0) {
        diminuiValorNutritivo();
    }
}

void AlimentoMisterio::avancaInstante(){
    diminuiValorDuracao();
    desapareceAlimento();
    aumentaValorNutritivo();
}
bool Bife::desapareceAlimento() {
    if (getDuracao() == 0){
        reserva.getZonas()[getLinhaAlimento()][getColunaAlimento()]->removeAlimento();
        return true;
    }
    return false;
}


bool AlimentoMisterio::desapareceAlimento() {
    if (getDuracao() == 0){
        reserva.getZonas()[getLinhaAlimento()][getColunaAlimento()]->removeAlimento();
        return true;
    }
    return false;
}
bool Relva::desapareceAlimento() {
   if (getDuracao() == 0){
       reserva.getZonas()[getLinhaAlimento()][getColunaAlimento()]->removeAlimento();
       return true;
   }
    return false;
}


//
//}





string Alimento::toString() const {
    ostringstream oss;
    oss << "Alimento com id: " << getIdAlimento() << " do tipo " << tipoAlimento << " com valor nutritivo "
        << valorNutritivo << " e com toxicidade de " << toxicidade << " com uma duracao de ";

    if (duracao == -1)
        oss << "infinita";
    else
        oss << duracao;

    oss << " e com cheiro de ";

    for (const auto &umCheiro : cheiro)
        oss << umCheiro << ", ";

    return oss.str().substr(0, oss.str().size() - 2);
}