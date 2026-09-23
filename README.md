# SoulsMar_Lang_Tec_Prog
Trabalho de Linguagem Técnica — RPG baseado em texto

RPG — SoulsMar
                           
1 - Henrique L. Santana   
2 - João Vitor S. Varini  
3 - Matheus Marins             

1. Apresentação do projeto

  Um RPG baseado em texto, utilizando a linguagem C. No jogo, o jogador poderá controlar um personagem, explorar diferentes ambientes, realizar ações, enfrentar desafios e tomar decisões que influenciam o desenvolvimento da "Run".
  A proposta é criar uma experiência divertida e interativa, utilizando textos, imagens em ASCII(Somente em alguns detalhes), personagens e situações do jogo, contribuindo para a imersão do jogador. O sistema será baseado em interações textuais, nas quais o jogador deverá escolher suas ações por meio de opções apresentadas no terminal. Essas escolhas poderão envolver exploração, combates, utilização de itens e outras funcionalidades definidas pelo grupo.

2. Dinâmica do jogo

  A partida começa com a apresentação do menu principal, no qual o jogador poderá iniciar uma nova partida ou acessar outras opções disponíveis no sistema.
  Durante o jogo, o jogador poderá explorar ambientes, interagir com situações, enfrentar adversários e realizar diferentes ações utilizando os recursos disponíveis para seu personagem. As escolhas realizadas poderão influenciar o desenvolvimento da partida, exigindo que o jogador analise as opções apresentadas e decida como prosseguir.
  As imagens em ASCII serão utilizadas em momentos específicos para representar visualmente personagens, acontecimentos ou itens, complementando os textos e contribuindo para a experiência de jogo.

3. Objetivo do projeto

  O principal objetivo do projeto é desenvolver um RPG baseado em texto que permita aplicar, de forma prática, os conhecimentos de programação aprendidos na disciplina de Linguagem e Técnicas de Programação. O projeto também busca estimular a criatividade, o raciocínio lógico e a resolução de problemas por meio da construção de um sistema interativo, utilizando os recursos da linguagem C.

4. Principais sistemas

O projeto contará com diferentes sistemas responsáveis pelo funcionamento do RPG:

* Sistema de menu:
    Permite ao jogador acessar as principais opções do jogo, como iniciar, continuar e encerrar uma partida.

* Sistema de personagem:
    Responsável pelas informações do personagem, como nome, atributos, nível e demais características definidas pelo grupo.

* Sistema de exploração:
    Permite ao jogador percorrer ambientes, escolher caminhos e participar de diferentes situações durante a partida.

* Sistema de combate:
    Controla os confrontos entre o personagem e os adversários, incluindo ações, ataques e resultados das batalhas.

* Sistema de inventário:
    Permite consultar e utilizar itens obtidos durante o jogo, conforme as regras definidas pelo grupo.

* Sistema de progressão:
    Controla a evolução do personagem, incluindo experiência, níveis e possíveis melhorias em seus atributos.

* Sistema de representação em ASCII:
    Apresenta imagens textuais de ambientes, personagens ou acontecimentos para auxiliar na imersão do jogador.

* Sistema de salvamento:
    Permite armazenar e recuperar informações da partida por meio de arquivos.

5. Problemática e solução proposta

O projeto aborda a questão da criação de um sistema de RPG que possa gerenciar diversos aspectos de uma partida de maneira estruturada e integrada. O jogo deverá gerenciar dados do personagem, exploração de cenários, batalhas, itens, evolução e salvamento do jogo. Para resolver essa questão, o projeto será segmentado em vários sistemas, cada um encarregado de uma função específica do jogo. Com isso, as funcionalidades poderão interagir, possibilitando que as ações do jogador afetem o progresso da partida. O uso da linguagem C permitirá que os conhecimentos adquiridos na disciplina sejam aplicados para desenvolver a lógica e o funcionamento desses sistemas.

6. Condições de vitória e derrota

As situações que levarão à vitória ou à derrota serão determinadas conforme as diretrizes estabelecidas para o RPG. 
Durante o jogo, o jogador precisará executar ações e enfrentar uma variedade de obstáculos. Com base nas escolhas realizadas e nos resultados alcançados, o jogador poderá seguir em frente ou ver seu jogo chegar ao fim.
Em batalhas, a vitória se dará quando o personagem conseguir derrotar o oponente, seguindo as normas acordadas pelo grupo.
A derrota poderá acontecer se o personagem falhar em superar um desafio específico ou atingir um estado que conclua a partida.
As regras particulares para vitória e derrota serão estabelecidas pelo grupo à medida que o jogo progride.

7. Proposta acadêmica

O RPG em texto será criado com a finalidade de aplicar na prática os conceitos abordados na disciplina de Linguagem e Técnicas de Programação de forma interativa.
Durante a criação, conceitos como controle de fluxo, funções, arrays, cadeias de caracteres, estruturas, arquivos e modularização serão empregados.
A entrada e saída de dados será utilizada para possibilitar que o jogador interaja com o sistema através do terminal. Estruturas condicionais serão empregadas para gerenciar decisões, escolhas e cenários do jogo, enquanto estruturas de repetição poderão ser aplicadas em menus, batalhas e outras situações que exijam repetição.
Funções serão implementadas para sistematizar as diversas funcionalidades do projeto. Cadeias de caracteres serão utilizadas para dados textuais, enquanto arrays poderão ser usados para guardar conjuntos de informações.
Estruturas (struct) serão utilizadas para organizar informações sobre personagens, inimigos e itens. Arquivos servirão para o sistema de salvamento e carregamento dos jogos.
A modularização será aplicada para separar as funcionalidades do projeto em diferentes arquivos .c e .h, possibilitando uma melhor estruturação do sistema.
