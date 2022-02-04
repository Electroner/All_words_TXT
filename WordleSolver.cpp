#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int longitudpalabra = 5;
const char CUALQUIERA = '*';

void pedirPalabra(char palabra[longitudpalabra], vector<char> &letrasquitar, vector<char> &letrasagregar)
{
	string entrada;
	string letrasmenos;
	string letrasmas;
	cout << "----------------------------------------------------------------------------------------------" << endl;
	cout << "Para los campos vacios (***** + - )" << endl
		 << endl;
	cout << "Ingrese una palabra: (***** +CONTIENELETRAS -NOTIENELETRAS): ";
	getline(cin >> ws, entrada);
	cout << "Palabra:";
	for (int i = 0; i < longitudpalabra; i++)
	{
		palabra[i] = entrada.at(i);
		cout << entrada.at(i);
	}
	cout << "." << endl;
	letrasmas = entrada.substr(entrada.find("+") + 1, entrada.find("-") - entrada.find("+") - 2);
	cout << "Letras a agregar:" << letrasmas << "." << endl;
	for (int i = 0; i < letrasmas.length(); i++)
	{
		letrasagregar.push_back(letrasmas.at(i));
	}
	letrasmenos = entrada.substr(entrada.find("-") + 1, entrada.length() - entrada.find("-") - 1);
	cout << "Letras a quitar:" << letrasmenos << "." << endl;
	for (int i = 0; i < letrasmenos.length(); i++)
	{
		letrasquitar.push_back(letrasmenos.at(i));
	}
	cout << endl
		 << "PALABRAS CANDIDATAS:" << endl;
}

int main()
{
	vector<string> palabras;
	vector<string> palabras_cortas;
	ifstream file("ES.txt");
	string line;

	while (!file.eof())
	{
		getline(file, line);
		palabras.push_back(line);
	}
	file.close();
	for (int i = 0; i < palabras.size(); i++)
	{
		if (palabras[i].size() == longitudpalabra)
		{
			palabras_cortas.push_back(palabras[i]);
		}
	}

	while (true)
	{
		char palabra[longitudpalabra];
		vector<char> letrasquitar;
		vector<char> letrasagregar;
		bool letrasconinciden = true;

		pedirPalabra(palabra, letrasquitar, letrasagregar);

		vector<string> palabras_candidatas;
		for (int i = 0; i < palabras_cortas.size(); i++)
		{
			for (int j = 0; j < longitudpalabra; j++)
			{
				if (palabra[j] != CUALQUIERA)
				{
					if (palabras_cortas[i].at(j) != palabra[j])
					{
						letrasconinciden = false;
					}
				}
			}
			if (letrasconinciden)
			{
				palabras_candidatas.push_back(palabras_cortas[i]);
			}
			letrasconinciden = true;
		}

		if (palabras_candidatas.size() > 0)
		{
			bool letrasagregadas = true;
			vector<string> palabras_candidatas_conletras;
			for (int i = 0; i < palabras_candidatas.size(); i++)
			{
				for (int j = 0; j < letrasagregar.size(); j++)
				{
					if (palabras_candidatas[i].find(letrasagregar[j]) == string::npos) // Si no encuentra la letra
					{
						letrasagregadas = letrasagregadas & false;
					}
					else
					{
						letrasagregadas = letrasagregadas & true;
					}
				}
				if (letrasagregadas)
				{
					palabras_candidatas_conletras.push_back(palabras_candidatas[i]);
				}
				letrasagregadas = true;
			}

			if (palabras_candidatas_conletras.size() > 0)
			{
				vector<string> palabras_candidatas_sinletras;
				bool letrasquitadas = true;
				for (int i = 0; i < palabras_candidatas_conletras.size(); i++)
				{
					for (int j = 0; j < letrasquitar.size(); j++)
					{
						if (palabras_candidatas_conletras[i].find(letrasquitar[j]) != string::npos) // Si encuentra la letra
						{
							letrasquitadas = letrasquitadas & false;
						}
						else
						{
							letrasquitadas = letrasquitadas & true;
						}
					}
					if (letrasquitadas)
					{
						palabras_candidatas_sinletras.push_back(palabras_candidatas_conletras[i]);
					}
					letrasquitadas = true;
				}

				for (int i = 0; i < palabras_candidatas_sinletras.size(); i++)
				{
					cout << palabras_candidatas_sinletras[i] << endl;
				}
				cout << "Hay " << palabras_candidatas_sinletras.size() << " palabras candidatas." << endl;
				
				palabras_candidatas_sinletras.clear();
			}
			palabras_candidatas_conletras.clear();
		}
		palabras_candidatas.clear();
		letrasquitar.clear();
		letrasagregar.clear();
	}
	return 0;
}