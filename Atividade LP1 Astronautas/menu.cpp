#include "menu.hpp"
#include <iostream>

// Construtor que inicializa o menu com os gerenciadores de astronautas e voos
Menu::Menu(GerenciadorAstronauta& ga, GerenciadorVoo& gv) : gerenciadorAstronauta(ga), gerenciadorVoo(gv) {}

// Função para aguardar o usuário pressionar qualquer tecla antes de continuar
void Menu::pressioneQualquerTecla() {
    std::cout << "\nPressione qualquer tecla para continuar...";
    std::cin.get(); // Espera o usuário pressionar qualquer tecla
}

// Função para exibir o menu principal
void Menu::exibirMenu() {
    int opcao;
    do {
        // Exibe o menu com as opções disponíveis
        std::cout << "\n============== Menu ==============" << std::endl;
        std::cout << "1. Cadastrar astronauta" << std::endl;
        std::cout << "2. Listar astronautas" << std::endl;
        std::cout << "3. Cadastrar voo" << std::endl;
        std::cout << "4. Listar voos" << std::endl;
        std::cout << "5. Adicionar astronauta a voo" << std::endl;
        std::cout << "6. Remover astronauta de voo" << std::endl;
        std::cout << "7. Listar astronautas de um voo" << std::endl;
        std::cout << "8. Operar Voo" << std::endl;
        std::cout << "9. Listar astronautas mortos" << std::endl;
        std::cout << "10. Sair" << std::endl;
        std::cout << "==================================\n";

        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao;
        std::cin.ignore(); // Limpar o buffer do teclado

        std::cout << "==================================\n";

        // Switch case para processar a escolha do usuário
        switch (opcao) {
        case 1: {
            // Caso 1: Cadastrar astronauta
            std::string nome, cpf, idade;
            std::cout << "\nEntre com os Dados do ASTRONAUTA:\nCPF do astronauta (somente números): ";
            std::getline(std::cin, cpf);
            std::cout << "Nome: ";
            std::getline(std::cin, nome);
            std::cout << "Idade (somente números): ";
            std::getline(std::cin, idade);
            
            // Chama a função do gerenciador de astronautas para cadastrar um novo astronauta
            gerenciadorAstronauta.cadastrarAstronauta(cpf, nome, idade, true, false);
            Menu::pressioneQualquerTecla();
            break;
        }
        case 2: {
            // Caso 2: Listar astronautas
            gerenciadorAstronauta.listarAstronautas();
            Menu::pressioneQualquerTecla();
            break;
        }
        case 3: {
            // Caso 3: Cadastrar voo
            std::string id, destino;
            std::cout << "\nEntre com os Dados do VOO:\nID do voo: ";
            std::getline(std::cin, id);
            std::cout << "Destino: ";
            std::getline(std::cin, destino);
            
            // Chama a função do gerenciador de voos para adicionar um novo voo
            gerenciadorVoo.adicionarVoo(id, destino);
            Menu::pressioneQualquerTecla();
            break;
        }
        case 4: {
            // Caso 4: Listar voos
            std::cout << "Escolha uma opção para listar os voos:" << std::endl;
            std::cout << "1. Listar todos os voos" << std::endl;
            std::cout << "2. Listar voos por situação" << std::endl;
            std::cout << "Opção: ";
            int escolha;
            std::cin >> escolha;

            if (escolha == 1) {
                // Lista todos os voos
                gerenciadorVoo.listarVoos();
            } else if (escolha == 2) {
                // Lista voos por situação específica
                std::cout << "Escolha uma opção para listar os voos por situação:" << std::endl;
                std::cout << "0. Voos em Preparação" << std::endl;
                std::cout << "1. Voos Lançados" << std::endl;
                std::cout << "2. Voos que Explodiram (Missão Falhou)" << std::endl;
                std::cout << "3. Voos Finalizados (Missão Cumprida)" << std::endl;
                std::cout << "Opção: ";
                int situacao;
                std::cin >> situacao;
                
                // Lista voos por situação com base na escolha do usuário
                gerenciadorVoo.listarVooSituacao(gerenciadorAstronauta, situacao);
            } else {
                std::cout << "Opção inválida." << std::endl;
            }
            
            Menu::pressioneQualquerTecla();
            break;
        }
        case 5: {
            // Caso 5: Adicionar astronauta a voo
            gerenciadorVoo.listarVoos();
            std::cout << "\n" << std::endl;
            gerenciadorAstronauta.listarAstronautas();
            std::string idVoo, cpf;
            std::cout << "Digite o ID do voo: ";
            std::getline(std::cin, idVoo);
            std::cout << "Digite o CPF do astronauta: ";
            std::getline(std::cin, cpf);
            
            // Chama a função do gerenciador de voos para adicionar um astronauta a um voo específico
            gerenciadorVoo.adicionarAstronautaVoo(idVoo, cpf, gerenciadorAstronauta);
            Menu::pressioneQualquerTecla();
            break;
        }
        case 6: {
            // Caso 6: Remover astronauta de voo
            std::string idVoo, cpf;
            gerenciadorVoo.listarVoos();
            std::cout << "Digite o ID do voo: ";
            std::getline(std::cin, idVoo);
            std::cout << "Astronautas no Voo:" << std::endl;
            
            // Lista astronautas no voo especificado
            gerenciadorVoo.listarAstronautasVoo(idVoo, gerenciadorAstronauta);
            std::cout << "Digite o CPF do astronauta: ";
            std::getline(std::cin, cpf);
            
            // Chama a função do gerenciador de voos para remover um astronauta de um voo
            gerenciadorVoo.removerAstronautaVoo(idVoo, cpf, gerenciadorAstronauta);
            Menu::pressioneQualquerTecla();
            break;
        }
        case 7: {
            // Caso 7: Listar astronautas de um voo
            gerenciadorVoo.listarVoos();
            std::string idVoo;
            std::cout << "Digite o ID do voo: ";
            std::getline(std::cin, idVoo);
            
            // Chama a função do gerenciador de voos para listar astronautas de um voo específico
            gerenciadorVoo.listarAstronautasVoo(idVoo, gerenciadorAstronauta);
            Menu::pressioneQualquerTecla();
            break;
        }
        case 8: {
            // Caso 8: Operar Voo (Lançar, Explodir, Finalizar)
            int opcao;
            do {
                std::cout << "Digite a opcao:\n1. Lancar Voo" << std::endl;
                std::cout << "2. Explodir Voo" << std::endl;
                std::cout << "3. Finalizar Voo" << std::endl;
                std::cin >> opcao;
                std::cin.ignore(); // Limpar o buffer do teclado

                if (opcao != 1 && opcao != 2 && opcao != 3) {
                    std::cout << "Opcao invalida. Por favor, digite 1, 2 ou 3." << std::endl;
                }
            } while (opcao != 1 && opcao != 2 && opcao != 3);

            std::string idVoo;
            std::cout << "Digite o ID do voo: ";
            std::getline(std::cin, idVoo);
            
            // Chama a função do gerenciador de voos para operar um voo com base na opção escolhida
            gerenciadorVoo.operarVoo(idVoo, opcao, gerenciadorAstronauta);
            Menu::pressioneQualquerTecla();
            break;
        }
        case 9: {
            // Caso 9: Listar astronautas mortos
            gerenciadorAstronauta.listarAstronautasMortos();
            Menu::pressioneQualquerTecla();
            break;
        }
        case 10: {
            // Caso 10: Sair do programa
            std::cout << "Saindo..." << std::endl;
            break;
        }
        default:
            // Opção inválida
            std::cout << "Opcao invalida. Tente novamente." << std::endl;
            Menu::pressioneQualquerTecla();
            break;
        }
    } while (opcao != 10);
}
