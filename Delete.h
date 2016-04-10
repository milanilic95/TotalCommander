#pragma once
#include "Commands.h"

class Delete : public Command {
	bool print;
	void deleteDir(string dirName);
	void deleteFile(string dirName);
	void deleteSelect(Selection *sel);
	void deleteAlias(string Path, string AliasName);

public:
	Delete(bool f = true) :print(f) { }
	void run(string Command)override;
};
