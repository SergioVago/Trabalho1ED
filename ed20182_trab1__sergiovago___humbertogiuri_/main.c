#include "Terminal.h"

int main(int argc, char** argv){
  FILE *Saida, *Log, *Dot;
  char comando[50], nome[100], locop[100];

  Saida = fopen ("saida.txt", "w");
  Log = fopen("log.txt", "w");
  Dot = fopen("saida.dot", "a");

  ListaT* lista = InicializaListaTerminais();
  ListaR* listaR = IniciaListaRoteadores();

  if(argc == 1) {
    fprintf(Log, "Erro: I/O, diretorio nao foi informado");
    exit(0);
  }

  FILE* FP = fopen(argv[1], "r");
  if (FP == NULL) {
    fprintf(Log,"Erro: I/O, nao foi possivel abrir o arquivo '%s'\n", argv[1]);
    exit(0);
  } else {
    do {
      fscanf(FP, "%s", comando);
      if(!strcmp(comando, "CADASTRAROTEADOR")) {
        fscanf(FP, "%s %s", nome, locop);
        CadastraRoteador(listaR, IniciaRoteador(nome, locop));
      }
      else if(!strcmp(comando, "CADASTRATERMINAL")){
        fscanf(FP, "%s %s", nome, locop);
        CadastraTerminal(lista, IniciaTerminal(nome, locop));
      }
      else if(!strcmp(comando, "REMOVEROTEADOR")){
        fscanf(FP, "%s", nome);
        DesconcetaTerminalRoteadorRemovido(lista, nome, Log);
        RemoveRoteador(listaR, nome, Log);
      }
      else if(!strcmp(comando, "REMOVETERMINAL")){
        fscanf(FP, "%s", nome);
        RetiraTerminal(lista, nome, Log);
      }
      else if(!strcmp(comando, "CONECTAROTEADORES")){
        fscanf(FP, "%s %s", nome, locop);
        ConectaRoteador(listaR, BuscaRoteador(listaR,nome, Log), BuscaRoteador(listaR,locop, Log));
      }
      else if(!strcmp(comando, "CONECTATERMINAL")){
        fscanf(FP, "%s %s", nome, locop);
        ConectaTerminalAoRoteador(lista, listaR, nome, locop, Log);
      }
      else if(!strcmp(comando, "DESCONECTAROTEADORES")){
        fscanf(FP, "%s %s", nome, locop);
        DesconectaRoteador(BuscaRoteador(listaR,nome, Log), BuscaRoteador(listaR,locop, Log));
      }
      else if(!strcmp(comando, "DESCONECTATERMINAL")){
        fscanf(FP, "%s", nome);
        DesconectaTerminal(lista , nome, Log);
      }
      else if(!strcmp(comando, "FREQUENCIATERMINAL")){
        fscanf(FP, "%s", nome);
        FrequenciaTerminal(lista, nome, Saida);
      }
      else if(!strcmp(comando, "FREQUENCIAOPERADORA")){
        fscanf(FP, "%s", nome);
        FrequenciaOperadora(listaR, nome, Saida);
    }
      else if(!strcmp(comando, "ENVIARPACOTESDADOS")){
        fscanf(FP, "%s %s", nome, locop);
        EnviaPacoteDeDados(lista, listaR, nome, locop, Log, Saida);
      }
      else if(!strcmp(comando, "IMPRIMENETMAP")){
        ImprimeNetMap(lista, listaR, Dot);
      }
    } while (strcmp(comando,"FIM"));
  }

  LiberaListaRoteadores(listaR);
  LiberaListaTerminais(lista);

  fclose(FP);
  fclose(Saida);
  fclose(Log);
  fclose(Dot);

  return 0;
}
