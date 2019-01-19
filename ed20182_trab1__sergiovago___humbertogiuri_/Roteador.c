#include "Roteador.h"

/*
OBS: Por nao utilizarmos ID nas estruturas, optamos por fazer a maiora das bucas pelo nome do equipamento
*/

// Lista simplesmente encadeada com sentinela
struct roteador {
  char* nome;
  char* operadora;
  Roteador* proximoEnlace; // Lista de enlaces
};

// Celula do tipo Roteador
struct celulaR {
  Roteador* roteador;
  CelulaR* prox;
};

// Sentinela
struct listaR {
  CelulaR* primeiro;
  CelulaR* ultimo;
};

// Funcao de alocacao dinamica de um novo roteador
Roteador* IniciaRoteador(char* nome, char* operadora) {
  Roteador* roteador = (Roteador*)malloc(sizeof(Roteador)); // Aloca a variavel "roteador" de acorodo o a struct "roteador"
  roteador -> nome = (char*)malloc((strlen(nome)+1)*sizeof(char)); // Aloca de acordo com o tamanho da string "nome"
  roteador -> operadora = (char*)malloc((strlen(operadora)+1)*sizeof(char)); // Aloca de acordo com o tamanho da string "operador"

  strcpy(roteador -> nome, nome); // Copia a string "nome" para roteador -> nome
  strcpy(roteador -> operadora, operadora); // Copia a string "operadora" para roteador -> operadora
  roteador -> proximoEnlace = NULL; // Atribui NULL inicialmente

  return roteador; // Retorna o ponteiro para o roteador
}

// Funcao de alocacao dinamica de uma nova celula de roteador
CelulaR* IniciaCelulaR(Roteador* roteador){
  CelulaR* novoC = (CelulaR*)malloc(sizeof(CelulaR)); // Aloca a variavel "novoC" de acorodo o a struct "celulaR"

  novoC -> roteador = roteador; // Atribui o endereco de memoria do "roteador" ao novoC -> roteador
  novoC -> prox = NULL; // Atribui NULL inicialmente

  return novoC; // Retorna o ponteiro para a celula
}

// Funcao de alocacao dinamica de uma nova sentinela
ListaR* IniciaListaRoteadores() {
  ListaR* lista = (ListaR*)malloc(sizeof(ListaR)); // Aloca a variavel "lista" de acordo com a struct "listaR"
  lista -> primeiro = lista -> ultimo = NULL; // Atribui NULL inicialmente

  return lista; // Retorna o ponteiro para a lista
}

// Cadastra um roteador e uma lista de roteadores, representando mais um roteador no netmap
void CadastraRoteador(ListaR* lista, Roteador* roteador) {
  CelulaR* novoC = IniciaCelulaR(roteador); // Inicia a celula para a insercao

  if(lista -> primeiro == NULL) { // Caso a lista esta vazia
    lista -> primeiro = lista -> ultimo = novoC; // Insere na primeira e na ultima posicao
  }
  else { // Insere na ultima posicao
    lista -> ultimo -> prox = novoC; // Atribui ao ponteiro "prox" da ultima posicao a nova celula
    lista -> ultimo = novoC; // Atribui ao ponteiro "ultimo" a nova celula
  }
}

// Tem como retorno o nome de um roteador
char* RetornaNomeRoteador(Roteador* roteador){
  if(roteador != NULL) return roteador -> nome; //Retorna o nome do roteador caso o roteador nao seja nulo
  else return NULL; //Senao retorna NULL
}

//Indica quantos roteadores sao de uma operadora
void FrequenciaOperadora(ListaR* lista, char* operadora, FILE* Arq){
  CelulaR* aux = lista -> primeiro; //Cria uma nova celula e faz ela apontar para o primeiro elemento de uma lista
  int contador = 0; //inicia um contador

  while(aux != NULL){ // Roda toda a lista
    if(!strcmp(aux -> roteador -> operadora, operadora)) // Verifica se e o procurado
      contador++; // Soma o contador
    aux = aux -> prox; // Avanca para a proxima posicao
  }

  fprintf(Arq,"FREQUENCIAOPERADORA %s: %d\n", operadora, contador);
}

//Faz a copia de um roteador para um roteador que sera alocado dinamicamente
Roteador* CopiaRoteador(Roteador* roteador){
  Roteador* novo = IniciaRoteador(roteador -> nome, roteador -> operadora); //Inicia um novo roteador com as caracrteristicas do de entrada

  return novo; //retorna esse roteador
}

//Conecta um roteador na lista de enlaces do outro e vice versa, representa uma nova conexao entre roteadores no NETMAP
void ConectaRoteador(ListaR* lista, Roteador* roteador1, Roteador* roteador2){
  CelulaR* aux = lista -> primeiro; //Cria uma nova celula e faz ela apontar para o primeiro elemento de uma lista
  int cont1 = 0, cont2 = 0; //inicia dois contadores

  if(roteador1 == NULL || roteador2 == NULL){
      return; //sai da funcao caso um dos dois roteadores sejam nulos
  }


  while(aux != NULL || (cont1 != 1 && cont2 != 1)) { //roda toda a lista caso os dois contadores nao sejam 1
    if(!strcmp(aux -> roteador -> nome, roteador1 -> nome)){ //compara dois nomes
      Roteador* eRot1 = aux -> roteador; //Cria um novo ponteiro para roteador e faz ele apontar para aux
      while (eRot1 -> proximoEnlace != NULL) { //roda a lista de enlaces
        eRot1 = eRot1 -> proximoEnlace;
      }
      eRot1 -> proximoEnlace = CopiaRoteador(roteador2); //chama a funcao CopiaRoteador
      cont1++; //atribui mais um no contador
    }
    //Nessa parte faz a mesma coisa que o primeiro if, mas agora para o roteador 2. Essa funcao joga um roteador na lista de enlaces do outro
    if(!strcmp(aux -> roteador -> nome, roteador2 -> nome)){
      Roteador* eRot2 = aux -> roteador;
      while (eRot2 -> proximoEnlace != NULL) {
        eRot2 = eRot2 -> proximoEnlace;
      }
      eRot2 -> proximoEnlace = CopiaRoteador(roteador1);
      cont2++;
    }

    aux = aux -> prox; //anda na lista de roteadores
  }
}

//Desfaz a conexao entre dois roteadores
void RemoveEnlace(CelulaR* cRot, char* nome){
  CelulaR* aux = cRot; //cria um novo ponteiro para uma celula e faz apontar para a celula de entrada

  while(aux != NULL) { //roda a lista de roteadores principais.
    Roteador* rodaE = aux -> roteador -> proximoEnlace;
    Roteador* rodaAux = aux -> roteador;
    while(rodaE != NULL) { //roda a lista de enlaces para desencadear um roteador do enlace.
      if(!strcmp(rodaE -> nome,nome)) { //Compara o nome do roteador com o nome de entrada, caso for igual entra no if
        rodaAux -> proximoEnlace = rodaE -> proximoEnlace;
        LiberaSoRoteador(rodaE); //Libera o roteador
        rodaE = aux -> roteador -> proximoEnlace;
        //desencadeia
      }
      rodaAux = rodaE;
      if(rodaE != NULL) {
          rodaE = rodaE -> proximoEnlace; //passa para a proxima posicao da lista de enlaces caso nao seja a ultima
      }
    }
    aux = aux -> prox; //passsa para a proxima posicao da lista principal
  }
}

//retira um roteador da lista e todas suas conexoes, Tirando do NETMAP
void RemoveRoteador(ListaR* lista, char* nome, FILE* Arq) {
  CelulaR* aux = lista -> primeiro; //Cria um novo ponteiro para uma celula de roteadores e faz ela apontar para o primeiro elemento da lista de roteadores
  CelulaR* p = NULL; //Cria um novo ponteiro para uma celula de roteadores e faz ela apontar para NULL

  RemoveEnlace(aux, nome); //Remove a conexao que existe entre os roteadores


  while(aux != NULL && strcmp(aux -> roteador -> nome,nome)) { //roda a lista de roteadores
      p = aux;
      aux = aux -> prox;
      //Marca a posicao da celula para depois desencadear
    }

    //Daqui para baixo eh a parte do desancedeamento e liberamento
  if(aux != NULL) {
    if(lista -> primeiro == aux) {
      lista -> primeiro = aux -> prox;
      LiberaCelulaRoteador(aux);
    } else {
      p -> prox = aux -> prox;
      LiberaCelulaRoteador(aux);
    }
  } else {
    ImprimeErroRoteador(nome, Arq); //Imprime um erro se nao estiver na lista
    return; //E retorna
  }
}

//Essa funcao faz a mesma coisa que a RemoveRoteador e segue os mesmos passos, porem ela nao imprime a mensagem de erro
void RemoveRoteadorSemMsg(ListaR* lista, char* nome) {
  CelulaR* aux = lista -> primeiro;
  CelulaR* p = NULL;

  RemoveEnlace(aux, nome);

  while(aux != NULL && strcmp(aux -> roteador -> nome,nome)) {
      p = aux;
      aux = aux -> prox;
    }

  if(aux != NULL) {
    if(lista -> primeiro == aux) {
      lista -> primeiro = aux -> prox;
      LiberaCelulaRoteador(aux);
    } else {
      p -> prox = aux -> prox;
      LiberaCelulaRoteador(aux);
    }
  } else {
    return;
  }
}

//Imprime o nome de um roteador
void ImprimeRoteador(Roteador* roteador, FILE* Arq) {
  fprintf(Arq, "%s", roteador -> nome); //Printa o nome do roteador no arquivo
}

//Imprime uma celula do tipo roteador
void ImprimeCelulaRoteador(CelulaR* cRoteador, FILE* Arq){
  ImprimeRoteador(cRoteador -> roteador, Arq); //Usa a imprime roteador mas usadando na celula
}

//Imprime os roteadores da lista de enlaces de uma determinada celula
void ImprimeEnlaces(CelulaR* cRoteador, FILE* Arq){
  CelulaR* aux = cRoteador; //Cria uma celula do tipo roteador e faz ela apontar para o roteador do input
  Roteador* rot = aux -> roteador -> proximoEnlace; //Cria um ponteiro para um roteador e faz ele apontar para o primeiro enlace de aux

  while(rot != NULL){ //Roda a lista de enlaces de rot
    //Nesse while ele imprime os roteadores da lista de enlaces do roteador
    fprintf(Arq, "    %s -- ", cRoteador -> roteador -> nome);
    ImprimeRoteador(rot, Arq);
    fprintf(Arq,";\n");
    rot = rot -> proximoEnlace;
  }
}

//Imprime os roteadores do NETMAP
void ImprimeListaRoteadores(ListaR* lista, FILE* Arq) {
  CelulaR* aux = lista -> primeiro; //Cria uma ponteiro para uma celula do tipo roteador e faz ele apontar para a primeira da lista

  while(aux != NULL) { //Roda a lista

    if(aux -> roteador -> proximoEnlace != NULL) { //Olha se tem enlances
      ImprimeEnlaces(aux, Arq); //Caso tenha, imprime o enlace
  } else { //caso nao tenha, imprime a celula apenas
      fprintf(Arq,"    ");
      ImprimeCelulaRoteador(aux, Arq);
      fprintf(Arq,";\n");
    }
    aux = aux -> prox; //passa para a proxima celula da lista
  }
}

//Libera uma lista de enlaces de um determinado roteador
void LiberaEnlace(Roteador* roteador) {
  Roteador* aux2;
  Roteador* aux = roteador -> proximoEnlace;
  while(aux != NULL) {
    free(aux -> nome);
    free(aux -> operadora); // Libera a operadora
    aux2 = aux; // Recebe a posicao atual
    aux = aux -> proximoEnlace; // Avanca
    free(aux2); // Libera a posicao atual
  }
}

//Libera um roteador e sua lista de enlaces
void LiberaRoteador(Roteador* roteador) {
  free(roteador -> nome); // Liberara o nome
  free(roteador -> operadora); // Libera a operadora
  LiberaEnlace(roteador); // Chama a funcao LiberaEnlace
  free(roteador); // Livera  o roteador
}

//Libera apenas o roteador
void LiberaSoRoteador(Roteador* roteador) {
  free(roteador -> nome); // Libera o nome
  free(roteador -> operadora); // Libera a operadora
  free(roteador); // Libera o roteador
}

//Libera uma celula do tipo roteador
void LiberaCelulaRoteador(CelulaR* aux2){
  LiberaRoteador(aux2 -> roteador); // Chama a funcao LiberaRoteador
  free(aux2); // Libera a celula
}

//Libera toda uma lista de roteadores
void LiberaListaRoteadores(ListaR* lista){
    CelulaR *aux, *aux2;

    aux = lista -> primeiro;

    while(aux != NULL){ //Roda toda a lista
      aux2 = aux; // Recebe a posicao atual
      aux = aux -> prox; // Avanca para a proxima posicao
      LiberaCelulaRoteador(aux2); // Chama a funcao LiberaCelulaRoteador
    }

    free(lista); // Libera a lista
}

//Retorna o  campo prox de uma celula do tipo roteador
CelulaR* RetornaProxR(CelulaR* aux){
  return aux -> prox; // Retorna a proxima posicao
}

//Retorna o campo roteador de um caelula de roteadore
Roteador* RetornaRoteador(CelulaR* aux){
  return aux -> roteador; // Retorna o roteador
}

//Retorna a primeira celula de uma lista de roteadores
CelulaR* RetornaPrimeiro(ListaR* listaR){
  return listaR -> primeiro; // Retorna a primeira posicao da lista
}

//Retorna de qual operadora um roteador eh
char* RetornaOperadoraRoteador(Roteador* roteador){
  return roteador -> operadora; // Retorna a operadora
}

// Funcao que encontra um roteador na lista pelo nome
Roteador* BuscaRoteador(ListaR* lista, char* nome, FILE* Arq){
  CelulaR* aux = lista -> primeiro;

  while(aux != NULL && strcmp(aux -> roteador -> nome, nome)) aux = aux -> prox; // Roda ate o final da lista ou encontrar

  if(aux == NULL){ // Se nao encontrar
    ImprimeErroRoteador(nome, Arq); // Imprime mensagem erro
    return NULL; // Retorna previamente com NULL
  }

  return aux -> roteador; // Retorna o ponteiro para o roteador
}

// Funcao que faz o mesmo que "BuscaRoteador" porem nao imprime mensagem de erro
Roteador* BuscaRoteadorSemMsg(ListaR* lista, char* nome){
  CelulaR* aux = lista -> primeiro;

  while(aux != NULL && strcmp(aux -> roteador -> nome, nome)) aux = aux -> prox; // Roda ate o final da lista ou encontrar

  if(aux == NULL){ // Se nao encontrar
    return NULL; // Retorna previamente com NULL
  }

  return aux -> roteador; // Retorna o ponteiro para o roteador
}

// Desconecta um roteador do outro
void DesconectaRoteador(Roteador* rote1, Roteador* rote2){
  if(rote1 != NULL && rote2 != NULL) { // Se forem diferente de NULL
    DesconectaUmEnlace(rote1, rote2); // Chama a funcao DesconectaUmEnlace
    DesconectaUmEnlace(rote2, rote1); // Chama novamente a funcao, porem com os parametros invertidos
  }
}

void DesconectaUmEnlace(Roteador* rote1, Roteador* rote2){
  Roteador* aux = rote1 -> proximoEnlace;
  Roteador* ant = rote1;

  while(aux != NULL && strcmp(rote2 -> nome, aux -> nome)){ //Roda ate encontrar ou acabar a lista
    ant = aux; // Recebe a posicao autal
    aux = aux -> proximoEnlace; // Avanca pro proximo
  }

  if(aux == NULL) return; // Se nao encontrar, retorna previamente

  if(aux -> proximoEnlace != NULL) ant -> proximoEnlace = aux -> proximoEnlace; // Se nao for o ultimo
  else ant -> proximoEnlace = NULL; // Se for o ultimo

  LiberaSoRoteador(aux); // Chama a funcao LiberaSoRoteador
}

//Imprime uma mensagem de erro caso o terminal nao exista no NETMAp
void ImprimeErroTerminal(char* nomeT, FILE* Arq){
    fprintf(Arq, "Erro: Terminal %s inexistente no NetMap\n", nomeT);
}

//Imprime uma mensagem de erro caso o roteador nao esteja no NETMAP
void ImprimeErroRoteador(char* nomeR, FILE* Arq){
    fprintf(Arq, "Erro: Roteador %s inexistente no NetMap\n", nomeR);
}

// Funcao que verifica se o roteador de destino esta na lista de enlaces do de origem
int DescobreSeEEnlace(Roteador* origem, Roteador* destino){
  Roteador* aux = origem;

  while(aux != NULL && strcmp(aux -> nome,destino -> nome)){ // Roda ate o final ou encontrar
    aux = aux -> proximoEnlace; // Avanca
  }

  if(aux != NULL) // Se encontrar
    return 1; // Retorna "verdadeiro"
  else // senao
    return 0; // Retorna "falso"
}

// Funcao que busca a celula de determinado roteador de certa lista
CelulaR* BuscaCelulaRoteador(ListaR* lista, Roteador* rote){
  if(rote == NULL){ // Se nao houver roteador
    return NULL; // Retorna previamente com NULL
  }

  CelulaR* aux = lista -> primeiro;

  while(aux != NULL && strcmp(aux -> roteador->nome, rote -> nome)) aux = aux -> prox; // Roda ate o final ou encontar

  if(aux == NULL){ // Se nao encontrar
    return NULL; // Retorna previamente com NULL
  }

  return aux; // Retorna o ponteiro pra celula
}

// Funcao que descobre se ha caminho para enviar o pacote
int DescobreSeHaCaminho(ListaR* lista, ListaR* listaP, Roteador* remetente, Roteador* destinatario){
  if(remetente == NULL || destinatario == NULL){ // Se um dos dois for NULL
    return 0; // Retorna "falso"
  }

  CelulaR* cAux = BuscaCelulaRoteador(listaP, remetente);
  Roteador* aux = NULL;

  if(cAux != NULL){ // Se aux diferente de NULL
    aux =  cAux -> roteador ->proximoEnlace; // Entra na lista de enlace
    if(DescobreSeEEnlace(cAux -> roteador, destinatario)) return 1; // Chama a funcao DescobreSeEEnlace, se sim retorna previamente com "verdadeiro"
  }

  while(cAux != NULL) { // Roda ate o final da lista
    while(aux != NULL){ // Rota ate o final da lista de enlaces
      Roteador* roteN = BuscaRoteadorSemMsg(lista, RetornaNomeRoteador(aux));
      if(roteN == NULL){ // Se nao encontrar "aux" na lista
        CadastraRoteador(lista, IniciaRoteador(RetornaNomeRoteador(remetente), RetornaOperadoraRoteador(remetente))); // Insere um roteador na lista auxiliar para marcar os roteadores ja passados
        int resposta = DescobreSeHaCaminho(lista,listaP, aux, destinatario); // Realiza a recusao
        if(resposta){ // Se resposta for diferente de 0
          return 1; // Retorna previamente com "verdadeiro"
        }
      }
      aux = aux -> proximoEnlace; // Avanca
    }
    cAux = BuscaCelulaRoteador(listaP, aux); // Avanca
  }

  return 0;
}