#pragma once
#include "Commands.h"

class Copy : public Command {
	bool print;
	void copyDirect(string src, string destin);

	bool copyFile(const char *SRC, const char* DEST);

	void copySelect(Selection *sel, string destin);

public:
	Copy(bool f = true) :print(f) {}
	void run(string Command);

};