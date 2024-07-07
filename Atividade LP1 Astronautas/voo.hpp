#ifndef VOO_HPP
#define VOO_HPP

#include <string>
#include <vector>
#include "astronauta.hpp"

class Voo {
private:
    std::string id;
    std::string destino;
    bool lancamento;
    bool integridade;
    bool finalizado;
    //std::vector<Astronauta> astronautas; // Vetor de objetos Astronauta
    std::vector<std::string> astronautas; // Vetor de CPFs dos astronautas participantes


public:
    Voo(const std::string& id, const std::string& destino, bool lancamento, bool integridade, bool finalizado);

    const std::string& getID() const;
    const std::string& getDestino() const;
    bool getLancamento() const;
    void setLancamento(bool lancamento);
    bool getIntegridade() const;
    void setIntegridade(bool integridade);
    bool getFinalizado() const;
    void setFinalizado(bool finalizado);
    //void adicionarAstronauta(const Astronauta& astronauta);
    void adicionarAstronauta(const std::string& cpf);
    void removerAstronauta(const std::string& cpf);
    void listarAstronautas() const;
    size_t getNumeroDeAstronautas() const;

    // Método para obter o vetor de astronautas
    const std::vector<std::string>& getAstronautas() const;

};

#endif // VOO_HPP
