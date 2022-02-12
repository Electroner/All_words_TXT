#define DEFAULTLENGTH
#define WINDOWS
//#define LINUX

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

#ifdef WINDOWS
#include <windows.h>
#endif 

#ifdef LINUX
#include <unistd.h>
#include <sys/stat.h>
#endif

using namespace std;

unsigned int longitudpalabra;

#ifdef DEFAULTLENGTH
longitudpalabra = 5;
#endif // DEFAULTLENGTH

const char CUALQUIERA = '*';
const char CUALQUIERACOINCIDE = '.';

#ifdef WINDOWS
std::string browse(HWND hwnd)
{
	std::string path(MAX_PATH, '\0');
	OPENFILENAME ofn = { sizeof(OPENFILENAME) };
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter =
		"Text files (*.txt)\0*.txt\0"
		"All files\0*.*\0";
	ofn.lpstrFile = &path[0];
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_FILEMUSTEXIST;
	if (GetOpenFileName(&ofn))
	{
		path.resize(strlen(path.c_str()));
	}
	return path;
}
#endif

#ifdef LINUX
string browse() {
	string path;
	char filename[1024];
	FILE* f = popen("zenity --file-selection", "r");
	fgets(filename, 1024, f);
	path = filename;
	uid_t permisos = geteuid();
	if(permisos == 0) {
		cout << "File needs to be executed as sudo." << endl;
		chmod(path.c_str(), 0700);
		exit(0);
	}
	return path;
}
#endif

void pedirPalabra(vector<char>& palabra, vector<char>& noletrasposicion, vector<char>& letrasquitar, vector<char>& letrasagregar)
{
	string entrada;
	string letrasmenos;
	string letrasmas;
	cout << "----------------------------------------------------------------------------------------------------" << endl;
	cout << "For a empty search (exaplme length of 5): (***** ..... + - )" << endl << endl;
	cout << "WORD (example length of 5) -> (***** ..... +LettersToAdd -LettersToSubtract): ";
	getline(cin >> ws, entrada);
	if(entrada >= ((longitudpalabra*2)+5)){
		cout << "Input String error"
		exit(3);
	}
	cout << "WORD:";
	for (int i = 0; i < longitudpalabra; i++)
	{
		palabra.push_back(entrada.at(i));
		cout << entrada.at(i);
	}
	cout << "|" << endl;
	cout << "REMOVE WORDS WHO LETTERS:";
	for (int i = longitudpalabra + 1; i < ((longitudpalabra * 2) + 1); i++) {
		noletrasposicion.push_back(entrada.at(i));
		cout << entrada.at(i);
	}
	cout << "|" << endl;
	letrasmas = entrada.substr(entrada.find("+") + 1, entrada.find("-") - entrada.find("+") - 2);
	cout << "LETTERS TO ADD:" << letrasmas << "|" << endl;
	for (int i = 0; i < letrasmas.length(); i++)
	{
		letrasagregar.push_back(letrasmas.at(i));
	}
	letrasmenos = entrada.substr(entrada.find("-") + 1, entrada.length() - entrada.find("-") - 1);
	cout << "LETTERS TO SUBTRACT:" << letrasmenos << "|" << endl;
	for (int i = 0; i < letrasmenos.length(); i++)
	{
		letrasquitar.push_back(letrasmenos.at(i));
	}
	cout << endl << "CANDIDATE WORDS:" << endl;
}

int main()
{
	vector<string> palabras;
	vector<string> palabras_cortas;
	string filename;

	cout << "CHOOSE A DICTIONARY..." << endl;

	#ifdef WINDOWS
		filename = browse(0);
		std::replace(filename.begin(), filename.end(), '\\', '/');
	#endif
	#ifdef LINUX
		filename = browse();
	#endif

	if (filename.size() == 0) {
		cout << "Error opening path. Exiting" << endl;
		exit(1);
	}
	cout << "Dictionary Selected:" << filename << endl << endl;
	ifstream file(filename);
	string line;

	if(file.fail()) {
		cout << "Error opening file. Exiting" << endl;
		exit(2);
	}

	while (!file.eof())
	{
		getline(file, line);
		palabras.push_back(line);
	}
	file.close();

	#ifndef DEFAULTLENGTH
		cout << endl;
		cout << endl;
		cout << "Set the length of the words: ";
		cin >> longitudpalabra;
		cout << endl;
	#endif

	for (int i = 0; i < palabras.size(); i++)
	{
		if (palabras[i].size() == longitudpalabra)
		{
			palabras_cortas.push_back(palabras[i]);
		}
	}

	while (true)
	{
		vector<char> palabra;
		vector<char> noletrasposicion;
		vector<char> letrasquitar;
		vector<char> letrasagregar;
		bool letrasconinciden = true;

		pedirPalabra(palabra, noletrasposicion, letrasquitar, letrasagregar);

		
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
			for (int j = 0; j < longitudpalabra; j++)
			{
				if (noletrasposicion[j] != CUALQUIERACOINCIDE)
				{
					if (palabras_cortas[i].at(j) == noletrasposicion[j])
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
				cout << "There is " << palabras_candidatas_sinletras.size() << " candidate words." << endl;

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
