#ifndef ROTEADOR_H
#define ROTEADOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Roteador roteador (tipo opaco)
  - nome (string)
  - operadora (string)
  - roteadorConectado (Roteador)
  */
typedef struct roteador Roteador;

/*CelulaR celulaR (tipo opaco)
  - roteador (Roteador)
  - prox (CelulaR)
  */
typedef struct celulaR CelulaR;

/*ListaR listaR (tipo opaco)
  - primero (CelulaR)
  - ultimo (CelulaR)
  */
typedef struct listaR ListaR;

/*Inicializa um novo roteador
* inputs: um nome e uma operadora
* output: Um novo roteador inicializado
* pre-condicao: nome e operadora validos
* pos-condicao: roteador inicializado e campo proximoEnlace aponta para NULL
*/
Roteador* IniciaRoteador(char* nome, char* operadora);

/*Inicializa um nova célula do tipo roteador
* inputs: um ponteiro para um roteador
* output: uma célula do tipo roteador inicializada
* pre-condicao: roteador nao nulo
* pos-condicao: Celula do tipo roteador inicializada e campo prox aponta para NULL
*/
CelulaR* IniciaCelulaR(Roteador* roteador);

/*Inicializa uma sentinela da lista de roteadores
* inputs: nenhum
* output: Sentinela inicializada
* pre-condicao: nenhuma
* pos-condicao: sentinela da lista de retorno existe e os campos primeiro e ultimo apontam para NULL
*/
ListaR* IniciaListaRoteadores();

/*Cadastra um roteador a uma lista de roteadores
* inputs: um ponteiro para a lista de roteadores e um para um roteador
* output: nenhum
* pre-condicao: lista de terminais  e roteador nao nulos
* pos-condicao: Lista com roteador inserido
*/
void CadastraRoteador(ListaR* lista, Roteador* roteador);

/* Retona o nome de um roteador
*inputs: um ponteiro para um roteador
*output: o nome do roteador
*pre-condicao: roteador nao nulo
*pos-condicao: nome do roteador retornado
*/
char* RetornaNomeRoteador(Roteador* roteador);

/*Imprime quantos roteadores são de uma determinada operadora
* inputs: um ponteiro para a lista de roteadores, uma operadora e um ponteiro do tipo FILE
* output: nenhum
* pre-condicao: lista de roteadores nao nula
* pos-condicao: quantidade de roteadores de uma operadora impresso
*/
void FrequenciaOperadora(ListaR* lista, char* operadora, FILE* Arq);

/*Copia um roteador para outro que sera alocado
*inputs: um ponteiro para um roteador
*output: um roteador
*pre-condicao: roteador nao nulo
*pos-condicao: um novo roteador alocado com caracteristicas iguais ao de entrada
*/
Roteador* CopiaRoteador(Roteador* roteador);

/*Conecta um roteador a um outro roteador
* inputs: um ponteiro para a lista de roteadores um ponteiro para o roteador 1 e um para o roteador2
* output: nenhum
* pre-condicao: lista de roteadores, roteador1 e roteador2 nao nulos
* pos-condicao: roteador1 conectado a roteador2 e vice versa
*/
void ConectaRoteador(ListaR* lista, Roteador* roteador1, Roteador* roteador2);

/*Remove um roteador e todas as sua conexoes da lista de roteadores
* inputs: um ponteiro para a lista de roteadores, um nome e um ponteiro do tipo FILE
* output: nenhum
* pre-condicao: lista de terminais nao nula e nome nao nulo
* pos-condicao: lista atualizada sem o roteador e suas conexoes
*/
void RemoveRoteador(ListaR* lista, char* nome, FILE* Arq);

/* Faz o mesmo que RemoveRoteador, porem nao imprime a mensagem de erro caso o roteador nao seja encontrado
*inputs: um ponteiro para a lista de roteadores e um nome
*output: nenhum
*pre-condicao: lista nao nula e nome valido
*pos-condicao: roteador com o nome passador como paramentro removido da lista
*/
void RemoveRoteadorSemMsg(ListaR* lista, char* nome);

/*Imprime um roteador
* inputs: um ponteiro para um roteador e um ponteiro do tipo FILE
* output: nenhum
* pre-condicao: roteador nao nula
* pos-condicao: dados de um roteador impressos
*/
void ImprimeRoteador(Roteador* roteador, FILE* Arq);

/*Imprime os dados de uma celula do tipo roteador
* inputs: um ponteiro para a celula do tipo roteador e um ponteiro do tipo FILE
* output: nenhum
* pre-condicao: celula não nula
* pos-condicao: dados da celula de roteadores impressos
*/
void ImprimeCelulaRoteador(CelulaR* cRoteador, FILE* Arq);

/*Imprime todos os roteadores que um roteador esta conectado
* inputs: um ponteiro para celula do tipo roteador e um ponteiro do tipo FILE
* output: nenhum
* pre-condicao: celula do tipo roteador nao nula
* pos-condicao: Roteadores do qual um roteador esta conectado impressos
*/
void ImprimeEnlaces(CelulaR* cRoteador, FILE* Arq);

/*Imprime os dados de todos os roteadores da lista
* inputs: um ponteiro para a lista de roteadores e um ponteiro do tipo FILE
* output: nenhum
* pre-condicao: lista de roteadores nao nula
* pos-condicao: dados dos roteadores da lista impressos
*/
void ImprimeListaRoteadores(ListaR* lista, FILE* Arq);

/*Libera o roteador especificado e sua lista de enlaces
* inputs: um ponteiro para o roteador
* output: nenhum
* pre-condicao: roteador nao nulo
* pos-condicao: roteador e sua lista de enlacesliberados
*/
void LiberaRoteador(Roteador* roteador);

/*Libera so roteador especificado
* inputs: um ponteiro para o roteador
* output: nenhum
* pre-condicao: roteador nao nulo
* pos-condicao: roteador liberado
*/
void LiberaSoRoteador(Roteador* roteador);

/*Libera celula do tipo roteador especificada
* inputs: um ponteiro para a celula do tipo roteador
* output: nenhum
* pre-condicao: celula do tipo roteador nao nula
* pos-condicao: celula do tipo roteador liberada
*/
void LiberaCelulaRoteador(CelulaR* aux2);

/*Libera a lista de roteadores especificada
* inputs: um ponteiro para a lista de roteadores
* output: nenhum
* pre-condicao: lista de roteadores nao nula
* pos-condicao: toda a lista liberada
*/
void LiberaListaRoteadores(ListaR* lista);

/*Libera a lista de enlances especificada
* inputs: um ponteiro para um roteador
* output: nenhum
* pre-condicao: roteador nao nulo
* pos-condicao:todo os roteadores ao qual o roteador de entrada esta conectado liberados
*/
void LiberaEnlace(Roteador* roteador);

/*Retorna um roteador
*inputs: ponteiro para uma celula do tipo roteador
*output: um roteador
*pre-condicao: celula nao nula
*pos-condicao: roteador que essa celula representa retornado
*/
Roteador* RetornaRoteador(CelulaR* aux);

/*Retorna o campo prox da celula do tipo roteador
*inputs: ponteiro para uma celula do tipo roteador
*output: uma celula do tipo roteador
*pre-condicao: celula não nula
*pos-condicao: campo prox da celula retornado
*/
CelulaR* RetornaProxR(CelulaR* aux);

/*Retorna a primeira celula da lista de roteadores
*inputs: ponteiro para uma lista de roteadores
*output: uma celula do tipo roteador
*pre-condicao: lista nao nula
*pos-condicao: a primeira celula da lista retornada
*/
CelulaR* RetornaPrimeiro(ListaR* listaR);

/* Busca um roteador dentro de uma lista de roteadores
*inputs:  ponteiro para uma lista de roteadores, um nome e um ponteiro do tipo FILE
*output: um roteador
*pre-condicao: lista e nome não nulos
*pos-condicao: roteador de nome solicitado retornado
*/
Roteador* BuscaRoteador(ListaR* lista, char* nome, FILE* Arq);

/* Faz o mesmo que a funcao "BuscaRoteador", porem nao imprime a mensagem de erro caso o roteador nao seja encontrado
*inputs: ponteiro pra lista e nome
*output: ponteiro para roteador
*pre-condicao: lista nao nula e nome valido
*pos-condicao: roetador retornado caso encontado
*/
Roteador* BuscaRoteadorSemMsg(ListaR* lista, char* nome);

/* Desconecta um roteador de outro
*inputs: dois ponteiros para roteadores
*output: nenhum
*pre-condicao: roteadores inicializados e nao nulos
*pos-condicao: rote1 fora da lista de enlaces de rote2 e vice-versa
*/
void DesconectaRoteador(Roteador* rote1, Roteador* rote2);

/* Romeve apenas um enlace especifico de algum roteador a partir de seu nome
*inputs: um ponteiro para o roteador que possui os enlaces e um para o roteador a ser removido do enlace do primeiro
*output: nenhum
*pre-condicao: roteadores inicilizados e nao nulos
*pos-condicao: rote2 fora da lista de elaces do rote1
*/
void DesconectaUmEnlace(Roteador* rote1, Roteador* rote2);

/*Imprime uma mensagem de erro
*inputs: um nome e um ponteiro do tipo FILE
*output: nenhum
*pre-condicao: nome nao nulo
*pos-condicao: imprime que o terminal do nome de entrada nao existe no netmap
*/
void ImprimeErroTerminal(char* nomeT, FILE* Arq);

/*Imprime uma mensagem de erro
*inputs: um nome e um ponteiro do tipo FILE
*output: nenhum
*pre-condicao: nome nao nulo
*pos-condicao: imprime que o roteador do nome de entrada nao existe no netmap
*/
void ImprimeErroRoteador(char* nomeR, FILE* Arq);

/* Roda a lista de Roteadores e seus enlaces para descobrir se há algum caminho
*inputs: dois ponteiros para lista de roteadoes e dois ponteiros para roteadores
*output: 0 se nao houver e 1 se houver (int)
*pre-condicao: listas e roteador ja inicializados
*pos-condicao: um valor inteiro retornado
*/
int DescobreSeHaCaminho(ListaR* lista,ListaR* listaP, Roteador* remetente, Roteador* destinatario);

/* Roda apenas a lista de enlace para descobrir se há algum caminho
*inputs: dois ponteiros para roteadores
*output: 0 se nao houver e 1 se houver (int)
*pre-condicao: roteadores ja inicializados e nao nulos
*pos-condicao: um valor inteiro retornado
*/
int DescobreSeEEnlace(Roteador* origem, Roteador* destino);

/* Descobre a celula do roteador passado como paramentro
*inputs: um ponteiro pra lista e um para um roteador
*output: um ponteiro para celula, se for encontrada
*pre-condicao: lista e rotador ja inicializados e nao nulos
*pos-condicao: se houver, ponteiro para celula retornado
*/
CelulaR* BuscaCelulaRoteador(ListaR* lista, Roteador* rote);

#endif
