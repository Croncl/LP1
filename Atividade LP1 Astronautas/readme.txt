Sistema de Gerenciamento de Astronautas e Voos
Este projeto em C++ é um sistema de gerenciamento de astronautas e voos espaciais, desenvolvido como parte do curso de Linguagem de Programação 1 da Universidade Federal do Rio Grande do Norte (UFRN).

Funcionalidades
O sistema permite realizar as seguintes operações:

- Cadastro de Astronautas: Incluir novos astronautas com nome, CPF e idade. (restricoes de entrada a depender do tipo do dado, por ex.:c CPF somente 11 numeros; nome nao permite numeros; idade restrita a faixa de 21 a 80).
- Listagem de Astronautas: Visualizar todos os astronautas cadastrados.
- Cadastro de Voos: Adicionar novos voos com Id(sem restricao quanto a nome ou numero, podendo ser Id: 123, ou Id: Apolo13, etc...) e destino.
- Listagem de Voos: Mostrar todos os voos cadastrados, com opção de listar por situação(em preparacao, lancado, explodiu, finalizado).
- Adicionar Astronauta a um Voo: Associar um astronauta a um voo específico(Voo finalizado se ftorna novamente "em preparacao" quando adicionado um astronauta)
- Remover Astronauta de um Voo: Desassociar um astronauta de um voo específico.
- Listar Astronautas de um Voo: Exibir todos os astronautas associados a um voo.
- Operar Voo: Realizar operações como lançamento, explosão(fracasso) ou finalização(sucesso) de um voo.
- Listar Astronautas Mortos: Mostrar astronautas que não estão mais disponíveis para voos por terem explodido.


Compilação
Para compilar o projeto, siga os passos abaixo:

Requisitos
C++ Compiler: Certifique-se de ter um compilador C++ instalado.

Compilação no Terminal (Linux/macOS)
Navegue até o diretório raiz do projeto.

Compile os arquivos usando o comando:
Opcao 1: 
g++ -o programa main.cpp gerenciador_astronauta.cpp gerenciador_voo.cpp menu.cpp voo.cpp astronauta.cpp

Opcao 2:
g++ -c -Wall main.cpp -o main.o && g++ -c -Wall gerenciador_astronauta.cpp -o gerenciador_astronauta.o && g++ -c -Wall gerenciador_voo.cpp -o gerenciador_voo.o && g++ -c -Wall astronauta.cpp -o astronauta.o && g++ -c -Wall voo.cpp -o voo.o && g++ -c -Wall menu.cpp -o menu.o && g++ main.o gerenciador_astronauta.o gerenciador_voo.o astronauta.o voo.o menu.o -o programa

Opcao 3: 
make

Execute o programa compilado.
Siga as instruções exibidas no menu para realizar as operações desejadas, conforme explicado nas funcionalidades.
Utilize as opções numéricas para navegar pelo menu e interagir com o sistema.

Aluno: Cristovao Lacerda Cronje

