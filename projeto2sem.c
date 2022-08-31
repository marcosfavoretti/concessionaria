#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>

/*
210039  GABRIEL PEREIRA DE CAMARGO
210036  GUSTAVO TAMBELLI RODRIGUES
210482  MARCOS FAVORETTI JUNIOR
210072  MATHEUS UYLKER ROMANO SIMON
*/

// Structs da Concessionária

typedef struct endereco { 
 char logradouro[80]; 
 char bairro[15]; 
 char CEP[10]; 
 char cidade[15]; 
 char estado[3]; 
 char fone[12]; 
 char email[40]; 
}endereco; 
 
typedef struct infocarro { 
 char sigla;// = 'r'
 int regcarro; 
}infocarro; 
 
typedef union dadoscarro { 
 char sigla; //= 'l'
 struct infocarro reservado; 
}dadoscarro; 

typedef struct loja { 
 int regloja;
 char nome[30]; 
 char CNPJ[19]; 
 struct endereco end; 
 int sold; 
 int reserved; 
 union  dadoscarro  tabela[3]; 
}loja; 

//Structs dos Carros

typedef struct infoloja { 
 char sigla; 
 char CNPJ[19]; 
}infoloja; 
 
typedef union dadosloja { 
 char sigla; 
 struct infoloja reserva; 
}dadosloja; 
 
typedef struct montadora  { 
 int regcarro; //gerar automático 
 char modelo[20]; 
 char cor[10]; 
 float  valor; 
 union dadosloja status; 
}montadora; 

//Structs do Historico

typedef struct data      { 
int dia;  
int mes;  
int ano;  
}data; 
 
typedef struct historicoVendas     { 
int reghist; 
int regcarro; 
char modelo[20]; 
char cor[10]; 
float valor;  
int regloja; 
char nome[30]; 
char cnpj[19]; 
struct data dataVenda; 
}histvenda; 
// Funções

int menu();
 //Funçoes para Loja
void aloca( loja **p, int tam);
int verifica();
void cadastro(loja *p, int *pcont);
void grava_loja(loja *p);
void busca(loja *p, int cont);
void altera_loja(loja *p, int cont);
 //Funçoes para Carro
void aloca_carros(montadora **p2, int tam2);
int verifica2();
void cadastro_carros(montadora *p, int *pcont2);
void grava_carro(montadora *p2);
void busca_carro(montadora *p2, int cont2);
void altera_carro(montadora *p2, int cont2);
void varrecarro(montadora *p2, int cont2, int option);
 //Funçoes para Reserva
void iniciar_reserva(loja *p, montadora *p2, int cont, int cont2);
void terminar_reserva(loja *p, montadora *p2, int cont2, int cont, histvenda *p3, int *pcont3);
void grava(loja *p, char *str, int pos);
int busca_pos(loja *p, char passa[19]);
void grava2(montadora *p2, char *str, int pos2);
int busca_pos_car(montadora *p2, int regcarro);
 //Funçoes para Historico de Vendas
void aloca_venda(histvenda **p3, int tam3);
int verifica3();
void cadastro_venda(histvenda *p3, int *pcont3, loja *p, montadora *p2);
void grava_venda(histvenda *p3);
void consulta_venda(histvenda *p3, int cont3);


int main(){//inicio da main
	
	setlocale(LC_ALL, "Portuguese"); // Deixar em português
    system("color 02");
	loja  *ptr = NULL;
	montadora *ptr2 = NULL;
	histvenda *ptr3 = NULL;
	
	int cont=0 , cont2=0,cont3=0,resp2,*pcont,*pcont2,*pcont3;
	pcont=&cont;
	pcont2=&cont2;	
	pcont3=&cont3;
	
	aloca(&ptr, cont+1);	 		// Alocar espaço para Montadora
	cont = verifica();				// Saber o valor de cont com base em leitura do arquivo .bin
	aloca_carros(&ptr2, cont2+1);	// Alocar espaço para Carro
	cont2 = verifica2();			// Saber o valor de cont2 com base em leitura do arquivo .bin
	aloca_venda(&ptr3, cont3+1);    // Alocar espaço para Histórico
	cont3 = verifica3();			// Saber o valor de cont3 com base em leitura do arquivo .bin
	
	do
	 {
      resp2=menu(); // Função de Menu
	  if (resp2 == 1) // Cadastro de Concessionaria	
	 	cadastro(ptr,pcont);		
	  else if (resp2 == 2) // Pesquisar Empresa
	    busca(ptr, cont);	
	  else if (resp2 == 3) // Registro de Carro	  			
	    cadastro_carros(ptr2,pcont2);	
	  else if (resp2 == 4) // Procurar Carro
	    busca_carro(ptr2, cont2);	
	  else if (resp2 == 5) // Inicio Reserva
	    iniciar_reserva(ptr,ptr2,cont,cont2);
	  else if (resp2 == 6) // Termino Reserva
	    terminar_reserva(ptr, ptr2, cont2, cont, ptr3, pcont3);
	  else if (resp2 == 7) // Consulta do Histórico de Venda
	    consulta_venda(ptr3, cont3);
	  else if (resp2 == 8 ) // Alterar concessionaria
	    altera_loja(ptr,cont);
	  else if (resp2 == 9) // Alterar carro
	    altera_carro(ptr2,cont2);
	} while(resp2 != 10); // Fechar programa
	return 0;
} // fim da main

int menu() // Função do Menu
{
	int opt;
	system("cls"); 
	printf("[Sistema da Concessionária]\n > O que deseja fazer hoje? \n  [1] - Registrar Empresa\n  [2] - Pesquisar Empresa\n  [3] - Registrar Carro \n  [4] - Procurar Carro\n  [5] - Iniciar Reserva\n  [6] - Terminar Reserva\n  [7] - Histórico de Vendas\n  [8] - Alterar Cadastro de Concessionária\n  [9] - Alterar Cadastro de Carros\n  [10]- Fechar Programa\n > Opção escolhida: ");
	scanf("%i",&opt);
	fflush(stdin);
	system("cls");
	printf("[Sistema da Concessionária]\n");  
	return(opt);
}

void aloca(loja **p, int tam) // Função para alocar espaço para loja
{
	if((*p=(loja*)realloc(*p,tam*sizeof(loja)))==NULL)
	 exit(1);
}

int verifica()
{
	FILE *fptr=NULL;
	long int cont = 0;
	if((fptr=fopen("concessionaria.bin","rb"))==NULL)
     return cont;
	else
     {
      fseek(fptr,0,2);   //posiciona fptr no final do arquivo
      cont=ftell(fptr)/sizeof(loja);
      fclose(fptr);     //dentro do else - por conta rb
      return cont;
     }
}

void cadastro(loja *p, int *pcont) // Função para cadastrar empresas
{
 char resp='S';
 int i; 
 if (*pcont == 5)
  printf(" > Limite de Empresas registradas alcançado!\n\n > "); 		
 while(*pcont<5 &&resp != 'N')
 {	
    p->sold=0;//iniciando loja sold como 0
	p->reserved=0;//iniciando loja reserved como 0	
	p->regloja=*pcont;//gerando automaticamente o valor de regloja
	printf(" > Cadastro da Concessionaria [%d]:\n",*pcont+1);		
	printf("  - Digite o nome da empresa: ");
    gets(p->nome);
    fflush(stdin);
	printf("  - Digite o CNPJ: ");
	gets(p->CNPJ);
	fflush(stdin);
	
	printf("  - Digite as seguintes informações:\n");
	printf("   > Logadouro: ");
	gets(p->end.logradouro);
	fflush(stdin);
	printf("   > Bairro: ");
	gets(p->end.bairro);
	fflush(stdin);
	printf("   > CEP: ");
	gets(p->end.CEP);
	fflush(stdin);
	printf("   > Cidade: ");
	gets(p->end.cidade);
	fflush(stdin);
	printf("   > Estado: ");
	gets(p->end.estado);
	fflush(stdin);
	printf("   > Telefone: ");
	gets(p->end.fone);
	fflush(stdin);
	printf("   > Email: ");
	gets(p->end.email);
	fflush(stdin);
	for (i=0;i<3;i++)
	{	
		p->tabela[i].sigla = 'L'; // inicializar tabela como L
	
    }
    grava_loja(p); // gravar no arquivo
    *pcont=*pcont+1; //incremento do cont
    printf(" > Deseja registrar outra empresa? (S/N)\n > Opção escolhida: ");
	scanf("%c", &resp);
	fflush(stdin);
	if (resp == 'n')
	 resp = 'N';
	printf("\n > ");	   	   
	system("pause");
	system("cls");
 }
}

void grava_loja(loja *p) // Função para salvar no disco
{
	FILE *fptr=NULL; // Declaração do ponteiro FILE
	if((fptr = fopen("concessionaria.bin","ab"))==NULL)
	 printf("\nErro ao abrir arquivo");
	else
     fwrite(p,sizeof(loja),1,fptr);
	fclose(fptr); 
}

void busca(loja *p, int cont) // Função de Busca de Empresa
{
	char passa[19];
	int i,j;
	printf(" > Digite o CNPJ da empresa a ser buscada: ");
	gets(passa);
	fflush(stdin);
	FILE *fptr=NULL;
	if((fptr=fopen("concessionaria.bin","rb"))==NULL)
     printf("\nErro ao abrir o arquivo");
	else
	 {
  	  for(i = 0; i < cont; i++)
       {
   		fseek(fptr,i*sizeof(loja), 0);
		fread(p,sizeof(loja),1,fptr);
		if(strcmp(passa,p->CNPJ) == 0)
	     {
	    	printf("  - Nome: %s\n  - Vendidos: %d\n  - Reservados: %d\n", p->nome, p->sold, p->reserved);
			for (j=0;j<3;j++)
			{
			 if (p->tabela[j].reservado.sigla=='R')
			  printf("  - Tabela [%i]: %c - %d\n",j+1,p->tabela[j].reservado.sigla,p->tabela[j].reservado.regcarro+1);
			 else
			  printf("  - Tabela [%i]: %c\n",j+1,p->tabela[j].sigla);	
			}
          }
   	    }
      
     
      fclose(fptr);//dentro do else - por conta rb
}
 	system("pause");
      system("cls");   
}

void aloca_carros(montadora **p2, int tam2) // Função para alocar espaço para carros
{
	if((*p2=(montadora*)realloc(*p2,tam2*sizeof(montadora)))==NULL)
     exit(1);
}

int verifica2()
{
	FILE *fptr=NULL;
	long int cont2 = 0;
	if((fptr=fopen("carro.bin","rb"))==NULL)
     return cont2;
	else
     {
   	  fseek(fptr,0,2);   //posiciona fptr no final do arquivo
      cont2=ftell(fptr)/sizeof(montadora);
      fclose(fptr);     //dentro do else - por conta rb
      return cont2;
  	 }
}

void cadastro_carros(montadora *p2, int *pcont2) // Função para cadastrar carros
{
 	char resp_carro='S';	
	if (*pcont2 == 50)
	 printf(" > Limite de Carros registrados alcançado!\n\n > "); 		
	while(*pcont2 < 50 && resp_carro != 'N')
	{
	 printf(" > Cadastro do Carro [%d]\n",*pcont2+1);		
	 p2->regcarro=*pcont2;
	 printf("  - Modelo do carro: ");
	 gets(p2->modelo);
	 fflush(stdin);
	 printf("  - Cor do carro: ");
	 gets(p2->cor);
	 fflush(stdin);
	 printf("  - Preço do carro: ");
	 scanf("%f", &(p2->valor));
	 fflush(stdin);
	 p2->status.sigla ='L';	//colocar l como carro
	 grava_carro(p2);//grava o carro
	 printf(" > Deseja registrar outro carro? (S/N)\n > Opção escolhida: ");
	 scanf("%c", &resp_carro);
	 fflush(stdin);
     *pcont2=*pcont2+1;
	 if (resp_carro=='n')
	 resp_carro= 'N';
	 
	 printf("\n > ");
	 system("pause");
	 system("cls");		 	
	}
}

void grava_carro(montadora *p2) // Função para gravar carros no .bin
{
	FILE *fptr=NULL; // Declaração do ponteiro FILE
	if((fptr = fopen("carro.bin","ab"))==NULL)
     printf("\nErro ao abrir arquivo");
	else
     fwrite(p2,sizeof(montadora),1,fptr);
    fclose(fptr); 
}
	
void busca_carro(montadora *p2, int cont2) // Função de busca total e parcial
{
	int resp;
	printf(" > Qual o tipo de busca desejado?\n  - [1]: Total \n  - [2]: Todos os carros Livres\n  - [3]: Todos os carros Ocupados\n  - [4]: Visualizar por modelo\n > Opção escolhida: ");
	scanf("%d", &resp);
	fflush(stdin);
	if(resp == 1 || resp == 2 || resp == 3 || resp == 4) // Se o pedido é valido
	 {
	   varrecarro(p2, cont2, resp);
	 }
	system("pause");
    system("cls");
}

void varrecarro(montadora *p2, int cont2, int option)
{
	FILE *fptr=NULL;	
	int i;	
	char modelin[20];
	  if (option==4)
	  {
	   printf(" > Deseja procurar qual modelo de carro? \n > Modelo desejado: ");
       gets(modelin);
	   fflush(stdin);
	  }
	  if((fptr=fopen("carro.bin","rb"))==NULL)
       printf("\nErro ao abrir o arquivo");
      else
       {
        for(i = 0; i < cont2; i++)
         {
   	      fseek(fptr,i*sizeof(montadora), 0);
		  fread(p2,sizeof(montadora),1,fptr);
		if (option==1) // Busca total
		 {
		  if(p2->status.sigla == 'R') // print de carro ocupado
	       printf("  - Número de Registro: %d\n   > Modelo: %s \n   > Cor: %s \n   > Valor: %.2f \n   > Status: %c - %s\n",p2->regcarro+1,p2->modelo, p2->cor, p2->valor,p2->status.reserva.sigla, p2->status.reserva.CNPJ);
	      else // print de carro livre
	   	   printf("  - Número de Registro: %d\n   > Modelo: %s \n   > Cor: %s \n   > Valor: %.2f \n   > Status: %c \n",p2->regcarro+1,p2->modelo, p2->cor, p2->valor,p2->status.sigla);	
		 }
		else if (option==2) // Ver todos os carros livres
		 {
		  if(p2->status.sigla=='L')
		   {	
	   		printf("  - Número de Registro: %d\n   > Modelo: %s \n   > Cor: %s \n   > Valor: %.2f \n   > Status: %c \n",p2->regcarro+1,p2->modelo, p2->cor, p2->valor,p2->status.sigla);
		   }		 	
		 }
		else if (option==3) // Ver todos os carros ocupados
		 {
		  if(p2->status.sigla=='R')
		   {	
	      	printf("  - Número de Registro: %d\n   > Modelo: %s \n   > Cor: %s \n   > Valor: %.2f \n   > Status: %c - %s\n",p2->regcarro+1,p2->modelo, p2->cor, p2->valor,p2->status.reserva.sigla, p2->status.reserva.CNPJ);
		   }		  	
		 }
		else if (option==4) // Procurar modelo específico de carro
		 {
		  if(strcmp(modelin,p2->modelo) == 0) // se achar o modelo
		   {
			if(p2->status.sigla == 'R')
	         printf("  - Número de Registro: %d\n   > Modelo: %s \n   > Cor: %s \n   > Valor: %.2f \n   > Status: %c %s\n",p2->regcarro+1,p2->modelo, p2->cor, p2->valor,p2->status.reserva.sigla, p2->status.reserva.CNPJ);
	    	else
	   		 printf("  - Número de Registro: %d\n   > Modelo: %s \n   > Cor: %s \n   > Valor: %.2f \n   > Status: %c \n",p2->regcarro+1,p2->modelo, p2->cor, p2->valor,p2->status.sigla);
		   }	      
		 }
 	   }
       fclose(fptr);   //dentro do else - por conta rb
	  }
}

void iniciar_reserva(loja *p, montadora *p2, int cont, int cont2) // funcao para iniciar reserva
{
	char passa[19], modelin[20];
	int  option,resp,numerocarro, pos2, pos;
	char statuszinho;	
	printf(" > Qual concessionária deseja realizar uma reserva?\n   - CNPJ: ");
	gets(passa);
	fflush(stdin);
	pos = busca_pos(p, passa);  // Posiciona o ponteiro no lugar certo
    if (pos==-1) // se não encontrou a empresa
    {
     printf("\n > Essa empresa não foi encontrada\n  - ");	
	 system("pause");
	 system("cls");
	 return;     	
	}
	printf("\n > Concessionária: %s\n", p->nome);
	if(p->reserved==3)
	{
	 printf("\n > Limite de carros alcançado para empresa %s \n",p->nome);
     system("pause");
     system("cls"); 		    
	 return;
	}
    printf(" > Deseja visualizar os carros livres da concessionária? \n  - [1]: Visualizar\n  - [2]: Não Visualizar\n  - Opção escolhida: ");
    scanf("%i",&option);
    fflush(stdin);
    if (option==1) // visualizar livres
      varrecarro(p2, cont2, 2);
	printf("\n > Qual carro deseja alugar? \n  - Insira o número do registro do carro: ");
	scanf("%d",&numerocarro);
    fflush(stdin);
	pos2 = busca_pos_car(p2, numerocarro-1);
	if (pos2==-1) // se não encontrou o carro
    {
     printf(" > Esse carro não foi encontrado\n  - ");	
	 system("pause");
	 system("cls");
	 return;     	
	}	
	if(p2->status.sigla == 'R') // se o carro que está tentando alugar já estáa reservado
	{
	 printf("\n\b > Esse carro não pode ser reservado!\n", p2->modelo);
     system("pause");
	 system("cls"); 		    
	 return;																									
	}
	 // mudanças na concessionária
	p->tabela[p->reserved].reservado.sigla = 'R';
	p->tabela[p->reserved].reservado.regcarro = numerocarro-1;
 	p->reserved++;//adiciona +1 no reservado
	grava(p, "rb+", pos);
   	printf("\ > Reservado com sucesso! \n\n");
  	 // mudanças no carro
	p2->status.sigla= 'R' ;
	strcpy (p2->status.reserva.CNPJ, p->CNPJ);
	grava(p,"rb+",pos);
  	grava2(p2, "rb+", pos2);
	system("pause");
	system("cls");     
}
 					
void terminar_reserva(loja *p, montadora *p2, int cont2, int cont,histvenda *p3, int *pcont3) // função para terminar reserva
{
	FILE *fptr=NULL;	
	int tempreserv,j, i, pos2 , pos;
	char liboucomp, tempcnpj[19], vago[5] = {"vago"};	
	printf(" > Qual carro deseja terminar a reserva?\n  - Número de registro: ");
	scanf("%i", &tempreserv);
	fflush(stdin);
	pos2 = busca_pos_car(p2, tempreserv-1); 
	if(p2->status.sigla == 'L') 
	 {
	  printf("\n > O carro de registro %i não está reservado!",p2->regcarro+1);
	  fclose(fptr);
      system("pause");
      system("cls"); 		    
	  return;
	 }
	printf(" > O carro de registro %d (%s) será comprado ou liberado da reserva:\n  - [C]: Comprado\n  - [L]: Liberado\n > Opção escolhida: ", p2->regcarro+1, p2->modelo);
	scanf("%c",&liboucomp);
	fflush(stdin);
	if(liboucomp == 'c')
	 liboucomp = 'C';
	else if(liboucomp == 'l')
	 liboucomp = 'L';	
	
	if (liboucomp == 'C') // compra
	{
	 pos = busca_pos(p, p2->status.reserva.CNPJ);		
	 cadastro_venda(p3, pcont3, p, p2);		
	 p2->status.reserva.sigla='L';
	 p2->valor = 0;
	 strcpy (p2->modelo, vago);
	 strcpy (p2->cor, vago);
	 for ( j = 0; j < 3; j++)
	  {	
	   if( p2->regcarro == p->tabela[j].reservado.regcarro && p->tabela[j].sigla == 'R') // se a empresa alugou esse carro
		{
		 p->reserved--;
		 p->sold++;
         p->tabela[j].reservado.sigla = 'L';	            
		 i = cont;		      
		}  	  		
	  }
	 grava(p, "rb+", pos);
     grava2(p2,"rb+",pos2); 
	}
	else if (liboucomp=='L')//liberar carro 
	{		
	 p2->status.sigla='L';
     pos = busca_pos(p, p2->status.reserva.CNPJ);
	 for ( j = 0; j < 3; j++)
	  {	
	   if( p2->regcarro == p->tabela[j].reservado.regcarro && p->tabela[j].sigla == 'R') // se a empresa alugou esse carro
		{ 	
		 p->reserved--; 
         p->tabela[j].reservado.sigla = 'L';
		 i = cont;		      
		}
      }
     grava(p, "rb+", pos);
     grava2(p2,"rb+",pos2);
    }
	system("pause");
	system("cls");      
}		

int busca_pos(loja *p, char passa[19])
{
	FILE *fptr=NULL;
	int i,achou=-1,qtde;
	qtde=verifica();
	if((fptr=fopen("concessionaria.bin","rb"))==NULL)
  	printf("\nErro");
	else
  	 {
   	  for(i=0;i<qtde+1;i++)
   	   {
        fseek(fptr,i*sizeof(loja),0);  //caminho com fptr dentro do arquivo
        fread(p,sizeof(loja),1,fptr);
        if(strcmp(passa, p->CNPJ) == 0)
         {
          achou=i;   //posicao do registro
          i=qtde;
		  //garante a saida do for
 	     }
       }
   fclose(fptr);    //DENTRO do else - pois abriu com rb 
  }
 	return achou;
}

void grava(loja *p,char *str,int pos)
{
	FILE *fptr=NULL;
	if((fptr=fopen("concessionaria.bin",str))==NULL)
  	 printf("\nErro ao abrir o arquivo");
	else
  	 {
   	  if(strcmp(str,"rb+")==0)
	  fseek(fptr,pos*sizeof(loja),0);
      fwrite(p,sizeof(loja),1,fptr);
     }
	fclose(fptr);   //fora do else - por conta do ab ou rb+
}

void grava2(montadora *p2, char *str, int pos2)
{
	FILE *fptr=NULL;
	if((fptr=fopen("carro.bin",str))==NULL)
  	 printf("\nErro ao abrir o arquivo");
	else
  	 {
   	  if(strcmp(str,"rb+")==0)
      fseek(fptr,pos2*sizeof(montadora),0);
   	  fwrite(p2,sizeof(montadora),1,fptr);
     }
	fclose(fptr);   //fora do else - por conta do ab ou rb+
}

int busca_pos_car(montadora *p2, int regcarro)
{
	FILE *fptr=NULL;
	int i,achou=-1,qtde;
	qtde=verifica2();
	if((fptr=fopen("carro.bin","rb"))==NULL)
  	 printf("\nErro");
	else
  	 {
   	  for(i=0;i<qtde+1;i++)
       {
        fseek(fptr,i*sizeof(montadora),0);  //caminho com fptr dentro do arquivo
        fread(p2,sizeof(montadora),1,fptr);
        if(p2->regcarro == regcarro)
    	 {
          achou=i;
          i=qtde;
 		 }
       }
	  fclose(fptr);    //DENTRO do else - pois abriu com rb 
     }
 return achou;	
}

void aloca_venda(histvenda **p3, int tam3)
{
	 if((*p3=(histvenda*)realloc(*p3,tam3*sizeof(histvenda)))==NULL)
	 exit(1);
}

int verifica3()
{
	FILE *fptr=NULL;
	long int cont3 = 0;
	if((fptr=fopen("historico.bin","rb"))==NULL)
     return cont3;
	else
     {
      fseek(fptr,0,2);   //posiciona fptr no final do arquivo
      cont3=ftell(fptr)/sizeof(histvenda);
      fclose(fptr);     //dentro do else - por conta rb
      return cont3;
     }
}

void cadastro_venda(histvenda *p3, int *pcont3, loja *p, montadora *p2)
{
	printf("\n - Digite o dia que foi feita essa compra: ");
	scanf("%i",&(p3->dataVenda.dia));
	fflush(stdin);
	printf("\n - Digite o mês que foi feita essa compra: ");
	scanf("%i",&(p3->dataVenda.mes));
	fflush(stdin);
	printf("\n Digite o ano que foi feita essa compra: ");
	scanf("%i",&(p3->dataVenda.ano));
	fflush(stdin);
	p3->reghist=*pcont3;
	p3->regcarro=p2->regcarro;
	strcpy(p3->modelo,p2->modelo);
	strcpy(p3->cor,p2->cor);
	p3->valor=p2->valor;
	p3->regloja=p->regloja;
	strcpy(p3->nome,p->nome);
 	strcpy(p3->cnpj,p->CNPJ);
 	*pcont3=*pcont3+1;
 	grava_venda(p3);
}

void grava_venda(histvenda *p3)
{
 	FILE *fptr=NULL; // Declaração do ponteiro FILE
	if((fptr = fopen("historico.bin","ab"))==NULL)
	 printf("\nErro ao abrir arquivo");
	else
     fwrite(p3,sizeof(histvenda),1,fptr);
	fclose(fptr); 				
}

void consulta_venda(histvenda *p3, int cont3)
{
	int i;
	char option,passa[19],modelin[20];
	FILE *fptr=NULL;
	printf(" > Deseja consultar o histórico de vendas por CPNJ de empresa ou por Modelo de carro?\n  - [C/M]\n > Opção escolhida: ");
	scanf("%c",&option);
	fflush(stdin);
	if(option=='c')
	option='C';
	else if (option=='m')
	option='M';
    if (option=='C') // por CPNJ
 	 {
	  printf(" > Digite o CNPJ da empresa a ser buscada: ");
	  gets(passa);
	  fflush(stdin);
	  if((fptr=fopen("historico.bin","rb"))==NULL)
       printf("\nErro ao abrir o arquivo");
	  else
	   {
  	    for(i = 0; i < cont3; i++)
         {
   		  fseek(fptr,i*sizeof(histvenda), 0);
		  fread(p3,sizeof(histvenda),1,fptr);
		  if(strcmp(passa,p3->cnpj) == 0)
	       {
	        printf(" > Número da Venda: %i\n > Registro do Carro: %i\n > Modelo do Carro: %s\n > Cor do Carro: %s\n > Valor do Carro: %.2f\n > Registro da Empresa: %i\n > Nome da Empresa: %s\n > CPNJ: %s\n > Data da Venda: %i/%i/%i",p3->reghist+1,p3->regcarro+1,p3->modelo,p3->cor,p3->valor,p3->regloja+1,p3->nome,p3->cnpj,p3->dataVenda.dia,p3->dataVenda.mes,p3->dataVenda.ano);	
           }
         }
        fclose(fptr);//dentro do else - por conta rb
       }
 	 }
	else if (option=='M') // por Modelo
 	 {
	  printf(" > Deseja procurar qual modelo de carro? \n > Modelo desejado: ");
	  gets(modelin);
	  fflush(stdin);
	  if((fptr=fopen("historico.bin","rb"))==NULL)
  	   printf("\nErro ao abrir o arquivo");
      else
  	   {
	    for( i = 0; i < cont3; i++)
  		 {
  		  fseek(fptr,i*sizeof(histvenda), 0);
		  fread(p3,sizeof(histvenda),1,fptr);
		  if(strcmp(modelin,p3->modelo) == 0)
		   printf(" > Número da Venda: %i\n > Registro do Carro: %i\n > Modelo do Carro: %s\n > Cor do Carro: %s\n > Valor do Carro: %.2f\n > Registro da Empresa: %i\n > Nome da Empresa: %s\n > CPNJ: %s\n > Data da Venda: %i/%i/%i",p3->reghist+1,p3->regcarro+1,p3->modelo,p3->cor,p3->valor,p3->regloja+1,p3->nome,p3->cnpj,p3->dataVenda.dia,p3->dataVenda.mes,p3->dataVenda.ano);
	     }
       	fclose(fptr);		   			    	
	   }
 	 }
	system("pause");
	system("cls");      
}

void altera_loja(loja *p, int cont)
{
	int pos,j;	
	char passa[19],opt,newname[30];
	printf(" > Digite o CNPJ da empresa a ser buscada: ");
	gets(passa);
	fflush(stdin);
	pos = busca_pos(p, passa);
	if (pos==-1) // se não encontrar a empresa
	 {
	  printf(" > Não foi encontrada uma empresa com esse CPNJ");	
	  system("pause");
	  system("cls"); 	 	
	  return;	
	 }
	 printf("  - Nome: %s\n  - Vendidos: %d\n  - Reservados: %d\n", p->nome, p->sold, p->reserved);
			for (j=0;j<3;j++)
			{
			 if (p->tabela[j].reservado.sigla=='R')
			  printf("  - Tabela [%i]: %c - %d\n",j+1,p->tabela[j].reservado.sigla,p->tabela[j].reservado.regcarro+1);
			 else
			  printf("  - Tabela [%i]: %c\n",j+1,p->tabela[j].sigla);	
			}
	printf(" > Deseja alterar o Nome ou CPNJ da empresa cadastrada?\n  - [N/C]\n > Opção escolhida: ");
	scanf("%c",&opt);
	fflush(stdin);
	if (opt=='c')
	 opt='C';
	else if (opt=='n')
	 opt='N';
	if (opt=='N')
	{
	 printf(" > Para o que sera alterado o nome da empresa?\n   - Nome novo: ");
	 gets(newname);
	 fflush(stdin);
	 strcpy(p->nome,newname);
     grava(p, "rb+", pos);	 
	}
	else if (opt=='C')
	{
	 printf(" > Para o que sera alterado o CNPJ da empresa?\n   - CNPJ novo: ");
	 gets(passa);
	 fflush(stdin);
	 strcpy(p->CNPJ,passa);
     grava(p, "rb+", pos);	    
	}
	system("pause");
	system("cls"); 				
}

void altera_carro(montadora *p2, int cont2)
{
	int pos,iregcarro,pos2;
	char newmodelo[20],newcor[10],opt;
	float newprice;
	printf("\n > Insira o registro do Carro a ser alterado: ");
	scanf("%i",&iregcarro);
	fflush(stdin);
	pos2 = busca_pos_car(p2, iregcarro-1);
	if (pos2==-1)
	 {
	  printf(" > Não foi encontrada um carro com esse registro");	
	  system("pause");
	  system("cls"); 	 	
	  return;	 	
	 }
	if(p2->status.sigla == 'R')	
	 printf("  - Número de Registro: %d\n   > Modelo: %s \n   > Cor: %s \n   > Valor: %.2f \n   > Status: %c %s\n",p2->regcarro+1,p2->modelo, p2->cor, p2->valor,p2->status.reserva.sigla, p2->status.reserva.CNPJ);
	else
	 printf("  - Número de Registro: %d\n   > Modelo: %s \n   > Cor: %s \n   > Valor: %.2f \n   > Status: %c \n",p2->regcarro+1,p2->modelo, p2->cor, p2->valor,p2->status.sigla);
	printf(" > Deseja alterar o Modelo, Cor ou Valor do Carro?\n  - [M/C/V]\n - Opção escolhida: ");
    scanf("%c",&opt);
	fflush(stdin);    
    if (opt=='m')
     opt='M';
    else if (opt=='c')
	 opt='C';
	else if (opt=='v')
	 opt='V';
	if (opt=='M')
	{
	 printf("\n > Qual será o novo modelo do carro?\n  - Novo modelo: ");
	 gets(newmodelo);
	 fflush(stdin);
	 strcpy(p2->modelo,newmodelo);
     grava2(p2,"rb+",pos2);	 
	}
	else if (opt=='C')
	{
	 printf("\n > Qual será a nova cor do carro?\n  - Nova cor: ");
	 gets(newcor);
	 fflush(stdin);
	 strcpy(p2->cor,newcor);
     grava2(p2,"rb+",pos2);	
	}
	else if(opt=='V')
	{
	 printf("\n > Qual será o novo valor do carro?\n  - Novo valor: ");
	 scanf("%f",&newprice);
	 fflush(stdin);
	 p2->valor=newprice;
     grava2(p2,"rb+",pos2);		
	}  
	system("pause");
	system("cls"); 		
}
