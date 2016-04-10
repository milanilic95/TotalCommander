#pragma once
#include "Commands.h"

class Cd :public Command {
public:
	void run(string dirName)override;
};
