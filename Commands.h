#pragma once

#include <iostream>
#include <map>
#include <dirent.h>
#include <direct.h>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <list>
#include "File.h"
#include "Aliases.h"
#include <string>


using namespace std;

class Selections;



class Greska {
	string s;
public: Greska(string ss):s(ss){}
		friend ostream& operator<<(ostream& it, Greska& g) { return it << g.s << endl; }
};
class Command;

class Commands {

	map<string, Command*> mapa;
public:
	void dodaj(string s, Command* c) { if (c)mapa[s] = c; }
	Command* operator[](string s) { if (!mapa[s])throw Greska("\nNE POSTOJI UNETA KOMANDA!\n\a"); return mapa[s]; }
	static string getCommandLine(string dirName) {
		size_t found = dirName.find(" ");
		return dirName.substr(found + 1);		
	}
	bool isCommand(string c) { if (!mapa[c])return false; return true; }
	~Commands() { mapa.clear(); }
	
};

class Command {
protected:	static File* tekuci;
			static Selections* selections;
			static Aliases* alias;
public:
	virtual ~Command() {};
	virtual void run(string) { }
};









