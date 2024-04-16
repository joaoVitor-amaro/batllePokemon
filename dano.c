#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <string.h>

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

//Struct que contém as características principais dos pokemons
typedef struct{
    char nome[50];
    Tipos tipo;
    int ataque;
    int defesa;
    int stamina;
    int vida;
} Status;


//Função que calcula o dano do pokemon durante a rodada
int calcular_dano(int atk_agressor, int def_defensor, int stamina_agressor){
    float dano = 0.0;

    dano = (2 * atk_agressor) + (stamina_agressor) - (2 * def_defensor);

    return (int)dano;

}

//Função que determina o dano final dependendo do tipo dos pokemons na batalha
int dano_tipo(Tipos tipo_agressor, Tipos tipo_defensor, int dano){
    int novo_dano = 0;

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

//Função que recebe os status do pokemon e guarda essas informações
    Status criacao_pokemon(char* nome, Tipos tipo, int atk, int def, int stm, int hp){

    Status personagem;
    strcpy(personagem.nome, nome);
    personagem.tipo = tipo;
    personagem.ataque = atk;
    personagem.defesa = def;
    personagem.stamina = stm;
    personagem.vida = hp;


    return personagem;
}

//Função de listar pokemom
void listaPokemom(Status *pokemom) {
	int i;
	printf("\tLista de Pokemons\n");
	printf("------------------------------------------------\n");
	for(i=0; i < 8; i++) {
		printf("%d° %s", i+1, pokemom[i].nome);
		if (i % 4 == 3 && i != 7) {
            printf("\n");
        } else if (i != 7) {
            printf(" - ");
        }
	}
	printf("\n------------------------------------------------\n");
}

int main() {

  setlocale(LC_ALL, "portuguese");

  Status pokemon[8];

    //Preenchendo os dados com os atributos dos pokemons
    pokemon[0] = criacao_pokemon("Squirtle", Agua, 48, 65, 50, 44);
    pokemon[1] = criacao_pokemon("Bulbassauro", Planta, 49, 49, 40, 45);
    pokemon[2] = criacao_pokemon("Charmander", Fogo, 52, 43, 36, 39);
    pokemon[3] = criacao_pokemon("Butterfree", Inseto, 45, 50, 39, 60);
    pokemon[4] = criacao_pokemon("Ekans", Venenoso, 60, 44, 38, 35);
    pokemon[5] = criacao_pokemon("Pikachu", Eletrico, 55, 40, 35, 35);
    pokemon[6] = criacao_pokemon("Clefairy", Fada, 45, 48, 38, 70);
    pokemon[7] = criacao_pokemon("Mankey", Lutador, 80, 35, 37, 40);


  return 0;
}
