#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Jogador {
  char tipo_jogador[20];
  int vida;
  int forca;
  int defesa;
  int agilidade;
  int inteligencia;
};

struct Monstros {
  char nome_mon[50];
  char alcunha[30];
  int vida;
  int defesa;
  int ataque;
  int velocidade;
};

int menu_ataques(){
    int opcao_ataque = 0;
    printf("\n----------------------------\n");
    printf("\n| 1 - Ataque simples       |\n");
    printf("\n| 2 - Regeneração e Ataque |\n");
    printf("\n| 3 - Ataque crítico       |\n");
    printf("\n| 4 - Ataque rápido        |\n");
    printf("\n----------------------------\n");
    printf("\nESCOLHA SUA OPÇÃO DE ATAQUE: ");
    scanf("%d", &opcao_ataque);

    return opcao_ataque;
}



void combate_monstro(struct Monstros mons[], struct Jogador jog[], int tipo_monstro, int tipo_jogador) {
    int dano = 0;
    dano = mons[tipo_monstro].ataque - (jog[tipo_jogador - 1].defesa / 2);

    if (dano < 0){
        dano = 20;
    }

    printf("\n-----------------------------\n");
    printf("\n|    VOCÊ PERDEU NO DADO    |\n");
    printf("\n|    E RECEBEU %d DE DANO   |\n", dano);
    printf("\n-----------------------------\n");

    jog[tipo_jogador - 1].vida -= dano;
}

void combate_jogador(struct Monstros mons[], int tipo_monstro, int *dano) {
    
    //dano = jog[tipo_jogador - 1].forca - (mons[tipo_monstro].defesa / 2);

    if (dano < 0) {
        *dano = 20;
    }

    printf("\n----------------------------\n");
    printf("\n|    VOCÊ GANHOU NO DADO   |\n");
    printf("\n|    E DEU %d DE DANO      |\n", *dano);
    printf("\n----------------------------\n");

    mons[tipo_monstro].vida -= *dano;
    }

void tipos_ataques(struct Monstros mons[], struct Jogador jog[], int tipo_jogador, int tipo_monstro){
    int ataques = 0, dano_mons = 0;

    ataques = menu_ataques();

    if (ataques == 1){
        dano_mons = jog[tipo_jogador - 1].forca - (mons[tipo_monstro].defesa / 2);
        combate_jogador(mons, tipo_monstro, &dano_mons);
    }

    else if (ataques == 2){
        jog[tipo_jogador - 1].vida += 20;
        dano_mons = jog[tipo_jogador - 1].forca / 2;
        combate_jogador(mons, tipo_monstro, &dano_mons);
    }

    else if (ataques == 3){
        int aposta_num = 0, apostador = 0;

        aposta_num = random() %10 + 0;

        printf("\n--------------------\n");
        printf("\n| ACERTE O NÚMERO  |\n");
        printf("\n--------------------\n");
        printf("\nDIGITE O NÚMERO: ");
        scanf("%d", &apostador);

        if (apostador == aposta_num){
            printf("\n------------------\n");
            printf("\n|  NÚMERO CERTO  |\n");
            printf("\n------------------\n");

            dano_mons = jog[tipo_jogador - 1].forca;
            dano_mons *= 1.5;

            combate_jogador(mons, tipo_monstro, &dano_mons);
        }
        else {
            printf("\n-----------------------\n");
            printf("\n|    NÚMERO ERRADO    |\n");
            printf("\n-----------------------\n");

            combate_jogador(mons, tipo_monstro, &dano_mons);
        }
    }

    else if (ataques == 4){
        dano_mons = jog[tipo_jogador - 1].forca * 0.6;
        combate_jogador(mons, tipo_monstro, &dano_mons);
    }

}

int combate_completo(struct Monstros mons[], struct Jogador jog[],int tipo_monstro, int tipo_jogador) {
        
        int dado_jogador = random() % 20 + 1;
        int dado_monstro = random() % 20 + 1;

        printf("\nDado do jogador: %d", dado_jogador);
        printf("\nDado do monstro: %d", dado_monstro);

        if (dado_monstro > dado_jogador) {

            combate_monstro(mons, jog, tipo_monstro, tipo_jogador);

            if (jog[tipo_jogador - 1].vida <= 0) {
            printf("\n----------------------------------\n");
            printf("\n|    VOCÊ PERDEU PARA O MONSTRO   |\n");
            printf("\n|            GAME OVER            |\n");
            printf("\n-----------------------------------\n");
            return 1;
            }
        }

        else if (dado_jogador > dado_monstro) {

            tipos_ataques(mons, jog, tipo_jogador, tipo_monstro);

            if (mons[tipo_monstro].vida <= 0) {
            printf("\n--------------------------------------\n");
            printf("\n|       VOCÊ VENCEU O MONSTRO        |\n");
            printf("\n--------------------------------------\n");
            printf("\n|  GANHOU 25 EM TODOS OS  ATRIBUTOS  |\n");
            printf("\n--------------------------------------\n");
            jog[tipo_jogador - 1].vida += 25;
            jog[tipo_jogador - 1].forca += 25;
            jog[tipo_jogador - 1].defesa += 25;
            jog[tipo_jogador - 1].agilidade += 25;
            jog[tipo_jogador - 1].inteligencia += 25;
            return 0;
            }
        }

        else {
            printf("\n----------------------------\n");
            printf("\n|     DADOS EMPATADOS      |\n");
            printf("\n----------------------------\n");
        }
        return 0;
    }

    int tabuleiro(int posicao_tabu, struct Monstros mons[], int tipo_jogador,struct Jogador jog[], int *qntd_monstros) {
        int tipo_monstro = 0;
        int perdeu = 0;

        switch (posicao_tabu) {
        case 1:
            printf("+------------+\n");
            printf("| 1          |\n");
            printf("| Inicio     |\n");
            printf("+------------+\n");
            break;

        case 2:
            printf("+------------+\n");
            printf("| 2          |\n");
            printf("| Vazia      |\n");
            printf("+------------+\n");
            break;

        case 3:
            printf("+------------+\n");
            printf("| 3          |\n");
            printf("| Combate    |\n");
            printf("+------------+\n");

            tipo_monstro = random() % 2 + 0;

            printf("\n----------------------------------\n");
            printf("\n|   CARACTERÍSTICAS DO MONSTRO   |\n");
            printf("\n----------------------------------\n");
            printf("\n Nome: %s\n", mons[tipo_monstro].nome_mon);
            printf("\nAlcunha: %s\n", mons[tipo_monstro].alcunha);
            printf("\nVida: %d\n", mons[tipo_monstro].vida);
            printf("\nDefesa: %d\n", mons[tipo_monstro].defesa);
            printf("\nAtaque: %d\n", mons[tipo_monstro].ataque);
            printf("\nVelocidade: %d\n", mons[tipo_monstro].velocidade);

            printf("\n----------------------------\n");
            printf("\n|  DUELO CONTRA O MONSTRO  |\n");
            printf("\n----------------------------\n");
        do {
        perdeu = combate_completo(mons, jog, tipo_monstro, tipo_jogador);
        if (perdeu == 1) {
            return 1;
        }

        } while (jog[tipo_jogador - 1].vida > 0 && mons[tipo_monstro].vida > 0);
        tipo_monstro = 0;
        break;

    case 4:
        printf("+------------+\n");
        printf("| 4          |\n");
        printf("| Tesouro    |\n");
        printf("+------------+\n");
        break;

    case 5:
        printf("+------------+\n");
        printf("| 5          |\n");
        printf("| Vazia      |\n");
        printf("+------------+\n");
        break;

    case 6:
        printf("+------------+\n");
        printf("| 6          |\n");
        printf("| Cura       |\n");
        printf("+------------+\n");
        break;

    case 7:
        printf("+------------+\n");
        printf("| 7          |\n");
        printf("| Armadilha  |\n");
        printf("+------------+\n");
        break;

    case 8:
        printf("+------------+\n");
        printf("| 8          |\n");
        printf("| Vazia      |\n");
        printf("+------------+\n");
        break;

    case 9:
        printf("+------------+\n");
        printf("| 9          |\n");
        printf("| Vazia      |\n");
        printf("+------------+\n");
        break;

    case 10:
        printf("+------------+\n");
        printf("| 10         |\n");
        printf("| Tesouro    |\n");
        printf("+------------+\n");
        break;

    case 11:
        printf("+------------+\n");
        printf("| 11         |\n");
        printf("| Missao     |\n");
        printf("+------------+\n");
        break;

    case 12:
        printf("+------------+\n");
        printf("| 12         |\n");
        printf("| Combate    |\n");
        printf("+------------+\n");

        tipo_monstro = random() % 3 + 3;

            printf("\n----------------------------------\n");
            printf("\n|   CARACTERÍSTICAS DO MONSTRO   |\n");
            printf("\n----------------------------------\n");
            printf("\n Nome: %s\n", mons[tipo_monstro].nome_mon);
            printf("\nAlcunha: %s\n", mons[tipo_monstro].alcunha);
            printf("\nVida: %d\n", mons[tipo_monstro].vida);
            printf("\nDefesa: %d\n", mons[tipo_monstro].defesa);
            printf("\nAtaque: %d\n", mons[tipo_monstro].ataque);
            printf("\nVelocidade: %d\n", mons[tipo_monstro].velocidade);

            printf("\n----------------------------\n");
            printf("\n|  DUELO CONTRA O MONSTRO  |\n");
            printf("\n----------------------------\n");

        perdeu = 0;

        do {
        perdeu = combate_completo(mons, jog, tipo_monstro, tipo_jogador);
        if (perdeu == 1) {
            return 1;
        }

        } while (jog[tipo_jogador - 1].vida > 0 && mons[tipo_monstro].vida > 0);
        tipo_monstro = 0;
        break;

    case 13:
        printf("+------------+\n");
        printf("| 13         |\n");
        printf("| Vazia      |\n");
        printf("+------------+\n");
        break;

    case 14:
        printf("+------------+\n");
        printf("| 14         |\n");
        printf("| Cura       |\n");
        printf("+------------+\n");
        break;

    case 15:
        printf("+------------+\n");
        printf("| 15         |\n");
        printf("| Vazia      |\n");
        printf("+------------+\n");
        break;

    case 16:
        printf("+------------+\n");
        printf("| 16         |\n");
        printf("| Tesouro    |\n");
        printf("+------------+\n");
        break;

    case 17:
        printf("+------------+\n");
        printf("| 17         |\n");
        printf("| Missao     |\n");
        printf("+------------+\n");
        break;

    case 18:
        printf("+------------+\n");
        printf("| 18         |\n");
        printf("| Vazia      |\n");
        printf("+------------+\n");
        break;

    case 19:
        printf("+------------+\n");
        printf("| 19         |\n");
        printf("| Vazia      |\n");
        printf("+------------+\n");
        break;

    case 20:
        printf("+------------+\n");
        printf("| 20         |\n");
        printf("| Armadilha  |\n");
        printf("+------------+\n");
        break;

    case 21:
        printf("+------------+\n");
        printf("| 21         |\n");
        printf("| Cura       |\n");
        printf("+------------+\n");
        break;

    case 22:
        printf("+------------+\n");
        printf("| 22         |\n");
        printf("| Tesouro    |\n");
        printf("+------------+\n");
        break;

    case 23:
        printf("+------------+\n");
        printf("| 23         |\n");
        printf("| Vazia      |\n");
        printf("+------------+\n");
        break;

    case 24:
        printf("+------------+\n");
        printf("| 24         |\n");
        printf("| Chefe/Fim  |\n");
        printf("+------------+\n");
        tipo_monstro = random() %3 + 6;

        printf("\n----------------------------------\n");
        printf("\n|   CARACTERÍSTICAS DO MONSTRO   |\n");
        printf("\n----------------------------------\n");
        printf("\n Nome: %s\n", mons[tipo_monstro].nome_mon);
        printf("\nAlcunha: %s\n", mons[tipo_monstro].alcunha);
        printf("\nVida: %d\n", mons[tipo_monstro].vida);
        printf("\nDefesa: %d\n", mons[tipo_monstro].defesa);
        printf("\nAtaque: %d\n", mons[tipo_monstro].ataque);
        printf("\nVelocidade: %d\n", mons[tipo_monstro].velocidade);

        printf("\n----------------------------\n");
        printf("\n|  DUELO CONTRA O MONSTRO  |\n");
        printf("\n----------------------------\n");
        perdeu = 0;
        do {
        perdeu = combate_completo(mons, jog, tipo_monstro, tipo_jogador);
        if (perdeu == 1) {
            return 1;
        }

        } while (jog[tipo_jogador - 1].vida > 0 && mons[tipo_monstro].vida > 0);
        break;
    }
    return 0;
}

int menu_continuar() {
    int continuar = 0;
    do {
        printf("\n-----------------------------\n");
        printf("\n|  1 - CONTINUAR            |\n");
        printf("\n|  0 - SAIR                 |\n");
        printf("\n-----------------------------\n");
        printf("ESCOLHA UMA DAS OPÇÕES: ");
        scanf("%d", &continuar);

        if (continuar < 0 || continuar > 1) {
        printf("\nOPÇÃO INVÁLIDA\n");
        }
    } while (continuar < 0 || continuar > 1);

    return continuar;
}

int main() {
    srandom(time(NULL));

    struct Jogador jogador[3] = {{"Zagueiro", 100, 60, 90, 50, 40},
                                {"Meio-Campista", 100, 70, 65, 75, 75},
                                {"Atacante", 100, 90, 45, 85, 55}};

    int escolha_jogador = 0, qntd_monstros = 0;

    do {
        printf("\n-----------------------------");
        printf("\n|     TIPO DE PERSONAGEM    |");
        printf("\n-----------------------------");
        printf("\n1 - %s", jogador[0].tipo_jogador);
        printf("\n2 - %s", jogador[1].tipo_jogador);
        printf("\n3 - %s", jogador[2].tipo_jogador);
        printf("\nFAÇA SUA ESCOLHA: ");

        scanf("%d", &escolha_jogador);

        if (escolha_jogador >= 1 && escolha_jogador <= 3) {
            printf("\nVocê escolheu: %s\n",
            jogador[escolha_jogador - 1].tipo_jogador);
        } 
        else {
            printf("\nEscolha inválida!\n");
        }
    } while (escolha_jogador < 1 || escolha_jogador > 3);

    struct Monstros m[9] = {
        {"Erling Haaland", "Golem de Gelo", 130, 85, 65, 65},
        {"Adama Traoré", "O Juggernaut", 140, 75, 85, 70},
        {"Antonio Rüdiger", "Monstro caótico", 120, 70, 75, 60},
        {"Kevin De Bruyne", "Olho que tudo vê", 170, 90, 70, 75},
        {"Vinícius Junior", "Espectro veloz", 150, 95, 55, 100},
        {"Bernardo Silva", "Sugador de energia", 160, 80, 75, 80},
        {"Lionel Messi", "Feiticeiro do Tempo", 220, 110, 60, 95},
        {"Neymar", "O Ousado / Mestre dos Dribles", 200, 115, 50, 110},
        {"Cristiano Ronaldo", "O Cyborg", 260, 120, 85, 105}};

  // int a = random() %6 + 1;
    int posicao_inicial = 1;
    int continuar_jogo = 0;
    int jogo = 0;
    do {
        int dado_6 = random() % 6 + 1;
        printf("\n\n SUA CASA: \n");
        jogo = tabuleiro(posicao_inicial, m, escolha_jogador, jogador, &qntd_monstros);

        if (jogo == 1) {
        break;
        }

        if (posicao_inicial == 24){
            break;
        }
        
        if (posicao_inicial < 24){
            continuar_jogo = menu_continuar();
        }

        if (continuar_jogo == 1) {
            printf("\nResultado do dado: %d\n", dado_6);

            if (posicao_inicial < 18){
            posicao_inicial += dado_6;
            }

            else if (posicao_inicial >= 18){
            posicao_inicial = 24;
            }

        }
    } while (posicao_inicial < 25 && continuar_jogo == 1);

    printf("\n-------------------------\n");
    printf("\n|     JOGO ENCERRADO    |\n");
    printf("\n-------------------------\n");

    return 0;
}
