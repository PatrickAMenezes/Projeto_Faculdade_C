#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
void login(){
    char login[15] = "teste";
    char login1[15];
    char senha[15] = "12345";
    char senha1[15];
    int login_efetuado = 0;
    printf("--------------------------------------\n\n");
    while(login_efetuado == 0){
        printf("Digite o Login: ");
        scanf("%s", login1);
        printf("\nDigite a Senha: ");
        scanf("%s", senha1);
        if(strcmp(login, login1) == 0 && strcmp(senha, senha1) == 0){
            printf("\n________________LOGADO________________\n\n");
            login_efetuado = 1;
        }else{
            printf("\nDados Invalidos, insira novamente.\n\n");
        }
    }
}
struct dados_paciente{
    char nome[50], email[50], cpf[50], telefone[50];
}paciente;
struct endereco_paciente{
    char rua[50], bairro[50], cidade[50], estado[50], cep[50];
    int numero;
}endereco;
struct diagnostico{
    int dia, mes, ano, comorbidade_paciente, idade_paciente;
}diagnostico_paciente;
// Função da comorbidade.
void comorbidade(){
    int comorbidade_p, i = 0;
    printf("\nO paciente tem comorbidade?(Digite 1 para sim e 0 para nao): ");
    scanf("%d", &comorbidade_p);
    while(i == 0){
        if(comorbidade_p == 1){
            i = 1;
        }else if(comorbidade_p == 0){
            i = 1;
        }else{
            printf("\nPor favor, coloque 1 ou 0: ");
            scanf("%d", &comorbidade_p);
        }
    }
    diagnostico_paciente.comorbidade_paciente = comorbidade_p;
}
struct data{
    int dia, mes, ano;
};
// Função da idade.
void idade(){
    //Verifica a data atual.
    struct tm tempo;
    time_t tempo_seg;
    time(&tempo_seg);
    tempo = *localtime(&tempo_seg);
    struct data data_atual;
    data_atual.dia = tempo.tm_mday;
    data_atual.mes = tempo.tm_mon + 1;
    data_atual.ano = tempo.tm_year + 1900;
    // Verifica a data de nascimento do paciente.
    int dia_nascimento, mes_nascimento, ano_nascimento, i = 0, idade_p=0;;
    printf("\nInsira a data de nascimento do paciente.\n");
    while(i == 0){
        printf("\nDia: ");
        scanf("%d", &dia_nascimento);
        if(dia_nascimento >= 1 && dia_nascimento <= 31){
        i = 1;
        }
    }
    i = 0;
    while(i == 0){
        printf("\nMes: ");
        scanf("%d", &mes_nascimento);
        if(mes_nascimento >= 1 && mes_nascimento <= 12){
            i = 1;
        }
    }
    i = 0;
    while(i == 0){
        printf("\nAno: ");
        scanf("%d", &ano_nascimento);
        if(ano_nascimento <= data_atual.ano){
            i = 1;
        }
    // Verifica a idade do paciente.
    idade_p = data_atual.ano - ano_nascimento;
    // Verifica se a pessoa já fez aniversário no ano.
    if((data_atual.mes > mes_nascimento) ||
       (data_atual.mes == mes_nascimento && data_atual.dia >= dia_nascimento)){
        idade_p += 0;
    }else{
        idade_p -= 1;
    }
    }
    diagnostico_paciente.idade_paciente = idade_p;
}
FILE *arquivo_SecSaude;
// Função do grupo de risco.
void grupo_risco(){
    // Gerando o arquivo com os pacientes contaminados
    arquivo_SecSaude = fopen("Arquivo_SecSaude.txt", "a");
    fprintf(arquivo_SecSaude, "--------------------------------------------------\n");
    fprintf(arquivo_SecSaude, "\nNome: %s\n", paciente.nome);
    fprintf(arquivo_SecSaude, "Cep: %s\n", endereco.cep);
    fprintf(arquivo_SecSaude, "Idade: %d\n", diagnostico_paciente.idade_paciente);
    if(diagnostico_paciente.comorbidade_paciente == 1){
        fprintf(arquivo_SecSaude, "\nComorbidade: Sim\n\n");
    }else{
        fprintf(arquivo_SecSaude, "\nComorbidade: Não\n\n");
    }
    fclose(arquivo_SecSaude);
    printf("\nO arquivo foi criado com sucesso!");
}
FILE *pacientes_contaminados;
FILE *pacientes_saudaveis;
// Função do cadastro do paciente.
void cadastro_paciente(){
    // Armazenando os dados do paciente.
    printf("\nInsira os dados do paciente.\n");
    printf("\nNome: ");
    fflush (stdin);
    fgets(paciente.nome,50,stdin);
    printf("\nCpf: ");
    fflush(stdin);
    fgets(paciente.cpf, 50, stdin);
    printf("\nEmail do paciente: ");
    fflush(stdin);
    fgets(paciente.email, 50, stdin);
    printf("\nTelefone: ");
    fflush(stdin);
    fgets(paciente.telefone, 50, stdin);
    // Armazenando o endereço do paciente.
    printf("\nColoque o endereco do paciente.\n");
    printf("\nRua: ");
    fflush(stdin);
    fgets(endereco.rua, 50, stdin);
    printf("\nNumero: ");
    scanf("%d", &endereco.numero);
    printf("\nBairro: ");
    fflush(stdin);
    fgets(endereco.bairro, 50, stdin);
    printf("\nCidade: ");
    fflush(stdin);
    fgets(endereco.cidade, 50, stdin);
    printf("\nEstado: ");
    fgets(endereco.estado, 50, stdin);
    printf("\nCep: ");
    fflush(stdin);
    fgets(endereco.cep, 50, stdin);
    int diagnostico, i=0;
    /* Verificação para ver se o paciente foi diagnosticado
    com covid ou não.*/
    printf("\nQual o diagnostico do paciente?\n");
    printf("\n(Digite 1 para positivo e 0 para negativo): ");
    while(i == 0){
        scanf("%d", &diagnostico);
        if(diagnostico == 1){
            int j = 0;
            // Data do diagnostico.
            printf("\nInsira a data do diagnostico.");
            while(j == 0){
                printf("\nDia: ");
                scanf("%d", &diagnostico_paciente.dia);
                if(diagnostico_paciente.dia >= 1 && diagnostico_paciente.dia <= 31){
                    j = 1;
                }
            }j = 0;
            while(j == 0){
                printf("\nMes: ");
                scanf("%d", &diagnostico_paciente.mes);
                if(diagnostico_paciente.mes >= 1 && diagnostico_paciente.mes <= 12){
                    j = 1;
                }
            }j = 0;
            while(j == 0){
                printf("\nAno: ");
                scanf("%d", &diagnostico_paciente.ano);
                struct tm tempo;
                time_t tempo_seg;
                time(&tempo_seg);
                tempo = *localtime(&tempo_seg);
                struct data data_atual;
                data_atual.ano = tempo.tm_year + 1900;
                if(diagnostico_paciente.ano <= data_atual.ano){
                    j = 1;
                }
            }
            // Verificando a idade do paciente.
            idade();
            // Verificando se o paciente tem comorbidade ou não.
            comorbidade();
            // Gerando o arquivo com os pacientes contaminados.
            pacientes_contaminados = fopen("pacientes_contaminados.txt", "a");
            fprintf(pacientes_contaminados, "--------------------------------------------------\n");
            fprintf(pacientes_contaminados, "\nNome: %s\n", paciente.nome);
            fprintf(pacientes_contaminados, "Cpf: %s\n", paciente.cpf);
            fprintf(pacientes_contaminados, "Idade: %d\n", diagnostico_paciente.idade_paciente);
            fprintf(pacientes_contaminados, "\nEmail: %s\n", paciente.email);
            fprintf(pacientes_contaminados, "Telefone: %s\n", paciente.telefone);
            fprintf(pacientes_contaminados, "Rua: %s\n", endereco.rua);
            fprintf(pacientes_contaminados, "Número: %d\n", endereco.numero);
            fprintf(pacientes_contaminados, "\nBairro: %s\n", endereco.bairro);
            fprintf(pacientes_contaminados, "Cidade: %s\n", endereco.cidade);
            fprintf(pacientes_contaminados, "Estado: %s\n", endereco.estado);
            fprintf(pacientes_contaminados, "Cep: %s\n", endereco.cep);
            if(diagnostico_paciente.comorbidade_paciente == 1){
                fprintf(pacientes_contaminados, "Comorbidade: Sim\n");
            }else{
                fprintf(pacientes_contaminados, "Comorbidade: Não\n");
            }
            fprintf(pacientes_contaminados, "\nData do diagnóstico: %02d/%02d/%d\n\n",
                    diagnostico_paciente.dia, diagnostico_paciente.mes, diagnostico_paciente.ano);
            fclose(pacientes_contaminados);
            // Verificando se o paciente pertence ao grupo de risco.
            if(diagnostico_paciente.comorbidade_paciente == 1 ||
               diagnostico_paciente.idade_paciente >= 65){
                grupo_risco();
                i = 1;
            }else{
                i = 1;
            }
        }else if(diagnostico == 0){
            // Arquivo para avisar aos pacientes que não estão contaminados.
            pacientes_saudaveis = fopen("pacientes_saudaveis.txt", "a");
            fprintf(pacientes_saudaveis, "--------------------------------------------------\n");
            fprintf(pacientes_saudaveis, "\nNome: %s\n", paciente.nome);
            fprintf(pacientes_saudaveis, "Cpf: %s\n", paciente.cpf);
            fprintf(pacientes_saudaveis, "Telefone: %s\n", paciente.telefone);
            fprintf(pacientes_saudaveis, "Email: %s\n", paciente.email);
            fprintf(pacientes_saudaveis, "Rua: %s\n", endereco.rua);
            fprintf(pacientes_saudaveis, "Número: %d\n\n", endereco.numero);
            fprintf(pacientes_saudaveis, "Bairro: %s\n", endereco.bairro);
            fprintf(pacientes_saudaveis, "Cidade: %s\n", endereco.cidade);
            fprintf(pacientes_saudaveis, "Estado: %s\n", endereco.estado);
            fprintf(pacientes_saudaveis, "Cep: %s\n\n", endereco.cep);
            fclose(pacientes_saudaveis);
            i = 1;
        }else{
            printf("\nPor favor, insira 0 ou 1: ");
        }
    }
    printf("\n-------- Paciente cadastrado com sucesso --------\n");
}
int main(){
    login();
    // O usuário registra quantos pacientes quer cadastrar.
    int numero_pacientes=0, i=0;
    printf("Quantos pacientes voce quer cadastrar?\n");
    scanf("%d", &numero_pacientes);
    printf("\n-------- Nao utilize acentos nos campos de cadastro --------\n");
    for(i = 0; i < numero_pacientes; i++){
        cadastro_paciente();
    }
}
