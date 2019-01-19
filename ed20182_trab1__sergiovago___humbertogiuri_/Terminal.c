#include "Terminal.h"

/*
OBS: Por nao utilizarmos ID nas estruturas, optamos por fazer a maiora das bucas pelo nome do equipamento
*/

// Lista simplesmente encadeada com sentinela
struct terminal {
  char* nome;
  char* local;
  Roteador* roteadorConectado;
};

// Celula do tipo Terminal
struct celulaT {
  Terminal* terminal;
  CelulaT* prox;
};

// Sentinela
struct listaT{
  CelulaT* primeiro;
  CelulaT* ultimo;
};

// Funcao de alocacao dinamica de um novo terminal
Terminal* IniciaTerminal(char* nome, char* local){
  Terminal* novo = (Terminal*)malloc(sizeof(Terminal)); // Aloca a variavel "novo" de acorodo o a struct "terminal"
  novo -> nome = (char*)malloc((strlen(nome)+1)*sizeof(char)); // Aloca de acordo com o tamanho da string "nome"
  novo -> local = (char*)malloc((strlen(local)+1)*sizeof(char)); // Aloca de acordo com o tamanho da string "local"

  novo -> nome = strcpy(novo -> nome, nome); // Copia a string "nome" para novo -> nome
  novo -> local = strcpy(novo -> local, local); // Copia a string "local" para novo -> local 
  novo -> roteadorConectado = NULL; // Atribui NULL incialmente

  return novo; // Retorna o ponteiro para o terminal
}

// Funcao de alocacao dinamica de uma nova celula do tipo terminal
CelulaT* IniciaCelulaTerminal(Terminal* terminal) {
  CelulaT* novo = (CelulaT*)malloc(sizeof(CelulaT)); // Aloca a variavel "novo" de acorodo o a struct "celulaT"

  novo -> terminal = terminal; // Atribui o endereco de memoria do "terminal" ao novo -> terminal
  novo -> prox = NULL; // Atribui NULL inicialmente

  return novo; // Retorna o ponteiro para a CelulaT
}

// Funcao de alocacao dinamica de uma nova lista de terminais
ListaT* InicializaListaTerminais() {
  ListaT* novaL = (ListaT*)malloc(sizeof(ListaT)); // Aloca a variavel "novaL" de acordo com a struct "listaT"
  novaL -> primeiro = novaL -> ultimo = NULL; // Atribui NULL inicialmente

  return novaL; // Retorna o ponteiro para ListaT
}

// Funcao de insersao de um terminal ja alocado no final da lista de terminais
void CadastraTerminal(ListaT* listaT, Terminal* terminal) {
  CelulaT* novoTerm = IniciaCelulaTerminal(terminal); // Inicia a celula para insersao

  if(listaT -> primeiro == NULL) // Verifica se a lista esta vazia
    listaT -> primeiro = listaT -> ultimo = novoTerm; // Insere na primeira e na ultima posicao
  else { // Insere na ultima posicao
    listaT -> ultimo -> prox = novoTerm; // Atribui ao ponteiro "prox" da ultima posicao a nova celula 
    listaT -> ultimo = novoTerm; // Atribui ao ponteiro "ultimo" a nova celula
  }
}

// Funcao que retira o terminal especificado da lista de terminais
void RetiraTerminal(ListaT* listaT, char* nome,  FILE* Arq) {
  CelulaT* aux = listaT -> primeiro; // Ponteiro principal
  CelulaT* ant = NULL; // Ponteiro auxiliar

  while (aux != NULL) { // Roda ate encontar o terminal ou acabar a lista
    if(!strcmp(aux -> terminal -> nome, nome)) break; // Para se achar
    ant = aux; // Salva a posicao anterior
    aux = aux -> prox; // Vai para a proxima posicao
  }

  Terminal* temp; 
  if(aux == NULL) { // Verifica se nao encontrou
    ImprimeErroTerminal(nome, Arq); // Imprime a mensage de erro caso nao encontre
  } else {
    temp = aux -> terminal; // Armazena o terminal a ser retirado
    if(aux == listaT -> primeiro) { // Verifica se e o primeiro da lista
      if(aux -> prox == NULL){ // Verifica se e o unico
        listaT -> primeiro = listaT -> ultimo = NULL; // A lista torna-se vazia
      } else { //caso nao seja o unico
        listaT -> primeiro = aux -> prox; // Desncadeia
      }
    } else if(aux == listaT -> ultimo) { // Verifica se e o ultimo
      ant -> prox = NULL; // Desncadeia
      listaT -> ultimo = ant; // Aponta para o penultimo
    } else { // Caso esteja nas outras posicoes da lista
      ant -> prox = aux -> prox; // Desencadeia
    }
    LiberaCelulaTerminal(aux); // Libera a celula
  }
}

// Funcao que conecta o terminal especificado ao roteador especificado
void ConectaTerminalAoRoteador(ListaT* listaT, ListaR* listaR, char* nomeT, char* nomeR, FILE* Arq) {
  CelulaT* auxT = listaT -> primeiro;
  CelulaR* auxR = RetornaPrimeiro(listaR);

  while(auxT!=NULL && strcmp(auxT -> terminal -> nome, nomeT)) auxT = auxT -> prox; // Roda ate achar a celula onde esta o terminal
  while(auxR != NULL && strcmp(RetornaNomeRoteador(RetornaRoteador(auxR)), nomeR)) auxR = RetornaProxR(auxR); // Roda ate achar a celula onde esta o terminal 

  if(auxT == NULL){ // Se nao encontrar o terminal
    ImprimeErroTerminal(nomeT, Arq); // Imprime a mensagem erro
    return; // Sai previamente
  }
  if(auxR == NULL){ // Se nao encotnrar o roteador
    ImprimeErroRoteador(nomeR, Arq); // Imrprime a mensagem de erro
    return; // Sai previamente
  }

  // Faz o ponteiro "roteadorConectado" apontar para o roteador, estabelecendo a conexao 
  auxT -> terminal -> roteadorConectado = RetornaRoteador(auxR);
}

// Funcao que retorna a quantidade de terminas do local especificado
void FrequenciaTerminal(ListaT* lista, char* local, FILE* Arq){
  CelulaT* aux;
  int contador = 0; //Conta a quantidade de terminais do local
  aux = lista -> primeiro;

  while(aux != NULL){ // Roda toda a lista em busca dos terminais
    if(!strcmp(aux -> terminal -> local, local)){
      contador++; // Soma o contador a cada terminal encontrado
    }
    aux = aux -> prox; // Avanca para a proxima posicao 
  }
  fprintf(Arq,"FREQUENCIATERMINAL %s: %d\n", local, contador); // Imprime a frequencia
}

// Funcao que desconecta o terminal
void DesconectaTerminal(ListaT* listaT, char* nome, FILE* Arq){
  CelulaT* aux = listaT -> primeiro;

  while(aux != NULL && !strcmp(aux -> terminal -> nome, nome)) // Roda ate encontrar o terminal ou chegar ao final da lista
    aux = aux -> prox;

  if(aux == NULL){
    ImprimeErroTerminal(nome, Arq); // Imprime a mensagem de erro
  } else {
    aux -> terminal -> roteadorConectado = NULL; // Desconecta o terminal do roteador
  }
}

// Funcao que faz o mesmo que "DesconectaTerminal" porem nao imprime mensagem de erro
void DesconcetaTerminalRoteadorRemovido(ListaT* listaT, char* nome, FILE* Arq){
  CelulaT* aux = listaT -> primeiro;

  while(aux != NULL){ // Roda toda a lista
    if(RetornaNomeRoteador(aux -> terminal -> roteadorConectado) != NULL) { // Se houver roteador conectado
        if(!strcmp(RetornaNomeRoteador(aux -> terminal -> roteadorConectado),nome)){ // Verifica se o nome e igual
            break; // Para se econtrar
        }
    }

    aux = aux -> prox; // Avanca para a proxima posicao
  }


  if(aux == NULL){ // Se nao encontrar
    return; // Retorna previamente
  } else { // Caso contrario
    aux -> terminal -> roteadorConectado = NULL; // Desconecta
  }
}

// Funcao que imprime o terminal especificado
void ImprimeTerminal(Terminal* terminal, FILE* Arq){
  fprintf(Arq,"    %s", terminal -> nome );
  if(terminal -> roteadorConectado != NULL){
    fprintf(Arq," -- %s;\n", RetornaNomeRoteador(terminal -> roteadorConectado));
  } else {
    fprintf(Arq,";\n");
  }
}

// Funcao que imprime a celula especificada
void ImprimeCelulaTerminal(CelulaT* cTerminal, FILE* Arq){
  ImprimeTerminal(cTerminal -> terminal, Arq); // Chama a funcao ImprimeTerminal
}

// Funcao que imprime toda a lista de terminais
void ImprimeListaTerminal(ListaT* lista, FILE* Arq){
  CelulaT* aux = lista -> primeiro;

  while(aux != NULL){ // Roda ate o final da lista
      ImprimeCelulaTerminal(aux, Arq); // Chama a funcao ImprimeCelulaTerminal
      aux = aux -> prox; // Avanca
  }
}

//Funcao que libera o terminal especificado
void LiberaTerminal(Terminal* terminal) {
  free(terminal -> nome);
  free(terminal -> local);
  free(terminal);
}

//Funcao que libera a celula especificada
void LiberaCelulaTerminal(CelulaT* cTerminal) {
  LiberaTerminal(cTerminal -> terminal); // Chama a funcao LiberaTerminal
  free(cTerminal);
}

//Funcao que libera a lista especificada
void LiberaListaTerminais(ListaT* lista) {
  CelulaT *aux, *aux2;
  aux = lista -> primeiro;

  while(aux != NULL){ //Roda toda a lista
    aux2 = aux; // Recebe a posicao atual
    aux = aux -> prox; //Avanca
    LiberaCelulaTerminal(aux2); // Chama a funcao LiberaCelulaTerminal
  }
  free(lista);
}

//Imprime a situacao atual do NetMAp
void ImprimeNetMap(ListaT* lista, ListaR* listaR, FILE* Arq){
  fprintf(Arq, "strict graph {\n");
  ImprimeListaTerminal(lista, Arq); // Chama a funcao ImprimeListaTerminal
  ImprimeListaRoteadores(listaR, Arq); // Chama a funcao ImprimeListaRoteadores
  fprintf(Arq, "}\n");
}

//Verifica se tem como enviar dados de um terminal para outro
void EnviaPacoteDeDados(ListaT* listaT, ListaR* listaR, char* nomeR, char* nomeD, FILE* Log, FILE* Saida) {
    Terminal* remetente = BuscaTerminal(listaT, nomeR);
    Terminal* destinatario = BuscaTerminal(listaT, nomeD);

    if (remetente == NULL) { // Verifica se foi passado um rementente nulo
      ImprimeErroTerminal(nomeR, Log); // Imprime mesnagem de erro
      return; // Retorna previamente
    }
    if (destinatario == NULL) { // Verifica se foi passado um terminal vazio
      ImprimeErroTerminal(nomeD, Log); // Imrpime mensagem de erro
      return; // Retorna previamente
    }

    ListaR* listaR_aux = IniciaListaRoteadores(); // Cria uma lista auxiliar de roteadores
    int resposta = DescobreSeHaCaminho(listaR_aux, listaR, remetente->roteadorConectado, destinatario->roteadorConectado); // Chama a otutra funcao para descobrir se ha caminho
    LiberaListaRoteadores(listaR_aux); // Libera a lista auxiliar criada

    if (resposta) // Se houver
      fprintf(Saida, "ENVIAPACOTEDADOS %s %s: SIM\n", nomeR, nomeD);
    else // Caso contrario
      fprintf(Saida, "ENVIAPACOTEDADOS %s %s: NAO\n", nomeR, nomeD);
}

//Busca um terminal e retorna um terminal na lista de terminais
Terminal* BuscaTerminal(ListaT* lista, char* nome){
  CelulaT* aux = lista -> primeiro;

  while(aux != NULL && strcmp(aux -> terminal -> nome, nome)) aux = aux -> prox; // Roda ate o final ou encontrar

  if(aux == NULL){ // Se nao encontrar
    return NULL; // Retorna previamente
  }

  return aux -> terminal; // Retorna o terminal
}