#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif

typedef struct {
    char nome[40];
    int tipo;
    int valor; 
    int quantidade;
} Item;

typedef struct {
    char nome[50];
    char classe[30];
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
int lerInteiro(int min, int max);



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
                
            case 2:
          
            case 3:
                
            case 0:
                
        }
    } while (opcao != 0);

  return 0;
}

void limparTela(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
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
