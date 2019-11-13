#include <stdio.h>

#define maxc 100//tamanho maximo do vetor

typedef struct {//struct com os dados de cada morador
  char identidade[5];//numero do apartamento
  char nome[51];//nome do dono da casa
  int moradores_por_ap;//numero de moradores por apartamento
  float area;//area do apartamento
  float valor_do_condominio;//valor resultante dos calculos informa o valor a ser pago ao condominio
}morador;

typedef struct {
  float despesa;//total gasto pelo condominio
  int tot_moradores;//numero total de moradores
  float tot_area;//area total da soma de todos os apartamentos
  float tot_valor;//soma do valor a ser pago por cada um dos condominos
}junta_totais;


int lerDadosDoArquivo (char file_name[],morador t[],int *tam, junta_totais *tot) {
  morador *p = t;//ponteiro auxiliar para percorrer o vetor

  FILE *arch= fopen(file_name,"r");//abre o arquivo e salva o local em que foi abrto
  
  if (arch == NULL) {//teste para saber se o arquivo foi aberto corretamente
    printf("Deu ruim ae meu patrao\nFaz denovo isso ae man!\n");
    return 1;
  }

  fscanf(arch,"%f%*c",&tot->despesa);//leitura do 1 dado que seria a despesa total

  for (; !feof(arch); p++) {//le uma struct e incrementa para a proxima ate o fim do arquivo
    fscanf(arch,"%[^\n]%*c",p->identidade);
    fscanf(arch,"%[^\n]",p->nome);
    fscanf(arch,"%d",&p->moradores_por_ap);
    fscanf(arch,"%f%*c",&p->area);
  }

  *tam = (p - t);//local final - local inicial eh igual tamanho do vetor
  fclose(arch);//fecha o arquivo
  return 0;
}

void calculaMoradoresArea(morador tabela[],int tam, junta_totais *totais) {
  int soma_moradores;//auxiliar para ser mais eficiente a leitura do num de moradores
  float soma_area;
  morador *fim = (tabela + tam);//ponteiro que aponta para o fim do vetor

  for (soma_area = soma_moradores = 0; tabela < fim; tabela++) {//percorre o vetor ate o fim
  //vai somando todas as areas e todos os moradores e salvando em suas variaveis auxiliares
    soma_area += tabela->area;
    soma_moradores += tabela->moradores_por_ap;
  }

  //joga para a struct os valores lidos
  totais->tot_area = soma_area;
  totais->tot_moradores = soma_moradores;
}

void calc (morador tabela[],int tam, junta_totais total) {//acha o valor a ser pago por cada morador
  float x = total.despesa/2;
  float k_area = x/total.tot_area;
  float k_moradores = x/total.tot_moradores;

  morador *fim = (tabela + tam);

  for (; tabela < fim; tabela++) {
    tabela->valor_do_condominio = k_area * tabela->area + k_moradores * tabela->moradores_por_ap;
  }
}

void finalizaCalc (morador v[],int tam, junta_totais *total) {//soma o valor a ser pago por cada condimino
  float aux;
  morador *fim = (v + tam);

  for (aux = 0; v < fim; v++) {
    aux += v->valor_do_condominio;
  }
  total->tot_valor = aux;
}

void printaCharNoArquivo (FILE *a,int tam, char c) {
  //coloca no arquivo um char indicado, a  quantidade de vezes indicada
  for (int count = 0; count < tam; count++) {
    fprintf(a,"%c",c);
  }
}

void cabecalho (FILE *a) {//faz o cabecalho
  fprintf(a,"|");
  printaCharNoArquivo(a,95,'-');
  fprintf(a,"|");
  fprintf(a,"\n");
  fprintf(a,"|");
  fprintf(a,"%-5s","NUM");
  fprintf(a,"|");
  fprintf(a,"%-49s","NOME");
  fprintf(a,"|");
  fprintf(a,"%-9s","APT");
  fprintf(a,"|");
  fprintf(a,"%-9s","MORAD");
  fprintf(a,"|");
  fprintf(a,"%-9s","AREA");
  fprintf(a,"|");
  fprintf(a,"%-9s","CUSTO");
  fprintf(a,"|\n");
  fprintf(a,"|");
  printaCharNoArquivo(a,95,'-');
  fprintf(a,"|\n");
}

void dados (FILE *arch,morador v[],int tam) {//coloca no aqruivo todos os dados
  morador *inicio = v;
  morador *fim  = (v + tam);

  for (; v < fim; v++) {
    fprintf(arch,"|");
    fprintf(arch,"%-5d",(v - inicio));
    fprintf(arch,"|");
    fprintf(arch,"%-49s",v->nome);
    fprintf(arch,"|");
    fprintf(arch,"%-9s",v->identidade);
    fprintf(arch,"|");
    fprintf(arch,"%-9d",v->moradores_por_ap);
    fprintf(arch,"|");
    fprintf(arch,"%-8.2f ",v->area);
    fprintf(arch,"|");
    fprintf(arch,"%-9.2f",v->valor_do_condominio);
    fprintf(arch,"|\n");
  }
}

void totais(FILE *arquivo,junta_totais tot) {//coloca no arquivo os totais gerados
  fprintf(arquivo,"|");
  printaCharNoArquivo(arquivo,95,'-');
  fprintf(arquivo,"|\n");
  fprintf(arquivo,"|");
  printaCharNoArquivo(arquivo,53,' ');
  fprintf(arquivo,"%-12s","TOTAIS");
  fprintf(arquivo,"|");
  fprintf(arquivo,"%-3d",tot.tot_moradores);
  printaCharNoArquivo(arquivo,6,' ');
  fprintf(arquivo,"|");
  fprintf(arquivo,"%-6.2f",tot.tot_area);
  printaCharNoArquivo(arquivo,3,' ');
  fprintf(arquivo,"|");
  fprintf(arquivo,"%-7.2f",tot.tot_valor);
  fprintf(arquivo," |\n");
  fprintf(arquivo,"|");
  printaCharNoArquivo(arquivo,95,'-');
  fprintf(arquivo,"|\n");
  fprintf(arquivo,"|");
  printaCharNoArquivo(arquivo,73,' ');
  fprintf(arquivo,"%-12s","VALOR");
  fprintf(arquivo,"|");
  fprintf(arquivo,"%8.2f",tot.despesa);
  fprintf(arquivo," |\n");
  fprintf(arquivo,"|");
  printaCharNoArquivo(arquivo,95,'-');
  fprintf(arquivo,"|\n");
}

void relat (char fn[],morador vet[],int tam,junta_totais total) {
  //chama todas as funcoes necessarias para fazer o relatorio
  FILE *arch = fopen (fn,"w");
  cabecalho(arch);
  dados(arch,vet,tam);
  totais(arch,total);
  fclose(arch);
}

int main () {
  morador vetor[maxc];
  int tam;
  junta_totais total;
  lerDadosDoArquivo("dados.txt",vetor,&tam,&total);
  calculaMoradoresArea(vetor,tam,&total);
  calc(vetor,tam,total);
  finalizaCalc(vetor,tam,&total);
  relat("relatorio.txt",vetor,tam,total);
  return 0;
}