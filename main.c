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
