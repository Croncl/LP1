#ifndef GERENCIADOR_VOO_HPP
#define GERENCIADOR_VOO_HPP

#include "voo.hpp"
#include "gerenciador_astronauta.hpp"
#include <map>
#include <string>

class GerenciadorVoo {
public:
    GerenciadorVoo();

    void adicionarVoo(const std::string& id, const std::string& destino);
    void removerVoo(const std::string& id);
    void adicionarAstronautaVoo(const std::string& idVoo, const std::string& cpf, GerenciadorAstronauta& gerenciadorAstronauta);
    void removerAstronautaVoo(const std::string& idVoo, const std::string& cpf, GerenciadorAstronauta& gerenciadorAstronauta);
    void listarVoos() const;
    void listarVooSituacao(const GerenciadorAstronauta& gerenciadorAstronauta, int situacao) const;
    void listarAstronautasVoo(const std::string& idVoo, GerenciadorAstronauta& gerenciadorAstronauta) const;


    // metodos voo
    void operarVoo(const std::string& idVoo, int opcao, GerenciadorAstronauta& gerenciadorAstronauta);


private:
    //GerenciadorAstronauta gerenciadorAstronauta; // Declare GerenciadorAstronauta object
    std::unordered_map<std::string, Voo> voos;
};

#endif // GERENCIADOR_VOO_HPP
