#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	int opcao = -1;
	int idade;

	string nome;
	string especie;
	string sexo;
	string tipo;
	string linha;
	bool vazio;

	while (opcao != 0)
	{
		cout << "\n======================================" << endl;
		cout << "              ZOOLOGICO" << endl;
		cout << "======================================" << endl;
		cout << "1 - Cadastrar novo animal" << endl;
		cout << "2 - Ver animais cadastrados" << endl;
		cout << "0 - Sair" << endl;
		cout << "--------------------------------------" << endl;
		cout << "Escolha uma opcao: ";
		cin >> opcao;
		cin.ignore();

		if (opcao == 1)
		{
			ofstream arquivo("animais.txt", ios::app);

			cout << "\n---------- Cadastro de Animal ----------\n";

			cout << "Nome: ";
			getline(cin, nome);

			cout << "Especie: ";
			getline(cin, especie);

			cout << "Idade: ";
			cin >> idade;
			cin.ignore();

			cout << "Sexo: ";
			getline(cin, sexo);

			cout << "Tipo de alimentacao: ";
			getline(cin, tipo);

			arquivo << nome << ";" << especie << ";" << idade << ";" << sexo << ";" << tipo << endl;
			arquivo.close();

			cout << "\nAnimal cadastrado com sucesso!\n" << endl;
		}

		else if (opcao == 2)
		{
			ifstream arquivo("animais.txt");
			cout << "\n============== Animais Cadastrados ==============\n";

			if (!arquivo.is_open())
			{
				cout << "Nenhum arquivo encontrado. Cadastre um animal primeiro." << endl;
			}
			else
			{
				vazio = true;
				int contador = 1;

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
					cout << "Nenhum animal cadastrado ainda." << endl;

				arquivo.close();
			}

			cout << "==================================================\n";
		}

		else if (opcao != 0)
		{
			cout << "\nOpcao invalida. Tente novamente.\n" << endl;
		}
	}

	cout << "\nEncerrando o programa..." << endl;

	return 0;
}
