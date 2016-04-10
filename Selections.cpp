#include "Commands.h"

Selections* Selections::selections = nullptr;
Selections* Selections::getSelections() { selections = new Selections(); return selections; }

unsigned Selections::getSize()const {
	int i = 0;
	using it_type = std::map<std::string, Selection*>::const_iterator;
	for (it_type iterator = mapa.begin(); iterator != mapa.end(); iterator++) {
		if (iterator->second != nullptr)i++;
	}
	return i;
}

ostream& operator<<(ostream& it, Selections &s) {
	using it_type = std::map<std::string, Selection*>::iterator;
	for (it_type iterator = s.mapa.begin(); iterator != s.mapa.end(); iterator++) {
		if (iterator->second != nullptr)it << iterator->first << " " << *(iterator->second) << endl;
	}
	return it;
}

istream& operator>>(istream& ut, Selections &s) {
	string Line;
	getline(ut, Line);

	size_t found = Line.find(" ");
	string SelectionName = Line.substr(0, found);
	Line = Line.substr(found + 1);

	Selection* sel = new Selection(SelectionName);

	while ((found = Line.find(" ")) != string::npos) {
		string files = Line.substr(0, found);
		Line = Line.substr(found + 1);
		sel->dodaj(new File(files));
	}
	s.mapa[SelectionName] = sel;
	return ut;
}