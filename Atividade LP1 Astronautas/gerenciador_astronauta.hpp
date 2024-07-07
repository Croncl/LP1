#ifndef GERENCIADOR_ASTRONAUTA_HPP
#define GERENCIADOR_ASTRONAUTA_HPP

#include "astronauta.hpp"
#include <unordered_map>

class GerenciadorAstronauta {
private:
    std::unordered_map<std::string, Astronauta> astronautas;

public:
    GerenciadorAstronauta();

    void cadastrarAstronauta(const std::string& cpf, const std::string& nome, std::string& idade, bool status, bool emVoo);
    void removerAstronauta(const std::string& cpf);
    void updateAstronauta(const std::string& cpf, bool disponivel, bool emVoo, bool status);
    const Astronauta* buscarAstronauta(const std::string& cpf) const;
    void listarAstronautas() const;
    void listarAstronautasMortos() const;
};

#endif // GERENCIADOR_ASTRONAUTA_HPP
