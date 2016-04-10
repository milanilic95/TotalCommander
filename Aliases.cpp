#include "Aliases.h"

Aliases* Aliases::alias = nullptr;
Aliases* Aliases::getAlias() { alias = new Aliases(); return alias; }

unsigned Aliases::getSize()const {
	int i = 0;
	using it_type = std::map<std::string, string>::const_iterator;
	for (it_type iterator = mapa.begin(); iterator != mapa.end(); iterator++) {
		if (iterator->second != "")i++;
	}
	return i;
}


ostream& operator<<(ostream& it, Aliases &a) {
	using it_type = std::map<std::string, string>::iterator;
	for (it_type iterator = a.mapa.begin(); iterator != a.mapa.end(); iterator++) {
		if (iterator->second != "")it << iterator->first << " " << iterator->second << endl;
	}
	return it;
}
istream& operator>>(istream& ut, Aliases &a) {
	string Line;
	getline(ut, Line);

	size_t found = Line.find(" ");
	string AliasName = Line.substr(0, found);
	Line = Line.substr(found + 1);

	string Path = Line;

	a.mapa[AliasName] = Line;
	return ut;
}