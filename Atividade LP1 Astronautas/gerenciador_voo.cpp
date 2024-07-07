#include "gerenciador_voo.hpp"
#include "gerenciador_astronauta.hpp"
#include "astronauta.hpp"
#include <iostream>

// Construtor da classe GerenciadorVoo
GerenciadorVoo::GerenciadorVoo() {}

void GerenciadorVoo::adicionarVoo(const std::string& id, const std::string& destino) {
    // Verifica se o voo com o ID já existe
    if (voos.find(id) != voos.end()) {
        std::cout << "\nVoo com o ID informado já existe. Tente novamente." << std::endl;
        return;
    }
    // Inicializa os estados do voo
    bool lancamento = false;
    bool integridade = true;
    bool finalizado = false;
    // Adiciona um novo voo ao mapa de voos
    voos.emplace(id, Voo(id, destino, lancamento, integridade, finalizado));
    std::cout << "\nVoo " << id << " para " << destino << " adicionado com sucesso!" << std::endl;
}

void GerenciadorVoo::removerVoo(const std::string& id) {
    // Procura o voo pelo ID
    auto it = voos.find(id);
    if (it != voos.end()) {
        // Remove o voo se encontrado
        voos.erase(it);
        std::cout << "\nVoo " << id << " removido com sucesso!" << std::endl;
    } else {
        std::cout << "\nVoo com o ID informado não encontrado." << std::endl;
    }
}

void GerenciadorVoo::listarVoos() const {
    // Verifica se há voos cadastrados
    if (voos.empty()) {
        std::cout << "Nenhum voo cadastrado." << std::endl;
        return;
    }
    std::cout << "\nLista de Voos:" << std::endl;
    for (const auto& par : voos) {
        std::string status;
        if (!par.second.getIntegridade()) {
            status = "Indisponivel: Explodiu";
        } else if (!par.second.getLancamento()) {
            status = "Em preparacao";
        } else {
            status = "Indisponivel: Lancado";
        }
        std::cout << "ID: " << par.second.getID() << " | Destino: " << par.second.getDestino() << " | Status: " << status << std::endl;
    }
}

void GerenciadorVoo::listarVooSituacao(const GerenciadorAstronauta& gerenciadorAstronauta, int situacao) const {
    if (voos.empty()) {
        std::cout << "Nenhum voo cadastrado." << std::endl;
        return;
    }

    switch (situacao) {
        case 0: // Voos em preparação
            std::cout << "\nVoos em Preparação:" << std::endl;
            for (const auto& par : voos) {
                if (par.second.getIntegridade() && !par.second.getLancamento() && !par.second.getFinalizado()) {
                    std::cout << "ID: " << par.second.getID() << " | Destino: " << par.second.getDestino() << std::endl;
                    std::cout << "Astronautas:" << std::endl;
                    for (const auto& cpf : par.second.getAstronautas()) {
                        const Astronauta* astronauta = gerenciadorAstronauta.buscarAstronauta(cpf);
                        if (astronauta) {
                            std::cout << "CPF: " << astronauta->getCPF() << " | Nome: " << astronauta->getNome() << std::endl;
                        }
                    }
                    std::cout << std::endl;
                }
            }
            break;
        case 1: // Voos lançados
            std::cout << "\nVoos Lançados:" << std::endl;
            for (const auto& par : voos) {
                if (par.second.getIntegridade() && par.second.getLancamento() && !par.second.getFinalizado()) {
                    std::cout << "ID: " << par.second.getID() << " | Destino: " << par.second.getDestino() << std::endl;
                    std::cout << "Astronautas:" << std::endl;
                    for (const auto& cpf : par.second.getAstronautas()) {
                        const Astronauta* astronauta = gerenciadorAstronauta.buscarAstronauta(cpf);
                        if (astronauta) {
                            std::cout << "CPF: " << astronauta->getCPF() << " | Nome: " << astronauta->getNome() << std::endl;
                        }
                    }
                    std::cout << std::endl;
                }
            }
            break;
        case 2: // Voos que explodiram (missão falhou)
            std::cout << "\nVoos que Explodiram (Missão Falhou):" << std::endl;
            for (const auto& par : voos) {
                if (!par.second.getIntegridade()) {
                    std::cout << "ID: " << par.second.getID() << " | Destino: " << par.second.getDestino() << std::endl;
                    std::cout << "Astronautas:" << std::endl;
                    for (const auto& cpf : par.second.getAstronautas()) {
                        const Astronauta* astronauta = gerenciadorAstronauta.buscarAstronauta(cpf);
                        if (astronauta) {
                            std::cout << "CPF: " << astronauta->getCPF() << " | Nome: " << astronauta->getNome() << std::endl;
                        }
                    }
                    std::cout << std::endl;
                }
            }
            break;
        case 3: // Voos finalizados (missão cumprida)
            std::cout << "\nVoos Finalizados (Missão Cumprida):" << std::endl;
            for (const auto& par : voos) {
                if (par.second.getFinalizado()) {
                    std::cout << "ID: " << par.second.getID() << " | Destino: " << par.second.getDestino() << " | Status: " << (par.second.getIntegridade() ? "Missão Cumprida" : "Falha na Missão") << std::endl;
                    std::cout << "Astronautas:" << std::endl;
                    for (const auto& cpf : par.second.getAstronautas()) {
                        const Astronauta* astronauta = gerenciadorAstronauta.buscarAstronauta(cpf);
                        if (astronauta) {
                            std::cout << "CPF: " << astronauta->getCPF() << " | Nome: " << astronauta->getNome() << std::endl;
                        }
                    }
                    std::cout << std::endl;
                }
            }
            break;
        default:
            std::cout << "Opção inválida." << std::endl;
            break;
    }
}


void GerenciadorVoo::adicionarAstronautaVoo(const std::string& idVoo, const std::string& cpf, GerenciadorAstronauta& gerenciadorAstronauta) {
    // Busca o astronauta pelo CPF
    const Astronauta* astronauta = gerenciadorAstronauta.buscarAstronauta(cpf);
    
    if (astronauta == nullptr) {
        std::cout << "Astronauta não encontrado com CPF: " << cpf << std::endl;
        return;
    }

    // Verifica se o astronauta está disponível para o voo
    if (!astronauta->getDisponivel()) {
        std::cout << "Astronauta não disponível para voo." << std::endl;
        return;
    }

    // Encontra o voo pelo ID
    auto it = voos.find(idVoo);
    if (it == voos.end()) {
        std::cout << "Voo não encontrado." << std::endl;
        return;
    }

    // Verifica se o voo foi lançado ou explodiu
    Voo& voo = it->second;
    if (voo.getLancamento()) {
        std::cout << "O voo " << idVoo << " já foi lançado. Não é possível adicionar astronautas." << std::endl;
        return;
    }
    if (!voo.getIntegridade()) {
        std::cout << "O voo " << idVoo << " explodiu. Não é possível adicionar astronautas." << std::endl;
        return;
    }

    // Adiciona o astronauta ao voo
    voo.adicionarAstronauta(cpf);

    // Marca o voo como não finalizado
    it->second.setFinalizado(false);

    // Marca o astronauta como não disponível para outros voos
    const_cast<Astronauta*>(astronauta)->setDisponivel(false);
    const_cast<Astronauta*>(astronauta)->setEmVoo(true);

    std::cout << "\nAstronauta adicionado ao voo com sucesso!" << std::endl;
}


void GerenciadorVoo::removerAstronautaVoo(const std::string& idVoo, const std::string& cpf, GerenciadorAstronauta& gerenciadorAstronauta) {
    auto it = voos.find(idVoo);
    if (it != voos.end()) {
        // Remove o astronauta do voo
        it->second.removerAstronauta(cpf);
        std::cout << "Astronauta removido do voo com sucesso!" << std::endl;

        // Busca o astronauta no gerenciador de astronautas
        Astronauta* astronauta = const_cast<Astronauta*>(gerenciadorAstronauta.buscarAstronauta(cpf));
        if (astronauta != nullptr) {
            // Marca o astronauta como disponível e não em voo
            astronauta->setDisponivel(true);
            astronauta->setEmVoo(false);
        } else {
            std::cout << "Astronauta com o CPF informado não encontrado." << std::endl;
        }

    } else {
        std::cout << "Voo com o ID informado não encontrado." << std::endl;

    }
}


void GerenciadorVoo::listarAstronautasVoo(const std::string& idVoo, GerenciadorAstronauta& gerenciadorAstronauta) const {
    auto it = voos.find(idVoo);
    if (it != voos.end()) {
        std::cout << "\nAstronautas no Voo " << idVoo << ":" << std::endl;
        
        for (const auto& cpf : it->second.getAstronautas()) {
            const Astronauta* astronauta = gerenciadorAstronauta.buscarAstronauta(cpf);
            if (astronauta != nullptr) {
                detalharAstronauta(*astronauta);
                std::cout << std::endl;
            }
        }
    } else {
        std::cout << "Voo com o ID informado não encontrado." << std::endl;
    }
}

void GerenciadorVoo::operarVoo(const std::string& idVoo, int opcao, GerenciadorAstronauta& gerenciadorAstronauta) {
    auto it = voos.find(idVoo);
    if (it != voos.end()) {
        std::vector<std::string> astronautasNoVoo;
        switch (opcao) {
            case 1: // Opção para lançar o voo
                if (!it->second.getIntegridade()) {
                    std::cout << "O voo " << idVoo << " não pode ser lançado porque explodiu." << std::endl;
                } else if (it->second.getLancamento()) {
                    std::cout << "O voo " << idVoo << " já foi lançado." << std::endl;
                } else if (it->second.getAstronautas().empty()) {
                    std::cout << "O voo " << idVoo << " não pode ser lançado porque não possui astronautas cadastrados." << std::endl;
                } else {
                    it->second.setLancamento(true);

                    // Atualiza astronautas e registra o voo que estão participando
                    for (const auto& cpf : it->second.getAstronautas()) {
                        Astronauta* astronauta = const_cast<Astronauta*>(gerenciadorAstronauta.buscarAstronauta(cpf));

                        if (astronauta != nullptr) {
                            astronauta->setDisponivel(false);
                            astronauta->setEmVoo(true);
                            astronauta->adicionarVooParticipou(idVoo);  // Adiciona o voo ao registro do astronauta
                        }
                    }

                    std::cout << "Voo " << idVoo << " lançado com sucesso!" << std::endl;
                }
                break;
            case 2: // Opção para explodir o voo
                if (!it->second.getLancamento()) {
                    std::cout << "Impossível: O voo " << idVoo << " não foi lançado." << std::endl;
                    break;
                }

                it->second.setIntegridade(false);
                it->second.setLancamento(false);

                // Atualiza astronautas
                for (const auto& cpf : it->second.getAstronautas()) {
                    Astronauta* astronauta = const_cast<Astronauta*>(gerenciadorAstronauta.buscarAstronauta(cpf));
                    if (astronauta != nullptr) {
                        astronauta->setDisponivel(false);
                        astronauta->setEmVoo(false);
                        astronauta->setStatus(false);
                    }
                }

                std::cout << "Voo " << idVoo << " explodiu!" << std::endl;
                break;
            case 3: // Opção para finalizar o voo
                if (!it->second.getLancamento()) {
                    std::cout << "Impossivel, o voo " << idVoo << " não foi lançado." << std::endl;
                    break;
                }

                it->second.setFinalizado(true);
                it->second.setLancamento(false);

                // Atualiza astronautas
                astronautasNoVoo = it->second.getAstronautas();
                for (const auto& cpf : astronautasNoVoo) {
                    Astronauta* astronauta = const_cast<Astronauta*>(gerenciadorAstronauta.buscarAstronauta(cpf));
                    if (astronauta != nullptr) {
                        astronauta->setEmVoo(false);
                        astronauta->setDisponivel(true);
                    }
                }

                // Remove todos os astronautas do voo
                for (const auto& cpf : astronautasNoVoo) {
                    removerAstronautaVoo(idVoo, cpf, gerenciadorAstronauta);
                }

                std::cout << "Voo " << idVoo << " finalizado com sucesso!" << std::endl;
                break;
            default:
                std::cout << "Opção inválida." << std::endl;
                break;
        }
    } else {
        std::cout << "Voo com o ID informado não encontrado." << std::endl;
    }
}
