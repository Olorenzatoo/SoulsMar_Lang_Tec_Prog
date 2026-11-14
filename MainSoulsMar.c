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

void criarPersonagem(Personagem *p);
void exibirStatus(Personagem *p);

void loopExploracao(Personagem *p);
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
                
                break;
            case 2:
                
                break;
            case 3:
                
                break;
            case 4:
                
                break;
            case 5:
                
                break;
            case 0:
                return;
        }
    }

    
}
