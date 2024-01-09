#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
//#include <speechapi_cxx.h>

using namespace std;
/*
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;

auto autenticacao = SpeechConfig::FromSubscription("<033cd38c62464261b4f5c3e307de37f0>","<brazilsouth>"); // DECLARAÇÃO DA AUTENTICAÇÃO DO RECURSO
auto audio_config = AudioConfig::FromDefaultMicrophoneInput(); // DECLARAÇÃO DA ENTRADA DO MICROFONE
auto requisicao_textofala = SpeechSynthesizer::FromConfig(autenticacao); //  DEFINIÇÃO DO OBJETO REQUISICAO_TEXTOFALA
auto requisicao_falatexto = SpeechRecognizer::FromConfig(autenticacao,audio_config); //  REDEFINIÇÃO DO OBJETO REQUISICAO_FALATEXTO COM AS NOVAS CONFIGURAÇÕES
*/

class TipodeEquipamento { //Classe Tipo de Equipamento
public:
    int idtipoequip; // Vai ser o id e qual o tipo de equipamento
    char qualtipo[50];
    
    int TipoEquipamento() { // Método construtor do tipo de equipamento
        idtipoequip = 0;
        strcpy(qualtipo, "\0");
    }

    void MostrarTipoEquipamento() { // Método para mostrar o tipo de equipamento
        cout << idtipoequip << "\t";
        cout << qualtipo << "\n";
    }
};

class Departamento { // Classe Departamento
public:
    int iddep;          // Vai ser o id do departamento
    char nome[50];      // Nome departamento
    char descricao[50]; // Descreve o apartamento
    char local[50];     // Local departamento

    Departamento() { // Método construtor do departamento
        iddep = 0;
        strcpy(nome, "\0");
        strcpy(descricao, "\0");
        strcpy(local, "\0");
    }

    void MostrarDepartamento() { // Método para mostrar o departamento
        cout << iddep << "\t";
        cout << nome << "\t";
        cout << descricao << "\t";
        cout << local << "\n";
    }
};

class Equipamentos { // Classe de Equipamentos
public:
    int idequip;   // ID  equipamento
    char nome[50]; // Nome Equipamento
    float valor;   // Valor Equipamento
    TipodeEquipamento* tipo = new TipodeEquipamento(); // Instancia o tipo de equipamento e departamento com a classe Equipamento
    Departamento* depart = new Departamento();

    void setTipo(TipodeEquipamento tipo) { // Método construtor utilizando set
        
        this->tipo->idtipoequip = tipo.idtipoequip;

        if (strlen(this->tipo->qualtipo) >= strlen(tipo.qualtipo)) {
            strcpy(this->tipo->qualtipo, tipo.qualtipo);
        }
        else {
            strncpy(this->tipo->qualtipo, tipo.qualtipo, strlen(tipo.qualtipo)+1);
        }
    }

    void setDepart(Departamento depart) { // Método construtor utilizando set

        this->depart->iddep = depart.iddep;

        if (strlen(this->depart->nome) >= strlen(depart.nome)) {
            strcpy(this->depart->nome, depart.nome);
        }
        else {
            strncpy(this->depart->nome, depart.nome, strlen(depart.nome)+1);
        }

        if (strlen(this->depart->descricao) >= strlen(depart.descricao)) {
            strcpy(this->depart->descricao, depart.descricao);
        }
        else {
            strncpy(this->depart->descricao, depart.descricao, strlen(depart.descricao)+1);
        }

        if (strlen(this->depart->local) >= strlen(depart.local)) {
            strcpy(this->depart->local, depart.local);
        }
        else {
            strncpy(this->depart->local, depart.local, strlen(depart.local)+1);
        }
    }

    void MostrarEquipamento() { // Método para mostrar o equipamento
        cout << idequip << "\t";
        cout << nome << "\t";
        cout << valor << "\t";
        cout << depart->nome << "\t\t";
        cout << tipo->qualtipo << "\n";
    }
};
 
void FazerBackup(Equipamentos equip[], int numEquip) { // procedimento para salvamento em arquivo
    FILE* arquivo;
    char titulo[50];
    cout << "Insira o nome do arquivo: ";
    cin >> titulo;
    fflush(stdin);

    strcat(titulo, ".bin");

    arquivo = fopen(titulo, "wb");

    try {
        if (!arquivo) {
            throw 0;
        }
        else { // Escreve e salva em arquivo
            fwrite(&numEquip, sizeof(int), 1, arquivo);
            fwrite(equip, sizeof(Equipamentos), numEquip + 1, arquivo);
            cout << "\n\nArquivo foi salvo!";  // arquivo salvo
        }

    }
    catch (int falhou) {
        if (falhou == 0) {
            cout << "\n\nErro ao salvar o arquivo!"; // Caso o arquivo não tenha sido aberto
        }
    }
    fclose(arquivo);
    getchar();
    system("cls");
}

void ListarArquivo() { // Mostra os equipamentos dentro de um arquivo
    FILE* arquivo; 

    Equipamentos equip[50];

    char titulo[50];
    int limite;

    cout << "Qual o nome do arquivo: ";
    cin >> titulo;
    fflush(stdin);
    strcat(titulo, ".bin");
    arquivo = fopen(titulo, "rb");
    try {
        if (!arquivo) {
            throw 0; // exceção
        }
        else {   // Mostra os equipamentos do arquivo
            fread(&limite, sizeof(int), 1, arquivo);
            fread(equip, sizeof(Equipamentos), limite, arquivo);
            for (int i = 0; i <= limite; i++) {
                equip[i].MostrarEquipamento();
            }
        }
    }
    catch (int falhou) {
        if (falhou == 0) {
            cout << "\n\nArquivo nao encontrado!"; // Caso não tenha encontrado o arquivo
        }
    }
    fclose(arquivo);
    getchar();
    system("cls");
}
/*
// FUNÇÃO QUE REALIZA A TRANSFORMAÇÃO DO TEXTO EM FALA, ATRAVÉS DA API
void texto_em_fala(std::shared_ptr<Microsoft::CognitiveServices::Speech::SpeechSynthesizer>requisicao_textofala, string Texto)
{
    cout << Texto + "\n";
    requisicao_textofala->SpeakTextAsync(Texto).get(); // REQUISIÇÃO DA SINTETIZAÇÃO DE TEXTO EM FALA
}

// FUNÇÃO QUE REQUISITA DA API O RECONHECIMENTO DE UMA FALA E A TRANSFORMAÇÃO DESSA FALA EM UM TEXTO
string fala_em_texto(std::shared_ptr<Microsoft::CognitiveServices::Speech::SpeechRecognizer>requisicao_falatexto)
{
    auto resultado = requisicao_falatexto->RecognizeOnceAsync().get(); // REQUISIÇÃO DO RECONHEIMENTO DE FALA EM TEXTO
    cout << resultado->Text + "\n";
    return resultado->Text; // CONVERSÃO DO RESULTADO DO RECONHECIMENTO EM TEXTO
}
*/
int main()
{
    setlocale(LC_ALL, "Portuguese");
/*
    autenticacao->SetSpeechRecognitionLanguage("pt-BR"); //  CONFIGURAÇÃO DA AUTENTICAÇÃO PARA O RECONHECIMENTO DE FALA EM PORTUGUÊS
    autenticacao->SetSpeechSynthesisLanguage("pt-BR"); //  CONFIGURAÇÃO DA AUTENTICAÇÃO PARA A SINTETIZAÇÃO DE FALA EM PORTUGUÊS
    autenticacao->SetSpeechSynthesisVoiceName("pt-BR-FranciscaNeural"); // CONFIGURAÇÃO DE UMA VOZ ESPECÍFICA: pt-BR-FranciscaNeural
    requisicao_textofala = SpeechSynthesizer::FromConfig(autenticacao); //  DEFINIÇÃO DO OBJETO REQUISICAO_TEXTOFALA
    requisicao_falatexto = SpeechRecognizer::FromConfig(autenticacao, audio_config); //  REDEFINIÇÃO DO OBJETO REQUISICAO_FALATEXTO COM AS NOVAS CONFIGURAÇÕES
*/
    TipodeEquipamento tipos[50];
    Departamento defdepartamento[50];
    Equipamentos equip[50];

    int opcao1, opcao2, i, j, inicio;
    int num, numTipo, numDepartamento, numEquip;
    char nome[50];
    bool naoExiste = true;;
    
    numTipo = -1;
    numDepartamento = -1;
    numEquip = -1;

    //Testes de variáveis por fala
    string opcao1F, opcao2F, iF, jF, inicioF;
    string numF, numTipoF, numDepartamentoF, numEquipF;

    do {
        goInicio: // funcao goto para retornar ao menu inicial
        // Menu Inicial
        cout << "Escolha a opcao desejada:\n\n";
        cout << "1.Usar por escrita\n";
        cout << "2.Usar por fala\n";
        cout << "0.Sair\n\n";
        cout << "Sua opcao: ";
        cin >> inicio;
        fflush(stdin);
        system("cls");

        switch (inicio) {

            // USAR POR ESCRITA
        case 1:

            do {
                goOpcao1: // funcao goto para retornar ao submenu
                // Submenu
                cout << "Escolha a opcao desejada:\n\n"; 
                cout << "1.Equipamento\n";
                cout << "2.Tipo de equipamento\n";
                cout << "3.Depatamento\n";
                cout << "0.Voltar\n\n";
                cout << "Sua opcao: ";
                cin >> opcao1;
                fflush(stdin);
                system("cls");
                
                switch (opcao1) {
                case 1: // CRUD Equipamento
                    do {
                        cout << "Escolha a opcao desejada:\n\n";
                        cout << "1.Inserir\n";
                        cout << "2.Excluir\n";
                        cout << "3.Alterar\n";
                        cout << "4.Listar\n";
                        cout << "5.Salvar\n";
                        cout << "6.Listar dados de um equipamento\n";
                        cout << "0.Voltar\n\n";
                        cout << "Sua opcao: ";
                        cin >> opcao2;
                        fflush(stdin);
                        system("cls");
                    
                        switch (opcao2) {
                        case 1: // Cadatrastro de Equipamento
                            try {
                                if (numTipo == -1 || numDepartamento == -1) { // Trava para ver se existe o departamento e o tipo de equipamento

                                    throw true;
                                }
                                else {
                                    if (numEquip < 50) { // Efetua o cadastro
                                        numEquip++;
                                        cout << "Digite o codigo: ";
                                        cin >> equip[numEquip].idequip;
                                        fflush(stdin);
                                        cout << "\nDigite o nome: ";
                                        scanf("%[^\n]", equip[numEquip].nome);
                                        fflush(stdin);
                                        cout << "\nDigite o valor do equipamento: ";
                                        cin >> equip[numEquip].valor;
                                        fflush(stdin);
                                        cout << "\nDigite o codigo do tipo do equipamento: ";
                                        cin >> num;
                                        for (i = 0; i <= numTipo; i++) {
                                            if (num == tipos[i].idtipoequip) {
                                                equip[numEquip].setTipo(tipos[i]);
                                                break;
                                            }
                                        }
                                        cout << "\nDigite o codigo do departamento: ";
                                        cin >> num;
                                        fflush(stdin);
                                        for (i = 0; i <= numDepartamento; i++) {
                                            if (num == defdepartamento[i].iddep) {
                                                equip[numEquip].setDepart(defdepartamento[i]);
                                                break;
                                            }
                                        }
                                    }
                                    else {
                                        cout << "Nao possui mais espaço para cadastro!"; // Mostra para o usuario que não possui mais espaço
                                        getchar();
                                    }
                                    system("cls");
                                }
                            }
                            catch (bool naoExiste) { //Caso não haja tipo de equipamento e departamento cadastrado antes de cadastrar equipamento
                                if (naoExiste) {
                                    if (numDepartamento == -1 && numTipo == -1) {
                                        cout << "Nao foi cadastrado nenhum tipo de equipamento e nenhum departamento!";
                                    }
                                    else if (numTipo == -1) {
                                        cout << "Nao foi cadastrado nenhum tipo de equipamento!"; 
                                    }
                                    else {
                                        cout << "Nao foi cadastrado nenhum departamento!"; 
                                    }
                                
                                }
                                getchar();
                                system("cls");
                            }
                            break;

                        case 2: // Exclusão de equipamento
                            if (numEquip == -1) {
                                cout << "Nenhum equipamento cadastrado!"; // Trava para caso não exista o departamento
                            }
                            else {
                                cout << "Digite o codigo do equipamento: "; 
                                cin >> num;
                                fflush(stdin);
                                for (i = 0; i <= numTipo; i++) { // Faz a busca do equipamento para exclusão
                                    if (num == tipos[i].idtipoequip) {
                                        naoExiste = false;
                                        for (j = i; j < numTipo; j++) {
                                            equip[j].idequip = equip[j + 1].idequip;
                                            if (strlen(equip[j].nome) >= strlen(equip[j + 1].nome)) {
                                                strcpy(equip[j].nome, equip[j + 1].nome);
                                            }
                                            else {
                                                strncpy(equip[j].nome, equip[j + 1].nome, strlen(equip[j + 1].nome));
                                            }
                                            equip[j].valor = equip[j + 1].valor;
                                            equip[j].setTipo(*equip[j + 1].tipo);
                                            equip[j].setDepart(*equip[j + 1].depart);
                                        }
                                        cout << endl << "\n\nEquipamento excluido!";
                                        numEquip--;
                                        naoExiste = false;
                                    }
                                }
                                if (naoExiste) {
                                    cout << "\n\nEquipamento nao encontrado!";
                                }
                                naoExiste = true;
                            }
                            getchar();
                            system("cls");
                            break;

                        case 3: // Alteração de equipamento
                            if (numEquip == -1) {
                                cout << "Nenhum equipamento cadastrado!";
                            }
                            else {
                                cout << "Digite o codigo do equipamento: "; 
                                cin >> num;
                                fflush(stdin);
                                for (i = 0; i <= numEquip; i++) { // Faz a busca do equipamento para alteração
                                    if (num == equip[i].idequip) {
                                        cout << "\n\nEquipamento encontrado!"
                                                "\n\n\nInforme os novos dados para alteracao:";
                                        cout << "\n\nDigite o codigo: ";
                                        cin >> equip[i].idequip;
                                        fflush(stdin);
                                        cout << "\nDigite o nome: ";
                                        scanf("%[^\n]", equip[numEquip].nome);
                                        fflush(stdin);
                                        cout << "\nDigite o valor do equipamento: ";
                                        cin >> equip[numEquip].valor;
                                        fflush(stdin);
                                        cout << "\nDigite o codigo do tipo do equipamento: ";
                                        cin >> num;
                                        for (i = 0; i <= numTipo; i++) {
                                            if (num == tipos[i].idtipoequip) {
                                                equip[numEquip].setTipo(tipos[i]);
                                                break;
                                            }
                                        }
                                        cout << "\nDigite o codigo do departamento: ";
                                        cin >> num;
                                        fflush(stdin);
                                        for (i = 0; i <= numDepartamento; i++) {
                                            if (num == defdepartamento[i].iddep) {
                                                equip[numEquip].setDepart(defdepartamento[i]);
                                                break;
                                            }
                                        }
                                        cout << "\n\nEquipamento alterado!";
                                        naoExiste = false;
                                    }
                                }
                                if (naoExiste) {
                                    cout << "\n\nEquipamento nao encontrado!";
                                }
                                naoExiste = true;
                            }
                            getchar();
                            system("cls");
                            break;

                        case 4: // Listagem de equipamentos
                            if (numEquip == -1) {
                                cout << "Nenhum equipamento cadastrado!";
                            }
                            else {
                                cout << "Codigo / Nome / Valor / Departamento / Tipo de equipamento\n\n";
                                for (i = 0; i <= numEquip; i++) { // mostra os equipamentos
                                    equip[i].MostrarEquipamento();
                                }
                            }
                            getchar();
                            system("cls");
                            break;

                        case 5: // Salvamento em arquivo
                            FazerBackup(equip, numEquip);
                            break;

                        case 6: // Restaurar dados salvos em arquivo
                            ListarArquivo();
                            break;
                    
                        case 0:
                            goto goOpcao1;
                                        
                        default:
                            cout << "Opcao invalida.";
                            getchar();
                            system("cls");
                            break;
                        }
                    } while (opcao2 != 0);

                    break;

                case 2: // CRUD Tipo de Equipamento
                    do{
                        cout << "Escolha a opcao desejada:\n\n";
                        cout << "1.Inserir\n";
                        cout << "2.Excluir\n";
                        cout << "3.Alterar\n";
                        cout << "4.Listar\n";
                        cout << "0.Voltar\n\n";
                        cout << "Sua opcao: ";
                        cin >> opcao2;
                        fflush(stdin);
                        system("cls");                        
                    
                        switch (opcao2) {
                        case 1: // Cadastro do tipo de equipamento
                            if (numTipo < 50) { // Trava para quantidade de tipos ja cadastrados
                                numTipo++;
                                cout << "Digite o codigo: ";
                                cin >> tipos[numTipo].idtipoequip; //  tipo de equipamento
                                fflush(stdin);
                                cout << "\nDigite a descricao do equipamento: "; // Descrição
                                scanf("%[^\n]", tipos[numTipo].qualtipo);
                                fflush(stdin);
                            }
                            else {
                                cout << "Nao possui mais espaço para cadastro!"; // Mostra para o usuario que não possui mais espaço
                                getchar();
                            }
                            system("cls");
                            break;

                        case 2: // Exclusão do tipo de equipamento
                            if (numTipo == -1) {
                                cout << "Nenhum tipo de equipamento cadastrado!"; // Trava para caso não exista o tipo de equipamento
                            }
                            else {
                                cout << "Digite o codigo do tipo do equipamento: ";
                                cin >> num;
                                fflush(stdin);
                                for (i = 0; i <= numTipo; i++) {
                                    if (num == tipos[i].idtipoequip) {
                                        for (j = i; j < numTipo; j++) {
                                            tipos[j].idtipoequip = tipos[j + 1].idtipoequip;
                                            if (strlen(tipos[j].qualtipo) >=
                                                strlen(tipos[j + 1].qualtipo)) {
                                                strcpy(tipos[j].qualtipo, tipos[j + 1].qualtipo);
                                            }
                                            else {
                                                strncpy(tipos[j].qualtipo, tipos[j + 1].qualtipo, strlen(tipos[j + 1].qualtipo));
                                            }
                                        }
                                        cout << "\n\nTipo de equipamento excluido"; // Caso tenha dado certo
                                        numTipo--;
                                        naoExiste = false;
                                    }
                                }
                                if (naoExiste) {
                                    cout << "\n\nTipo de equipamento nao encontrado!";
                                }
                                naoExiste = true;
                            }
                            getchar();
                            system("cls");
                            break;
                    
                        case 3: // Alteração do tipo de equipamento
                            if (numTipo == -1) {
                                cout << "Nenhum tipo de equipamento cadastrado!";
                            }
                            else {
                                cout << "Digite o codigo: ";
                                cin >> num;
                                fflush(stdin);
                                for (i = 0; i <= numTipo; i++) { // Faz a busca do tipo de equipamento para alteração
                                    if (num == tipos[i].idtipoequip) {
                                        cout << "\n\nTipo de equipamento encontrado!"
                                                "\n\n\nInforme os novos dados para alteracao:";
                                        cout << "\n\nDigite o codigo: ";
                                        cin >> tipos[i].idtipoequip;
                                        fflush(stdin);
                                        cout << "\nDigite a descricao: ";
                                        scanf("%[^\n]", tipos[i].qualtipo);
                                        fflush(stdin);
                                        cout << "\n\nTipo de equipamento alterado!";
                                        naoExiste = false;
                                    }
                                }
                                if (naoExiste) {
                                    cout << "\n\nTipo de equipamento nao encontrado!";
                                }
                                naoExiste = true;
                            }
                            getchar();
                            system("cls");
                            break;
                    
                        case 4: // Listagem dos tipos de equipamentos
                            if (numTipo == -1) {
                                cout << "Nenhum tipo de equipamento cadastrado!";
                            }
                            else {
                                cout << "Codigo /  Descricao           \n\n";
                                for (i = 0; i <= numTipo; i++) { // Mostra todos equipamentos existentes
                                    tipos[i].MostrarTipoEquipamento();
                                }
                            }
                            getchar();
                            system("cls");
                            break;
                    
                        case 0:
                            goto goOpcao1;
                                        
                        default:
                            cout << "Opcao invalida.";
                            getchar();
                            system("cls");
                            break;
                        }
                
                    } while (opcao2 != 0);

                    break;

                case 3: // CRUD Departamento
                    do {
                        cout << "Escolha a opcao desejada:\n\n";
                        cout << "1.Inserir\n";
                        cout << "2.Excluir\n";
                        cout << "3.Alterar\n";
                        cout << "4.Listar\n";
                        cout << "0.Voltar\n\n";
                        cout << "Sua opcao: ";
                        cin >> opcao2;
                        fflush(stdin);
                        system("cls");
                    
                        switch (opcao2) {
                        case 1: // Cadastro de departamento
                            if (numDepartamento <= 9) {
                                numDepartamento++;
                                cout << "Digite o codigo: ";
                                cin >> defdepartamento[numDepartamento].iddep;
                                fflush(stdin);
                                cout << "\nDigite o nome: ";
                                cin >> defdepartamento[numDepartamento].nome;
                                fflush(stdin);
                                cout << "\nDigite a descricao: ";
                                scanf("%[^\n]", defdepartamento[numDepartamento].descricao);
                                fflush(stdin);
                                cout << "\nDigite a localizacao: ";
                                scanf("%[^\n]", defdepartamento[numDepartamento].local);
                                fflush(stdin);
                            }
                            else {
                                cout << "Nao possui mais espaço para cadastro!"; // Mostra para o usuario que não possui mais espaço
                                getchar();
                            }
                            system("cls");
                            break;
                        
                        case 2: // Exclusão de departamento
                            if (numDepartamento == -1) {
                                cout << "Nenhum departamento cadastrado!";
                            }
                            else {
                                cout << "Digite o codigo do departamento: ";
                                cin >> num;
                                fflush(stdin);
                                for (i = 0; i <= numDepartamento; i++) { // Faz a busca para exclusão do departamento
                                    if (num == defdepartamento[i].iddep) {
                                        for (j = i; j < numDepartamento; j++) {
                                            defdepartamento[j].iddep = defdepartamento[j + 1].iddep;
                                            if (strlen(defdepartamento[j].nome) >= strlen(defdepartamento[j + 1].nome)) {
                                                strcpy(defdepartamento[j].nome, defdepartamento[j + 1].nome);
                                            }
                                            else {
                                                strncpy(defdepartamento[j].nome, defdepartamento[j + 1].nome, strlen(defdepartamento[j + 1].nome));
                                            }
                                            if (strlen(defdepartamento[j].descricao) >= strlen(defdepartamento[j + 1].descricao)) {
                                                strcpy(defdepartamento[j].descricao, defdepartamento[j + 1].descricao);
                                            }
                                            else {
                                                strncpy(defdepartamento[j].descricao, defdepartamento[j + 1].descricao, strlen(defdepartamento[j + 1].descricao));
                                            }
                                            if (strlen(defdepartamento[j].local) >= strlen(defdepartamento[j + 1].local)) {
                                                strcpy(defdepartamento[j].local, defdepartamento[j + 1].local);
                                            }
                                            else {
                                                strncpy(defdepartamento[j].local,defdepartamento[j + 1].local,strlen(defdepartamento[j + 1].local));
                                            }
                                        }
                                        cout << "\n\nDepartamento excluido!";
                                        numDepartamento--;
                                        naoExiste = false;
                                    }
                                }
                                if (naoExiste) {
                                    cout << "\n\nDepartamento nao encontrado!";
                                }
                                naoExiste = true;
                            }
                            getchar();
                            system("cls");
                            break;

                        case 3: // Alteração de departamento
                            if (numDepartamento == -1) {
                                cout << "Nenhum departamento cadastrado!";
                            }
                            else {
                                cout << "Digite o codigo do departamento: ";
                                cin >> num;
                                fflush(stdin);
                                for (i = 0; i <= numDepartamento; i++) { //Faz a busca para alteração do departamento
                                    if (num == defdepartamento[i].iddep) {
                                        cout << "\n\nDepartamento encontrado!"
                                                "\n\n\nInforme os novos dados para alteracao:";
                                        cout << "\n\nDigite o codigo: ";
                                        cin >> defdepartamento[i].iddep;
                                        fflush(stdin);
                                        cout << "\nDigite o nome: ";
                                        scanf("%[^\n]", defdepartamento[i].nome);
                                        fflush(stdin);
                                        cout << "\nDigite a descricao: ";
                                        scanf("%[^\n]", defdepartamento[i].descricao);
                                        fflush(stdin);
                                        cout << "\nDigite a localizacao: ";
                                        scanf("%[^\n]", defdepartamento[i].local);
                                        fflush(stdin);
                                        cout << "\n\nDepartamento alterado!";
                                        naoExiste = false;
                                    }
                                }
                                if (naoExiste) {
                                    cout << "\n\nDepartamento nao encontrado!";
                                }
                                naoExiste = true;
                            }
                            getchar();
                            system("cls");
                            break;

                        case 4: // Listagem de departamento
                            if (numDepartamento == -1) {
                                cout << "Nenhum departamento cadastrado!";
                                getchar();
                                system("cls");
                            }
                            else {
                                cout << "Codigo / Nome /       Descricao        / Localizacao\n\n";
                                for (i = 0; i <= numDepartamento; i++) {
                                    defdepartamento[i].MostrarDepartamento();
                                }
                                do {
                                    cout << "\n\n1.Inserir filtro por nome\n"
                                            "0.Continuar\n\n"
                                            "Sua opcao: ";
                                    cin >> num;
                                    fflush(stdin);
                                    if (num == 1) {
                                        cout << "\nDigite o nome do departamento: ";
                                        cin >> nome;
                                        fflush(stdin);
                                        system("cls");
                                        naoExiste = true;
                                        for (i = 0; i <= numDepartamento; i++) { // Compara pra ver se existe o departamento
                                            if (strcmp(nome, defdepartamento[i].nome) == 0) { //Se existir retorna naoExiste falso
                                                naoExiste = false;
                                            }
                                        }
                                        if (naoExiste) { // Nao sendo retornado false anteriormente mostra na tela
                                            cout << "Departamento nao encontrado!\n"; 
                                        }
                                        else{ // naoExiste falso mostra os departamentos com aquele nome
                                            cout << "Codigo / Nome /       Descricao        / Localizacao\n\n";
                                            for (i = 0; i <= numDepartamento; i++) {
                                                if (strcmp(nome, defdepartamento[i].nome) == 0) {
                                                    defdepartamento[i].MostrarDepartamento();
                                                }
                                            }
                                        }
                                    }
                                    else if (num != 0) {
                                        system("cls");
                                    }
                                } while (num >= 1 || num < 0);
                            }
                            system("cls");
                            break;
                    
                        case 0:
                            goto goOpcao1;
                                        
                        default:
                            cout << "Opcao invalida.";
                            getchar();
                            system("cls");
                            break;
                        }
                
                    } while (opcao2 != 0);

                    break;
                
                default:
                    cout << "Opcao invalida.";
                    getchar();
                    system("cls");
                    break;

                case 0:
                    goto goInicio;
                }
                
            } while (opcao1 != 0);

 
            // USAR POR FALA
            /*
        case 2:

            do {

                do {
                    texto_em_fala(requisicao_textofala, "Escolha a opção desejada"); // Menu
                    texto_em_fala(requisicao_textofala, "1.Equipamento");
                    texto_em_fala(requisicao_textofala, "2.Tipo equipamento");
                    texto_em_fala(requisicao_textofala, "3.Depatamento");
                    texto_em_fala(requisicao_textofala, "0.Sair");
                    opcao1F = fala_em_texto(requisicao_falatexto);
                    fflush(stdin);
                    system("cls");
                } while (opcao1F != "zero" || opcao1F != "opcao zero");

                if (opcao1F == "um" || opcao1F == "opcao um")
                    opcao1 = 1;

                    switch (opcao1) {
                    case 1: // CRUD Equipamento
                        do {
                            texto_em_fala(requisicao_textofala, "Escolha a opção desejada");
                            texto_em_fala(requisicao_textofala, "1.Inserir");
                            texto_em_fala(requisicao_textofala, "2.Excluir");
                            texto_em_fala(requisicao_textofala, "3.Alterar");
                            texto_em_fala(requisicao_textofala, "4.Listar");
                            texto_em_fala(requisicao_textofala, "5.Salvar");
                            texto_em_fala(requisicao_textofala, "6.Listar dados de um equipamento");
                            texto_em_fala(requisicao_textofala, "0.Sair");
                            string opcao2 = fala_em_texto(requisicao_falatexto);
                            fflush(stdin);
                            system("cls");
                        } while (opcao2 < 0 || opcao2 > 6);
                        switch (opcao2) {
                        case 1:
                             try {
                                 if (numTipo == -1 || numDepartamento == -1) { // Trava para ver se existe o departamento

                                     throw true;
                                 }
                                 else {
                                     if (numEquip < 50) {
                                         numEquip++;

                                         texto_em_fala(requisicao_textofala, "Fale o codigo");
                                         string equip[numEquip].idequip = fala_em_texto(requisicao_falatexto);
                                         fflush(stdin);
                                         texto_em_fala(requisicao_textofala, "Fale o nome");
                                         string equip[numEquip].nome = fala_em_texto(requisicao_falatexto);
                                         fflush(stdin);
                                         texto_em_fala(requisicao_textofala, "Fale o valor do equipamento");
                                         string equip[numEquip].valor = fala_em_texto(requisicao_falatexto);
                                         fflush(stdin);
                                         texto_em_fala(requisicao_textofala, "Fale o codigo do tipo do equipamento");
                                         string num2 = fala_em_texto(requisicao_falatexto);
                                         for (i = 0; i <= numTipo; i++) {
                                             if (num2 == tipos[i].idtipoequip) {
                                                 equip[numEquip].setTipo(tipos[i]);
                                                 break;
                                             }
                                         }
                                         texto_em_fala(requisicao_textofala, "Fale o codigo do Departamento");
                                         string num2 = fala_em_texto(requisicao_falatexto);
                                         fflush(stdin);
                                         for (i = 0; i <= numDepartamento; i++) {
                                             if (num == defdepartamento[i].iddep) {
                                                 equip[numEquip].setDepart(defdepartamento[i]);
                                                 break;
                                             }
                                         }
                                     }
                                     else {
                                         texto_em_fala(requisicao_textofala,"Não é possível mais colocar equipamento"); // Limite maximo foi atigido
                                     }
                                 }
                             }
                             catch (bool falhou) {
                                 if (falhou) {
                                     if (numDepartamento == -1 && numTipo == -1) {
                                         texto_em_fala(requisicao_textofala,"Nenhum tipo de equipamento e tipo de departamento cadastrado");
                                     }
                                     else if (numTipo == -1) {
                                         texto_em_fala(requisicao_textofala,"Nenhum equipamento cadastrado"); // Trava para caso não exista o equipamento
                                     }
                                 }
                             }
                             break;

                         case 2:
                             if (numEquip == -1) {
                                 texto_em_fala(requisicao_textofala, "Nenhum departamento  cadastrado"); // Trava para caso não exista o departamento
                             }
                             else {
                                 texto_em_fala(requisicao_textofala,"Fale o codigo do equipamento ");
                                 string num2 = fala_em_texto(requisicao_falatexto);
                                 fflush(stdin);
                                 for (i = 0; i <= numTipo; i++) {
                                     if (num == tipos[i].idtipoequip) {
                                         NaoExiste = false;
                                         for (j = i; j < numTipo; j++) {
                                             equip[j].idequip = equip[j + 1].idequip;
                                             if (strlen(equip[j].nome) >= strlen(equip[j + 1].nome)) {
                                                 strcpy(equip[j].nome, equip[j + 1].nome);
                                             }
                                             else {
                                                 strncpy(equip[j].nome, equip[j + 1].nome,strlen(equip[j + 1].nome));
                                             }
                                             equip[j].valor = equip[j + 1].valor;
                                             equip[j].setTipo(*equip[j + 1].tipo);
                                             equip[j].setDepart(*equip[j + 1].depart);
                                         }
                                         texto_em_fala(requisicao_textofala, "Excluido");
                                     }
                                 }
                                 if (NaoExiste) {
                                     texto_em_fala(requisicao_textofala,"O departamento não foi  cadastrado"); //  Trava para caso não exista o departamento
                                     NaoExiste = true;
                                 }
                             }
                             break;

                         case 3:
                             texto_em_fala(requisicao_textofala,"Fale o codigo do equipamento: "); // Update
                             string num2 = fala_em_texto(requisicao_falatexto);
                             fflush(stdin);
                             if (numEquip == -1) {
                                 texto_em_fala(requisicao_textofala,"Nenhum equipamento  cadastrado");
                             }
                             else {
                                 for (i = 0; i <= numEquip; i++) {
                                     if (num == equip[i].idequip) {
                                         texto_em_fala(requisicao_textofala, "Fale o novo codigo: ");
                                         string equip[i].idequip = fala_em_texto(requisicao_falatexto);
                                         fflush(stdin);
                                         texto_em_fala(requisicao_textofala, "Fale o novo nome: ");
                                         scanf("%[^]", equip[i].nome);
                                         fflush(stdin);
                                         texto_em_fala(requisicao_textofala,
                                             "Fale o novo valor do equipamentoo: ");
                                         string equip[i].valor = fala_em_texto(requisicao_falatexto);
                                         fflush(stdin);
                                         texto_em_fala(requisicao_textofala,
                                             "Fale o codigo do tipo de equipamento: ");
                                         string num = fala_em_texto(requisicao_falatexto);
                                         fflush(stdin);
                                         for (j = 0; j <= numTipo; j++) {
                                             if (num == tipos[j].idtipoequip) {
                                                 equip[numEquip].setTipo(tipos[j]);
                                                 break;
                                             }
                                         }
                                         texto_em_fala(requisicao_textofala,
                                             "Fale o codigo do departamento : ");
                                         string num = fala_em_texto(requisicao_falatexto);
                                         fflush(stdin);

                                         for (j = 0; j <= numDepartamento; j++) {
                                             if (num == defdepartamento[j].iddep) {
                                                 equip[i].setDepart(defdepartamento[j]);
                                                 break;
                                             }
                                         }
                                         NaoExiste = false;
                                     }
                                     break;
                                 }
                                 if (NaoExiste) {
                                     texto_em_fala(
                                         requisicao_textofala,
                                         "O codigo não foi cadastrado"); /// Verifica se existe  o
                                     // codigo
                                 }
                                 NaoExiste = true;
                             }
                             break;

                         case 4:
                             if (numEquip == -1) {
                                 texto_em_fala(
                                     requisicao_textofala,
                                     "0 equipamento não foi encontrado"); // Verifica se existe
                                 // os equipamentos
                             }

                             texto_em_fala(requisicao_textofala,
                                 "Codigo / Nome / Valor / Tipo de equipamento / "
                                 "Departamento");
                             for (i = 0; i <= numEquip;
                                 i++) { // Mostra todos equipamentos cadastrados
                                 equip[i].MostrarEquipamento();
                             }

                             break;

                         case 5:
                             FazerBackup(equip, numEquip);
                             break;

                         case 6:
                             ListarArquivo();
                             break;

                         default:
                             opcao1 = 0;
                         }
                         break;

                     case 2:
                         opcao2 = menu(titulo1);

                         switch (opcao2) {
                         case 1:
                             if (numTipo < 50) { // Trava para quantidade de tipos ja cadastrados
                                 numTipo++;

                                 texto_em_fala(requisicao_textofala, "Fale o codigo");
                                 string tipos[numTipo].idtipoequip fala_em_texto(
                                     requisicao_falatexto); //  tipo de equipamento
                                 fflush(stdin);
                                 texto_em_fala(requisicao_textofala,
                                     "Fale a descrição equipamento"); // Descrição
                                 scanf("%[^]", tipos[numTipo].qualtipo);
                                 fflush(stdin);
                             }
                             break;

                         case 2:
                             if (numTipo == -1) {
                                 texto_em_fala(
                                     requisicao_textofala,
                                     "Equipamento não cadastrado"); // Trava para caso não
                                 // exista o equipamento
                             }
                             else {
                                 texto_em_fala(requisicao_textofala, "Fale o codigo");
                                 string num = fala_em_texto(requisicao_falatexto);
                                 fflush(stdin);
                                 for (i = 0; i <= numTipo; i++) {
                                     if (num == tipos[i].idtipoequip) {
                                         for (j = i; j < numTipo; j++) {
                                             tipos[j].idtipoequip = tipos[j + 1].idtipoequip;
                                             if (strlen(tipos[j].qualtipo) >=
                                                 strlen(tipos[j + 1].qualtipo)) {
                                                 strcpy(tipos[j].qualtipo, tipos[j + 1].qualtipo);
                                             }
                                             else {
                                                 strncpy(tipos[j].qualtipo, tipos[j + 1].qualtipo,
                                                     strlen(tipos[j + 1].qualtipo));
                                             }
                                         }
                                         texto_em_fala(requisicao_textofala,
                                             "Excluido"); // Caso tenha dado certo
                                         numTipo--;
                                         NaoExiste = false;
                                         break;
                                     }
                                 }

                                 if (NaoExiste) {
                                     texto_em_fala(requisicao_textofala, "Codigo não  cadastrado");
                                 }
                             }
                             NaoExiste = true;
                             break;
                         case 3:
                             if (numTipo == -1) {
                                 texto_em_fala(requisicao_textofala,
                                     "Nenhum equipamento cadastrado");
                             }
                             else {
                                 texto_em_fala(requisicao_textofala, "Fale o codigo");
                                 string num = fala_em_texto(requisicao_falatexto);
                                 fflush(stdin);
                                 for (i = 0; i <= numTipo; i++) {
                                     if (num == tipos[i].idtipoequip) {
                                         texto_em_fala(requisicao_textofala,
                                             "Fale o codigo"); // Update
                                         string tipos[i].idtipoequip =
                                             fala_em_texto(requisicao_falatexto);
                                         fflush(stdin);
                                         texto_em_fala(requisicao_textofala,
                                             "Fale uma nova descrição: ");
                                         scanf("%[^]", tipos[i].qualtipo);
                                         fflush(stdin);
                                         NaoExiste = false;
                                     }
                                 }
                                 if (NaoExiste) {
                                     texto_em_fala(requisicao_textofala,
                                         "Nenhum codigo cadastrado"); // Mostra caso não
                                     // tenha o codigo
                                 }
                                 NaoExiste = true;
                             }
                             break;
                         case 4:
                             if (numTipo == -1) {
                                 texto_em_fala(requisicao_textofala,
                                     "Nenhum tipo de equipamento cadastrado");
                             }
                             else {
                                 texto_em_fala(requisicao_textofala, "Codigo e descrição");
                                 for (i = 0; i <= numTipo;
                                     i++) { // Mostra todos equipamentos existentes
                                     tipos[i].MostrarTipoEquipamento();
                                 }
                             }
                             break;
                         default:
                             opcao1 = 0;
                         }
                         break;

                     case 3:
                         opcao2 = menu(titulo2);
                         switch (opcao2) {
                         case 1:
                             if (numDepartamento <= 9) {
                                 numDepartamento++;
                                 texto_em_fala(requisicao_textofala, "Fale o codigo");
                                 string defdepartamento[numDepartamento].iddep =
                                     fala_em_texto(requisicao_falatexto);
                                 fflush(stdin);
                                 texto_em_fala(requisicao_textofala, "Fale o nome");
                                 string defdepartamento[numDepartamento].nome =
                                     fala_em_texto(requisicao_falatexto);
                                 fflush(stdin);
                                 texto_em_fala(requisicao_textofala, "Fale a descrição");
                                 scanf("%[^]", defdepartamento[numDepartamento].descricao);
                                 fflush(stdin);
                                 texto_em_fala(requisicao_textofala, "Fale a local");
                                 scanf("%[^]", defdepartamento[numDepartamento].local);
                                 fflush(stdin);
                             }
                             else {
                                 texto_em_fala(requisicao_textofala,"Não possui mais espaço para cadastro"); // Mostra para o
                                 // usuario que não
                                 // possui mais
                                 // espaço
                             }
                             break;
                         case 2:

                             if (numDepartamento == -1) {
                                 texto_em_fala(requisicao_textofala,
                                     "Nenhum departamento cadastrado"); // caso não tenha
                                 // o departamento
                             }
                             else {
                                 texto_em_fala(requisicao_textofala, "Fale o codigo");
                                 string num = fala_em_texto(requisicao_falatexto);
                                 fflush(stdin);
                                 for (i = 0; i <= numDepartamento; i++) {
                                     if (num == defdepartamento[i].iddep) {
                                         for (j = i; j < numDepartamento; j++) {
                                             defdepartamento[j].iddep = defdepartamento[j + 1].iddep;
                                             if (strlen(defdepartamento[j].nome) >=
                                                 strlen(defdepartamento[j + 1].nome)) {
                                                 strcpy(defdepartamento[j].nome,
                                                     defdepartamento[j + 1].nome);
                                             }
                                             else {
                                                 strncpy(defdepartamento[j].nome,
                                                     defdepartamento[j + 1].nome,
                                                     strlen(defdepartamento[j + 1].nome));
                                             }
                                             if (strlen(defdepartamento[j].descricao) >=
                                                 strlen(defdepartamento[j + 1].descricao)) {
                                                 strcpy(defdepartamento[j].descricao,
                                                     defdepartamento[j + 1].descricao);
                                             }
                                             else {
                                                 strncpy(defdepartamento[j].descricao,
                                                     defdepartamento[j + 1].descricao,
                                                     strlen(defdepartamento[j + 1].descricao));
                                             }
                                             if (strlen(defdepartamento[j].local) >=
                                                 strlen(defdepartamento[j + 1].local)) {
                                                 strcpy(defdepartamento[j].local,
                                                     defdepartamento[j + 1].local);
                                             }
                                             else {
                                                 strncpy(defdepartamento[j].local,
                                                     defdepartamento[j + 1].local,
                                                     strlen(defdepartamento[j + 1].local));
                                             }
                                         }
                                         texto_em_fala(requisicao_textofala, "Excluido");
                                         numDepartamento--;
                                         NaoExiste = false;
                                     }
                                 }
                                 if (NaoExiste) {
                                     texto_em_fala(requisicao_textofala, "Nenhum codigo cadastrado");
                                 }
                                 NaoExiste = true;
                             }
                             break;

                         case 3:
                             if (numDepartamento == -1) {
                                 texto_em_fala(requisicao_textofala,
                                     "Nenhum departamento cadastrado");
                             }
                             else {
                                 texto_em_fala(requisicao_textofala,
                                     "Fale o codigo"); // Altera��o de qualtiporma��o dos
                                 // departamentos
                                 string num = fala_em_texto(requisicao_falatexto);
                                 fflush(stdin);
                                 for (i = 0; i <= numDepartamento; i++) {
                                     if (num == defdepartamento[i].iddep) {
                                         texto_em_fala(requisicao_textofala, "Fale o codigo");
                                         string defdepartamento[i].iddep =
                                             fala_em_texto(requisicao_falatexto);
                                         fflush(stdin);
                                         texto_em_fala(requisicao_textofala, "Fale o nome");
                                         scanf("%[^]", defdepartamento[i].nome);
                                         fflush(stdin);
                                         texto_em_fala(requisicao_textofala, "Fale a descricao");
                                             scanf("%[^]", defdepartamento[i].descricao);
                                         fflush(stdin);
                                         texto_em_fala(requisicao_textofala, "Fale a localizacao");
                                         scanf("%[^]", defdepartamento[i].local);
                                         fflush(stdin);
                                         NaoExiste = false;
                                     }
                                 }
                                 if (NaoExiste) {
                                     texto_em_fala(requisicao_textofala,
                                         "Nenhum codigo cadastrado"); // Verifica se existe
                                     // o codigo
                                 }
                                 NaoExiste = true;
                             }
                             break;

                         case 4:

                             if (numDepartamento == -1) {
                                 texto_em_fala(requisicao_textofala,
                                     "Nenhum departamento encontrado");
                             }
                             else {
                                 texto_em_fala(requisicao_textofala,
                                     "Codigo / Nome / Descricao / Localizacao");
                                 for (i = 0; i <= numDepartamento; i++) {
                                     defdepartamento[i].MostrarDepartamento();
                                 }
                                 do {
                                     texto_em_fala(requisicao_textofala,"Fale. 1 - Inserir filtro por nome. 0 - Continuar.Sua opcao");
                                         string num = fala_em_texto(requisicao_falatexto);
                                     fflush(stdin);
                                     if (num == 1) {
                                         texto_em_fala(requisicao_textofala, "Fale");
                                         string nome = fala_em_texto(requisicao_falatexto);
                                         fflush(stdin);
                                         system("cls");
                                         NaoExiste = true;
                                         for (i = 0; i <= numDepartamento; i++) {
                                             if (strcmp(nome, defdepartamento[i].nome) ==
                                                 0) { // Mostra os departamentos
                                                 defdepartamento[i].MostrarDepartamento();
                                                 NaoExiste = false;
                                             }
                                         }
                                         if (NaoExiste) {
                                             texto_em_fala(
                                                 requisicao_textofala,
                                                 "Nenhum departamento cadastrado"); // Verifica se
                                             // existe  o
                                             // departamento
                                         }
                                     }
                                     else if (num != 0) {
                                         system("cls");
                                     }
                                 } while (num >= 1 || num < 0);
                             }
                             break;
                         default:
                             opcao1 = 0;
                         }
                         break;
                     }
                     if (opcao1 != 0) {
                         texto_em_fala(requisicao_textofala, "Fale uma das opções");
                         getchar();
                         system("cls");
                     }

                    
                

            } while (opcao1F != "zero" || opcao1F != "opcao zero");
        */
        case 0:
            return 0;
        
        default:
            cout << "Opcao invalida.";
            getchar();
            system("cls");
            break;
        }

    } while (inicio != 0);
}


                
                    


