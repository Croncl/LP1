#include "menu.hpp"
#include "gerenciador_astronauta.hpp"
#include "gerenciador_voo.hpp"

int main() {
    GerenciadorAstronauta ga;
    GerenciadorVoo gv;
    Menu menu(ga, gv); // Passando os gerenciadores para o construtor
    menu.exibirMenu();
    return 0;
}
