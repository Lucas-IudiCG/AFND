//Nossa relosu��o do problema foi baseado no processamento de cadeia de um AFND, utilizando recurs�o, abrindo caminhos possiveis baseado nas letras lidas e se esses caminhos existem, ou n�o.
//se n�o possuir caminhos o processo "morre", j� que n�o pode mais abrir nenhuma recurs�o ou chegar no fim da palavra.
// se o caminho escolhido chegar no final, mas n�o for um estado final, esse caminho tamb�m � descartado.

// Gabriel Ramires TIA: 42080681
// Lucas Iudi Corregliano Gallinari TIA: 32138628

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int Trans[10][10][10];// a matriz de transi��o funciona da seguinte maneira Trans[EstadoAtual][Letra lida][Estado que ele vai estar]
int verifica;//variavel para definir se a palavra � "OK" ou "not OK"
int size=0;//tamanho do alfabeto
int Q=0;//n�mero de estados
int F=0;//n�mero de estados finais

void DefineSize(char* Alfa){// � um fun��o que modifica o valor de size (o tamanho do alfabeto)
  int c;
  for(c=0;c<10;c++){
    if(Alfa[c]=='\0'){
     break;
  }
  }
  size=c;
}


void AdicionaTransicao(int teste1,char teste2,int teste3,char *Alfa){
  int c;// procura a letra de teste2 no alfabeto
  for(c=0;c<size;c++){
    if(teste2 ==Alfa[c]){
      break;
    }
  }
  Trans[teste1][c][teste3]=1;// muda o valor de Trans para 1, esse 1 indica que existe passagem, ou seja, Trans [0][a][0] =1, indicaria que se o Q0 receber um a ele pode ir para Q0.
}

int PegaLetra(char* Palavra,int index,char* Alfa){
  int c;
  for(c=0;c<size;c++){
    if(Palavra[index] ==Alfa[c]){
      return c;
    }
  }
  return -1;
}

bool VerificaPalavra(int Qatual,int index,int Fim,char* Alfa,char *Palavra,int* Final){
  int b=PegaLetra(Palavra,index,Alfa);// busca se existe a letra lida no alfabeto e retorna a indice do alfabeto.
  if(b>-1){// se a letra existe no alfabeto
      for(int c=0;c<Q;c++){
        if(Trans[Qatual][b][c]==1){// basicamente esse for procura baseado no seu estado atual e letra recebida se ele tem algum caminho possivel, exemplo se trans[0][a][0]=1, ent�o ele pode prosseguir, o mesmo acontece para [0][a][1]=1,
          Qatual=c;// o estado atual muda para o estado de destino j� que existe um caminho.
          VerificaPalavra(Qatual,index+1, Fim,Alfa,Palavra,Final);// chama a fun��o recursivamente
          for (int x=0;x<F;x++){// se chegou no fim na palavra verifica se � um estado final
            if(c==Final[x] && index== Fim-1){
              verifica++;
          }
          }
      }
  }
  }
  if (verifica>0){// se chegou a pelo menos um estado final na ultima letra, ent�o verifica concerteza � maior que 0, retornando true
    return true;
  }
  return false;// caso contrario retorna false.
}

void leitura(char *Alfa,char *Final,char* palavra){// � um fun��o que le o arquivo input.txt, e salva os valores nas respectivas variaveis, para depois executar o afnd.

  FILE  *textfile;// define um FILE
  int x = 0;

  int a=0;
  textfile = fopen("input.txt", "r");//abre o file
  if (textfile) {
    //ler o alfabeto
    Alfa[a]=fgetc(textfile);// pega o primeiro caracter do alfabeto
    while(Alfa[a]!=EOF&& Alfa[a]!='\n'){  // pega letras do alfabeto at� chegar no final, ou seja, n�o existe mais letras.
        a++;
        Alfa[a]=fgetc(textfile);
    }
    // limpa o array alfa, para ficar de acordo com o necessario para realizar o restos das fun��es
    for(a=0;a<10;a++){
    if(Alfa[a]!='\0'){
      if(Alfa[a]=='\n'){
        Alfa[a]='\0';
      }
  }
    }
    DefineSize(Alfa);// define quantas letras o alfabeto pode ler atrav�s da fun��o DefineSize


    //ler que e atualiza estados
    int a=0;
    char t=fgetc(textfile);
    Q=atoi(&t);// modifica o valor de Q,Transformando o t em int
    char nada=fgetc(textfile);// pega um '\0'
    t=fgetc(textfile);// pega o n�mero de estados finais
    F =atoi(&t);
    nada=fgetc(textfile);// pega um '\0'
    Final[a]=fgetc(textfile);

    //ler os estados finais com uma fun��o semelhante ao do alfabeto
    //o vetor final na realizada � o vetor str na main, que serve para carregar os valores em char, que depois ser� modificado para int com o atoi.
    while(Final[a]!=EOF&& Final[a]!='\n'){
        a++;
        Final[a]=fgetc(textfile);
    }
    //limpa o vetor str
    for(a=0;a<20;a++){
    if(Final[a]!='\0'){
      if(Final[a]=='\n'){
        Final[a]='\0';
      }
  }
}
    //ler o n�mero de fun��es de transi��es
  t=fgetc(textfile);
  t=atoi(&t);
    int teste1;
    char teste2;
    int teste3;
    nada=fgetc(textfile);
    //ler a fun��o de transi��o.
    for(x=0;x<t;x++){
      fscanf(textfile, "%d\t%c\t%d", &teste1, &teste2, &teste3);// utiliza uma outra fun��o para ler a linha que cont�m a fun��o de transi��o, e repete igual o n�mero de vezes que foi comentado acima.
      // salva as variaveis em teste1, teste2 e teste3.
      nada=fgetc(textfile);// le o '\0'
      AdicionaTransicao(teste1,teste2,teste3,Alfa);// adiciona na fun��o de trasi��o.
    }
    //le o n�mero das palavras que v�o ser lidas
    t=fgetc(textfile);
    t=atoi(&t);

    //le as express�es
    a=0;
    nada=fgetc(textfile);
    // le as palavras, utilizando uma fun��o semelhante ao alfa e ao final, mas desta vez � lido o '\n'
    palavra[a]=fgetc(textfile);
    while(palavra[a]!=EOF){
        a++;
        palavra[a]=fgetc(textfile);
    }
    palavra[a]='\0';// limpar lixo
    fclose(textfile); // fecha o arquivo de texto
}
}

int main(void) {
  char Alfa[10]={'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};//define o alfabeto
  int Final[20];//define os estados finais
  char str[20];// define um array auxiliar para os estados finais
  char palavra[100];// define um array aonde todas as palavras ser�o salvas.
  int a=0;

  // o for abaixo preenche a matriz tridimensional com 0
  for(a=0;a<10;a++){
    for(int b=0;b<10;b++){
      for(int c=0;c<10;c++){
        Trans[a][b][c]=0;
      }
    }
  }
   // o for abaixo preenche o array final com -1, e o array str com '\0'
  for(a=0;a<20;a++){
    Final[a]=-1;
    str[a]='\0';
  }
  // o for abaixo preenche o array palavra com '\0'
  for(a=0;a<100;a++){
    palavra[a]='\0';
  }

  // isso foi feito apenas para limpar os arrays

  leitura(Alfa,str,palavra);// chama a fun��o leitura que vai ler todas as instru��es do input

  for(a=0;a<20;a++){
    if(str[a]!='\0' && str[a]!='\n'){
      Final[a]=atoi(&str[a]);// troca os valores da str de char, para int e salva em final
  }
  }


  int Soma=0;
  for(a=0;a<100;a++){
    if(palavra[a]!='\0' && palavra[a]!='\n'){// le e escreve as palavra
      printf("%c",palavra[a]);
      Soma++;
    }
    else if(palavra[a]=='\n'){ // se a palavra[a] for '\n' indica que a palavra terminou, e pode ser verificada
      verifica=0;// reseta o verifica por palavra.
        bool teste=VerificaPalavra(0,(a-Soma),a,Alfa,palavra,Final);
      //VerificaPalavra recebe , primeiro: estado atual, todos come�am em q0, segundo: o indice inicio da palavra (ou seja o o tamanho da palavra-final da palavra), terceiro: o indice final da palavra que � classificado com '\n', e por fim respectivamento o alfabeto, a palavra e o final.
      // obs como o array palavra tem todas as palavras foi nescessario colocar os indices de inicio e fim.
        Soma=0;
        if(!teste){
          printf(" not OK\n");
        }
        if(teste){
          printf(" OK\n");
        }
      }
    if(palavra[a]=='\0'){
      break;
    }
  }
 bool teste=VerificaPalavra(0,a-1,a,Alfa,palavra,Final);// verifica a ultima palavra que termina com '\0', e n�o '\n'
if(!teste){
          printf(" not OK\n");
        }
        if(teste){
          printf(" OK\n");
        }

  return 0;
}
