#pragma once
#include "Commands.h"

class Ls : public Command {
	bool samoTekuci = true; //sprecava rekurzivno listanje direktorijuma,vec samo tekuceg

	void fsize(const char *name);

	void dirwalk(const char *dir);

public:
	void run(string Command)override;
};