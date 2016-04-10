#pragma once
#include "Commands.h"
#include "Selections.h"
#include "File.h"

class Move : public Command {

	void moveSelect(Selection *sel, string destin);


public:
	void run(string Command);
};