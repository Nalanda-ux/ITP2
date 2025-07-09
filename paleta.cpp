// mostra como as classes fazem
#include "paleta.h" // pra usar o outro arquivo, entre aspas pra indicar que é um nome de arquivo
#include <fstream> // biblioteca pra manipulação de arquivos 
#include <iostream> // mensagens no terminal
using namespace pc;

Cores::Cores(int qtd, const Cor c[], const double v[]){
    quantidade = qtd;
    for (int i = 0; i < qtd; ++i) {
        cores[i] = c[i];
        valores[i] = v[i];
    }
}

Cor Cores::obterCor(double valor) const {
    if (valor <= valores[0])
        return cores[0];

    if (valor >= valores[quantidade - 1])
        return cores[quantidade - 1];

    for (int i = 0; i < quantidade - 1; ++i) {
        if (valor >= valores[i] && valor < valores[i + 1]) {
            return cores[i];
        }
    }

    return cores[quantidade - 1]; // fallback de segurança
}

bool Cores::estaOrdenados() const {
    for (int i = 0; i < quantidade - 1; ++i) {
        if (valores[i] >= valores[i + 1]) {
            return false;
        }
    }
    return true;
}

bool Cores::carregarDeArquivos(const std::string& caminho) {
    std::ifstream arquivo(caminho);
    if (!arquivo.is_open()) return false;

    arquivo >> quantidade;
    if (quantidade <= 0 || quantidade > 100) return false;

    for (int i = 0; i < quantidade; ++i) {
        int r, g, b;
        if (!(arquivo >> valores[i] >> r >> g >> b)) {
            return false; // erro na leitura
        }
        cores[i] = { static_cast<unsigned char>(r),
                     static_cast<unsigned char>(g),
                     static_cast<unsigned char>(b) };
    }

    return true;
}
