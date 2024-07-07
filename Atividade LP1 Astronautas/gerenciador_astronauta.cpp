#include "gerenciador_astronauta.hpp"
#include "astronauta.hpp"
#include <iostream>

// Construtor da classe GerenciadorAstronauta.
GerenciadorAstronauta::GerenciadorAstronauta() {}

// Método para cadastrar um astronauta.
void GerenciadorAstronauta::cadastrarAstronauta(const std::string& cpf, const std::string& nome, std::string& idade, bool status, bool emVoo) {
    bool disponivel = true; // Astronauta inicialmente disponível para voos.

    // Valida o status do astronauta (0 para morto, 1 para vivo).
    if (!validarStatus(status)) { 
        std::cout << "Status inválido! Aceita apenas 0 (morto) ou 1 (vivo)." << std::endl;
        return;
    }

    // Valida o CPF do astronauta.
    if (!validarCPF(cpf)) {
        std::cout << "Cadastro Negado: CPF inválido!\n" << std::endl;
        return;
    }

    // Valida o nome do astronauta.
    if (!validarNome(nome)) {
        std::cout << "Cadastro Negado: Nome inválido! O nome deve conter apenas letras e espaços.\n" << std::endl;
        return;
    }

    // Valida a idade do astronauta.
    if (!validarIdadeStr(idade)) {
        std::cout << "Cadastro Negado: Idade inválida! A idade deve estar entre 21 e 80 anos.\n" << std::endl;
        return;
    }

    // Verifica se o astronauta com o CPF informado já está cadastrado.
    if (astronautas.find(cpf) != astronautas.end()) {
        std::cout << "Astronauta com o CPF informado já existe. Tente novamente.\n" << std::endl;
        return;
    }

    // Adiciona o novo astronauta ao mapa de astronautas.
    astronautas.emplace(cpf, Astronauta(cpf, nome, idade, status, emVoo, disponivel)); 
    std::cout << "\nAstronauta " << nome << " cadastrado com sucesso!" << std::endl;
}

// Método para remover um astronauta pelo CPF.
void GerenciadorAstronauta::removerAstronauta(const std::string& cpf) {
    auto it = astronautas.find(cpf);
    if (it != astronautas.end()) {
        astronautas.erase(it);
        std::cout << "Astronauta " << cpf << " removido com sucesso!" << std::endl;
    } else {
        std::cout << "Astronauta com o CPF informado não encontrado." << std::endl;
    }
}

// Método para atualizar os atributos de um astronauta.
void GerenciadorAstronauta::updateAstronauta(const std::string& cpf, bool disponivel, bool emVoo, bool status) {
    // Busca o astronauta pelo CPF.
    const Astronauta* astronautaConst = buscarAstronauta(cpf);
    Astronauta* astronauta = const_cast<Astronauta*>(astronautaConst);
    if (astronauta == nullptr) {
        std::cout << "Astronauta não encontrado com CPF: " << cpf << std::endl;
        return;
    }

    // Atualiza o status do astronauta.
    astronauta->setDisponivel(disponivel);
    astronauta->setEmVoo(emVoo);
    astronauta->setStatus(status);

    std::cout << "\nStatus do astronauta " << cpf << " atualizado com sucesso!" << std::endl;
}

// Método para buscar um astronauta pelo CPF.
const Astronauta* GerenciadorAstronauta::buscarAstronauta(const std::string& cpf) const {
    auto it = astronautas.find(cpf);
    if (it != astronautas.end()) {
        return &it->second;
    } else {
        std::cout << "Astronauta com o CPF informado não encontrado." << std::endl;
        return nullptr;
    }
}

// Método para listar todos os astronautas cadastrados.
void GerenciadorAstronauta::listarAstronautas() const {
    if (astronautas.empty()) {
        std::cout << "Nenhum astronauta cadastrado.\n" << std::endl;
        return;
    }

    std::cout << "----------------------------------\nLista de astronautas cadastrados:\n----------------------------------\n";

    for (const auto& par : astronautas) {
        const Astronauta& astronauta = par.second; 
        detalharAstronauta(astronauta); 
        std::cout << std::endl;
    }
}

// Método para listar todos os astronautas mortos.
void GerenciadorAstronauta::listarAstronautasMortos() const {
    if (astronautas.empty()) {
        std::cout << "Nenhum astronauta cadastrado." << std::endl;
        return;
    }

    std::cout << "Lista de astronautas mortos:\n";

    for (const auto& par : astronautas) {
        const Astronauta& astronauta = par.second;
        if (!astronauta.getStatus()) { // Verifica se o astronauta está morto.
            detalharAstronauta(astronauta);  
            std::cout << std::endl;
        }
    }
}
