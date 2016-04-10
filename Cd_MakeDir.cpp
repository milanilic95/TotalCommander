#include "Commands.h"


void Cd::run(string dirName) {

	dirName = Commands::getCommandLine(dirName);
	DIR * dir = (DIR*)Command::tekuci;

	if (Aliases::isAlias(alias, dirName)) { dirName = (*alias)[dirName]; }
	if (dirName == ".")return;

	if (dirName == "..")dirName = File::getParent(Command::tekuci->getFullPath());
	else dirName = File::getFullNameFile(dirName, Command::tekuci->getFullPath() + "/" + dirName);

	if (dir = opendir(dirName.c_str())) {
		File *t = Command::tekuci;
		Command::tekuci = new File(dirName);
		File::tekuci = Command::tekuci;
		delete t;
		closedir(dir);
	}
	else throw Greska("NE POSTOJI UNETI DIREKTORIJUM");

	return;
}



void MakeDir::run(string Command){
	Command = Commands::getCommandLine(Command);

	Command = File::getFullNameFile(Command, Command::tekuci->getFullPath() + "/" + Command);

	if (_mkdir(Command.c_str()) == 0) { cout << "USPESNO KREIRANO " << Command << endl; return; }
	else throw Greska("\nNEUSPESNO KREIRANJE " + File::getFileName(Command) + "\n\a");
}