#pragma once
#include "Commands.h"

class Assign :public Command {
	map<string, string> mapa;
	Commands &list;

	string parseCommands(string List) {

		size_t found;
		string back = "";
		bool first = true;
		while ((found = List.find(" ")) != string::npos) {
			if (list.isCommand(List.substr(0, found))) {
				if (!first)back += "\n";
				back += List.substr(0, found) + " ";
				List = List.substr(found + 1);
				first = false;
			}
			else { if (!first)back += " "; }

			found = List.find(" ");
			if (found != string::npos)back += List.substr(0, found);
			List = List.substr(found + 1);
		}
		back += " " + List;
		return back;
	}
public:
	Assign(Commands &l) :list(l) {}

	void runCommand(string Name) {
		if (mapa[Name] == "")return;
		string ListOfCommands = mapa[Name];
		size_t found;
		while ((found = ListOfCommands.find("\n")) != string::npos) {
			string Command = ListOfCommands.substr(0, found);
			ListOfCommands = ListOfCommands.substr(found + 1);
			cout << "IZVRSAVA SE: " << Command << endl;
			string CommandName = Command.substr(0, Command.find(" "));
			list[CommandName]->run(Command);
		}
		string CommandName = ListOfCommands.substr(0, ListOfCommands.find(" "));
		list[CommandName]->run(ListOfCommands);
	}

	void run(string Command) {
		size_t found = Command.find(" ");
		string AssignName = Command.substr(0, found);
		if (AssignName != "assign") { runCommand(AssignName); return; }
		Command = Commands::getCommandLine(Command); //sklanja mu assign - ostaju mu jos AssignName i lista komandi
		found = Command.find(" ");
		AssignName = Command.substr(0, found);
		mapa[AssignName] = parseCommands(Command.substr(found + 1));
		list.dodaj(AssignName, this);
		cout << "USPESNO SACUVAN NOVI ASSIGN: " << AssignName << endl << endl;
	}
};


