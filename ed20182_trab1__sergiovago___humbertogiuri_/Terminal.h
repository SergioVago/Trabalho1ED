#ifndef TERMINAL_H
#define TERMINAL_H

#include "Roteador.h"

/*Terminal terminal (tipo opaco)
  - nome (string)
  - local (string)
  - roteadorConectado (Roteador)
  */
typedef struct terminal Terminal;

/*CelulaT celulaT (tipo opaco)
  - terminal (Terminal)
  - prox (CelulaT)
  */
typedef struct celulaT CelulaT;

/*ListaT listaT (tipo opaco)
  - primero (CelulaT)
  - ultimo (CelulaT)
  */
typedef struct listaT ListaT;

/*Inicializa um Terminal terminal
* inputs: nome e o local
* output: um ponteiro para o Terminal criado
* pre-condicao: nome e local validos
* pos-condicao: terminal inicializado e campo roteadorConectado aponta para NULL
*/
Terminal* IniciaTerminal(char* nome, char* local);

/*Inicializa a celula de um terminal
* inputs: um Terminal especifico
* output: um ponteiro para a Celula criada
* pre-condicao: terminal inicializado e nao nulo
* pos-condicao: celula existe, o campos terminal aponta pro terminal de entrada e campo prox aponta para null
*/
CelulaT* IniciaCelulaTerminal(Terminal* terminal);

/*Inicializa o sentinela da lista de terminais
* inputs: nenhum
* output: Sentinela inicializado
* pre-condicao: nenhuma
* pos-condicao: sentinela da lista de retorno existe e os campos primeiro e ultimo apontam para NULL
*/
ListaT* InicializaListaTerminais();

/*Cadastra um terminal a uma lista de terminais
* inputs: um ponteiro para lista e um para o terminal
* output: Nenhum
* pre-condicao: lista e terminal nao nulos
* pos-condicao: lista atualizada com terminal inserido
*/
void CadastraTerminal(ListaT* listaT, Terminal* terminal);

/*Retira um terminal da lista de terminais
* inputs: um ponteiro para lista e o nome do terminal e um ponteiro do tipo FILE
* output: nenhum
* pre-condicao: lista nao nula e nome valido
* pos-condicao: terminal especificado fora da lista e retornado pela funcao
*/
void RetiraTerminal(ListaT* listaT, char* nome, FILE* Arq);

/*Conecta um terminal a um roteador
* inputs: um ponteiro para uma lista de terminais, um ponteiro para uma lista de roteadores, dois nomes e um ponteiro do tipo FILE
* output: nenhum
* pre-condicao: lista terminal e lista roteador nao nulos
* pos-condicao: terminal especificado conectado ao roteador especificado
*/
void ConectaTerminalAoRoteador(ListaT* listaT, ListaR* listaR, char* nomeT, char* nomeR, FILE* Arq);

/*Indica a quantidade de terminais em determinado local
* inputs: um ponteiro para a lista de terminais e um para o local e um ponteiro do tipo FILE
* output: nenhum
* pre-condicao: lista nao nula e local valido
* pos-condicao: Impresso a quantidade de terminais de um local
*/
void FrequenciaTerminal(ListaT* lista, char* local, FILE* Arq);

/*Desconecta o terminal do roteador
* inputs: um ponteiro para uma lista de terminais, um nome e um ponteiro do tipo FILE
* output: nenhum
* pre-condicao: lista de terminais e nome nao nulos
* pos-condicao: terminal desconectado
*/
void DesconectaTerminal(ListaT* listaT, char* nome, FILE* Arq);

/*Imprime o terminal especificado
* inputs: um ponteiro para o terminal e um ponteiro do tipo FILE
* output: nenhum
* pre-condicao: terminal nao nulo
* pos-condicao: nome e local impressos
*/
void ImprimeTerminal(Terminal* terminal, FILE* Arq);

/*Imprime a celula terminal especificada
* inputs: um ponteiro para a celula terminal um ponteiro do tipo FILE
* output: nenhum
* pre-condicao: celula terminal nao nulo
* pos-condicao: terminal impresso
*/
void ImprimeCelulaTerminal(CelulaT* cTerminal, FILE* Arq);

/*Imprime toda a lista de terminais especificada
* inputs: um ponteiro para a lista de terminais e um ponteiro do tipo FILE
* output: nenhum
* pre-condicao: lista nao nula
* pos-condicao: toda a lista impressa
*/
void ImprimeListaTerminal(ListaT* lista, FILE* Arq);

/*Libera o terminal especificado
* inputs: um ponteiro para o terminal
* output: nenhum
* pre-condicao: terminal nao nulo
* pos-condicao: nome, local e o terminal liberados
*/
void LiberaTerminal(Terminal* terminal);

/*Libera a celula terminal especificada
* inputs: um ponteiro para a celula terminal
* output: nenhum
* pre-condicao: celula terminal nao nula
* pos-condicao: celula terminal e terminal liberado
*/
void LiberaCelulaTerminal(CelulaT* cTerminal);

/*Libera a lista terminal especificada
* inputs: um ponteiro para a lista de terminais
* output: nenhum
* pre-condicao: lista de terminais nao nula
* pos-condicao: toda a lista liberada
*/
void LiberaListaTerminais(ListaT* lista);

/*Desconecta um terminal do seu devivdo roteador
* inputs: um ponteiro para a lista de terminais, um nome e um ponteiro do tipo FILE
* output: nenhum
* pre-condicao: lista de terminais e nome nao nulos
* pos-condicao: Terminal desconectado do reteador
*/
void DesconcetaTerminalRoteadorRemovido(ListaT* listaT, char* nome, FILE* Arq);

/*Imprimi a situação atual do NETMAP
* inputs: um ponteiro para a lista de terminais, um para a lista de roteadores e um ponteiro do tipo File
* output: nenhum
* pre-condicao: lista de terminais e roteadores nao nula
* pos-condicao: NETMAP impresso como especificado
*/
void ImprimeNetMap(ListaT* lista, ListaR* listaR, FILE* Arq);

/*Verifica se eh possivel enviar dados entre dois terminas
*inputs: um ponteiro para a lista de terminais, um ponteiro para uma lista de roteadores dois nome e dois ponteiros do tipo FILE
*output: nenhum
*pre-condicao: listas e nomes nao nulos
*pos-condicao: Mensagem se pode ou nao pode enviar dados de um terminal para o outro
*/
void EnviaPacoteDeDados(ListaT* listaT, ListaR* listaR,  char* nomeR, char* nomeD, FILE* Log, FILE* Saida);

/*Busca um terminal dentro de uma lista de terminais
*inputs: um ponteiro para uma lista de terminais e um nome
*output: um terminal
*pre-condicao: lista e nome nao nulos
*pos-condicao: nenhuma
*/
Terminal* BuscaTerminal(ListaT* lista, char* nome);

#endif
