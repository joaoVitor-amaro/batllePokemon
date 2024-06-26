#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

//Enum com tipos de pokemons para fazer vantagem entre tipos posteriormente
typedef enum{
    Agua,
    Planta,
    Fogo,
    Inseto,
    Venenoso,
    Eletrico,
    Fada,
    Lutador
} Tipos;

typedef struct{
    char nome_ataques[50];
    int dano_ataques;
} Ataques;

//Struct que contem as caracteristicas principais dos pokemons
typedef struct{
    char nome[50];
    Tipos tipo;
    int ataque;
    int defesa;
    int stamina;
    int vida;
    Ataques ataques[4];
} Status;

// struct com nome e escolhas jogador 1
typedef struct{
    char nome[20];
    Status escolhas[3];
}Jogador1;

// struct com nome e escolhas jogador 2
typedef struct
{
    char nome[20];
    Status escolhas[3];
}Jogador2;

// struct que agrupa os dois jogadores para uso em fun��o posterior
typedef struct
{
    Jogador1 jogador1;
    Jogador2 jogador2;
}Jogo;

//Função que calcula o dano do pokemon durante a rodada
int calcular_dano(int atk_agressor, int def_defensor){

    int dano = (atk_agressor - def_defensor);

     if (dano <= 0) {
        dano = 0;
        int dano_comum = rand() % 8 + 1;
        dano += dano_comum;
     }
     return dano;

}

//Função que determina o dano final dependendo do tipo dos pokemons na batalha
int dano_tipo(Tipos tipo_agressor, Tipos tipo_defensor, int dano){
    int novo_dano = dano;

    switch (tipo_agressor){
        case Agua:
            if (tipo_defensor == Planta){
                novo_dano -= 4;
            } else if (tipo_defensor == Fogo){
                novo_dano += 6;
            }
            break;
        case Planta:
            if (tipo_defensor == Agua){
                novo_dano += 6;
            } else if (tipo_defensor == Fogo){
                novo_dano -= 4;
            } else if (tipo_defensor == Inseto){
                novo_dano -= 4;
            } else if (tipo_defensor == Venenoso){
                novo_dano -= 4;
            }
            break;
        case Fogo:
            if (tipo_defensor == Agua){
                novo_dano -= 4;
            } else if (tipo_defensor == Planta){
                novo_dano += 6;
            } else if (tipo_defensor == Inseto){
                novo_dano += 6;
            }
            break;
        case Inseto:
            if (tipo_defensor == Planta){
                novo_dano += 6;
            } else if (tipo_defensor == Fogo){
                novo_dano -= 4;
            }
            break;
        case Venenoso:
            if (tipo_defensor == Planta){
                novo_dano += 6;
            } else if (tipo_defensor == Fada){
                novo_dano += 6;
            }
            break;
        case Eletrico:
            if (tipo_defensor == Agua){
                novo_dano += 6;
            }
            break;
        case Fada:
            if (tipo_defensor == Lutador){
                novo_dano += 6;
            } else if (tipo_defensor == Venenoso){
                novo_dano -= 4;
            }
            break;
        case Lutador:
            if (tipo_defensor == Fada){
                novo_dano -= 4;
            }
            break;
    }

    if (novo_dano < 0){
        novo_dano = 0;
    }
    return novo_dano;

}

void atualizacao_vida(Status *pokemon, int novo_dano){
    pokemon->vida -= novo_dano;

    if (pokemon->vida > 0){
        printf("%s recebeu %d de dano. Resta %d de vida\n", pokemon->nome, novo_dano, pokemon->vida);

    } else {
        printf("%s recebeu %d de dano. Resta 0 de vida\n", pokemon->nome, novo_dano);
    }
}

//Função que recebe os status do pokemon e guarda essas informações
Status criacao_pokemon(char* nome, Tipos tipo, int atk, int def, int stm, int hp, Ataques ataques[4]){
    int i;
    Status personagem;
    strcpy(personagem.nome, nome);
    personagem.tipo = tipo;
    personagem.ataque = atk;
    personagem.defesa = def;
    personagem.stamina = stm;
    personagem.vida = hp;

    for (i = 0; i < 4; i++) {
        strcpy(personagem.ataques[i].nome_ataques, ataques[i].nome_ataques);
        personagem.ataques[i].dano_ataques = ataques[i].dano_ataques;
    }

    return personagem;
}

//Função de listar pokemons
void listaPokemon(Status *pokemons) {
    int i;
    printf("-----------------------------------\n");
    printf("\tLista de Pokemons\n");
    printf("-----------------------------------\n");
    for(i=0; i < 8; i++) {
        printf("%d - %s", i+1, pokemons[i].nome);
        printf("\t");
        if(i % 2 != 0) {
            printf("\n");
        }
    }
    printf("\n----------------------------------\n");
}

// Função de escolher pokemons
void escolherPokemon(Jogo *jogo, int jogadorNumero, Status *pokemons, int n) {
    int escolha;

    if (jogadorNumero == 1) {
        printf("Jogador 1, escolha seu pokémon (1-%d): ", n);
        scanf("%d", &escolha);
        while (escolha < 1 || escolha > n) {
            printf("Escolha inválida. Tente novamente: ");
            scanf("%d", &escolha);
        }
        jogo->jogador1.escolhas[0] = pokemons[escolha - 1];
    } else {
        printf("Jogador 2, escolha seu pokémon (1-%d): ", n);
        scanf("%d", &escolha);
        while (escolha < 1 || escolha > n) {
            printf("Escolha inválida. Tente novamente: ");
            scanf("%d", &escolha);
        }
        jogo->jogador2.escolhas[0] = pokemons[escolha - 1];
    }
}

void statusPokemon(Status *pokemon, int numPoke) {
    int i;
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("      Pokemon %s\n", pokemon[numPoke - 1].nome);
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("Poder: %d\n", pokemon[numPoke - 1].ataque);
    printf("Defesa: %d\n", pokemon[numPoke - 1].defesa);
    printf("Stamina: %d\n", pokemon[numPoke - 1].stamina);
    printf("Vida: %d\n", pokemon[numPoke - 1].vida);
    printf("Ataques:\n");
    for (i = 0; i < 4; ++i) {
        printf("%d - %s | Dano: %d)\n", i + 1, pokemon[numPoke - 1].ataques[i].nome_ataques, pokemon[numPoke - 1].ataques[i].dano_ataques);
    }
    printf("--------------------------\n");
}

//Menu de escolher e ver status dos pokemons
void menuSelecionar() {
    printf("=-=-=-=-==-=-=-=\n");
    printf("[1] - Escolher\n");
    printf("[2] - Pokemons\n");
    printf("=-=-=-=-==-=-=-=\n");
}

// função de batalha
void batalha(Jogo *jogo){
    int jogador1_escolha, jogador2_escolha;
    int ataque1_escolha, ataque2_escolha;

    printf("\nIniciando batalha!\n");

    // Escolha de pokémons para batalha
    printf("\nJogador 1, confirme a escolha do seu pokemon (1 - Sim 0 - Não): ");
    scanf("%d", &jogador1_escolha);
    jogador1_escolha -= 1; // Ajusta para índice

    printf("\nJogador 2, confirme a escolha do seu pokemon (1 - Sim 0 - Não): ");
    scanf("%d", &jogador2_escolha);
    jogador2_escolha -= 1; // Ajusta para índice

     if (jogador2_escolha != 0 || jogador1_escolha != 0)
    {
        exit(0);
    }


    Status *pokemon1 = &jogo->jogador1.escolhas[jogador1_escolha];
    Status *pokemon2 = &jogo->jogador2.escolhas[jogador2_escolha];

    while (pokemon1->vida > 0 && pokemon2->vida > 0) {
        int i;
        // Ataque do jogador 1
        printf("\nJogador 1, escolha um ataque para seu %s (1-4):\n", pokemon1->nome);
        for (i = 0; i < 4; i++) {
            printf("%d - %s\n", i + 1, pokemon1->ataques[i].nome_ataques);
        }
        scanf("%d", &ataque1_escolha);
        ataque1_escolha -= 1; //Necessario para compreender o indice do array

         // Mostra o ataque usado pelo pokemon 1 e a vida do defensor apos o ataque
        printf("\n%s usa %s\n", pokemon1->nome, pokemon1->ataques[ataque1_escolha].nome_ataques);
        int dano1 = calcular_dano(pokemon1->ataques[ataque1_escolha].dano_ataques, pokemon2->defesa);
        int dano1final = dano_tipo(pokemon1->tipo, pokemon2->tipo, dano1);
        atualizacao_vida(pokemon2, dano1final);

        // Verifica a vida dos pokemons após o primeiro ataque
         if (pokemon1->vida <= 0)
        {
            printf("\nJogador 2 vence a batalha!\n");
            return;
        } else if (pokemon2->vida <= 0)
        {
            printf("\nJogador 1 vence a batalha!\n");
            return;
        }

        // Ataque do jogador 2
        printf("\nJogador 2, escolha um ataque para %s (1-4):\n", pokemon2->nome);
        for (i = 0; i < 4; i++) {
            printf("%d - %s\n", i + 1, pokemon2->ataques[i].nome_ataques);
        }
        scanf("%d", &ataque2_escolha);
        ataque2_escolha -= 1;

        printf("\n%s usa %s\n", pokemon2->nome, pokemon2->ataques[ataque2_escolha].nome_ataques);
        int dano2 = calcular_dano(pokemon2->ataques[ataque2_escolha].dano_ataques, pokemon1->defesa);
        int dano2final = dano_tipo(pokemon2->tipo, pokemon1->tipo, dano2);
        atualizacao_vida(pokemon1, dano2final);

        // Verifica a vida dos pokemons após segundo ataque

    if (pokemon1->vida <= 0)
        {
            printf("\nJogador 2 vence a batalha!\n");
            return;
        } else if (pokemon2->vida <= 0)
        {
            printf("\nJogador 1 vence a batalha!\n");
            return;
        }
   }
}

void menu() {
    printf("\nMenu:\n");
    printf("[1] Escolher Pokémons\n");
    printf("[2] Exibir lista de Pokémons\n");
    printf("[3] Iniciar batalha\n");
    printf("[4] Sair\n");
}


int main() {
    setlocale(LC_ALL, "portuguese");

    srand(time(NULL)); //Gerador de numeros aleatorios

    Jogo jogo;
    //Preenchendo a struct com os ataques dos pokemons
    Ataques golpes_squirtle[4] = {{"Tackle", 40}, {"Water Gun", 60}, {"Bite", 50}, {"Bubble", 45}};
    Ataques golpes_bulbassaur[4] = {{"Tackle", 40}, {"Vine Whip", 45}, {"Seed Bomb", 50}, {"Razor Leaf", 55}};
    Ataques golpes_charmander[4] = {{"Scratch", 40}, {"Ember", 60}, {"Fire Fang", 55}, {"Slash", 70}};
    Ataques golpes_butterfree[4] = {{"Gust", 40}, {"Bug Bite", 35}, {"Air Slash", 50}, {"Psybeam", 65}};
    Ataques golpes_ekans[4] = {{"Poison Sting", 30}, {"Acid", 40}, {"Bite", 60}, {"Wrap", 45}};
    Ataques golpes_pikachu[4] = {{"Thunder Shock", 40}, {"Spark", 50}, {"Quick Attach", 55}, {"Iron Tail", 60}};
    Ataques golpes_clefairy[4] = {{"Pound", 40}, {"Stored Power", 50}, {"Double Slap", 45}, {"Disarming Voice", 60}};
    Ataques golpes_mankey[4] = {{"Karate Chop", 50}, {"Cross Chop", 70}, {"Scratch", 40}, {"Pursuit", 45}};

    Status pokemon[8];
    // Dados dos pokemons
    pokemon[0] = criacao_pokemon("Squirtle", Agua, 48, 65, 50, 44, golpes_squirtle);
    pokemon[1] = criacao_pokemon("Bulbassaur", Planta, 49, 49, 40, 45, golpes_bulbassaur);
    pokemon[2] = criacao_pokemon("Charmander", Fogo, 52, 43, 36, 39, golpes_charmander);
    pokemon[3] = criacao_pokemon("Butterfree", Inseto, 45, 50, 39, 60, golpes_butterfree);
    pokemon[4] = criacao_pokemon("Ekans", Venenoso, 60, 44, 38, 35, golpes_ekans);
    pokemon[5] = criacao_pokemon("Pikachu", Eletrico, 55, 40, 35, 35, golpes_pikachu);
    pokemon[6] = criacao_pokemon("Clefairy", Fada, 45, 48, 38, 70, golpes_clefairy);
    pokemon[7] = criacao_pokemon("Mankey", Lutador, 80, 35, 37, 40, golpes_mankey);

    int opcao;
    int pokemons_escolhidos = 0;

    while (1) {
        menu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                listaPokemon(pokemon);
            // Jogador 1 escolhe o pokémon
                escolherPokemon(&jogo, 1, pokemon, 8);
                // Jogador 2 escolhe o pokémon
                escolherPokemon(&jogo, 2, pokemon, 8);
                pokemons_escolhidos = 1;

                printf("\nEscolha do jogador 1:\n");
                printf("%s\n", jogo.jogador1.escolhas[0].nome);

                printf("\nEscolha do jogador 2:\n");
                printf("%s\n", jogo.jogador2.escolhas[0].nome);

                continue;
            case 2:
                // Exibir lista de pokémons
                listaPokemon(pokemon);
                printf("Digite o número do pokémon para ver os detalhes: ");
                int numPoke;
                scanf("%d", &numPoke);
                statusPokemon(pokemon, numPoke);
                continue;
            case 3:
                // Iniciar batalha
                if (pokemons_escolhidos) {
                    batalha(&jogo);
                } else {
                    printf("\nVocê precisa escolher seu pok�mon primeiro!\n");
                }
                menu();
                printf("Escolha uma opção: ");
                scanf("%d", &opcao);
                break;
            case 4:
                // Sair do jogo
                printf("\nSaindo do jogo...\n");
                return 0;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
                break;
        }

  }
  return 0;
}
