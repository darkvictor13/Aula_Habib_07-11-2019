#include <stdio.h>

#define maxc 100

typedef struct {
  char identidade[5];
  char nome[51];
  int moradores_por_ap;
  float area,valor_do_condominio;
}morador;

typedef struct {
  float despesa;
  int tot_moradores;
  float tot_area;
  float tot_valor;
}junta_totais;


int ler (char file_name[],morador t[],int *tam, junta_totais *tot) {
  int i;
  morador *p = t;

  FILE *arch= fopen(file_name,"r");
  
  if (arch == NULL) {
    printf("Deu ruim ae meu patrao\nFaz denovo isso ae man!\n");
    return 1;
  }
  fscanf(arch,"%f%*c",&tot->despesa);

  /*for (i = 0; !feof(arch); i++) {
    fscanf(arch,"%[^\n]%*c",t[i].identidade);
    fscanf(arch,"%[^\n]",t[i].nome);
    fscanf(arch,"%d",&t[i].moradores_por_ap);
    fscanf(arch,"%f%*c",&t[i].area);
  }*/

  for (; !feof(arch); p++) {
    fscanf(arch,"%[^\n]%*c",p->identidade);
    fscanf(arch,"%[^\n]",p->nome);
    fscanf(arch,"%d",&p->moradores_por_ap);
    fscanf(arch,"%f%*c",&p->area);
  }

  //*tam = i;
  *tam = (p - t);
  fclose(arch);
  return 0;
}

void calculaMoradoresArea(morador tabela[],int tam, junta_totais *totais) {
  int soma_moradores,i;
  float soma_area;
  morador *fim = (tabela + tam);
  
  /*for (soma_area = soma_moradores = i = 0; i < tam; i++) {
    soma_area += tabela[i].area;
    soma_moradores += tabela[i].moradores_por_ap;
  }*/

  for (soma_area = soma_moradores = 0; tabela < fim; tabela++) {
    soma_area += tabela->area;
    soma_moradores += tabela->moradores_por_ap;
  }

  totais->tot_area = soma_area;
  totais->tot_moradores = soma_moradores;
}

void calc (morador tabela[],int tam, junta_totais total) {
  float x = total.despesa/2;
  float k_area = x/total.tot_area;
  float k_moradores = x/total.tot_moradores;
  morador *fim = (tabela + tam);

  /*for (int i = 0; i < tam; i++) {
    tabela[i].valor_do_condominio = ((float)tabela[i].moradores_por_ap/total.tot_moradores)*x + 
    (tabela[i].area/total.tot_area) *x ;
  }*/

  /*for (int i = 0; i <tam; i++) {
    tabela[i].valor_do_condominio = k_area * tabela[i].area + k_moradores * tabela[i].moradores_por_ap;
  }*/

  for (; tabela < fim; tabela++) {
    tabela->valor_do_condominio = k_area * tabela->area + k_moradores * tabela->moradores_por_ap;
  }
}

void finalizaCalc (morador v[],int tam, junta_totais *total) {
  float aux;
  morador *fim = (v + tam);

  for (aux = 0; v < fim; v++) {
    aux += v->valor_do_condominio;
  }
  total->tot_valor = aux;
}

void printaCharNoArquivo (FILE *a,int tam, char c) {
  for (int count = 0; count < tam; count++) {
    fprintf(a,"%c",c);
  }
}

void cabecalho (FILE *a) {
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

void dados (FILE *arch,morador v[],int tam) {
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

void totais(FILE *arquivo,junta_totais tot) {
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
  ler("dados.txt",vetor,&tam,&total);
  calculaMoradoresArea(vetor,tam,&total);
  calc(vetor,tam,total);
  finalizaCalc(vetor,tam,&total);
  relat("relatorio.txt",vetor,tam,total);
  return 0;
}