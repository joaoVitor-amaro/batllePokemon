#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
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
    Ataques ataques[8];
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

// struct que agrupa os dois jogadores para uso em função posterior
typedef struct 
{
    Jogador1 jogador1;
    Jogador2 jogador2;
}Jogo;



//Funcaoo que calcula o dano do pokemon durante a rodada
int calcular_dano(int atk_agressor, int def_defensor, int stamina_agressor){
    float dano = 0.0;

    dano = (2 * atk_agressor) + (stamina_agressor) - (2 * def_defensor);

    return (int)dano;

}

//Funcaoo que determina o dano final dependendo do tipo dos pokemons na batalha
int dano_tipo(Tipos tipo_agressor, Tipos tipo_defensor, int dano){
    int novo_dano = 0;

    int critico = rand() % 100; // Gera um número aleatório

    if (critico < 5){ // Se o número for menor que cinco, o dano duplica
        dano = dano * 2;
    }

    switch (tipo_agressor){
        case Agua:
            if (tipo_defensor == Planta){
                novo_dano = dano - 10;
            } else if (tipo_defensor == Fogo){
                novo_dano = dano + 15;
            }
            break;
        case Planta:
            if (tipo_defensor == Agua){
                novo_dano = dano + 15;
            } else if (tipo_defensor == Fogo){
                novo_dano = dano - 10;
            } else if (tipo_defensor == Inseto){
                novo_dano = dano - 10;
            } else if (tipo_defensor == Venenoso){
                novo_dano = dano - 10;
            }
            break;
        case Fogo:
            if (tipo_defensor == Agua){
                novo_dano = dano - 10;
            } else if (tipo_defensor == Planta){
                novo_dano = dano + 15;
            } else if (tipo_defensor == Inseto){
                novo_dano = dano + 15;
            }
            break;
        case Inseto:
            if (tipo_defensor == Planta){
                novo_dano = dano + 15;
            } else if (tipo_defensor == Fogo){
                novo_dano = dano - 10;
            }
            break;
        case Venenoso:
            if (tipo_defensor == Planta){
                novo_dano = dano + 15;
            } else if (tipo_defensor == Fada){
                novo_dano = dano + 15;
            }
            break;
        case Eletrico:
            if (tipo_defensor == Agua){
                novo_dano = dano + 15;
            }
            break;
        case Fada:
            if (tipo_defensor == Lutador){
                novo_dano = dano + 15;
            } else if (tipo_defensor == Venenoso){
                novo_dano = dano - 10;
            }
            break;
        case Lutador:
            if (tipo_defensor == Fada){
                novo_dano = dano - 10;
            }
            break;
        default:
            break;
    }
    return novo_dano;
}

void atualizacao_vida(Status *pokemon, int novo_dano){
    pokemon -> vida -= novo_dano;

    printf("%s recebeu %d de dano. Resta %d de vida", pokemon->nome, novo_dano, pokemon->vida);
}

void atualizar_status_apos_batalha(Status *pokemon) {
    pokemon->stamina -= 10; 
    
    if (pokemon->stamina < 0) {
        pokemon->stamina = 0;
    }

    if (pokemon->vida < 0) {
        pokemon->vida = 0;
    }

    printf("\nAp�s a batalha:\n");
    printf("Stamina restante de %s: %d\n", pokemon->nome, pokemon->stamina);
    printf("Vida restante de %s: %d\n", pokemon->nome, pokemon->vida);
}


//Fun��o que recebe os status do pokemon e guarda essas informa��es
Status criacao_pokemon(char* nome, Tipos tipo, int atk, int def, int stm, int hp, Ataques ataque[8]){

    Status personagem;
    strcpy(personagem.nome, nome);
    personagem.tipo = tipo;
    personagem.ataque = atk;
    personagem.defesa = def;
    personagem.stamina = stm;
    personagem.vida = hp;


    return personagem;
}

//Fun��o de listar pokemom
void listaPokemom(Status *pokemom) {
	int i; 
	printf("--------------------------------------\n");
	printf("\tLista de Pokemons\n");
	printf("--------------------------------------\n");
	for(i=0; i < 8; i++) {
		printf("%d %s", i+1, pokemom[i].nome);
		printf("\t");
		if(i % 2 != 0) {
			printf("\n");
		}
	}
	printf("--------------------------------------\n");
}

// Função de escolher pokemons
void escolherPokemon(Jogo *jogo, int jogadorNumero, Status *pokemons, int n){
    int escolha, i;

    Jogador1 *jogador1;
    Jogador2 *jogador2;

    if (jogadorNumero == 1)
    {
        jogador1 = &jogo->jogador1;
    }else {
        jogador2 = &jogo->jogador2;
    }
    

    for ( i = 0; i < 3; i++)
    {
        printf("Jogador, escolha o %dº pokemon (1-%d): ", i + 1, n );
        scanf("%d", &escolha);

        //validação da escolha
        while (escolha < 1 || escolha > n)
        {
            printf("Escolha inválida. Tente novamente: ");
            scanf("%d", &escolha);
        }
        
        // armazenando escolhas para cada jogador
        if (jogadorNumero == 1) {
            jogador1->escolhas[i] = pokemons[escolha - 1];
        } else {
            jogador2->escolhas[i] = pokemons[escolha - 1];
        }
    }
}

void status_pokemom(Status *pokemom, int numPoke) {
	int i;
	printf("-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf("      Pokemom %s\n", pokemom[numPoke-1].nome);
	printf("-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf("Poder: %d\n", pokemom[numPoke-1].ataque);
	printf("Defesa: %d\n", pokemom[numPoke-1].defesa);
	printf("Stamina: %d\n", pokemom[numPoke-1].stamina);
	printf("Vida: %d\n", pokemom[numPoke-1].vida);
	printf("--------------------------\n");
}

//Menu de escolher e ver status dos pokemons
void menuSelecionar() {
	printf("=-=-=-=-==-=-=-=\n");
	printf("[1] - Escolher\n");
	printf("[2] - Pokem�ns\n");
	printf("=-=-=-=-==-=-=-=\n");
}

// função de batalha

void batalha(Jogo *jogo){
    int jogador1_escolha, jogador2_escolha;

    printf("\nIniciando batalha!\n");

    // Escolha de pokémons para batalha
    printf("\nJogador 1, escolha um pokémon (1-3): ");
    scanf("%d", &jogador1_escolha);
    jogador1_escolha -= 1; // Ajusta para índice

    printf("\nJogador 2, escolha um pokémon (1-3): ");
    scanf("%d", &jogador2_escolha);
    jogador2_escolha -= 1; // Ajusta para índice

    Status *pokemon1 = &jogo->jogador1.escolhas[jogador1_escolha];
    Status *pokemon2 = &jogo->jogador2.escolhas[jogador2_escolha];

    // Conduz a batalha até que um pokémon perca toda a vida
    while (pokemon1->vida > 0 && pokemon2->vida > 0) {
        // Jogador 1 ataca
        printf("\nJogador 1's %s ataca o Jogador 2's %s!\n", pokemon1->nome, pokemon2->nome);
        int dano1 = calcular_dano(pokemon1->ataque, pokemon2->defesa, pokemon1->stamina);
        dano1 = dano_tipo(pokemon1->tipo, pokemon2->tipo, dano1);
        atualizacao_vida(pokemon2, dano1);
        printf("\nJogador 1 causa %d de dano. Vida restante do pokémon do Jogador 2: %d\n", dano1, pokemon2->vida);

        // Verifica se o pokémon 2 foi derrotado
        if (pokemon2->vida <= 0) {
            printf("\nJogador 1 vence a batalha!\n");
		atualizar_status_apos_batalha(pokemon1);
            return;
        }

        // Jogador 2 ataca
        printf("\nJogador 2's %s ataca o Jogador 1's %s!\n", pokemon2->nome, pokemon1->nome);
        int dano2 = calcular_dano(pokemon2->ataque, pokemon1->defesa, pokemon2->stamina);
        dano2 = dano_tipo(pokemon2->tipo, pokemon1->tipo, dano2);
        atualizacao_vida(pokemon1, dano2);
        printf("\nJogador 2 causa %d de dano. Vida restante do pokémon do Jogador 1: %d\n", dano2, pokemon1->vida);

        // Verifica se o pokémon 1 foi derrotado
        if (pokemon1->vida <= 0) {
            printf("\nJogador 2 vence a batalha!\n");
			atualizar_status_apos_batalha(pokemon2);
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

    Ataques golpes_squirtle[4] = {{"Tackle", 50}, {"Water Gun", 50}, {"Bite", 60}, {"Bubble", 40}};
    Ataques golpes_bulbassaur[4] = {{"Tackle", 40}, {"Vine Whip", 45}, {"Seed Bomb", 80}, {"Razor Leaf", 55}};
    Ataques golpes_charmander[4] = {{"Scratch", 40}, {"Ember", 40}, {"Fire Fang", 65}, {"Slash", 70}};
    Ataques golpes_butterfree[4] = {{"Gust", 50}, {"Bug Bite", 50}, {"Air Slash", 75}, {"Psybeam", 65}};
    Ataques golpes_ekans[4] = {{"Poison Sting", 50}, {"Acid", 50}, {"Bite", 60}, {"Wrap", 15}};
    Ataques golpes_pikachu[4] = {{"Thunder Shock", 40}, {"Spark", 65}, {"Quick Attach", 40}, {"Iron Tail", 100}};
    Ataques golpes_clefairy[4] = {{"Pound", 40}, {"Stored Power", 20}, {"Double Slap", 15}, {"Disarming Voice", 40}};
    Ataques golpes_mankey[4] = {{"Karate Chop", 50}, {"Cross Chop", 100}, {"Scratch", 40}, {"Pursuit", 40}};

  	Status pokemon[8];
    //Preenchendo os dados com os atributos dos pokemons
	pokemon[0] = criacao_pokemon("Squirtle", Agua, 48, 65, 50, 44, golpes_squirtle);
    pokemon[1] = criacao_pokemon("Bulbassaur", Planta, 49, 49, 40, 45, golpes_bulbassaur);
    pokemon[2] = criacao_pokemon("Charmander", Fogo, 52, 43, 36, 39, golpes_charmander);
    pokemon[3] = criacao_pokemon("Butterfree", Inseto, 45, 50, 39, 60, golpes_butterfree);
    pokemon[4] = criacao_pokemon("Ekans", Venenoso, 60, 44, 38, 35, golpes_ekans);
    pokemon[5] = criacao_pokemon("Pikachu", Eletrico, 55, 40, 35, 35, golpes_pikachu);
    pokemon[6] = criacao_pokemon("Clefairy", Fada, 45, 48, 38, 70, golpes_clefairy);
    pokemon[7] = criacao_pokemon("Mankey", Lutador, 80, 35, 37, 40, golpes_mankey);

	int i, opcao, numPoke;
	int qt_pokeEscolhidos = 0;
    int pokemons_escolhidos = 0;
	while (1) {
        menu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                // Jogador 1 escolhe pokémons
                printf("\nJogador 1, escolha seus pokémons:\n");
                escolherPokemon(&jogo, 1, pokemon, 8);
                // Jogador 2 escolhe pokémons
                printf("\nJogador 2, escolha seus pokémons:\n");
                escolherPokemon(&jogo, 2, pokemon, 8);
                pokemons_escolhidos = 1;
                printf("\nEscolhas jogador 1:\n");
                for ( i = 0; i < 3; i++)
                {
                    printf("%d - %s ",i+1, jogo.jogador1.escolhas[i].nome );
                    printf("\n");
                }
                printf("\nEscolhas jogador 2:\n");
                for ( i = 0; i < 3; i++)
                {
                    printf("%d - %s ",i+1, jogo.jogador2.escolhas[i].nome );
                    printf("\n");
                }
                
                continue;
            case 2:
                // Exibir lista de pokémons
                listaPokemom(pokemon);
                printf("Digite o número do pokémon para ver os detalhes: ");
                int numPoke;
                scanf("%d", &numPoke);
                status_pokemom(pokemon, numPoke);
                continue;;
            case 3:
                // Iniciar batalha
                if (pokemons_escolhidos) {
                    batalha(&jogo);
                } else {
                    printf("\nVocê precisa escolher pokémons primeiro!\n");
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
    return 0;
  }
}
