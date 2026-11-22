#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ESTRUTURA DA HOSPEDAGEM
typedef struct {
    int codigo;
    char nome[100];
    char cpf[20];
    char telefone[20];
    int quarto;
    char entrada[20];
    char saida[20];
    float valorDiaria;
    int status; // 1 = ativa | 0 = desativada
} Hospedagem;

// PROTOTIPOS DAS FUNCOES
int exibirMenu();
void cadastrarHospedagem();
void consultarHospedagem();
void listarHospedagens();
void excluirHospedagem();
void exportarTXT();
void contarRegistros();
int codigoExiste(int codigo);
void limparBuffer();
void lerTexto(char texto[], int tamanho);

// FUNCAO PARA LIMPAR O BUFFER
void limparBuffer() {
    int c;

    while ((c = getchar()) != '\n' && c != EOF);
}

// FUNCAO PARA LER TEXTOS
void lerTexto(char texto[], int tamanho) {
    fgets(texto, tamanho, stdin);
    if (strchr(texto, '\n') == NULL) {
        limparBuffer();
    }
    texto[strcspn(texto, "\n")] = '\0';
}

// VERIFICAR SE O CODIGO JA EXISTE
int codigoExiste(int codigo) {
    FILE *arquivo;
    Hospedagem h;

    arquivo = fopen("hospedagens.dat", "rb");

    if (arquivo == NULL) {
        return 0;
    }

    while (fread(&h, sizeof(Hospedagem), 1, arquivo) == 1) {
        if (h.codigo == codigo) {
            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    return 0;
}

// MENU PRINCIPAL
int exibirMenu() {
    int opcao;

    printf("\n==============================\n");
    printf("        HOTEL MANAGER         \n");
    printf("==============================\n");
    printf("1. Cadastrar hospedagem\n");
    printf("2. Consultar por codigo\n");
    printf("3. Listar hospedagens\n");
    printf("4. Excluir hospedagem\n");
    printf("5. Exportar para TXT\n");
    printf("6. Contar registros\n");
    printf("0. Sair\n");
    printf("------------------------------\n");
    printf("Escolha uma opcao: ");

    scanf("%d", &opcao);
    limparBuffer();

    return opcao;
}

// 1 - CADASTRAR HOSPEDAGEM
void cadastrarHospedagem() {
    FILE *arquivo;
    Hospedagem h;

    printf("\n===== CADASTRAR HOSPEDAGEM =====\n");

    printf("Codigo: ");
    scanf("%d", &h.codigo);
    limparBuffer();

    if (codigoExiste(h.codigo)) {
        printf("\nEste codigo ja esta cadastrado!\n");
        return;
    }

    printf("Nome do hospede: ");
    lerTexto(h.nome, 100);

    printf("CPF: ");
    lerTexto(h.cpf, 20);

    printf("Telefone: ");
    lerTexto(h.telefone, 20);

    printf("Numero do quarto: ");
    scanf("%d", &h.quarto);
    limparBuffer();

    printf("Data de entrada (DD/MM/AAAA): ");
    lerTexto(h.entrada, 20);

    printf("Data de saida (DD/MM/AAAA): ");
    lerTexto(h.saida, 20);

    printf("Valor da diaria: R$ ");
    scanf("%f", &h.valorDiaria);
    limparBuffer();

    h.status = 1;

    arquivo = fopen("hospedagens.dat", "ab");

    if (arquivo == NULL) {
        printf("\nErro ao abrir o arquivo!\n");
        return;
    }

    fwrite(&h, sizeof(Hospedagem), 1, arquivo);

    fclose(arquivo);

    printf("\nHospedagem cadastrada com sucesso!\n");
}

// 2 - CONSULTAR HOSPEDAGEM
void consultarHospedagem() {
    FILE *arquivo;
    Hospedagem h;
    int codigo;
    int encontrado = 0;

    printf("\n===== CONSULTAR HOSPEDAGEM =====\n");

    printf("Digite o codigo da hospedagem: ");
    scanf("%d", &codigo);
    limparBuffer();

    arquivo = fopen("hospedagens.dat", "rb");

    if (arquivo == NULL) {
        printf("\nNenhuma hospedagem cadastrada!\n");
        return;
    }

    while (fread(&h, sizeof(Hospedagem), 1, arquivo) == 1) {

        if (h.codigo == codigo && h.status == 1) {

            printf("\n===== DADOS DA HOSPEDAGEM =====\n");
            printf("Codigo: %d\n", h.codigo);
            printf("Nome: %s\n", h.nome);
            printf("CPF: %s\n", h.cpf);
            printf("Telefone: %s\n", h.telefone);
            printf("Quarto: %d\n", h.quarto);
            printf("Entrada: %s\n", h.entrada);
            printf("Saida: %s\n", h.saida);
            printf("Valor da diaria: R$ %.2f\n", h.valorDiaria);

            encontrado = 1;
            break;
        }
    }

    if (encontrado == 0) {
        printf("\nHospedagem nao encontrada!\n");
    }

    fclose(arquivo);
}

// 3 - LISTAR HOSPEDAGENS
void listarHospedagens() {
    FILE *arquivo;
    Hospedagem h;
    int quantidade = 0;

    printf("\n===== LISTA DE HOSPEDAGENS =====\n");

    arquivo = fopen("hospedagens.dat", "rb");

    if (arquivo == NULL) {
        printf("\nNenhuma hospedagem cadastrada!\n");
        return;
    }

    while (fread(&h, sizeof(Hospedagem), 1, arquivo) == 1) {

        if (h.status == 1) {

            printf("\n------------------------------\n");
            printf("Codigo: %d\n", h.codigo);
            printf("Nome: %s\n", h.nome);
            printf("CPF: %s\n", h.cpf);
            printf("Telefone: %s\n", h.telefone);
            printf("Quarto: %d\n", h.quarto);
            printf("Entrada: %s\n", h.entrada);
            printf("Saida: %s\n", h.saida);
            printf("Valor da diaria: R$ %.2f\n", h.valorDiaria);

            quantidade++;
        }
    }

    if (quantidade == 0) {
        printf("\nNenhuma hospedagem ativa encontrada!\n");
    }

    printf("\nTotal de hospedagens ativas: %d\n", quantidade);

    fclose(arquivo);
}

// 4 - EXCLUIR HOSPEDAGEM
void excluirHospedagem() {
    FILE *arquivo;
    Hospedagem h;
    int codigo;
    int encontrado = 0;

    printf("\n===== EXCLUIR HOSPEDAGEM =====\n");

    printf("Digite o codigo: ");
    scanf("%d", &codigo);
    limparBuffer();

    arquivo = fopen("hospedagens.dat", "rb+");

    if (arquivo == NULL) {
        printf("\nNenhuma hospedagem cadastrada!\n");
        return;
    }

    while (fread(&h, sizeof(Hospedagem), 1, arquivo) == 1) {

        if (h.codigo == codigo && h.status == 1) {

            h.status = 0;

            fseek(arquivo, -(long)sizeof(Hospedagem), SEEK_CUR);
            fwrite(&h, sizeof(Hospedagem), 1, arquivo);

            encontrado = 1;
            break;
        }
    }

    fclose(arquivo);

    if (encontrado == 1) {
        printf("\nHospedagem excluida com sucesso!\n");
    } else {
        printf("\nHospedagem nao encontrada!\n");
    }
}

// 5 - EXPORTAR PARA TXT
void exportarTXT() {
    FILE *arquivo;
    FILE *txt;
    Hospedagem h;
    int quantidade = 0;

    arquivo = fopen("hospedagens.dat", "rb");

    if (arquivo == NULL) {
        printf("\nNenhuma hospedagem cadastrada!\n");
        return;
    }

    txt = fopen("hospedagens.txt", "w");

    if (txt == NULL) {
        printf("\nErro ao criar arquivo TXT!\n");
        fclose(arquivo);
        return;
    }

    fprintf(txt, "===== HOTEL MANAGER =====\n");

    while (fread(&h, sizeof(Hospedagem), 1, arquivo) == 1) {

        if (h.status == 1) {

            fprintf(txt, "\n------------------------------\n");
            fprintf(txt, "Codigo: %d\n", h.codigo);
            fprintf(txt, "Nome: %s\n", h.nome);
            fprintf(txt, "CPF: %s\n", h.cpf);
            fprintf(txt, "Telefone: %s\n", h.telefone);
            fprintf(txt, "Quarto: %d\n", h.quarto);
            fprintf(txt, "Entrada: %s\n", h.entrada);
            fprintf(txt, "Saida: %s\n", h.saida);
            fprintf(txt, "Valor da diaria: R$ %.2f\n", h.valorDiaria);

            quantidade++;
        }
    }

    fprintf(txt, "\nTotal de hospedagens: %d\n", quantidade);

    fclose(arquivo);
    fclose(txt);

    printf("\nDados exportados com sucesso para hospedagens.txt!\n");
}

// 6 - CONTAR REGISTROS
void contarRegistros() {
    FILE *arquivo;
    Hospedagem h;
    int total = 0;
    int ativos = 0;

    arquivo = fopen("hospedagens.dat", "rb");

    if (arquivo == NULL) {
        printf("\nNenhuma hospedagem cadastrada!\n");
        return;
    }

    while (fread(&h, sizeof(Hospedagem), 1, arquivo) == 1) {

        total++;

        if (h.status == 1) {
            ativos++;
        }
    }

    fclose(arquivo);

    printf("\n===== CONTAGEM DE REGISTROS =====\n");
    printf("Total de registros cadastrados: %d\n", total);
    printf("Hospedagens ativas: %d\n", ativos);
    printf("Hospedagens excluidas: %d\n", total - ativos);
}

// PROGRAMA PRINCIPAL
int main() {
    int opcao;

    do {
        opcao = exibirMenu();

        switch (opcao) {

            case 1:
                cadastrarHospedagem();
                break;

            case 2:
                consultarHospedagem();
                break;

            case 3:
                listarHospedagens();
                break;

            case 4:
                excluirHospedagem();
                break;

            case 5:
                exportarTXT();
                break;

            case 6:
                contarRegistros();
                break;

            case 0:
                printf("\nEncerrando o Hotel Manager...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}