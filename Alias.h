#pragma once
#include "Commands.h"



class Alias :public Command {

public:
	void run(string Command) {
		if (Command == "alias") { cout << *alias << endl; return; }

		Command = Commands::getCommandLine(Command);

		size_t found = Command.find(" ");
		string AliasName = Command.substr(0, found);
		string Path = Command.substr(found + 1);
		if (!File::Exists(new File(Path))) { cout << "\nUNETA PUTANJA ZA SADA NE POSTOJI!\n\a"; }


		alias->put(AliasName, Path);
		cout << "\nUSPESNO KREIRAN ALIAS " << AliasName << endl;
	}

};
