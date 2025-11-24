#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <windows.h>
using namespace std;

bool somenteLetras(string s)
{
    if (s == "") return false;
    for (int i = 0; i < s.size(); i++)
        if (!isalpha((unsigned char)s[i]) && s[i] != ' ')
            return false;
    return true;
}

bool somenteNumeros(string s)
{
    if (s == "") return false;
    for (int i = 0; i < s.size(); i++)
        if (!isdigit((unsigned char)s[i]))
            return false;
    return true;
}

string paraMaiusculo(string s)
{
    for (int i = 0; i < s.size(); i++)
        s[i] = toupper((unsigned char)s[i]);
    return s;
}

// =======================================================
//       Tenta encontrar e abrir foto com várias extensões
// =======================================================
void abrirFotoDoAnimal(const string& nome)
{
    string ext[5] = { ".jpg", ".jpeg", ".png", ".bmp", ".gif" };

    for (int i = 0; i < 5; i++)
    {
        string caminho = nome + ext[i];
        ifstream arq(caminho.c_str());

        if (arq.is_open())
        {
            cout << "Abrindo foto: " << caminho << endl;
            ShellExecuteA(NULL, "open", caminho.c_str(), NULL, NULL, SW_SHOW);
            return;
        }
    }

    cout << "Esse animal NAO possui foto salva." << endl;
}

int main()
{
    int opcao = -1;
    int idade;
    int contador;
    bool vazio;
    bool encontrado;

    string nome, especie, sexo, tipo;
    string idadeStr;
    string linha;
    string buscarNome;
    string apagarNome;

    while (opcao != 0)
    {
        cout << "\n======================================" << endl;
        cout << "              ZOOLOGICO" << endl;
        cout << "======================================" << endl;
        cout << "1 - Cadastrar animal" << endl;
        cout << "2 - Ver animais" << endl;
        cout << "3 - Buscar animal pelo nome" << endl;
        cout << "4 - Excluir animal pelo nome" << endl;
        cout << "5 - Apagar todos os animais" << endl;
        cout << "0 - Sair" << endl;
        cout << "--------------------------------------" << endl;
        cout << "Opcao: ";
        cin >> opcao;
        cin.ignore(1000, '\n');

        // ============================================================
        //                       CADASTRAR
        // ============================================================
        if (opcao == 1)
        {
            ofstream arquivo("animais.txt", ios::app);

            // Nome
            do {
                cout << "Nome: ";
                getline(cin, nome);
                if (!somenteLetras(nome))
                    cout << "Erro: apenas letras." << endl;
            } while (!somenteLetras(nome));
            nome = paraMaiusculo(nome);

            // Espécie
            do {
                cout << "Especie: ";
                getline(cin, especie);
                if (!somenteLetras(especie))
                    cout << "Erro: apenas letras." << endl;
            } while (!somenteLetras(especie));
            especie = paraMaiusculo(especie);

            // Idade
            do {
                cout << "Idade: ";
                getline(cin, idadeStr);
                if (!somenteNumeros(idadeStr))
                    cout << "Erro: apenas numeros." << endl;
            } while (!somenteNumeros(idadeStr));

            idade = 0;
            for (int i = 0; i < idadeStr.size(); i++)
                idade = idade * 10 + (idadeStr[i] - '0');

            // Sexo
            do {
                cout << "Sexo (Masculino/Feminino): ";
                getline(cin, sexo);

                if (!somenteLetras(sexo)) {
                    cout << "Erro: apenas letras." << endl;
                    continue;
                }

                sexo = paraMaiusculo(sexo);

                if (sexo != "MASCULINO" && sexo != "FEMININO")
                {
                    cout << "Erro: digite Masculino ou Feminino." << endl;
                    sexo = "";
                }
            } while (sexo == "");

            // Alimentação
            do {
                cout << "Tipo de alimentacao: ";
                getline(cin, tipo);
                if (!somenteLetras(tipo))
                    cout << "Erro: apenas letras." << endl;
            } while (!somenteLetras(tipo));
            tipo = paraMaiusculo(tipo);

            // Salva no arquivo
            arquivo << nome << ";" << especie << ";" << idade << ";" << sexo << ";" << tipo << endl;
            arquivo.close();

            cout << "\nAnimal cadastrado com sucesso!" << endl;

            // Pergunta sobre foto
            string resp;
            do
            {
                cout << "\nDeseja adicionar uma foto desse animal? (S/N): ";
                getline(cin, resp);
                resp = paraMaiusculo(resp);

                if (resp == "S" || resp == "SIM")
                {
                    cout << "\n>>> SALVE a foto com o nome: " << nome << ".jpg/.png/etc" << endl;
                    cout << "    NA MESMA PASTA do programa.\n";
                    break;
                }
                else if (resp == "N" || resp == "NAO")
                {
                    cout << "Prosseguindo sem foto." << endl;
                    break;
                }
                else
                {
                    cout << "Resposta inválida." << endl;
                }
            } while (true);
        }

        // ============================================================
        //                        LISTAR
        // ============================================================
        else if (opcao == 2)
        {
            ifstream arquivo("animais.txt");
            cout << "\n========= LISTA DE ANIMAIS =========" << endl;

            if (!arquivo.is_open())
            {
                cout << "Nenhum arquivo encontrado." << endl;
            }
            else
            {
                contador = 1;
                vazio = true;

                while (getline(arquivo, linha))
                {
                    if (linha != "")
                    {
                        cout << "Animal " << contador << ": " << linha << endl;
                        contador++;
                        vazio = false;
                    }
                }

                if (vazio)
                    cout << "Nenhum animal cadastrado." << endl;

                arquivo.close();
            }
        }

        // ============================================================
        //                      BUSCAR + FOTO
        // ============================================================
        else if (opcao == 3)
        {
            cout << "Nome para buscar: ";
            getline(cin, buscarNome);
            buscarNome = paraMaiusculo(buscarNome);

            ifstream arquivo("animais.txt");
            encontrado = false;

            while (getline(arquivo, linha))
            {
                string nomeArq = linha.substr(0, linha.find(';'));

                if (nomeArq == buscarNome)
                {
                    cout << "Animal encontrado: " << linha << endl;
                    encontrado = true;

                    // chama função para abrir foto
                    abrirFotoDoAnimal(buscarNome);

                    break;
                }
            }

            if (!encontrado)
                cout << "Animal nao encontrado." << endl;

            arquivo.close();
        }

        // ============================================================
        //                     EXCLUIR POR NOME
        // ============================================================
        else if (opcao == 4)
        {
            cout << "Nome para excluir: ";
            getline(cin, apagarNome);
            apagarNome = paraMaiusculo(apagarNome);

            ifstream arquivo("animais.txt");
            ofstream temp("temp.txt");
            encontrado = false;

            while (getline(arquivo, linha))
            {
                if (linha.substr(0, linha.find(';')) == apagarNome)
                {
                    encontrado = true;
                    continue;
                }
                temp << linha << endl;
            }

            arquivo.close();
            temp.close();

            remove("animais.txt");
            rename("temp.txt", "animais.txt");

            if (encontrado)
                cout << "Animal removido com sucesso." << endl;
            else
                cout << "Animal nao encontrado." << endl;
        }

        // ============================================================
        //                     APAGAR TUDO
        // ============================================================
        else if (opcao == 5)
        {
            string resp;

            while (true)
            {
                cout << "Tem certeza que quer apagar TUDO? (S/N): ";
                getline(cin, resp);
                resp = paraMaiusculo(resp);

                if (resp == "S" || resp == "SIM")
                {
                    ofstream limpar("animais.txt", ios::trunc);
                    limpar.close();
                    cout << "Todos os animais foram apagados." << endl;
                    break;
                }
                else if (resp == "N" || resp == "NAO")
                {
                    cout << "Operacao cancelada." << endl;
                    break;
                }
                else
                {
                    cout << "Resposta invalida. Digite S ou N." << endl;
                }
            }
        }

        else if (opcao != 0)
        {
            cout << "Opcao invalida." << endl;
        }
    }

    cout << "Encerrando o programa." << endl;
    return 0;
}
