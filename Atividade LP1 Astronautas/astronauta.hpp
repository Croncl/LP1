#ifndef ASTRONAUTA_HPP
#define ASTRONAUTA_HPP

#include <string>
#include <vector>
#include <regex>

class Astronauta {
private:
    std::string cpf;
    std::string nome;
    std::string idade;
    bool status; // true para vivo, false para morto
    bool emVoo;
    bool disponivel;
    std::vector<std::string> voosParticipou; // Lista de voos que o astronauta participou

public:
    Astronauta(const std::string& cpf, const std::string& nome, const std::string& idade, bool status, bool emVoo, bool disponivel);

    const std::string& getCPF() const;
    const std::string& getNome() const;
    const std::string& getIdade() const;
    bool getStatus() const;
    void setStatus(bool status);
    bool getEmVoo() const;
    void setEmVoo(bool emVoo);
    bool getDisponivel() const;
    void setDisponivel(bool disponivel);

    void adicionarVooParticipou(const std::string& voo); // Função para adicionar um voo que o astronauta participou
    const std::vector<std::string>& getVoosParticipou() const; // Função para obter a lista de voos que o astronauta participou
    

};

void detalharAstronauta(const Astronauta& astronauta);

inline bool validarCPF(const std::string& cpf) {
    std::regex cpf_pattern("\\d{11}");
    return std::regex_match(cpf, cpf_pattern);
}

inline bool validarNome(const std::string& nome) {
    std::regex name_pattern("^[A-Za-zÀ-ÖØ-öø-ÿ ]+$");
    return std::regex_match(nome, name_pattern);
}

inline bool validarIdade(int idade) {
    return idade >= 21 && idade <= 80;
}

inline bool validarIdadeStr(const std::string& idadeStr) {
    try {
        int idade = std::stoi(idadeStr);
        return validarIdade(idade);
    } catch (const std::exception& e) {
        return false;
    }
}

inline bool validarStatus(bool status) {
    return status == 0 || status == 1;
}

#endif // ASTRONAUTA_HPP
