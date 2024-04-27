#include "Animal.h"
#include "Comandos.h"

using namespace std;

Animal::
Animal(Reserva &reserva, char typeAnimal, int health, int weight, int duration, int x, int y) :
        reserva(reserva), tipoAnimal(typeAnimal), idA(Reserva::getNextId()), saude(health), peso(weight),
        duracao(duration),
        fome(0), linha(x), coluna(y), historico(nullptr) {}


//coloquei o const
int Animal::getIdAnimal() const {
    return idA;
}

int Animal::getSaudeAnimal() const {
    return saude;
}

char Animal::getTipoAnimal() const {
    return tipoAnimal;
}

int Animal::getPesoAnimal() const {
    return peso;
}

int Animal::getDuracao() const {
    return duracao;
}

int Animal::getFomeAnimal() const {
    return fome;
}

int Animal::getLinhaAnimal() const {
    return linha;
}

int Animal::getColunaAnimal() const {
    return coluna;
}

void Animal::setLinhaAnimal(int linhanova) {
    linha = linhanova;
}

void Animal::setColunaAnimal(int novaColuna) {
    coluna = novaColuna;
}

void Animal::setPesoAnimal(int novoPeso) {
    peso = novoPeso;
}

void Animal::diminuiSaude(int toxicidade) {
    saude -= toxicidade;
}

void Animal::aumentaSaude(int vNutritivo) {
    saude += vNutritivo;
}

void Animal::diminuiDuracao() {
    duracao--;
}

void Animal::aumentaFome(int n) {
    fome = fome + n;
}


void Animal::diminuiSaudeA(int n) {
    saude = saude - n;
}


int Animal::randomPesoC() {
    srand((unsigned) time(nullptr));
    return (rand() % 4) + 1;//bug 0 de peso
}

int Animal::randomPesoO() {
    srand((unsigned) time(nullptr));
    return 4 + rand() % (8 - 4 + 1);   //para obter um valor entre 4 e 8
}

HistoricoAlimentacao *Animal::getHistoricoAlimentacao() {
    return historico;
}

HistoricoAlimentacao::HistoricoAlimentacao(string nome, int valorNutritivo, int valorToxicidade) : nome(nome),
                                                                                                   valorNutritivo(
                                                                                                           valorNutritivo),
                                                                                                   toxicidade(
                                                                                                           valorToxicidade),
                                                                                                   proximo(nullptr) {}


HistoricoAlimentacao *HistoricoAlimentacao::getProximo() const {
    return proximo;
}

void HistoricoAlimentacao::setProximo(HistoricoAlimentacao *proximo) {
    this->proximo = proximo;
}

string HistoricoAlimentacao::toString() const {
    ostringstream oss;

    oss << "Nome: " << nome << ", com valor nutritivo " << valorNutritivo << " e com toxicidade " << toxicidade << endl;

    return oss.str();
}

void Animal::adicionaAlimentoHistorico(string nome, int valorNutritivo, int valorToxicidade) {
    HistoricoAlimentacao *novoHistorico = new HistoricoAlimentacao(nome, valorNutritivo, valorToxicidade);
    HistoricoAlimentacao *aux = getHistoricoAlimentacao();
    if (aux == nullptr) {
        setHistorico(novoHistorico);
    } else {
        while (aux->getProximo() != nullptr) {
            aux = aux->getProximo();
        }
        aux->setProximo(novoHistorico);
    }
}


Animal::~Animal() = default;


Coelho::Coelho(Reserva &reserva, int x, int y) : Animal(reserva, 'C', InicioJogo::getCoelhoSaude(), randomPesoC(),
                                                        InicioJogo::getCoelhoVida(), x, y) {}

Coelho::~Coelho() = default;

void Coelho::avancaInstante() {
    if (isJaAvancouInstante())
        return;
    setJaAvancouInstante(true);
    diminuiDuracao();
    if (verificamorreAnimal()) {
        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAnimal(getIdAnimal(), true);//morte natural
        return;
    }


    if ((InicioJogo::getCoelhoVida() - getDuracao()) % 8 == 0) {
        int random = 1 + rand() % (2 - 1 + 1);
        if (random == 1) {
            int linha = -10 + rand() % (10 - (-10) + 1);
            int coluna = -10 + rand() % (10 - (-10) + 1);

            if (linha < 0)
                linha += reserva.getNLinhas();
            if (coluna < 0)
                coluna += reserva.getNColunas();
            if (linha >= reserva.getNLinhas())
                linha -= reserva.getNLinhas();
            if (coluna >= reserva.getNColunas())
                coluna -= reserva.getNColunas();

            reserva.adicionaAnimal(new Coelho(reserva, linha, coluna), linha, coluna);
        }
    }

    Alimento *alimento = reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->getAlimento();
    bool comeu = false;
    if (alimento != nullptr) {
        for (auto cheiro:alimento->getCheiro()) {
            if (cheiro == "verdura") {
                aumentaSaude(alimento->getvalorNutritivo());
                diminuiSaude(alimento->getToxicidade());
                adicionaAlimentoHistorico(alimento->getNomeAlimento(), alimento->getvalorNutritivo(),
                                          alimento->getToxicidade());
                reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAlimento();


                comeu = true;
                break;
            }
        }
    }
    if (!comeu) {
        for (int i = -4; i < 4; i++) {
            for (int j = -4; j < 4; j++) {
                int linha = (getLinhaAnimal() + i) % reserva.getNLinhas();
                int coluna = (getColunaAnimal() + j) % reserva.getNColunas();

                if (linha < 0)
                    linha += reserva.getNLinhas();
                if (coluna < 0)
                    coluna += reserva.getNColunas();
                if (linha >= reserva.getNLinhas())
                    linha -= reserva.getNLinhas();
                if (coluna >= reserva.getNColunas())
                    coluna -= reserva.getNColunas();

                alimento = reserva.getZonas()[linha][coluna]->getAlimento();
                if (alimento != nullptr) {
                    for (auto cheiro:alimento->getCheiro())
                        if (cheiro == "verdura") {
                            reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAnimal(getIdAnimal(), false);
                            setLinhaAnimal(linha);
                            setColunaAnimal(coluna);
                            reserva.getZonas()[linha][coluna]->adicionaAnimal(this);
                            return;
                        }
                }
            }
        }
    }

    //Animal com mais de 10k
    vector<Animal *> animais = reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->getAnimais();

    for (int i = -4; i < 4; i++) {
        for (int j = -4; j < 4; j++) {
            int linha1 = (getLinhaAnimal() + i) % reserva.getNLinhas();
            int coluna1 = (getColunaAnimal() + j) % reserva.getNColunas();

            if (linha1 < 0)
                linha1 += reserva.getNLinhas();
            if (coluna1 < 0)
                coluna1 += reserva.getNColunas();
            if (linha1 >= reserva.getNLinhas())
                linha1 -= reserva.getNLinhas();
            if (coluna1 >= reserva.getNColunas())
                coluna1 -= reserva.getNColunas();

            animais = reserva.getZonas()[linha1][coluna1]->getAnimais();
            for (auto animal: animais)
                if (animal->getPesoAnimal() > 10) {

                    int calculoLinhas = getLinhaAnimal() - animal->getLinhaAnimal();
                    int calculoColunas = getColunaAnimal() - animal->getColunaAnimal();

                    reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAnimal(getIdAnimal(), false);
                    setLinhaAnimal(getLinhaAnimal() + calculoLinhas);
                    setColunaAnimal(getColunaAnimal() + calculoColunas);

                    if (getLinhaAnimal() < 0)
                        setLinhaAnimal(getLinhaAnimal() + reserva.getNLinhas());
                    if (getColunaAnimal() < 0)
                        setColunaAnimal(getColunaAnimal() + reserva.getNColunas());
                    if (getLinhaAnimal() >= reserva.getNLinhas())
                        setLinhaAnimal(getLinhaAnimal() - reserva.getNLinhas());
                    if (getColunaAnimal() >= reserva.getNColunas())
                        setColunaAnimal(getColunaAnimal() - reserva.getNColunas());

                    reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->adicionaAnimal(this);
                    return;
                }

        }
    }


    if (getFomeAnimal() <= 10) {

        aumentaFome(1);

        int numRandColuna;
        int numRandLinha;
        do {
            numRandColuna = -2 + rand() % (2 - (-2) + 1);
        } while (numRandColuna == 0);

        do {
            numRandLinha = -2 + rand() % (2 - (-2) + 1);
        } while (numRandLinha == 0);


        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAnimal(getIdAnimal(), false);
        setLinhaAnimal((getLinhaAnimal() + numRandLinha) % reserva.getNLinhas());
        setColunaAnimal((getColunaAnimal() + numRandColuna) % reserva.getNColunas());

        if (getLinhaAnimal() < 0) {
            setLinhaAnimal(getLinhaAnimal() + reserva.getNLinhas());
        }
        if (getColunaAnimal() < 0) {
            setColunaAnimal(getColunaAnimal() + reserva.getNColunas());
        }

        if (getLinhaAnimal() >= reserva.getNLinhas())
            setLinhaAnimal(getLinhaAnimal() - reserva.getNLinhas());

        if (getColunaAnimal() >= reserva.getNColunas())
            setColunaAnimal(getColunaAnimal() - reserva.getNColunas());

        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->adicionaAnimal(this);

    } else if (getFomeAnimal() > 10 && getFomeAnimal() <= 20) {
        aumentaFome(1);
        diminuiSaudeA(1);

        int numRandColuna;
        int numRandLinha;
        do {
            numRandColuna = -3 + rand() % (3 - (-3) + 1);
        } while (numRandColuna == 0);

        do {
            numRandLinha = -3 + rand() % (3 - (-3) + 1);
        } while (numRandLinha == 0);

        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAnimal(getIdAnimal(), false);
        setLinhaAnimal((getLinhaAnimal() + numRandLinha) % reserva.getNLinhas());
        setColunaAnimal((getColunaAnimal() + numRandColuna) % reserva.getNColunas());

        if (getLinhaAnimal() < 0) {
            setLinhaAnimal(getLinhaAnimal() + reserva.getNLinhas());
        }
        if (getColunaAnimal() < 0) {
            setColunaAnimal(getColunaAnimal() + reserva.getNColunas());
        }

        if (getLinhaAnimal() >= reserva.getNLinhas())
            setLinhaAnimal(getLinhaAnimal() - reserva.getNLinhas());

        if (getColunaAnimal() >= reserva.getNColunas())
            setColunaAnimal(getColunaAnimal() - reserva.getNColunas());


        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->adicionaAnimal(this);

    } else {
        aumentaFome(1);
        diminuiSaudeA(2);

        int numRandColuna;
        int numRandLinha;
        do {
            numRandColuna = -4 + rand() % (4 - (-4) + 1);
        } while (numRandColuna == 0);

        do {
            numRandLinha = -4 + rand() % (4 - (-4) + 1);
        } while (numRandLinha == 0);

        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAnimal(getIdAnimal(), false);
        setLinhaAnimal((getLinhaAnimal() + numRandLinha) % reserva.getNLinhas());
        setColunaAnimal((getColunaAnimal() + numRandColuna) % reserva.getNColunas());

        if (getLinhaAnimal() < 0) {
            setLinhaAnimal(getLinhaAnimal() + reserva.getNLinhas());
        }
        if (getColunaAnimal() < 0) {
            setColunaAnimal(getColunaAnimal() + reserva.getNColunas());
        }

        if (getLinhaAnimal() >= reserva.getNLinhas())
            setLinhaAnimal(getLinhaAnimal() - reserva.getNLinhas());

        if (getColunaAnimal() >= reserva.getNColunas())
            setColunaAnimal(getColunaAnimal() - reserva.getNColunas());


        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->adicionaAnimal(this);
    }
    if (verificamorreAnimal()) {
        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAnimal(getIdAnimal(), true);//morte natural
        return;
    }
}


void Coelho::morreAnimal() {
}

bool Coelho::verificamorreAnimal() {
    if (getSaudeAnimal() <= 0 || getDuracao() <= 0) {
        return true;
    }
    return false;
}


Ovelha::Ovelha(Reserva &reserva, int x, int y) : Animal(reserva, 'O', InicioJogo::getOvelhaSaude(), randomPesoO(),
                                                        InicioJogo::getOvelhaVida(), x, y) {}

Ovelha::~Ovelha() = default;

void Ovelha::avancaInstante() {

    if (isJaAvancouInstante())
        return;
    setJaAvancouInstante(true);
    diminuiDuracao();
    if (verificamorreAnimal()) {
        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAnimal(getIdAnimal(), true);//morte natural
        return;
    }

    if ((InicioJogo::getOvelhaVida() - getDuracao()) % 15 == 0) { //15 instantes
        int linha = -12 + rand() % (12 - (-12) + 1);
        int coluna = -12 + rand() % (12 - (-12) + 1);

        if (linha < 0)
            linha += reserva.getNLinhas();
        if (coluna < 0)
            coluna += reserva.getNColunas();
        if (linha >= reserva.getNLinhas())
            linha -= reserva.getNLinhas();
        if (coluna >= reserva.getNColunas())
            coluna -= reserva.getNColunas();

        int saudeOvelha = InicioJogo::getOvelhaSaude();

        reserva.adicionaAnimal(new Ovelha(reserva, linha, coluna), linha, coluna);
        InicioJogo::setOvelhaSaude(saudeOvelha);
    }

    Alimento *alimento = reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->getAlimento();
    bool comeu = false;
    if (alimento != nullptr) {
        for (auto cheiro:alimento->getCheiro())

            if (cheiro == "erva") {
                aumentaSaude(alimento->getvalorNutritivo());
                diminuiSaude(alimento->getToxicidade());
                adicionaAlimentoHistorico(alimento->getNomeAlimento(), alimento->getvalorNutritivo(),
                                          alimento->getToxicidade());
                reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAlimento();

                comeu = true;
                break;
            }
    }

    if (!comeu) {
        for (int i = -4; i < 4; i++) {
            for (int j = -4; j < 4; j++) {
                int linha = (getLinhaAnimal() + i) % reserva.getNLinhas();
                int coluna = (getColunaAnimal() + j) % reserva.getNColunas();

                if (linha < 0)
                    linha += reserva.getNLinhas();
                if (coluna < 0)
                    coluna += reserva.getNColunas();
                if (linha >= reserva.getNLinhas())
                    linha -= reserva.getNLinhas();
                if (coluna >= reserva.getNColunas())
                    coluna -= reserva.getNColunas();

                alimento = reserva.getZonas()[linha][coluna]->getAlimento();
                if (alimento != nullptr) {
                    for (auto cheiro:alimento->getCheiro())
                        if (cheiro == "erva") {
                            reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAnimal(getIdAnimal(), false);
                            setLinhaAnimal(linha);
                            setColunaAnimal(coluna);
                            reserva.getZonas()[linha][coluna]->adicionaAnimal(this);
                            return;
                        }
                }
            }
        }
    }

    //Animal com mais de 15k
    vector<Animal *> animais = reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->getAnimais();

    for (int i = -3; i < 3; i++) {
        for (int j = -3; j < 3; j++) {
            int linha1 = (getLinhaAnimal() + i) % reserva.getNLinhas();
            int coluna1 = (getColunaAnimal() + j) % reserva.getNColunas();

            if (linha1 < 0)
                linha1 += reserva.getNLinhas();
            if (coluna1 < 0)
                coluna1 += reserva.getNColunas();
            if (linha1 >= reserva.getNLinhas())
                linha1 -= reserva.getNLinhas();
            if (coluna1 >= reserva.getNColunas())
                coluna1 -= reserva.getNColunas();

            animais = reserva.getZonas()[linha1][coluna1]->getAnimais();
            for (auto animal: animais)
                if (animal->getPesoAnimal() > 15) {

                    int calculoLinhas = getLinhaAnimal() - animal->getLinhaAnimal();
                    int calculoColunas = getColunaAnimal() - animal->getColunaAnimal();

                    reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAnimal(getIdAnimal(), false);
                    setLinhaAnimal(getLinhaAnimal() + calculoLinhas);
                    setColunaAnimal(getColunaAnimal() + calculoColunas);

                    if (getLinhaAnimal() < 0)
                        setLinhaAnimal(getLinhaAnimal() + reserva.getNLinhas());
                    if (getColunaAnimal() < 0)
                        setColunaAnimal(getColunaAnimal() + reserva.getNColunas());
                    if (getLinhaAnimal() >= reserva.getNLinhas())
                        setLinhaAnimal(getLinhaAnimal() - reserva.getNLinhas());
                    if (getColunaAnimal() >= reserva.getNColunas())
                        setColunaAnimal(getColunaAnimal() - reserva.getNColunas());

                    reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->adicionaAnimal(this);
                    return;
                }

        }
    }

    if (getFomeAnimal() <= 15) {

        aumentaFome(1);

        int quantos;
        int direcao;
        do {
            quantos = -1 + rand() % (1 - (-1) + 1);
        } while (quantos == 0);

        direcao = rand() % (1 + 1);

        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAnimal(getIdAnimal(), false);
        if (direcao == 0) {
            setLinhaAnimal((getLinhaAnimal() + quantos) % reserva.getNLinhas());
        } else {
            setColunaAnimal((getColunaAnimal() + quantos) % reserva.getNColunas());
        }

        if (getLinhaAnimal() < 0) {
            setLinhaAnimal(getLinhaAnimal() + reserva.getNLinhas());
        }
        if (getColunaAnimal() < 0) {
            setColunaAnimal(getColunaAnimal() + reserva.getNColunas());
        }

        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->adicionaAnimal(this);

    } else if (getFomeAnimal() > 15 && getFomeAnimal() <= 20) {
        diminuiSaudeA(1);
        aumentaFome(1);

        int numRandColuna;
        int numRandLinha;
        do {
            numRandColuna = -2 + rand() % (2 - (-2) + 1);
        } while (numRandColuna == 0);

        do {
            numRandLinha = -2 + rand() % (2 - (-2) + 1);
        } while (numRandLinha == 0);

        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAnimal(getIdAnimal(), false);
        setLinhaAnimal((getLinhaAnimal() + numRandLinha) % reserva.getNLinhas());
        setColunaAnimal((getColunaAnimal() + numRandColuna) % reserva.getNColunas());

        if (getLinhaAnimal() < 0) {
            setLinhaAnimal(getLinhaAnimal() + reserva.getNLinhas());
        }
        if (getColunaAnimal() < 0) {
            setColunaAnimal(getColunaAnimal() + reserva.getNColunas());
        }

        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->adicionaAnimal(this);

    } else {
        diminuiSaudeA(2);
        aumentaFome(1);

        int numRandColuna;
        int numRandLinha;
        do {
            numRandColuna = -2 + rand() % (2 - (-2) + 1);
        } while (numRandColuna == 0);

        do {
            numRandLinha = -2 + rand() % (2 - (-2) + 1);
        } while (numRandLinha == 0);

        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAnimal(getIdAnimal(), false);
        setLinhaAnimal((getLinhaAnimal() + numRandLinha) % reserva.getNLinhas());
        setColunaAnimal((getColunaAnimal() + numRandColuna) % reserva.getNColunas());

        if (getLinhaAnimal() < 0) {
            setLinhaAnimal(getLinhaAnimal() + reserva.getNLinhas());
        }
        if (getColunaAnimal() < 0) {
            setColunaAnimal(getColunaAnimal() + reserva.getNColunas());
        }
        if (getLinhaAnimal() >= reserva.getNLinhas())
            setLinhaAnimal(getLinhaAnimal() + reserva.getNLinhas());
        if (getColunaAnimal() >= reserva.getNColunas())
            setColunaAnimal(getColunaAnimal() + reserva.getNColunas());

        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->adicionaAnimal(this);
    }
    if (verificamorreAnimal()) {
        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAnimal(getIdAnimal(), true);//morte natural
        return;
    }
}

void Ovelha::morreAnimal() {

    int numRandColuna;
    int numRandLinha;
    int numTentativas = 16;

    do {
        numRandColuna = -1 + rand() % (1 - (-1) + 1);
        numRandLinha = -1 + rand() % (1 - (-1) + 1);


        numRandLinha += getLinhaAnimal();
        numRandColuna += getColunaAnimal();

        if (numRandLinha < 0) {
            numRandLinha += reserva.getNLinhas();
        }
        if (numRandColuna < 0) {
            numRandColuna += reserva.getNColunas();
        }

        if (numRandLinha >= reserva.getNLinhas())
            numRandLinha -= reserva.getNLinhas();

        if (numRandColuna >= reserva.getNColunas())
            numRandColuna -= reserva.getNColunas();

        numTentativas--;
    } while (
            reserva.getZonas()[numRandLinha][numRandColuna]->getAlimento() !=
            nullptr && numTentativas > 0);

    if (numTentativas > 0) {
        reserva.getZonas()[numRandLinha][numRandColuna]->colocaAlimento(
                new Corpo(numRandLinha, numRandColuna, getPesoAnimal(), 0));
    }

}

bool Ovelha::verificamorreAnimal() {
    if (getDuracao() <= 0 || getSaudeAnimal() <= 0) {
        return true;
    }
    return false;
}

Lobo::Lobo(Reserva &reserva, int x, int y) : Animal(reserva, 'L', InicioJogo::getLoboSaude(), InicioJogo::getLoboPeso(),
                                                    InicioJogo::getLoboVida(), x, y) {}

Lobo::~Lobo() = default;

void Lobo::geraInstanteNascimento() {
    instanteNascimento = 5 + rand() % (40 - 5 + 1);
    gerouFilho = true;
}


void Lobo::avancaInstante() {
    if (isJaAvancouInstante())
        return;
    setJaAvancouInstante(true);

    diminuiDuracao();
    if (verificamorreAnimal()) {
        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAnimal(getIdAnimal(), true);//morte natural
        return;
    }

    if (gerouFilho == false) {
        geraInstanteNascimento();
    }
    if (getDuracao() - (40 - instanteNascimento) == 0) {
        int linha = -15 + rand() % (15 - (-15) + 1);
        int coluna = -15 + rand() % (15 - (-15) + 1);

        if (linha < 0)
            linha += reserva.getNLinhas();
        if (coluna < 0)
            coluna += reserva.getNColunas();
        if (linha >= reserva.getNLinhas())
            linha -= reserva.getNLinhas();
        if (coluna >= reserva.getNColunas())
            coluna -= reserva.getNColunas();

        reserva.adicionaAnimal(new Lobo(reserva, linha, coluna), linha, coluna);
    }


    Alimento *alimento = reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->getAlimento();
    bool comeu = false;
    if (alimento != nullptr) {
        for (auto cheiro:alimento->getCheiro())

            if (cheiro == "carne") {
                aumentaSaude(alimento->getvalorNutritivo());
                diminuiSaude(alimento->getToxicidade());
                adicionaAlimentoHistorico(alimento->getNomeAlimento(), alimento->getvalorNutritivo(),
                                          alimento->getToxicidade());
                reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAlimento();

                comeu = true;
                break;
            }
    }

    if (!comeu) {
        for (int i = -5; i < 5; i++) {
            for (int j = -5; j < 5; j++) {
                int linha = (getLinhaAnimal() + i) % reserva.getNLinhas();
                int coluna = (getColunaAnimal() + j) % reserva.getNColunas();


                if (linha < 0)
                    linha += reserva.getNLinhas();
                if (coluna < 0)
                    coluna += reserva.getNColunas();
                if (linha >= reserva.getNLinhas())
                    linha -= reserva.getNLinhas();
                if (coluna >= reserva.getNColunas())
                    coluna -= reserva.getNColunas();

                alimento = reserva.getZonas()[linha][coluna]->getAlimento();
                if (alimento != nullptr) {
                    for (auto cheiro:alimento->getCheiro())
                        if (cheiro == "carne") {
                            reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAnimal(getIdAnimal(), false);
                            setLinhaAnimal(linha);
                            setColunaAnimal(coluna);
                            reserva.getZonas()[linha][coluna]->adicionaAnimal(this);
                            return;
                        }
                }
            }
        }
    }


    //Mata animal que pesa menos
    vector<Animal *> animais = reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->getAnimais();
    bool matou = false;
    for (int i = -1; i < 1; i++) {
        for (int j = -1; j < 1; j++) {
            int linha = (getLinhaAnimal() + i) % reserva.getNLinhas();
            int coluna = (getColunaAnimal() + j) % reserva.getNColunas();

            if (linha < 0)
                linha += reserva.getNLinhas();
            if (coluna < 0)
                coluna += reserva.getNColunas();

            if (linha >= reserva.getNLinhas())
                linha -= reserva.getNLinhas();
            if (coluna >= reserva.getNColunas())
                coluna -= reserva.getNColunas();

            animais = reserva.getZonas()[linha][coluna]->getAnimais();
            for (auto animal: animais) {
                if (animal == this)
                    continue;
                if (animal->getPesoAnimal() < getPesoAnimal()) {
                    reserva.getZonas()[animal->getLinhaAnimal()][animal->getColunaAnimal()]->removeAnimal(
                            animal->getIdAnimal(), true);
                    matou = true;
                } else {

                    srand((unsigned) time(nullptr));
                    //morre aleatoriamente
                    int valor = 1 + rand() % (2 - 1 + 1);   //para obter um valor entre 1 e 2
                    if (animal->getTipoAnimal() == 'G') {
                        reserva.getZonas()[animal->getLinhaAnimal()][animal->getColunaAnimal()]->removeAnimal(
                                animal->getIdAnimal(), true);
                        matou = true;
                    } else if (valor == 1) {
                        reserva.getZonas()[animal->getLinhaAnimal()][animal->getColunaAnimal()]->removeAnimal(
                                animal->getIdAnimal(), true);
                        matou = true;
                    } else {
                        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAnimal(
                                getIdAnimal(), true);
                        return;
                    }

                }
                if (matou)
                    break;
            }
            if (matou)
                break;
        }
        if (matou)
            break;
    }


    Animal *maisPesado = nullptr;

    if (!matou) {
        for (int i = -5; i < 5; i++) {
            for (int j = -5; j < 5; j++) {
                int linha = (getLinhaAnimal() + i) % reserva.getNLinhas();
                int coluna = (getColunaAnimal() + j) % reserva.getNColunas();

                if (linha < 0)
                    linha += reserva.getNLinhas();
                if (coluna < 0)
                    coluna += reserva.getNColunas();

                if (linha >= reserva.getNLinhas())
                    linha -= reserva.getNLinhas();
                if (coluna >= reserva.getNColunas())
                    coluna -= reserva.getNColunas();

                animais = reserva.getZonas()[linha][coluna]->getAnimais();
                for (Animal *animal: animais) {
                    if (animal == this)
                        continue;
                    if (maisPesado == nullptr)
                        maisPesado = animal;
                    else if (maisPesado->getPesoAnimal() < animal->getPesoAnimal()) {
                        maisPesado = animal;
                    }
                }
            }
        }
        if (maisPesado != nullptr) {
            int calculaLinhas = maisPesado->getLinhaAnimal() - getLinhaAnimal();
            int calculaColunas = maisPesado->getColunaAnimal() - getColunaAnimal();
            int distancia = 2;

            if (getFomeAnimal() > 15)
                distancia = 3;

            if (calculaLinhas > distancia) {
                calculaLinhas = distancia;
            } else if (calculaLinhas < -distancia) {
                calculaLinhas = -distancia;
            }

            if (calculaColunas > distancia) {
                calculaColunas = distancia;
            } else if (calculaColunas < -distancia) {
                calculaColunas = -distancia;
            }

            calculaLinhas += getLinhaAnimal();
            calculaColunas += getColunaAnimal();
            if (calculaLinhas < 0) {
                calculaLinhas += reserva.getNLinhas();
            }
            if (calculaColunas < 0) {
                calculaColunas += reserva.getNColunas();
            }

            if (calculaLinhas >= reserva.getNLinhas())
                calculaLinhas -= reserva.getNLinhas();

            if (calculaColunas >= reserva.getNColunas())
                calculaColunas -= reserva.getNColunas();

            reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAnimal(getIdAnimal(), false);
            setLinhaAnimal(calculaLinhas);
            setColunaAnimal(calculaColunas);
            reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->adicionaAnimal(this);
            return;
        }
    }

    if (getFomeAnimal() <= 15) {
        aumentaFome(2);
        int quantos;
        int direcao;
        do {
            quantos = -1 + rand() % (1 - (-1) + 1);
        } while (quantos == 0);

        direcao = rand() % (1 + 1);

        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAnimal(getIdAnimal(), false);
        if (direcao == 0) {
            setLinhaAnimal((getLinhaAnimal() + quantos) % reserva.getNLinhas());
        } else {
            setColunaAnimal((getColunaAnimal() + quantos) % reserva.getNColunas());
        }

        if (getLinhaAnimal() < 0) {
            setLinhaAnimal(getLinhaAnimal() + reserva.getNLinhas());
        }
        if (getColunaAnimal() < 0) {
            setColunaAnimal(getColunaAnimal() + reserva.getNColunas());
        }

        if (getLinhaAnimal() >= reserva.getNLinhas())
            setLinhaAnimal(getLinhaAnimal() - reserva.getNLinhas());

        if (getColunaAnimal() >= reserva.getNColunas())
            setColunaAnimal(getColunaAnimal() - reserva.getNColunas());

        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->adicionaAnimal(this);

    } else if (getFomeAnimal() > 15 && getFomeAnimal() <= 25) {
        aumentaFome(2);
        diminuiSaudeA(1);

        int numRandColuna;
        int numRandLinha;
        do {
            numRandColuna = -2 + rand() % (2 - (-2) + 1);
        } while (numRandColuna == 0);

        do {
            numRandLinha = -2 + rand() % (2 - (-2) + 1);
        } while (numRandLinha == 0);

        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAnimal(getIdAnimal(), false);
        setLinhaAnimal((getLinhaAnimal() + numRandLinha) % reserva.getNLinhas());
        setColunaAnimal((getColunaAnimal() + numRandColuna) % reserva.getNColunas());

        if (getLinhaAnimal() < 0) {
            setLinhaAnimal(getLinhaAnimal() + reserva.getNLinhas());
        }
        if (getColunaAnimal() < 0) {
            setColunaAnimal(getColunaAnimal() + reserva.getNColunas());
        }

        if (getLinhaAnimal() >= reserva.getNLinhas())
            setLinhaAnimal(getLinhaAnimal() - reserva.getNLinhas());

        if (getColunaAnimal() >= reserva.getNColunas())
            setColunaAnimal(getColunaAnimal() - reserva.getNColunas());

        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->adicionaAnimal(this);

    } else {
        aumentaFome(2);
        diminuiSaudeA(2);

        int numRandColuna;
        int numRandLinha;
        do {
            numRandColuna = -2 + rand() % (2 - (-2) + 1);
        } while (numRandColuna == 0);

        do {
            numRandLinha = -2 + rand() % (2 - (-2) + 1);
        } while (numRandLinha == 0);

        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAnimal(getIdAnimal(), false);
        setLinhaAnimal((getLinhaAnimal() + numRandLinha) % reserva.getNLinhas());
        setColunaAnimal((getColunaAnimal() + numRandColuna) % reserva.getNColunas());

        if (getLinhaAnimal() < 0) {
            setLinhaAnimal(getLinhaAnimal() + reserva.getNLinhas());
        }
        if (getColunaAnimal() < 0) {
            setColunaAnimal(getColunaAnimal() + reserva.getNColunas());
        }

        if (getLinhaAnimal() >= reserva.getNLinhas())
            setLinhaAnimal(getLinhaAnimal() - reserva.getNLinhas());

        if (getColunaAnimal() >= reserva.getNColunas())
            setColunaAnimal(getColunaAnimal() - reserva.getNColunas());


        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->adicionaAnimal(this);
    }
    if (verificamorreAnimal()) {
        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAnimal(getIdAnimal(), true);//morte natural
        return;
    }
}


void Lobo::morreAnimal() {

    int numRandColuna;
    int numRandLinha;
    int numTentativas = 64;

    do {
        do {
            numRandColuna = -1 + rand() % (1 - (-1) + 1);
        } while (numRandColuna == 0);

        do {
            numRandLinha = -1 + rand() % (1 - (-1) + 1);
        } while (numRandLinha == 0);

        if (numRandLinha < 0) {
            numRandLinha += reserva.getNLinhas();
        }
        if (numRandColuna < 0) {
            numRandColuna += reserva.getNColunas();
        }

        if (numRandLinha >= reserva.getNLinhas())
            numRandLinha -= reserva.getNLinhas();

        if (numRandColuna >= reserva.getNColunas())
            numRandColuna -= reserva.getNColunas();


        numTentativas--;
    } while (
            reserva.getZonas()[numRandLinha][numRandColuna]->getAlimento() !=
            nullptr && numTentativas > 0);

    reserva.getZonas()[numRandLinha][numRandColuna]->colocaAlimento(
            new Corpo(getLinhaAnimal() + numRandLinha, getColunaAnimal() + numRandColuna, 10, 0));
}


bool Lobo::verificamorreAnimal() {
    if (getSaudeAnimal() <= 0) {
        return true;
    }
    return false;
}

Canguru::Canguru(Reserva &reserva, int x, int y, Canguru *progenitor) : Animal(reserva, 'G',
                                                                               InicioJogo::getCanguruSaude(),
                                                                               InicioJogo::getCanguruPeso(),
                                                                               InicioJogo::getCanguruVida(), x,
                                                                               y), progenitor(progenitor) {}

Canguru::~Canguru() = default;


Canguru *Canguru::getProgenitor() const {
    return progenitor;
}

void Canguru::adicionaCanguruBolsa(Canguru *canguru) {
    bolsa.emplace_back(canguru);
}

int Canguru::getTempoNaBolsa() const {
    return tempoNaBolsa;
}

void Canguru::setTempoNaBolsa(int novoTempo) {
    tempoNaBolsa = novoTempo;
}

void Canguru::avancaInstante() {
    if (isJaAvancouInstante())
        return;
    setJaAvancouInstante(true);
    diminuiDuracao();


    if (verificamorreAnimal()) {
        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAnimal(getIdAnimal(), true);//morte natural
        return;
    }

    for (int i = 0; i < bolsa.size(); i++) {
        Canguru *filho = bolsa[i];
        filho->setTempoNaBolsa(filho->getTempoNaBolsa() + 1);

        if (filho->getTempoNaBolsa() == 5) {
            // Adiciona o canguru de volta a reserva
            bolsa.erase(bolsa.begin() + i);
            reserva.adicionaAnimal(filho, getLinhaAnimal(), getColunaAnimal());
            filho->setTempoNaBolsa(0);
            i--;
        }
    }

    if (getDuracao() == (InicioJogo::getCanguruVida() - 20)) {
        setPesoAnimal(20);
    }

    // faz nascer canguru
    if ((InicioJogo::getCanguruVida() - getDuracao()) % 30 == 0) {
        int linha = -3 + rand() % (3 - (-3) + 1);
        int coluna = -3 + rand() % (3 - (-3) + 1);

        linha += getLinhaAnimal();
        coluna += getColunaAnimal();
        if (linha < 0)
            linha += reserva.getNLinhas();
        if (coluna < 0)
            coluna += reserva.getNColunas();
        if (linha >= reserva.getNLinhas())
            linha -= reserva.getNLinhas();
        if (coluna >= reserva.getNColunas())
            coluna -= reserva.getNColunas();


        reserva.adicionaAnimal(new Canguru(reserva, linha, coluna, this), linha, coluna);
    }

    bool outroAnimal = false;
    for (int i = -7; i < 7; i++) {
        for (int j = -7; j < 7; j++) {

            int linha = getLinhaAnimal() + i;
            int coluna = getColunaAnimal() + j;

            if (linha < 0)
                linha += reserva.getNLinhas();
            if (coluna < 0)
                coluna += reserva.getNColunas();
            if (linha >= reserva.getNLinhas())
                linha -= reserva.getNLinhas();
            if (coluna >= reserva.getNColunas())
                coluna -= reserva.getNColunas();

            for (auto animal: reserva.getZonas()[linha][coluna]->getAnimais()) {
                if (animal != this && animal != getProgenitor()) {
                    outroAnimal = true;
                    break;
                }
            }
            if (outroAnimal) {
                break;
            }
        }
        if (outroAnimal) {
            break;
        }
    }

    if (InicioJogo::getCanguruVida() - getDuracao() < 10 && outroAnimal && progenitor!= nullptr) {
// Obtém a posição do progenitor
        int calculaLinhas = progenitor->getLinhaAnimal() - getLinhaAnimal();
        int calculaColunas = progenitor->getColunaAnimal() - getColunaAnimal();
        int distancia = 2;

        if ((calculaLinhas >= 0 && calculaLinhas < distancia || calculaLinhas <= 0 && calculaLinhas > -distancia)
            &&
            (calculaColunas >= 0 && calculaColunas < distancia || calculaColunas <= 0 && calculaColunas > -distancia)) {
            reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAnimal(getIdAnimal(), false);
            progenitor->adicionaCanguruBolsa(this);
            tempoNaBolsa = 0;
            return;
        }
        if (calculaLinhas > distancia) {
            calculaLinhas = distancia;
        } else if (calculaLinhas < -distancia) {
            calculaLinhas = -distancia;
        }

        if (calculaColunas > distancia) {
            calculaColunas = distancia;
        } else if (calculaColunas < -distancia) {
            calculaColunas = -distancia;
        }

        calculaLinhas += getLinhaAnimal();
        calculaColunas += getColunaAnimal();
        if (calculaLinhas < 0) {
            calculaLinhas += reserva.getNLinhas();
        }
        if (calculaColunas < 0) {
            calculaColunas += reserva.getNColunas();
        }

        if (calculaLinhas >= reserva.getNLinhas())
            calculaLinhas -= reserva.getNLinhas();

        if (calculaColunas >= reserva.getNColunas())
            calculaColunas -= reserva.getNColunas();

        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAnimal(getIdAnimal(), false);
        setLinhaAnimal(calculaLinhas);
        setColunaAnimal(calculaColunas);
        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->adicionaAnimal(this);
        return;
    } else if (InicioJogo::getCanguruVida() - getDuracao() < 10 && progenitor!= nullptr ) { //alterei este original (InicioJogo::getCanguruVida() - getDuracao() < 10)
        int calculaLinhas = progenitor->getLinhaAnimal() - getLinhaAnimal();
        int calculaColunas = progenitor->getColunaAnimal() - getColunaAnimal();
        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAnimal(getIdAnimal(), false);
        do {
            int linha = rand() % reserva.getNLinhas();
            int coluna = rand() % reserva.getNColunas();

            if (abs(linha - progenitor->getLinhaAnimal()) < 4 && abs(coluna - progenitor->getColunaAnimal()) < 4) {
                setLinhaAnimal(linha);
                setColunaAnimal(coluna);
                break;
            }
        } while (true);
        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->adicionaAnimal(this);

    } else {
        int quantos;
        int direcao;
        do {
            quantos = -1 + rand() % (1 - (-1) + 1);
        } while (quantos == 0);

        direcao = rand() % (1 + 1);

        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAnimal(getIdAnimal(), false);
        if (direcao == 0) {
            setLinhaAnimal((getLinhaAnimal() + quantos) % reserva.getNLinhas());
        } else {
            setColunaAnimal((getColunaAnimal() + quantos) % reserva.getNColunas());
        }

        if (getLinhaAnimal() < 0) {
            setLinhaAnimal(getLinhaAnimal() + reserva.getNLinhas());
        }
        if (getColunaAnimal() < 0) {
            setColunaAnimal(getColunaAnimal() + reserva.getNColunas());
        }

        if (getLinhaAnimal() >= reserva.getNLinhas())
            setLinhaAnimal(getLinhaAnimal() - reserva.getNLinhas());

        if (getColunaAnimal() >= reserva.getNColunas())
            setColunaAnimal(getColunaAnimal() - reserva.getNColunas());

        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->adicionaAnimal(this);
    }
    if (verificamorreAnimal()) {
        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAnimal(getIdAnimal(), true);//morte natural
        return;
    }
}

void Canguru::morreAnimal() {

    int numRandColuna;
    int numRandLinha;
    int numTentativas = 16;

    do {
        numRandColuna = -1 + rand() % (1 - (-1) + 1);
        numRandLinha = -1 + rand() % (1 - (-1) + 1);


        numRandLinha += getLinhaAnimal();
        numRandColuna += getColunaAnimal();

        if (numRandLinha < 0) {
            numRandLinha += reserva.getNLinhas();
        }
        if (numRandColuna < 0) {
            numRandColuna += reserva.getNColunas();
        }

        if (numRandLinha >= reserva.getNLinhas())
            numRandLinha -= reserva.getNLinhas();

        if (numRandColuna >= reserva.getNColunas())
            numRandColuna -= reserva.getNColunas();

        numTentativas--;
    } while (
            reserva.getZonas()[numRandLinha][numRandColuna]->getAlimento() !=
            nullptr && numTentativas > 0);

    if (numTentativas > 0) {
        reserva.getZonas()[numRandLinha][numRandColuna]->colocaAlimento(
                new Corpo(numRandLinha, numRandColuna, 15, 5));
    }
}

bool Canguru::verificamorreAnimal() {
    if (getDuracao() <= 0 || getSaudeAnimal() <= 0) {
        return true;
    }
    return false;
}

Misterio::Misterio(Reserva &reserva, int x, int y) : Animal(reserva, 'M', InicioJogo::getMisterioSaude(),
                                                            InicioJogo::getMisterioPeso(),
                                                            InicioJogo::getMisterioVida(), x, y) {}

Misterio::~Misterio() = default;

void Misterio::avancaInstante() {
    if (isJaAvancouInstante())
        return;
    setJaAvancouInstante(true);
    diminuiDuracao();

    //morte natural
    if (verificamorreAnimal()) {
        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAnimal(getIdAnimal(), true);//morte natural
        return;
    }

    //novo animal misterio certo
    if ((InicioJogo::getMisterioVida() - getDuracao()) % 8 == 0) { //8 instantes
        int linha = -4 + rand() % (4 - (-4) + 1);
        int coluna = -4 + rand() % (4 - (-4) + 1);

        if (linha < 0)
            linha += reserva.getNLinhas();
        if (coluna < 0)
            coluna += reserva.getNColunas();
        if (linha >= reserva.getNLinhas())
            linha -= reserva.getNLinhas();
        if (coluna >= reserva.getNColunas())
            coluna -= reserva.getNColunas();


        reserva.adicionaAnimal(new Misterio(reserva, linha, coluna), linha, coluna);
    }

    //alimentacao certo
    Alimento *alimento = reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->getAlimento();
    bool comeu = false;
    if (alimento != nullptr) {
        for (auto cheiro:alimento->getCheiro())

            if (cheiro == "rosas") {
                aumentaSaude(alimento->getvalorNutritivo());
                diminuiSaude(alimento->getToxicidade());
                adicionaAlimentoHistorico(alimento->getNomeAlimento(), alimento->getvalorNutritivo(),
                                          alimento->getToxicidade());
                reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAlimento();

                comeu = true;
                break;
            }
    }

    if (!comeu) {
        for (int i = -6; i < 6; i++) {
            for (int j = -6; j < 6; j++) {
                int linha = (getLinhaAnimal() + i) % reserva.getNLinhas();
                int coluna = (getColunaAnimal() + j) % reserva.getNColunas();

                if (linha < 0)
                    linha += reserva.getNLinhas();
                if (coluna < 0)
                    coluna += reserva.getNColunas();
                if (linha >= reserva.getNLinhas())
                    linha -= reserva.getNLinhas();
                if (coluna >= reserva.getNColunas())
                    coluna -= reserva.getNColunas();

                alimento = reserva.getZonas()[linha][coluna]->getAlimento();
                if (alimento != nullptr) {
                    for (auto cheiro:alimento->getCheiro())
                        if (cheiro == "rosas") {
                            reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAnimal(getIdAnimal(), false);
                            setLinhaAnimal(linha);
                            setColunaAnimal(coluna);
                            reserva.getZonas()[linha][coluna]->adicionaAnimal(this);
                            return;
                        }
                }
            }
        }
    }

    //diminui 4 de saude ao animal que esteja perto dele
    vector<Animal *> animais = reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->getAnimais();
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int linha = (getLinhaAnimal() + i) % reserva.getNLinhas();
            int coluna = (getColunaAnimal() + j) % reserva.getNColunas();

            if (linha == -1) {
                linha += reserva.getNLinhas();
            }
            if (coluna == -1) {
                coluna += reserva.getNColunas();
            }
            if (linha >= reserva.getNLinhas()) {
                linha -= reserva.getNLinhas();
            }
            if (coluna >= reserva.getNColunas()) {
                coluna -= reserva.getNColunas();
            }

            animais = reserva.getZonas()[linha][coluna]->getAnimais();
            for (auto animal: animais) {
                if (animal == this) {
                    continue;
                }
                if (animal->getTipoAnimal() == 'C'){
                    animal->diminuiSaudeA(4);
                }
                if (animal->getTipoAnimal() == 'G'){
                    continue;

                }
                if (animal->getTipoAnimal() == 'O'){

                    animal->diminuiSaudeA(4);
                }
                if (animal->getTipoAnimal() == 'L'){

                    animal->diminuiSaudeA(4);
                }



            }
        }
    }

    if (getFomeAnimal() > 20) {
        aumentaFome(3);
        diminuiSaudeA(4);

        int numRandColuna;
        int numRandLinha;
        do {
            numRandColuna = -4 + rand() % (4 - (-4) + 1);
        } while (numRandColuna == 0);

        do {
            numRandLinha = -4 + rand() % (4 - (-4) + 1);
        } while (numRandLinha == 0);

        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAnimal(getIdAnimal(), false);
        setLinhaAnimal((getLinhaAnimal() + numRandLinha) % reserva.getNLinhas());
        setColunaAnimal((getColunaAnimal() + numRandColuna) % reserva.getNColunas());

        if (getLinhaAnimal() < 0) {
            setLinhaAnimal(getLinhaAnimal() + reserva.getNLinhas());
        }
        if (getColunaAnimal() < 0) {
            setColunaAnimal(getColunaAnimal() + reserva.getNColunas());
        }
        if (getLinhaAnimal() >= reserva.getNLinhas())
            setLinhaAnimal(getLinhaAnimal() - reserva.getNLinhas());

        if (getColunaAnimal() >= reserva.getNColunas())
            setColunaAnimal(getColunaAnimal() - reserva.getNColunas());

        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->adicionaAnimal(this);
    } else if (getFomeAnimal() <= 20) {

        aumentaFome(3);
        int numRandColuna;
        int numRandLinha;
        do {
            numRandColuna = -3 + rand() % (3 - (-3) + 1);
        } while (numRandColuna == 0);

        do {
            numRandLinha = -3 + rand() % (3 - (-3) + 1);
        } while (numRandLinha == 0);

        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAnimal(getIdAnimal(), false);
        setLinhaAnimal((getLinhaAnimal() + numRandLinha) % reserva.getNLinhas());
        setColunaAnimal((getColunaAnimal() + numRandColuna) % reserva.getNColunas());

        if (getLinhaAnimal() < 0) {
            setLinhaAnimal(getLinhaAnimal() + reserva.getNLinhas());
        }
        if (getColunaAnimal() < 0) {
            setColunaAnimal(getColunaAnimal() + reserva.getNColunas());
        }

        if (getLinhaAnimal() >= reserva.getNLinhas())
            setLinhaAnimal(getLinhaAnimal() - reserva.getNLinhas());

        if (getColunaAnimal() >= reserva.getNColunas())
            setColunaAnimal(getColunaAnimal() - reserva.getNColunas());

        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->adicionaAnimal(this);

    }
    if (verificamorreAnimal()) {
        reserva.getZonas()[getLinhaAnimal()][getColunaAnimal()]->removeAnimal(getIdAnimal(), true);//morte natural
        return;
    }
}


void Misterio::morreAnimal() {

    int numRandColuna;
    int numRandLinha;
    int numTentativas = 16;

    do {
        numRandColuna = -1 + rand() % (1 - (-1) + 1);
        numRandLinha = -1 + rand() % (1 - (-1) + 1);


        numRandLinha += getLinhaAnimal();
        numRandColuna += getColunaAnimal();

        if (numRandLinha < 0) {
            numRandLinha += reserva.getNLinhas();
        }
        if (numRandColuna < 0) {
            numRandColuna += reserva.getNColunas();
        }

        if (numRandLinha >= reserva.getNLinhas())
            numRandLinha -= reserva.getNLinhas();

        if (numRandColuna >= reserva.getNColunas())
            numRandColuna -= reserva.getNColunas();

        numTentativas--;
    } while (
            reserva.getZonas()[numRandLinha][numRandColuna]->getAlimento() !=
            nullptr && numTentativas > 0);

    if (numTentativas > 0) {
        reserva.getZonas()[numRandLinha][numRandColuna]->colocaAlimento(
                new Corpo(numRandLinha, numRandColuna, 0, 10));
    }

}

bool Misterio::verificamorreAnimal() {
    if (getSaudeAnimal() == 0 || getDuracao() == 0) {
        return true;
    }
    return false;
}


string Animal::toString() const {
    ostringstream oss;

    oss << "Animal com ID: " << idA << ", do tipo " << getTipoAnimal() << ", com saude " << getSaudeAnimal()
        << ", com peso " << getPesoAnimal() << " com duracao " << duracao << " e com fome " << fome << endl;

    oss << "  Historico de Alimentacao: " << endl;
    HistoricoAlimentacao *aux = historico;
    while (aux != nullptr) {

        oss << "   " << aux->toString();
        aux = aux->getProximo();
    }
    return oss.str();
}

bool Animal::isJaAvancouInstante() const {
    return jaAvancouInstante;
}

void Animal::setJaAvancouInstante(bool jaAvancouInstante) {
    Animal::jaAvancouInstante = jaAvancouInstante;
}

void Animal::setHistorico(HistoricoAlimentacao *historico) {
    Animal::historico = historico;
}

