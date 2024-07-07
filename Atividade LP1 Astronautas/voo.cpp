#include "voo.hpp"
#include <iostream>

// Construtor da classe Voo.
Voo::Voo(const std::string& id, const std::string& destino, bool lancamento, bool integridade, bool finalizado)
    : id(id), destino(destino), lancamento(lancamento), integridade(integridade), finalizado(finalizado) {}

// Método para obter o ID do voo.
const std::string& Voo::getID() const {
    return id;
}

// Método para obter o destino do voo.
const std::string& Voo::getDestino() const {
    return destino;
}

// Método para verificar se o lançamento foi realizado.
bool Voo::getLancamento() const {
    return lancamento;
}

// Método para definir o status de lançamento.
void Voo::setLancamento(bool novoLancamento) {
    lancamento = novoLancamento;
}

// Método para verificar a integridade do voo.
bool Voo::getIntegridade() const {
    return integridade;
}

// Método para definir a integridade do voo.
void Voo::setIntegridade(bool novoIntegridade) {
    integridade = novoIntegridade;
}

// Método para verificar se o voo foi finalizado.
bool Voo::getFinalizado() const {
    return finalizado;
}

// Método para definir o status de finalização do voo.
void Voo::setFinalizado(bool novoFinalizado) {
    finalizado = novoFinalizado;
}

// Método para adicionar o CPF de um astronauta ao voo.
void Voo::adicionarAstronauta(const std::string& cpf) {
    astronautas.push_back(cpf);
}

// Método para remover o CPF de um astronauta do voo.
void Voo::removerAstronauta(const std::string& cpf) {
    auto it = std::find(astronautas.begin(), astronautas.end(), cpf);
    if (it != astronautas.end()) {
        astronautas.erase(it);
    }
}

// Método para listar os CPFs dos astronautas no voo.
void Voo::listarAstronautas() const {
    if (astronautas.empty()) {
        std::cout << "Nenhum astronauta no voo." << std::endl;
        return;
    }

    for (const auto& cpf : astronautas) {
        std::cout << "CPF: " << cpf << std::endl;
    }
}

// Método para obter o número de astronautas no voo.
size_t Voo::getNumeroDeAstronautas() const {
    return astronautas.size();
}

// Método para obter a lista de CPFs dos astronautas no voo.
const std::vector<std::string>& Voo::getAstronautas() const {
    return astronautas;
}
