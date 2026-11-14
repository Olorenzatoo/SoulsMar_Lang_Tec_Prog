#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(int argc, char *argv[]){

    Personagem jogador;
    int opcao;

  do {
    
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
