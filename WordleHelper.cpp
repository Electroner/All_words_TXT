#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int longitudpalabra = 5;

void pedirPalabra(char palabra[longitudpalabra], vector<char> &letrasquitar)
{
	string aux;
	cout << "Ingrese una palabra de 5 letras: (##### - LETRASAQUITAR): ";
	getline(cin >> ws, aux);
	for (int i = 0; i < longitudpalabra; i++)
	{
		palabra[i] = aux.at(i);
	}
	aux.erase(0, aux.find("-") + 2);
	for (int i = 0; i < aux.length(); i++)
	{
		letrasquitar.push_back(aux.at(i));
	}
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
	pedirPalabra(palabra, letrasquitar);

	bool letrasconinciden;
	bool condition = true;
	for (int i = 0; i < palabras_cortas.size(); i++)
	{
		for (int j = 0; j < palabras_cortas[i].length(); j++)
		{
			for (int k = 0; k < letrasquitar.size(); k++)
			{
				if (palabras_cortas[i].at(j) == letrasquitar.at(k))
				{
					condition = false;
				}
			}
		}
		letrasconinciden = true;
		for (int j = 0; j < longitudpalabra; j++)
		{
			if (palabra[j] != '#')
			{
				if (palabras_cortas[i].at(j) != palabra[j])
				{
					letrasconinciden = false;
				}
			}
		}
		if (condition && letrasconinciden)
		{
			cout << palabras_cortas[i] << endl;
		}
		condition = true;
	}

	file.close();
	return 0;
}
