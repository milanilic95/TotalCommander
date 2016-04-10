#include "Rename_Help.h"
#include "Selections.h"
#include "File.h"


void Rename::RenameFile(string oldName, string newName) {
	if (rename(oldName.c_str(), newName.c_str()) == 0)cout << "\nDATOTEKA " << File::getFileName(oldName) << " JE USPESNO PREIMENOVANA\n";
	else throw Greska("\nNEUSPESNO PREIMENOVANJE!\n\a");
}
void Rename::RenameDir(string oldName, string newName) {
	if (rename(oldName.c_str(), newName.c_str()) == 0)cout << "\nDIREKTORIJUM " << File::getFileName(oldName) << " JE USPESNO PREIMENOVAN\n";
	else throw Greska("\nNEUSPESNO PREIMENOVANJE!\n\a");
}
void Rename::RenameSelection(string oldName, string newName) {
	if (!Selections::isSelection(oldName))throw Greska("\nNEUSPESNO PREIMENOVANJE SELEKCIJE!\n\a");
	Command::selections->Rename(oldName, newName);
	cout << "\nSELEKCIJA " << oldName << " JE USPESNO PREIMENOVANA\n";
}
void Rename::RenameAlias(string oldName, string newName) {
	if (!Aliases::isAlias(alias, oldName))throw Greska("\nNEUSPESNO PREIMENOVANJE ALIASA!\n\a");
	alias->Rename(oldName, newName);
	cout << "\nALIAS " << oldName << " JE USPESNO PREIMENOVAN\n";
}

void Rename::run(string Command) {
	Command = Commands::getCommandLine(Command);

	size_t found = Command.find(" ");
	string oldName = Command.substr(0, found);
	string newName = Command.substr(found + 1);

	oldName = File::getFullNameFile(oldName, tekuci->getFullPath() + "/" + oldName);
	newName = File::getFullNameFile(newName, tekuci->getFullPath() + "/" + newName);

	if (Aliases::isAlias(alias, File::getFileName(oldName))) RenameAlias(File::getFileName(oldName), File::getFileName(newName));
	else if (Selections::isSelection(File::getFileName(oldName))) RenameSelection(File::getFileName(oldName), File::getFileName(newName));
	else if (File::isDir(oldName))RenameDir(oldName, newName);
	else RenameFile(oldName, newName);
}



void Help::run(string) {
	cout << "\nHELP:\n\n";
	cout << "mv       " << "Move files,folders or selections from one folder to another" << endl;
	cout << "cd       " << "Change Directory - move to a specific Folder" << endl;
	cout << "rm       " << "Delete one or more files,folders or selections" << endl;
	cout << "cp       " << "Copy one or more files,folders or selections to another location" << endl;
	cout << "mk       " << "Create new folder" << endl;
	cout << "exit     " << "Quit the current routine  -force : without questions   -nosave : without saving configuration " << endl;
	cout << "select   " << "Select one or more files or folders and give them a specific name" << endl;
	cout << "rename   " << "Change the name of a file, folder or a selection" << endl;
	cout << "alias    " << "Path gets a specific name" << endl;
	cout << "assign   " << "One or more commands in one name" << endl;
	cout << "help     " << "Help" << endl;
	cout << "\n\n\n";
}