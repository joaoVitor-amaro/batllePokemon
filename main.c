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
        case Fogo:
            if (tipo_defensor == Agua){
                novo_dano = dano - 10;
            } else if (tipo_defensor == Planta){
                novo_dano = dano + 15;
            } else if (tipo_defensor == Inseto){
                novo_dano = dano + 15;
            }
        case Inseto:
            if (tipo_defensor == Planta){
                novo_dano = dano + 15;
            } else if (tipo_defensor == Fogo){
                novo_dano = dano - 10;
            }
        case Venenoso:
            if (tipo_defensor == Planta){
                novo_dano = dano + 15;
            } else if (tipo_defensor == Fada){
                novo_dano = dano + 15;
            }
        case Eletrico:
            if (tipo_defensor == Agua){
                novo_dano = dano + 15;
            }
        case Fada:
            if (tipo_defensor == Lutador){
                novo_dano = dano + 15;
            } else if (tipo_defensor == Venenoso){
                novo_dano = dano - 10;
            }
        case Lutador:
            if (tipo_defensor == Fada){
                novo_dano = dano - 10;
            }
        default:
            novo_dano = dano;
    }
    return novo_dano;
}

void atualizacao_vida(Status *pokemon, int novo_dano){
    pokemon -> vida -= novo_dano;

    printf("%s recebeu %d de dano. Resta %d de vida", pokemon->nome, novo_dano, pokemon->vida);
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

int main() {
    setlocale(LC_ALL, "portuguese");

    Jogador1 escolha[3];

    srand(time(NULL)); //Gerador de numeros aleatorios

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
	while(1) {
		menuSelecionar();
		printf("Qual a sua opcao: ");
		scanf("%d", &opcao);
		sleep(1);
		switch (opcao) {
			case 1:
				//selecionar pokemom
				qt_pokeEscolhidos++;
				break;
			case 2:
				//ver status pokemom
				listaPokemom(pokemon);
				printf("Quer ver dados de qual pokemom? N");
				scanf("%d", &numPoke);
				status_pokemom(pokemon, numPoke);
				break;
		}	
		if (qt_pokeEscolhidos == 3) {
			break;
		}
	}

  return 0;
}
