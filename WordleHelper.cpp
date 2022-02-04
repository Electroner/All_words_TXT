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
	cout << "Para los campos vacios (***** +  - )"<<endl<<endl;
	cout << "Ingrese una palabra: (##### + CONTIENELETRAS - NOTIENELETRAS): ";
	getline(cin >> ws, entrada);
	cout<< "Palabra:";
	for (int i = 0; i < longitudpalabra; i++)
	{
		palabra[i] = entrada.at(i);
		cout<<entrada.at(i);
	}
	cout <<"."<< endl;
	letrasmas = entrada.substr(entrada.find("+") + 2, entrada.find("-") - entrada.find("+") - 3);
	cout << "Letras a agregar:" << letrasmas <<"."<< endl;
	for (int i = 0; i < letrasmas.length(); i++)
	{
		letrasagregar.push_back(letrasmas.at(i));
	}
	letrasmenos = entrada.substr(entrada.find("-") + 2, entrada.length() - entrada.find("-") - 2);
	cout << "Letras a quitar:" << letrasmenos <<"."<< endl;
	for (int i = 0; i < letrasmenos.length(); i++)
	{
		letrasquitar.push_back(letrasmenos.at(i));
	}
	cout << endl << "PALABRAS CANDIDATAS:" << endl;
}

int main()
{
	vector<string> palabras;
	vector<string> palabras_cortas;
	ifstream file("ES.txt");
	string line;

	getline(file, line);
	while (!file.eof())
	{
		getline(file, line);
		line.erase(0, line.find(" ") + 1);
		palabras.push_back(line);
	}

	for (int i = 0; i < palabras.size(); i++)
	{
		if (palabras[i].size() == longitudpalabra)
		{
			palabras_cortas.push_back(palabras[i]);
		}
	}

	char palabra[longitudpalabra];
	vector<char> letrasquitar;
	vector<char> letrasagregar;
	bool contieneletra = false;
	bool nocontieneletra = true;
	bool letrasconinciden = true;

	pedirPalabra(palabra, letrasquitar, letrasagregar);
	
	for (int i = 0; i < palabras_cortas.size(); i++)
	{
		for (int j = 0; j < palabras_cortas[i].length(); j++)
		{
			for (int k = 0; k < letrasquitar.size(); k++)
			{
				if (palabras_cortas[i].at(j) == letrasquitar.at(k))
				{
					nocontieneletra = false;
				}
			}
			for (int k = 0; k < letrasagregar.size(); k++)
			{
				if (palabras_cortas[i].at(j) == letrasagregar.at(k))
				{
					contieneletra = true;
				}
			}
		}
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
		if(letrasagregar.empty())
		{
			contieneletra = true;
		}
		if (nocontieneletra && letrasconinciden && contieneletra)
		{
			cout << palabras_cortas[i] << endl;
		}
		contieneletra = false;
		nocontieneletra = true;
		letrasconinciden = true;
	}

	file.close();
	return 0;
}
