#pragma once
#include "Commands.h"

class Exit : public Command {
	void saveConfiguration();

public:
	void run(string Command);
};
