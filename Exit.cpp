#include "Commands.h"


void Exit::saveConfiguration() {
	if (File::Exists(new File("konfiguracija.txt"))) {
		remove("BackUp.txt");
		rename("konfiguracija.txt", "BackUp.txt");
	}
	ofstream out("konfiguracija.txt");

	unsigned SelSize = Command::selections->getSize();
	unsigned AliSize = alias->getSize();
	out << SelSize << endl;
	out << *Command::selections << endl;
	out << AliSize << endl;
	out << *alias << endl;

	out.close();

	cout << "KONFIGURACIJA USPESNO SACUVANA!\n";

}


void Exit::run(string Command) {
	Command = Commands::getCommandLine(Command);

	/*treba dodati
	parametar: izbegavanje snimanja konfiguracije
	force: da se ne pita da li smo sigurni za napustanje
	*/
	bool saveConfig = true;
	bool dontAsk = false;
	size_t found = Command.find(" ");
	string noSave = Command.substr(0, found);
	string Force = Command.substr(found + 1);

	if (noSave == "-nosave" || Force == "-nosave")saveConfig = false;
	if (Force == "-force" || noSave == "-force")dontAsk = true;

	if (!dontAsk)
	{
		cout << "\nDA LI STE SIGURNI DA ZELITE DA NAPUSTITE PROGRAM? <Y,N>: ";
		char c;  cin >> c; cin.ignore(); if (c != 'Y' && c != 'y')return;
	}

	if (saveConfig)saveConfiguration();
	cout << "\n\nGOODBYE MASTER\n" << endl;

	delete tekuci;
	delete Command::selections;
	delete alias;

	exit(0);
}