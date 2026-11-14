#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL_ETAPAS 5
#define SAVE "soulsmar_save.txt"

typedef struct {
    char nome[50];
    int vida, vidaMaxima, forca, pocoes, experiencia;
} Personagem;

typedef struct {
    char nome[50];
    int vida, forca, recompensa;
} Inimigo;

void mostrarMenu(void);
int lerOpcao(int min, int max);
void pausar(void);
void mostrarStatus(const Personagem *p);
void mostrarArte(int etapa);
void explorar(Personagem *p, int etapa);
int combater(Personagem *p, Inimigo inimigo);
int salvar(const Personagem *p, int etapa);
int carregar(Personagem *p, int *etapa);
void jogar(Personagem *p, int etapa);
void novoJogo(void);
void continuarJogo(void);

void mostrarMenu(void) {
    printf("\n=====================================\n");
    printf("              SOULSMAR               \n");
    printf("=====================================\n");
    printf("1 - Novo jogo\n2 - Continuar jogo salvo\n3 - Sobre\n0 - Sair\n");
    printf("-------------------------------------\n");
}

int lerOpcao(int min, int max) {
    char linha[100], *fim;
    long valor;
    while (1) {
        printf("> ");
        if (!fgets(linha, sizeof(linha), stdin)) return min;
        valor = strtol(linha, &fim, 10);
        while (*fim == ' ' || *fim == '\t') fim++;
        if (fim == linha || (*fim != '\n' && *fim != '\0') ||
            valor < min || valor > max)
            printf("Opcao invalida. Digite um numero entre %d e %d.\n", min, max);
        else
            return (int)valor;
    }
}

void pausar(void) {
    char linha[8];
    printf("\nPressione ENTER para continuar...");
    fgets(linha, sizeof(linha), stdin);
}

void mostrarStatus(const Personagem *p) {
    printf("\n+--------------------------------------+\n");
    printf("| %-36s |\n", p->nome);
    printf("| Vida: %-4d/%-4d  Forca: %-4d        |\n",
           p->vida, p->vidaMaxima, p->forca);
    printf("| Pocoes: %-3d  Experiencia: %-5d      |\n",
           p->pocoes, p->experiencia);
    printf("+--------------------------------------+\n");
}

void mostrarArte(int etapa) {
    switch (etapa) {
        case 1:
            printf("\n       /\\\n      /  \\\n     /____\\\n       ||\n   A FLORESTA\n");
            break;
        case 2:
            printf("\n      _______\n     / _____ \\\n    | |     | |\n    |_|     |_|\n  RUINAS ANTIGAS\n");
            break;
        case 3:
            printf("\n       .---.\n      /     \\\n     |  ???  |\n      \\_____/\n  CAVERNA ECOANTE\n");
            break;
        case 4:
            printf("\n      /~~~~~\\\n     /  ^^^  \\\n    /_________\\\n   TERRENO SOMBRIO\n");
            break;
        default:
            printf("\n         /\\\n        /!!\\\n       /!!!!\\\n      /______\\\n  SANTUARIO FINAL\n");
    }
}

void explorar(Personagem *p, int etapa) {
    int evento;
    int chanceMonstro = 0;

    if (etapa == 3) chanceMonstro = 20;
    else if (etapa == 4) chanceMonstro = 35;
    else if (etapa >= 5) chanceMonstro = 50;

    printf("\nVoce examina o local com cuidado...\n");

    if (chanceMonstro > 0 && rand() % 100 < chanceMonstro) {
        const char *nomes[TOTAL_ETAPAS] = {
            "Lobo das Sombras", "Sentinela Enferrujado",
            "Aranha das Profundezas", "Cavaleiro Corrompido",
            "Guardiao de SoulsMar"
        };

        const int vidas[TOTAL_ETAPAS] = {32, 43, 52, 65, 90};
        const int forcas[TOTAL_ETAPAS] = {6, 7, 8, 10, 12};
        const int xp[TOTAL_ETAPAS] = {10, 12, 15, 18, 30};

        Inimigo inimigo;

        printf("\n!!! VOCE FOI SURPREENDIDO POR UM MONSTRO! !!!\n");

        strcpy(inimigo.nome, nomes[etapa - 1]);
        inimigo.vida = vidas[etapa - 1];
        inimigo.forca = forcas[etapa - 1];
        inimigo.recompensa = xp[etapa - 1];

        if (!combater(p, inimigo)) {
            printf("\nA exploracao terminou em derrota...\n");
            p->vida = 0;
        }

        return;
    }

    evento = rand() % 3;

    if (evento == 0) {
        int cura = 12 + rand() % 10;
        p->vida += cura;

        if (p->vida > p->vidaMaxima)
            p->vida = p->vidaMaxima;

        printf("Uma fonte antiga recupera sua vida (ate %d pontos).\n", cura);

    } else if (evento == 1) {
        p->pocoes++;
        printf("Voce encontrou uma pocao! Total: %d.\n", p->pocoes);

    } else {
        int dano = 5 + rand() % 8;
        p->vida -= dano;

        if (p->vida < 1)
            p->vida = 1;

        printf("Uma armadilha causa %d de dano.\n", dano);
    }
}

int combater(Personagem *p, Inimigo inimigo) {
    printf("\nUm inimigo apareceu: %s!\n", inimigo.nome);
    while (p->vida > 0 && inimigo.vida > 0) {
        int acao, dano;
        mostrarStatus(p);
        printf("\n%s - Vida: %d\n", inimigo.nome, inimigo.vida);
        printf("1 - Ataque comum\n2 - Golpe poderoso (70%% de chance)\n");
        printf("3 - Usar pocao (%d disponiveis)\n", p->pocoes);
        acao = lerOpcao(1, 3);

        if (acao == 1) {
            dano = p->forca + rand() % 6;
            inimigo.vida -= dano;
            printf("Voce causa %d de dano!\n", dano);
        } else if (acao == 2) {
            if (rand() % 100 < 70) {
                dano = p->forca + 9 + rand() % 9;
                inimigo.vida -= dano;
                printf("Golpe poderoso! %d de dano!\n", dano);
            } else {
                printf("Voce errou o golpe!\n");
            }
        } else {
            if (p->pocoes == 0) {
                printf("Voce nao possui pocoes!\n");
                continue;
            }
            p->pocoes--;
            p->vida += 25;
            if (p->vida > p->vidaMaxima) p->vida = p->vidaMaxima;
            printf("Voce recuperou vida usando uma pocao.\n");
        }

        if (inimigo.vida > 0) {
            int recebido = inimigo.forca + rand() % 4;
            p->vida -= recebido;
            printf("%s contra-ataca e causa %d de dano!\n", inimigo.nome, recebido);
        }
    }

    if (p->vida <= 0) {
        printf("\nVoce foi derrotado por %s...\n", inimigo.nome);
        return 0;
    }

    printf("\n%s foi derrotado! +%d de experiencia.\n",
           inimigo.nome, inimigo.recompensa);
    p->experiencia += inimigo.recompensa;
    if (p->experiencia >= 30) {
        p->experiencia -= 30;
        p->vidaMaxima += 10;
        p->forca += 3;
        p->vida = p->vidaMaxima;
        printf("\n*** NOVO NIVEL! Vida maxima +10, forca +3 e vida restaurada. ***\n");
    }
    return 1;
}

int salvar(const Personagem *p, int etapa) {
    FILE *arq = fopen(SAVE, "w");
    if (!arq) {
        printf("Erro ao abrir o arquivo de salvamento.\n");
        return 0;
    }
    fprintf(arq, "%s\n%d %d %d %d %d %d\n", p->nome, p->vida,
            p->vidaMaxima, p->forca, p->pocoes, p->experiencia, etapa);
    if (fclose(arq) != 0) {
        printf("Erro ao fechar o arquivo de salvamento.\n");
        return 0;
    }
    printf("Jogo salvo com sucesso!\n");
    return 1;
}

int carregar(Personagem *p, int *etapa) {
    FILE *arq = fopen(SAVE, "r");
    if (!arq) {
        printf("Nenhum salvamento encontrado.\n");
        return 0;
    }
    if (!fgets(p->nome, sizeof(p->nome), arq) ||
        fscanf(arq, "%d %d %d %d %d %d", &p->vida, &p->vidaMaxima,
               &p->forca, &p->pocoes, &p->experiencia, etapa) != 6) {
        printf("Arquivo de salvamento invalido.\n");
        fclose(arq);
        return 0;
    }
    p->nome[strcspn(p->nome, "\r\n")] = '\0';
    fclose(arq);
    if (p->vida < 1 || p->vida > p->vidaMaxima || p->vidaMaxima < 1 ||
        p->forca < 1 || p->pocoes < 0 || *etapa < 1 || *etapa > TOTAL_ETAPAS) {
        printf("Dados do salvamento inconsistentes.\n");
        return 0;
    }
    return 1;
}

void jogar(Personagem *p, int etapa) {
    const char *nomes[TOTAL_ETAPAS] = {
        "Lobo das Sombras", "Sentinela Enferrujado",
        "Aranha das Profundezas", "Cavaleiro Corrompido",
        "Guardiao de SoulsMar"
    };
    const int vidas[TOTAL_ETAPAS] = {32, 43, 52, 65, 90};
    const int forcas[TOTAL_ETAPAS] = {6, 7, 8, 10, 12};
    const int xp[TOTAL_ETAPAS] = {10, 12, 15, 18, 30};

    while (etapa <= TOTAL_ETAPAS && p->vida > 0) {
        int escolha;
        Inimigo inimigo;
        printf("\n=====================================\nETAPA %d/%d\n", etapa, TOTAL_ETAPAS);
        mostrarArte(etapa);
        printf("\n1 - Explorar\n2 - Consultar personagem\n");
        printf("3 - Salvar e voltar ao menu\n4 - Enfrentar o inimigo\n");
        escolha = lerOpcao(1, 4);

        if (escolha == 1) {
            explorar(p, etapa);
            	if (p->vida <= 0) {
			    printf("Fim de jogo. Voce foi derrotado na etapa %d.\n", etapa);
			    pausar();
			    return;
				}
            pausar();
        } else if (escolha == 2) {
            mostrarStatus(p);
            pausar();
        } else if (escolha == 3) {
            salvar(p, etapa);
            return;
        } else {
            strcpy(inimigo.nome, nomes[etapa - 1]);
            inimigo.vida = vidas[etapa - 1];
            inimigo.forca = forcas[etapa - 1];
            inimigo.recompensa = xp[etapa - 1];

            if (!combater(p, inimigo)) {
                printf("Fim de jogo. Voce chegou a etapa %d.\n", etapa);
                pausar();
                return;
            }
            etapa++;
            if (etapa <= TOTAL_ETAPAS) {
                p->vida += 10;
                if (p->vida > p->vidaMaxima) p->vida = p->vidaMaxima;
                printf("\nVoce descansa e recupera ate 10 pontos de vida.\n");
                pausar();
            }
        }
    }

    if (p->vida > 0 && etapa > TOTAL_ETAPAS) {
        printf("\n=====================================\n");
        printf("       VOCE CONCLUIU A JORNADA!\n");
        printf("=====================================\n");
        printf("O Guardiao caiu. SoulsMar esta livre!\n");
        mostrarStatus(p);
        remove(SAVE);
        pausar();
    }
}

void novoJogo(void) {
    Personagem p = {"Viajante", 100, 100, 12, 3, 0};
    char nome[50];
    printf("\n=== NOVA JORNADA ===\nNome do personagem: ");
    if (!fgets(nome, sizeof(nome), stdin)) return;
    nome[strcspn(nome, "\r\n")] = '\0';
    if (strlen(nome) > 0) {
        strncpy(p.nome, nome, sizeof(p.nome) - 1);
        p.nome[sizeof(p.nome) - 1] = '\0';
    }
    printf("\nCinco desafios aguardam por voce, %s.\n", p.nome);
    jogar(&p, 1);
}

void continuarJogo(void) {
    Personagem p;
    int etapa;
    if (carregar(&p, &etapa)) {
        printf("\nBem-vindo de volta, %s!\n", p.nome);
        jogar(&p, etapa);
    }
}

int main(void) {
    int opcao;
    srand((unsigned int)time(NULL));
    do {
        mostrarMenu();
        printf("Escolha: ");
        opcao = lerOpcao(0, 3);
        switch (opcao) {
            case 1: novoJogo(); break;
            case 2: continuarJogo(); break;
            case 3:
                printf("\nSoulsMar e um RPG textual em C. Explore, lute e supere cinco desafios.\n");
                pausar();
                break;
            case 0: printf("\nObrigado por jogar SoulsMar!\n"); break;
        }
    } while (opcao != 0);
    return 0;
}
