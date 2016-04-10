#pragma once
#include "Commands.h"




class Selection {
	string ime;
	list<File*> fajlovi;
public:
	Selection(string iime) :ime(iime) {}
	void dodaj(File* f) { if (f)fajlovi.push_back(f); }
	File* uzmi() { File *f = fajlovi.front(); fajlovi.pop_front(); return f; }

	list<File*>::const_iterator begin()const { return fajlovi.begin(); }
	list<File*>::const_iterator end()const { return fajlovi.end(); }

	list<File*>::iterator begin() { return fajlovi.begin(); }
	list<File*>::iterator end() { return fajlovi.end(); }

	bool isEmpty()const { return fajlovi.empty(); }
	string getName()const { return ime; }
	~Selection() { fajlovi.clear(); }

	friend ostream& operator<<(ostream& it, Selection *s) {
		for (File* f : s->fajlovi) {
			it << f->getName() << endl;
		}
		return it;
	}
	friend ostream& operator<<(ostream& it, Selection &s) {
		for (File* f : s.fajlovi) {
			it << f->getFullPath() << " ";
		}
		return it;
	}


};


class Selections {
	map<string, Selection*> mapa;
	static Selections *selections;
	Selections() {}

public:
	static Selections* getSelections();

	Selection* operator[](string s) { if (!mapa[s])return nullptr;/*throw Greska("\n NE POSTOJI SELEKCIJA SA UNETIM IMENOM!\n\a");*/ return mapa[s]; }
	void put(string s, Selection *sel) { if (sel)mapa[s] = sel; }
	void erase(string s) { mapa.erase(s); }
	static bool isSelection(string s) { return selections->mapa[s] != nullptr; }
	void Rename(string oldName, string newName) {
		mapa[newName] = mapa[oldName];
		mapa.erase(oldName);
	}
	unsigned getSize()const;
	~Selections() { mapa.clear(); }

	friend ostream& operator<<(ostream& it, Selections &s);
	friend istream& operator>>(istream& ut, Selections &s);
};


class Select : public Command {


	bool match(const char *first, const char * second)
	{
		// If we reach at the end of both strings, we are done
		if (*first == '\0' && *second == '\0')
			return true;

		// Make sure that the characters after '*' are present
		// in second string. This function assumes that the first
		// string will not contain two consecutive '*'
		if (*first == '*' && *(first + 1) != '\0' && *second == '\0')
			return false;

		// If the first string contains '?', or current characters
		// of both strings match
		if (*first == '?' || *first == *second)
			return match(first + 1, second + 1);

		// If there is *, then there are two possibilities
		// a) We consider current character of second string
		// b) We ignore current character of second string.
		if (*first == '*')
			return match(first + 1, second) || match(first, second + 1);
		return false;
	}

	void pack(Selection* sel, string criteria) {

		string currPath = tekuci->getFullPath();
		DIR* dir;
		struct dirent *element;
		string elem;

		if (dir = opendir(currPath.c_str())) {

			while (element = readdir(dir))
			{
				elem = element->d_name;
				if (match(criteria.c_str(), elem.c_str())) {
					File *f = new File(tekuci->getFullPath() + "/" + elem);
					sel->dodaj(f);
				}

			}

		}
		closedir(dir);

	}

public:
	void run(string Command) {
		Command = Commands::getCommandLine(Command);
		size_t found = Command.find(" ");
		string nameOfSelection = Command.substr(found + 1);
		Command = Command.substr(0, found);//Command sadrzi kriterijum selekcije 

		if (nameOfSelection == "")return;

		Selection* sel = new Selection(nameOfSelection);
		pack(sel, Command);
		if (!(sel->isEmpty()))	Command::selections->put(nameOfSelection, sel);
		else { delete sel; return; }
		cout << sel;

	}


};



