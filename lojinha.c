#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct
{
    char Nproduto[10];
    float price;
}produtos;

char useradmin[10]= "admin";
int senhadmin=123;


typedef struct{
    char usuario[50];
    char email[80];
    int senha;
}cadastro;



void vendastotais(){
    char x[25];
    FILE *file=fopen("vendas.txt", "r");
    printf("\nAqui estão as vendas realizadas até agora:\n");
    while(fgets(x, 25, file)!=NULL){
        printf("R$ %s\n", x);
    }
}

int tamanho() {
    FILE* file = fopen("CADuser.b", "rb");
    cadastro cad;
    int cont = 0;
    while(fread(&cad, sizeof(cadastro), 1, file)){
        cont++;
    }
    fclose(file);
    return cont;
}

void menu1(){
    printf("Selcione uma das opções abaixo: \n");
    printf("1 - Cadastrar usuario\n");
    printf("2 - Login\n");
    printf("3 - Menu admin\n");
    printf("0 - Sair\n");
}


void menucompra(){
    float x[5]={4000, 102.95, 150, 80, 15};
    printf("\nSelecione o que deseja comprar:\n");
    printf("1 - iPhone R$4000\n");
    printf("2 - Fones de ouvido R$102.95\n");
    printf("3 - Carregador R$150\n");
    printf("4 - Cabo USB R$80\n");
    printf("5 - Capa de proteção 15\n");

    int fim;
    int n;
    float quant, k, soma=0;
    while(fim!=0){
        printf("Digite o numero do produto: ");
        scanf("%i", &n);
        printf("Digite a quantidade: ");
        scanf("%f", &quant);
        k=x[n-1]*quant;
        soma=soma+k;
        printf("Digite 0 para sair ou qualquer outro numero para continuar: ");
        scanf("%i", &fim);
    }
    printf("Total a pagar: R$%.2f\n", soma);
    printf("Volte sempre :)\n");
    FILE *file=fopen("vendas.txt", "a");
    fprintf(file, "%.2f\n", soma);
    fclose(file);
}


int loginAdmin(){
    char name[20];
    int num;
    int control;
    printf("Informe o nome de usuario:");
    scanf("%s", name);
    printf("Digite a senha: ");
    scanf("%i", &num);
    if(strcmp(name, useradmin)==0){
        control=1;
        if(num==senhadmin){
        control++;
    }
    }
    return control;    
}


void menuadmin(){
    printf("\nSelecione a opção que deseja: \n");
    printf("1 - Listar usuarios\n");
    printf("2 - Excluir usuario\n");
    printf("3 - Quantidade de usuarios\n");
    printf("4 - Vendas totais\n");
    printf("0 - Sair\n");
}

void lista(){
    FILE *file=fopen("CADuser.b", "rb");
    cadastro cad;
    while(fread(&cad, sizeof(cadastro), 1, file)){
        printf("\nusuario: %s, e-mail:%s e senha: %i\n", cad.usuario, cad.email, cad.senha);
    }
    fclose(file);
}

void excluir(char nome[20]){
    int n = tamanho();
    cadastro v[n];
    FILE *file = fopen("CADuser.b", "rb");
    int i = 0;
    while (fread(&v[i], sizeof(cadastro), 1, file)) {
        i++;
    }
    fclose(file);
    file = fopen("CADuser.b", "wb");
    for(i=0; i<n; i++){
        if(strcmp(v[i].usuario, nome)!=0){
            fwrite(&v[i], sizeof(cadastro), 1, file);
        }
    }
    fclose(file);
}


void cad(){
    int n = tamanho();
    cadastro v[n];
    FILE *file = fopen("CADuser.b", "rb");
    int i = 0;
    while (fread(&v[i], sizeof(cadastro), 1, file)) {
        i++;
    }
    fclose(file);
    file=fopen("CADuser.b", "ab");
    cadastro cad;
    int controle;

    do{
    controle=2;
    printf("informe o nome de usuario, e-mail e a senha: ");
    scanf("%s %s %d", cad.usuario, cad.email, &cad.senha);
    fflush(stdin);
    if(strchr(cad.email, '@')==NULL){
            printf("E-mail invalido\n");
               
            }else{
                controle--;
            }
    for(int i=0; i<n; i++){
        if(strcmp(cad.usuario, v[i].usuario)==0){
            printf("Usuario já existe\n");
            
        }else{
            controle--;
        }
        
         }}while(controle==2);
    
    fwrite(&cad, sizeof(cadastro), 1, file);
    fclose(file);
}


int login(){
     int n = tamanho();
    cadastro v[n];
    FILE *file = fopen("CADuser.b", "rb");
    int i = 0;
    while (fread(&v[i], sizeof(cadastro), 1, file)) {
        i++;
    }
    fclose(file);
    file=fopen("CADuser,b", "rb");
    int entrou=0;
    char nome[20];
    int senha;
    printf("Informe o nome de usuario: ");
    scanf("%s", nome);
    printf("Informe a sua senha: ");
    scanf("%i", &senha);
    for(int i=0; i<n; i++){
        if(strcmp(v[i].usuario, nome)==0){
            entrou=1;
            if(v[i].senha==senha){
            entrou++;
        }
        } 
    }
    fclose(file);
    return entrou;
}




int main (){
    
    printf("******Boas vindas a Lojinha******\n");
    int op;
   
    do{
        menu1();
        scanf("%i", &op);
        if(op==1){
           cad();
        } 
        else if(op == 2){
            int n;
            n=login();
            if(n==2){
                menucompra();
            }else{
                printf("\nNome de usuario ou senha incorretos.\n");
            }
        } 
        else if(op==3){
            int j=0;
            j=loginAdmin();
            if(j==2){
                int l;
                do{
                menuadmin();
                scanf("%i", &l);
                if(l==1){
                    lista();
                }
                if(l==2){
                    char name[20];
                    printf("\nInforme o nome de usuario para exclusão: ");
                    scanf("%s", name);
                    excluir(name);
                }
                if(l==3){
                    int b;
                    b=tamanho();
                    printf("\nAtualmente existem %i usuarios cadastrados.\n", b);
                }
                if(l==4){
                    vendastotais();
                }
            }while(l!=0);}
            else{
                printf("Nome de usuario ou senha incorretos.\n");
            }
        } 
    
    }while(op!=0);

    return 0;
}