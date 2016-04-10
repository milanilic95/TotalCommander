#pragma once
#include "Commands.h"


class Rename :public Command {

	void RenameFile(string oldName, string newName);
	void RenameDir(string oldName, string newName);
	void RenameSelection(string oldName, string newName);
	void RenameAlias(string oldName, string newName);
public:
	void run(string Command)override;
};

class Help : public Command {

public:
	void run(string)override;
};
