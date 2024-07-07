#include "astronauta.hpp"
#include <iostream>

// Construtor da classe Astronauta. Inicializa os atributos com os valores fornecidos.
Astronauta::Astronauta(const std::string& cpf, const std::string& nome, const std::string& idade, bool status, bool emVoo, bool disponivel)
    : cpf(cpf), nome(nome), idade(idade), status(status), emVoo(emVoo), disponivel(disponivel) {}

// Método para obter o CPF do astronauta.
const std::string& Astronauta::getCPF() const {
    return cpf;
}

// Método para obter o nome do astronauta.
const std::string& Astronauta::getNome() const {
    return nome;
}

// Método para obter a idade do astronauta.
const std::string& Astronauta::getIdade() const {
    return idade;
}

// Método para obter o status do astronauta (vivo ou morto).
bool Astronauta::getStatus() const {
    return status;
}

// Método para definir o status do astronauta (vivo ou morto).
void Astronauta::setStatus(bool status) {
    this->status = status;
}

// Método para verificar se o astronauta está em voo.
bool Astronauta::getEmVoo() const {
    return emVoo;
}

// Método para definir se o astronauta está em voo.
void Astronauta::setEmVoo(bool emVoo) {
    this->emVoo = emVoo;
}

// Método para verificar se o astronauta está disponível para novos voos.
bool Astronauta::getDisponivel() const {
    return disponivel;
}

// Método para definir a disponibilidade do astronauta para novos voos.
void Astronauta::setDisponivel(bool disponivel) {
    this->disponivel = disponivel;
}

// Método para adicionar um voo ao histórico de voos que o astronauta participou.
void Astronauta::adicionarVooParticipou(const std::string& voo) {
    voosParticipou.push_back(voo);
}

// Método para obter a lista de voos que o astronauta participou.
const std::vector<std::string>& Astronauta::getVoosParticipou() const {
    return voosParticipou;
}

// Função para detalhar as informações de um astronauta.
void detalharAstronauta(const Astronauta& astronauta) {
    std::cout << "CPF: " << astronauta.getCPF() 
              << "\nNome: " << astronauta.getNome() 
              << "\nIdade: " << astronauta.getIdade() 
              << "\nStatus: " << (astronauta.getStatus() ? "Vivo" : "Morto") 
              << "\nEm Voo: " << (astronauta.getEmVoo() ? "Sim" : "Não") 
              << "\nDisponível: " << (astronauta.getDisponivel() ? "Sim" : "Não") 
              << "\nVoos que participou:";

    const std::vector<std::string>& voosParticipados = astronauta.getVoosParticipou();

    for (const auto& voo : voosParticipados) {
        std::cout << "\n- " << voo;
    }

    std::cout << std::endl;
}
