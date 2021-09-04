#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <conio.h>

using namespace std;

struct node
{
	char value;
	node* dot;
	node* dash;
};

node* createNode()
{
	node* newnode = new node;
	newnode->value = '\0';
	newnode->dot = NULL; // left child
	newnode->dash = NULL; // right child
	return newnode;
}

void readTree(node*& curr, ifstream& ifs)
{
	// read the input for the tree
	if (ifs.eof()) return;

	string s;
	getline(ifs, s);

	curr = createNode();
	// empty nodes keep value '\0' 
	if (s[0] != '*') curr->value = s[0];

	// end of a path
	if (s.length() > 1) return;

	// read left child
	readTree(curr->dot, ifs);
	//read right child
	readTree(curr->dash, ifs);
}

char singleTranslate(node* root, string code)
{
	// translate a single character
	// if it is a slash, return a space character
	if (code == "/") return ' ';
	int index = 0;

	node* temp = root;
	while (index < code.length())
	{
		// if reach NULL node, break
		if (temp == NULL) break;
		// if any character in the source morse code is not dot or dash, break
		if ((code[index] != '.') && (code[index] != '-'))
		{
			temp = NULL;
			break;
		}
		// if the character is dot, go to dot subtree and vice versa
		if (code[index] == '.') temp = temp->dot;
		else temp = temp->dash;
		index++;
	}
	// if the input is violated, return NULL character
	if (temp == NULL) return '\0';
	return temp->value;
}

string messageTranslate(node* root, string code)
{
	// translate 1 line of morse code
	stringstream ss(code);
	string character, message = "";
	getline(ss, character, ' ');
	do
	{
		char translatedChar = singleTranslate(root, character);
		if (translatedChar == '\0') message += "<unable to translate>";
		else message.push_back(translatedChar);
		getline(ss, character, ' ');
	} while (ss);
	return message;
}

string terminal_input()
{
	system("CLS");
	cin.ignore();
	string code;
	cout << "Enter morse code. Use \".\" for dots and \"-\" for dashes \nIndividual letters are seperated by a space (\" \").\nIndividual words are seperated by a forward slash(\" / \").\n";
	getline(cin, code);
	return code;
}

string file_input()
{
	system("CLS");
	cin.ignore();
	string filename;
	cout << "Enter input file name: ";
	getline(cin, filename);
	ifstream ifs(filename);
	if (ifs)
	{
		string code;
		getline(ifs, code);
		return code;
	}
	return "\0";
}

void terminal_output(string mess)
{
	cout << "Translated message: " << mess;
}

void file_output(string mess)
{
	string filename;
	cout << "Enter output file name: ";
	getline(cin, filename);
	ofstream ofs(filename);
	ofs << mess;
}

void menu()
{
	node* root = NULL;
	ifstream ifs("input.txt");
	readTree(root, ifs);
	if (ifs)
	{
		while (1)
		{
			// choose to use or exit
			char choice = '\0';
			while ((choice != '2') && (choice != '1'))
			{
				system("CLS");
				cout << "<< Morse code to message translator >>\n";
				cout << "Choose your action: \n1. Use translator.\n2. Exit.\n";
				cin >> choice;
			}

			if (choice == '2') break;

			string code, mess;

			// choose input method
			choice = '\0';
			while ((choice != '2') && (choice != '1'))
			{
				system("CLS");
				cout << "Choose your input method:\n";
				cout << "1. Terminal input.\n2. File input.\n";
				cin >> choice;
			}

			// read input
			if (choice == '1') code = terminal_input();
			else code = file_input();

			if (code == "\0")
			{
				// break if the input file is not found
				cout << "Input code file not found!";
			}
			else
			{
				// translate input
				mess = messageTranslate(root, code);

				// choose output method
				choice = '\0';
				while ((choice != '2') && (choice != '1'))
				{
					cout << "Choose your output method:\n";
					cout << "1. Terminal output.\n2. File output.\n";
					cin >> choice;
				}

				if (choice == '1') terminal_output(mess);
				else file_output(mess);
			}

			cout << "\n\nPress any key to continue ...";
			_getch();
		}
	}
	// does not execute without the input stored file
	else cout << "Input file is missing!";
}

int main()
{
	menu();
	return 0;
}