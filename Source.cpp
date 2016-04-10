#include <iostream>
#include "File.h"
#include <string>
#include "Commands.h"
#include <direct.h>
#include <stdio.h>




using namespace std;




string getComand(string dir) {
	size_t found = dir.find(" ");
	return dir.substr(0, found);
}

void init(Commands list) {
	
	cout << "\n< "<<File::getCurrent()->getFullPath()<<" > Yes,master: ";
	
	try {
		string dir;
		getline(cin, dir);

		string com = getComand(dir);
		list[com]->run(dir);
	}
	catch (Greska g) { cout << g << endl; }
	catch (...) {}
	
	
}

void load() {
	ifstream in("konfiguracija.txt");
	if (!in.is_open())in.open("BackUp.txt");
	if (!in.is_open())return;

	string s;
	int numSelections;
	in >> numSelections; getline(in,s);
	while (numSelections--)in >> *Selections::getSelections();
	int numAlias;
	in>>numAlias; getline(in, s);
	while(numAlias--)in>>*Aliases::getAlias();
	in.close();
	cout << "USPESNO UCITANA KONFIGURACIJA!\n\n" << endl;
}


int main() {

	Commands list;
	
	load();
	

	list.dodaj("cd", new Cd());
	list.dodaj("ls", new Ls());
	list.dodaj("rm", new Delete());
	list.dodaj("mk", new MakeDir());
	list.dodaj("cp", new Copy());
	list.dodaj("mv", new Move());
	list.dodaj("exit", new Exit());
	list.dodaj("select", new Select());
	list.dodaj("rename", new Rename());
	list.dodaj("alias", new Alias());
	list.dodaj("assign", new Assign(list));
	list.dodaj("help", new Help());
	
	while(1)init(list);
	


}

