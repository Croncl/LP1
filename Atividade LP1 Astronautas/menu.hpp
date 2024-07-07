#ifndef MENU_HPP
#define MENU_HPP

#include "gerenciador_astronauta.hpp"
#include "gerenciador_voo.hpp"

class Menu {
private:
    GerenciadorAstronauta& gerenciadorAstronauta;
    GerenciadorVoo& gerenciadorVoo;

public:
    Menu(GerenciadorAstronauta& ga, GerenciadorVoo& gv); // Construtor com parâmetros
    void exibirMenu(); // Método para exibir o menu
    static void pressioneQualquerTecla(); // Função estática para esperar o usuário pressionar qualquer tecla
};

#endif // MENU_HPP
