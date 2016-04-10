#pragma once
#include <iostream>
#include <map>
#include <string>


using namespace std;


class Aliases {
	map<string, string> mapa;
	static Aliases* alias;
	Aliases(){}
public:
	static Aliases* getAlias();
	void put(string s, string a) {	if(a!="")mapa[s] = a;}
	string operator[](string s) { return mapa[s]; }
	void erase(string s) { mapa[s].erase(); }
	~Aliases() { mapa.clear(); }

	void Rename(string oldName, string newName) {
		mapa[newName] = mapa[oldName];
		mapa.erase(oldName);
	}
	unsigned getSize()const;

	static bool isAlias(Aliases* alias, string s) { if ((*alias).mapa[s] != "")return true; return false; }


	friend ostream& operator<<(ostream& it, Aliases &a);

	friend istream& operator>>(istream& ut, Aliases &a);
};



