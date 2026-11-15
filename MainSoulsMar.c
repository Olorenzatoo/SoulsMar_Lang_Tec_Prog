#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

typedef struct {
    char nome[40];
    int tipo;
    int valor; 
    int quantidade;
} Item;

typedef struct {
    char nome[50];
    int nivel;
    int xp;
    int xpProximoNivel;
    int hp;
    int hpMax;
    int vigor; 
    int vigorMax;
    int ataque;
    int defesa;
    int areaAtual; 
    int progressoArea;
    Item inventario[MAX_ITENS];
    int numItens;
} Personagem;

typedef struct {
    char nome[50];
    int hp;
    int hpMax;
    int ataque;
    int defesa;
    int xpRecompensa;
    int tipoArte;
} Inimigo;

void limparTela(void);
void pausar(void);
void limparBuffer(void);
int lerInteiro(int min, int max);

void exibirArteFogueira(void);
void exibirArteVitoria(void);
void exibirArteDerrota(void);
void exibirArteInimigo(int tipoArte);

int salvarJogo(Personagem *p);

void criarPersonagem(Personagem *p);
void verificarProgressao(Personagem *p);

void adicionarItem(Personagem *p, char *nome, int tipo, int valor, int qtd);
void abrirInventario(Personagem *p);

int iniciarCombate(Personagem *p, Inimigo inimigo);
void loopExploracao(Personagem *p);
void explorarAvancar(Personagem *p);
void cacarAlmas(Personagem *p);
void descansarFogueira(Personagem *p);
void exibirCreditos(void);
//==================================================================================================
int main(int argc, char *argv[]){

    Personagem jogador;
    int opcao;

  do {
		printf("==============================================================\n");
	    printf("   ____   ___  _   _ _     ____  __  __    _    ____          \n");
	    printf("  / ___| / _ \\| | | | |   / ___||  \\/  |  / \\  |  _ \\         \n");
	    printf("  \\___ \\| | | | | | | |   \\___ \\| |\\/| | / _ \\ | |_) |        \n");
	    printf("   ___) | |_| | |_| | |___ ___) | |  | |/ ___ \\|  _ <         \n");
	    printf("  |____/ \\___/ \\___/|_____|____/|_|  |_/_/   \\_\\_| \\_\\        \n");
	    printf("             --- AS COSTAS CINZENTAS DO ABISMO ---            \n");
	    printf("==============================================================\n\n");

        printf("  [1] Nova Jornada (Novo Jogo)\n");
        printf("  [2] Continuar Jornada (Carregar Save)\n");
        printf("  [3] Sobre o Projeto & Creditos\n");
        printf("  [0] Sair\n");
        printf("\nEscolha uma opcao: ");
    
        switch (opcao) {
            case 1:
                criarPersonagem(&jogador);
				loopExploracao(&jogador);
				break;
            case 2:
          
            case 3:
                
            case 0:
                
        }
    } while (opcao != 0);

  return 0;
}
//==================================================================================================
void limparTela(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pausar(void) {
    printf("\nPressione ENTER para continuar...");
    getchar();
}

int lerInteiro(int min, int max) {
    int valor;
    while (1) {
        if (scanf("%d", &valor) == 1) {
            limparBuffer();
            if (valor >= min && valor <= max) {
                return valor;
            }
        } else {
            limparBuffer();
        }
        printf("Entrada invalida! Digite um numero entre %d e %d: ", min, max);
    }
}
//==================================================================================================
void exibirArteFogueira(void) {
    printf("\n        (  .      )\n");
    printf("      )           (              )\n");
    printf("            .  '   .   '  .  '  .\n");
    printf("   (    , )       (.   )  (   ',    )\n");
    printf("    .' ) ( . )    ,  ( ,     )   ( .\n");
    printf(" ). , ( .   (  ) ( , ')  .' (  ,    )\n");
    printf("(_,) . ), ) _) _,')  (, ) '. )  ,. (' )\n");
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    printf("     [ FOGUEIRA DAS ALMAS ACESA ]\n\n");
}

void exibirArteVitoria(void) {
    printf("\n==============================================================\n");
    printf("  __   _____ _____ ___  ____  ___    _                        \n");
    printf("  \\ \\ / /_ _|_   _/ _ \\|  _ \\|_ _|  / \\                       \n");
    printf("   \\ V / | |  | || | | | |_) || |  / _ \\                      \n");
    printf("    \\_/ |___| |_||_| |_|_| \\_\\___|/_/ \\_\\                     \n");
    printf("        A MALDICAO DE SOULSMAR FOI DISSIPADA!                 \n");
    printf("==============================================================\n");
}

void exibirArteInimigo(int tipoArte) {
    if (tipoArte == 1) {
        printf("\n        .-\"\"\"-.\n");
        printf("       / _   _ \\\n");
        printf("       ](_' '_)[\n");
        printf("       `-. N .-'   [ ESPECTRO DA MARE ]\n");
        printf("         |===|\n");
        printf("        /     \\\n\n");
    } else {
        printf("\n       |\\     /|\n");
        printf("       | \\___/ |\n");
        printf("      /  O   O  \\\n");
        printf("     |   ==^==   |  [ GUARDIAO ABISSAL ]\n");
        printf("    /|\\  |===|  /|\\\n");
        printf("   / | \\_/   \\_/ | \\\n\n");
    }
}

void exibirArteDerrota(void) {
    printf("\n==============================================================\n");
    printf("   __     _____   ____ _____   __  __  ___  ____  ____  _____ _   _ \n");
    printf("   \\ \\   / / _ \\ / ___| ____| |  \\/  |/ _ \\|  _ \\|  _ \\| ____| | | |\n");
    printf("    \\ \\ / / | | | |   |  _|   | |\\/| | | | | |_) | |_) |  _| | | | |\n");
    printf("     \\ V /| |_| | |___| |___  | |  | | |_| |  _ <|  _ <| |___| |_| |\n");
    printf("      \\_/  \\___/ \\____|_____| |_|  |_|\\___/|_| \\_\\_| \\_\\_____|\\___/ \n");
    printf("            SUAS ALMAS SE PERDERAM NAS PROFUNDEZAS...               \n");
    printf("==============================================================\n");
}
//==================================================================================================
int salvarJogo(Personagem *p) {
    FILE *arquivo = fopen(SAVE_FILE, "wb");
    if (arquivo == NULL) return 0;

    fwrite(p, sizeof(Personagem), 1, arquivo);
    fclose(arquivo);
    return 1;
}
//==================================================================================================

void criarPersonagem(Personagem *p) {
    limparTela();
    printf("=== CRIACAO DO PERSONAGEM ===\n\n");
    printf("Digite o nome do seu viajante: ");
    scanf(" %49[^\n]", p->nome);
    limparBuffer();

    p->nivel = 1;
    p->xp = 0;
    p->xpProximoNivel = 50;
    p->hpMax = 110;
    p->vigorMax = 50;
    p->ataque = 18;
    p->defesa = 8;
    p->hp = p->hpMax;
    p->vigor = p->vigorMax;

    p->areaAtual = 1;
    p->progressoArea = 0;
    p->numItens = 0;

    adicionarItem(p, "Frasco de Estus", 1, 45, 2);
    adicionarItem(p, "Erva Marinha", 2, 25, 1);

    limparTela();
    printf("\nBem-vindo a SoulsMar, %s!\n", p->nome);
    printf("Seu objetivo: atravessar as 4 regioes e derrotar Vorath.\n");
    pausar();
}

void verificarProgressao(Personagem *p) {
    int escolha;

    while (p->xp >= p->xpProximoNivel) {
        p->xp -= p->xpProximoNivel;
        p->nivel++;
        p->xpProximoNivel = (int)(p->xpProximoNivel * 1.5);

        limparTela();
        printf("**********************************************\n");
        printf("  SUBIU DE NIVEL! Agora voce e Nivel %d!\n", p->nivel);
        printf("**********************************************\n");
        printf("\nEscolha um atributo para fortalecer:\n");
        printf("  [1] Vitalidade (+25 HP Maximo)\n");
        printf("  [2] Forca      (+5 Ataque)\n");
        printf("  [3] Resiliencia(+3 Defesa)\n");
        printf("  [4] Tenacidade (+15 Vigor Maximo)\n");
        printf("\nOpcao: ");

        escolha = lerInteiro(1, 4);
        switch (escolha) {
            case 1: p->hpMax += 25; break;
            case 2: p->ataque += 5; break;
            case 3: p->defesa += 3; break;
            case 4: p->vigorMax += 15; break;
        }
        p->hp = p->hpMax;
        p->vigor = p->vigorMax;
        printf("\nAtributo aprimorado e energias restauradas!\n");
        pausar();
    }
}

void exibirStatus(const Personagem *p) {
    limparTela();
    printf("==============================================\n");
    printf("  STATUS DE %s \n", p->nome);
    printf("==============================================\n");
    printf("  Nivel: %d  |  Almas (XP): %d / %d\n", p->nivel, p->xp, p->xpProximoNivel);
    printf("  HP:    %d / %d\n", p->hp, p->hpMax);
    printf("  Vigor: %d / %d\n", p->vigor, p->vigorMax);
    printf("  Ataque: %d  |  Defesa: %d\n", p->ataque, p->defesa);
    printf("  Regiao Atual: %d / 4\n", p->areaAtual);
    printf("==============================================\n");
    pausar();
}

int iniciarCombate(Personagem *p, Inimigo inimigo) {
    int acao, dano, defendendo;

    while (p->hp > 0 && inimigo.hp > 0) {
        defendendo = 0;
        limparTela();
        exibirArteInimigo(inimigo.tipoArte);

        printf("INIMIGO: %s | HP: %d/%d\n", inimigo.nome, inimigo.hp, inimigo.hpMax);
        printf("JOGADOR: %s | HP: %d/%d | Vigor: %d/%d\n\n", p->nome, p->hp, p->hpMax, p->vigor, p->vigorMax);

        printf("[1] Ataque Rapido  (0 Vigor)\n");
        printf("[2] Golpe Pesado   (15 Vigor - Dano extra)\n");
        printf("[3] Defender       (Reduz dano e recupera 15 Vigor)\n");
        printf("[4] Inventario\n");
        printf("\nSua acao: ");
        scanf("%d", &acao);
        limparBuffer();

        if (acao == 1) {
            dano = p->ataque - (inimigo.defesa / 2) + (rand() % 4);
            if (dano < 1) dano = 1;
            inimigo.hp -= dano;
            printf("\n>> Voce atacou e causou %d de dano!\n", dano);
        } else if (acao == 2) {
            if (p->vigor >= 15) {
                p->vigor -= 15;
                dano = (p->ataque + 8) - (inimigo.defesa / 2) + (rand() % 4);
                if (dano < 1) dano = 1;
                inimigo.hp -= dano;
                printf("\n>> GOLPE PESADO! Voce causou %d de dano!\n", dano);
            } else {
                printf("\n[!] Vigor insuficiente! Voce perdeu o turno!\n");
            }
        } else if (acao == 3) {
            defendendo = 1;
            p->vigor += 15;
            if (p->vigor > p->vigorMax) p->vigor = p->vigorMax;
            printf("\n>> Voce ergueu a guarda e recuperou 15 de Vigor!\n");
        } else if (acao == 4) {
            abrirInventario(p);
            continue;
        } else {
            printf("\nOpcao invalida! Voce hesitou e perdeu a vez.\n");
        }

        /* Verifica se o inimigo morreu */
        if (inimigo.hp <= 0) {
            printf("\n*** %s FOI DERROTADO! (+%d Almas) ***\n", inimigo.nome, inimigo.xpRecompensa);
            p->xp += inimigo.xpRecompensa;

            if (rand() % 100 < 50) {
                printf("Voce encontrou um Frasco de Estus!\n");
                adicionarItem(p, "Frasco de Estus", 1, 45, 1);
            }
            pausar();
            return 1;
        }

        /* Turno do Inimigo */
        dano = inimigo.ataque - (p->defesa / 2) + (rand() % 4);
        if (defendendo) dano /= 2;
        if (dano < 1) dano = 1;

        p->hp -= dano;
        printf("<< %s atacou e causou %d de dano em voce!\n", inimigo.nome, dano);
        pausar();
    }

    return 0;
}
//==================================================================================================
void adicionarItem(Personagem *p, char *nome, int tipo, int valor, int qtd) {
    int i;
    for (i = 0; i < p->numItens; i++) {
        if (strcmp(p->inventario[i].nome, nome) == 0) {
            p->inventario[i].quantidade += qtd;
            return;
        }
    }
    if (p->numItens < MAX_ITENS) {
        strcpy(p->inventario[p->numItens].nome, nome);
        p->inventario[p->numItens].tipo = tipo;
        p->inventario[p->numItens].valor = valor;
        p->inventario[p->numItens].quantidade = qtd;
        p->numItens++;
    }
}

void abrirInventario(Personagem *p) {
    int i, j, escolha;

    limparTela();
    printf("=== INVENTARIO DE %s ===\n\n", p->nome);

    if (p->numItens == 0) {
        printf("Sua bolsa esta vazia.\n");
        pausar();
        return;
    }

    for (i = 0; i < p->numItens; i++) {
        printf("  [%d] %s (x%d) - ", i + 1, p->inventario[i].nome, p->inventario[i].quantidade);
        if (p->inventario[i].tipo == 1) {
            printf("Recupera %d de HP\n", p->inventario[i].valor);
        } else {
            printf("Recupera %d de Vigor\n", p->inventario[i].valor);
        }
    }
    printf("  [0] Fechar inventario\n");
    printf("\nEscolha um item para usar: ");

    escolha = lerInteiro(0, p->numItens);
    if (escolha == 0) return;

    i = escolha - 1;
    if (p->inventario[i].tipo == 1) {
        p->hp += p->inventario[i].valor;
        if (p->hp > p->hpMax) p->hp = p->hpMax;
        printf("\n>> Voce usou %s! HP atual: %d/%d.\n", p->inventario[i].nome, p->hp, p->hpMax);
    } else {
        p->vigor += p->inventario[i].valor;
        if (p->vigor > p->vigorMax) p->vigor = p->vigorMax;
        printf("\n>> Voce usou %s! Vigor atual: %d/%d.\n", p->inventario[i].nome, p->vigor, p->vigorMax);
    }

    p->inventario[i].quantidade--;
    if (p->inventario[i].quantidade <= 0) {
        for (j = i; j < p->numItens - 1; j++) {
            p->inventario[j] = p->inventario[j + 1];
        }
        p->numItens--;
    }
    pausar();
}
//==================================================================================================
void loopExploracao(Personagem *p) {
    int opcao;
    char *nomesAreas[] = {"", "1. Praia dos Naufragios", "2. Catedral Submersa", "3. Farol das Cinzas", "4. Trono Abissal de Vorath"};

    while (p->hp > 0 && p->areaAtual <= 4) {
        limparTela();
        printf("==============================================================\n");
        printf("  LOCALIZACAO: %s\n", nomesAreas[p->areaAtual]);
        printf("  %s (Nv.%d) | HP: %d/%d | Vigor: %d/%d | Almas: %d/%d\n", p->nome, p->nivel, p->hp, p->hpMax, p->vigor, p->vigorMax, p->xp, p->xpProximoNivel);
        printf("==============================================================\n\n");

        if (p->progressoArea == 0) {
            printf("Status da Regiao: Caminho desconhecido a frente.\n\n");
        } else {
            printf("Status da Regiao: O Guardiao desta area bloqueia a passagem!\n\n");
        }

        printf("  [1] Avancar na Jornada\n");
        printf("  [2] Cacar Almas nos Arredores (Combate Livre)\n");
        printf("  [3] Descansar na Fogueira (Curar, Subir Nivel e Salvar)\n");
        printf("  [4] Abrir Inventario\n");
        printf("  [5] Ver Status Completo\n");
        printf("  [0] Voltar ao Menu Principal\n");
        printf("\nO que deseja fazer? ");

        opcao = lerInteiro(0, 5);

        switch (opcao) {
            case 1:
                explorarAvancar(p);
                break;
            case 2:
                cacarAlmas(p);
                break;
            case 3:
                descansarFogueira(p);
                break;
            case 4:
                abrirInventario(p);
                break;
            case 0:
                return;
        }
    }

	if (p->hp <= 0) {
        limparTela();
        printf("\n=== VOCE MORREU! SUAS ALMAS SE PERDERAM... ===\n");
        pausar();
    }
}

void explorarAvancar(Personagem *p) {
    int escolha;
    limparTela();

    /* Evento da regiao */
    if (p->progressoArea == 0) {
        printf("=== EVENTO DA REGIAO %d ===\n\n", p->areaAtual);

        if (p->areaAtual == 1) {
            printf("Voce encontra um altar submerso emanando uma nevoa escarlate.\n");
            printf("[1] Tocar o altar (-15 HP, +35 Almas e +1 Frasco)\n");
            printf("[2] Ignorar e seguir (+15 Almas)\nEscolha: ");
            scanf("%d", &escolha);
            limparBuffer();

            if (escolha == 1) {
                p->hp -= 15;
                if (p->hp < 1) p->hp = 1;
                p->xp += 35;
                adicionarItem(p, "Frasco de Estus", 1, 45, 1);
                printf("\n>> A nevoa queima sua pele, mas voce ganha poder e um Frasco!\n");
            } else {
                p->xp += 15;
                printf("\n>> Voce contorna o altar em seguranca.\n");
            }
        } else if (p->areaAtual == 2) {
            printf("Um peregrino cego pede ajuda para suportar o frio da catedral.\n");
            printf("[1] Ajudar o peregrino (+40 Almas e +2 Ataque)\n");
            printf("[2] Seguir adiante (+15 Almas)\nEscolha: ");
            scanf("%d", &escolha);
            limparBuffer();

            if (escolha == 1) {
                p->xp += 40;
                p->ataque += 2;
                printf("\n>> O peregrino abencoa sua arma!\n");
            } else {
                p->xp += 15;
                printf("\n>> Voce segue focado rumo ao altar.\n");
            }
        } else if (p->areaAtual == 3) {
            printf("No topo do farol, uma reliquia antiga brilha cravada na pedra.\n");
            printf("[1] Empunhar a reliquia (+50 Almas e +3 Defesa)\n");
            printf("[2] Descansar um pouco (+20 HP)\nEscolha: ");
            scanf("%d", &escolha);
            limparBuffer();

            if (escolha == 1) {
                p->xp += 50;
                p->defesa += 3;
                printf("\n>> Uma armadura espectral envolve seus ombros!\n");
            } else {
                p->hp += 20;
                if (p->hp > p->hpMax) p->hp = p->hpMax;
                printf("\n>> Voce recupera suas energias.\n");
            }
        } else {
            printf("Voce atravessa os portoes do Trono Abissal. Vorath aguarda!\n");
        }

        p->progressoArea = 1;
        pausar();
        return;
    }

    /* Luta contra o Guardiao da regiao ou boss final */
    Inimigo chefes[5] = {
        {"", 0, 0, 0, 0, 0, 2}, {"Carcereiro dos Naufragios", 75, 75, 14, 6, 60, 2}, {"Bispo das Profundezas", 110, 110, 19, 9, 95, 2}, {"Sentinela do Farol Cinzento", 145, 145, 24, 12, 140, 2}, {"VORATH, O SOBERANO DO ABISMO", 210, 210, 30, 15, 500, 2}
    };

    if (iniciarCombate(p, chefes[p->areaAtual])) {
        if (p->areaAtual == 4) {
            limparTela();
            exibirArteVitoria();
            printf("\nParabens, %s! Voce concluiu a jornada no Nivel %d.\n", p->nome, p->nivel);
            pausar();
            p->areaAtual = 5;
        } else {
            p->areaAtual++;
            p->progressoArea = 0;
            printf("\n>> Guardiao derrotado! Voce avancou para a proxima regiao!\n");
            pausar();
        }
    }
}
    /*Luta contra o Guardiao da regiao ou boss final*/
    Inimigo chefes[5] = {{"", 0, 0, 0, 0, 0, 2}, {"Carcereiro dos Naufragios", 75, 75, 14, 6, 60, 2}, {"Bispo das Profundezas", 110, 110, 19, 9, 95, 2}, 
	{"Sentinela do Farol Cinzento", 145, 145, 24, 12, 140, 2}, {"VORATH, O SOBERANO DO ABISMO", 210, 210, 30, 15, 500, 2}};

	    if (iniciarCombate(p, chefes[p->areaAtual])) {
        if (p->areaAtual == 4) {
            limparTela();
            exibirArteVitoria();
            printf("\nParabens, %s! Voce concluiu a jornada no Nivel %d.\n", p->nome, p->nivel);
            pausar();
            p->areaAtual = 5;
        } else {
            p->areaAtual++;
            p->progressoArea = 0;
            printf("\n>> Guardiao derrotado! Voce avancou para a proxima regiao!\n");
            pausar();
        }
    }
}
		
    }
}

void cacarAlmas(Personagem *p) {
    Inimigo comum;
    int escala = p->areaAtual;

    strcpy(comum.nome, "Espectro da Mare");
    comum.hpMax = 35 + (escala * 18);
    comum.hp = comum.hpMax;
    comum.ataque = 9 + (escala * 4);
    comum.defesa = 3 + (escala * 2);
    comum.xpRecompensa = 25 + (escala * 12);
    comum.tipoArte = 1;

    iniciarCombate(p, comum);
}

void descansarFogueira(Personagem *p) {
    limparTela();
    exibirArteFogueira();

    p->hp = p->hpMax;
    p->vigor = p->vigorMax;

    printf("Suas feridas foram fechadas e seu vigor foi totalmente restaurado!\n");
    verificarProgressao(p);

    if (salvarJogo(p)) {
        printf("\n>> Progresso salvo com sucesso em '%s'!\n", SAVE_FILE);
    } else {
        printf("\n[!] Erro ao salvar o arquivo.\n");
    }
    pausar();
}

void exibirCreditos(void) {
    limparTela();
    printf("==============================================================\n");
    printf("  SOULSMAR - TRABALHO DE LINGUAGEM E TECNICAS DE PROGRAMACAO  \n");
    printf("==============================================================\n\n");
    printf("Integrantes do Grupo:\n");
    printf("  1 - Henrique L. Santana\n");
    printf("  2 - Joao Vitor S. Varini\n");
    printf("  3 - Matheus Marins\n");
    printf("  4 - Pedro A. Rangel\n");
    printf("  5 - Guilherme Trepack\n\n");
    printf("Sistemas Implementados:\n");
    printf("  - Menu, Personagem, Exploracao, Combate por Turnos,\n");
    printf("    Inventario, Progressao (XP/Nivel), Arte ASCII e Save Binario.\n");
    printf("==============================================================\n");
    pausar();
}
