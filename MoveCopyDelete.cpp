#include "Move.h"
#include "Copy.h"
#include "Delete.h"
#include "MakeDir.h"




void Copy::copyDirect(string src, string destin) {
	//izvor i destin su sigurno pune putanje
	DIR* dir, *zz;
	struct dirent *element;
	string elem;

	if (dir = opendir(src.c_str())) {
		/*kreiranje datoteke ako vec ne postoji kao odredisna*/
		if (zz = opendir(destin.c_str())) { closedir(zz); }
		else { MakeDir *mk = new MakeDir(); mk->run("mk " + destin); delete mk; }

		while (element = readdir(dir))
		{
			elem = element->d_name; if (elem == "." || elem == "..")continue;
			string fajl = src + "/" + elem;
			string fajl2 = destin + "/" + elem;
			this->run("cp " + fajl + " " + fajl2); //AKO NECE DODATI PUNU KOMANDU "cp izvor destin"

		}
	}
	else throw Greska("NEUSPESNO KOPIRAN DIREKTORIJUM " + src);

}

bool Copy::copyFile(const char *SRC, const char* DEST)
{

	std::ifstream src(SRC, std::ios::binary);
	std::ofstream dest(DEST, std::ios::binary);
	dest << src.rdbuf();
	return src && dest; //return <>0 if good
}

void Copy::copySelect(Selection *sel, string destin) {

	for (File *f : *sel) {
		if (File::Exists(f))
			this->run("cp " + f->getFullPath() + " " + destin);
	}
	if (print)cout << "\nUSPESNO PREKOPIRANA SELEKCIJA " << sel->getName() << endl;
}

void Copy::run(string Command) {
	Command = Commands::getCommandLine(Command);

	size_t found = Command.find(" ");
	string src = Command.substr(0, found);
	string destin = Command.substr(found + 1);

	if (Aliases::isAlias(alias, src)) { src = (*alias)[src]; }
	else src = File::getFullNameFile(src, Command::tekuci->getFullPath() + "/" + src);

	destin = File::getFullNameFile(destin, Command::tekuci->getFullPath() + "/" + destin);

	if (Selections::isSelection(File::getFileName(src))) { copySelect((*Command::selections)[File::getFileName(src)], destin); }
	else if (File::isDir(src)) { copyDirect(src, destin); }
	else {
		destin += "/" + File::getFileName(src); //posto se kopira u folder mora se nazvati nekako

		if (copyFile(src.c_str(), destin.c_str()) != 0) { if (print)cout << "USPESNO KOPIRAN " << src << endl; }
		else throw Greska("NEUSPESNO KOPIRANJE!");
	}
}


void Delete::deleteSelect(Selection *sel) {

	for (File *f : *sel) {
		if (File::Exists(f))
			this->run("rm " + f->getFullPath());
	}

	if (print)cout << "\nUSPESNO OBRISANA SELEKCIJA " << sel->getName() << endl;
}

void Delete::deleteAlias(string Path, string AliasName) {
	this->run("rm " + Path);
	if (print)cout << "\nUSPESNO OBRISAN ALIAS " << AliasName << endl;
}


void Delete::deleteDir(string dirName) {

	dirName = Commands::getCommandLine(dirName);

	dirName = File::getFullNameFile(dirName, Command::tekuci->getFullPath() + "/" + dirName);

	if (_rmdir(dirName.c_str()) == 0) { cout << "USPESNO OBRISAN " << dirName << endl; return; }
	else //trazi potvrdu ako direktorijum nije prazan
		if ((_rmdir(dirName.c_str()) == -1)) {
			char c;

			if (print) { cout << "DIREKTORIJUM <" << dirName << "> NIJE PRAZAN!\nDA LI ZELITE DA NASTAVITE SA BRISANJEM? (Y,N): ";  cin >> c; cin.ignore(); cout << endl; }
			else { c = 'y'; }

			if (c == 'Y' || c == 'y') {
				DIR* dir;
				struct dirent *element;
				string elem;
				if (dir = opendir(dirName.c_str())) {

					while (element = readdir(dir))
					{
						elem = element->d_name; if (elem == "." || elem == "..")continue;
						string fajl = dirName + "/" + elem;
						this->run(fajl);

					}
					this->run(dirName);
					return;
				}

			}
		}

	throw Greska("\nNEUSPESNO BRISANJE\n\a");
}

void Delete::deleteFile(string FileName) {
	FileName = Commands::getCommandLine(FileName);
	FileName = File::getFullNameFile(FileName, Command::tekuci->getFullPath() + "/" + FileName);

	if (remove(FileName.c_str()) == 0) { if (print)cout << "USPESNO OBRISANA DATOTEKA " << FileName << endl; }
	else throw Greska("\nNEUSPESNO BRISANJE " + FileName + "\n\a");
}

void Delete::run(string Command){

	Command = Commands::getCommandLine(Command);

	string dirName = File::getFullNameFile(Command, Command::tekuci->getFullPath() + "/" + Command);

	if (Aliases::isAlias(alias, Command)) {
		string Path = (*alias)[Command];
		deleteAlias(Path, Command);
		alias->erase(Command); return;
	}

	if (Selections::isSelection(File::getFileName(dirName))) {
		deleteSelect((*Command::selections)[File::getFileName(dirName)]);
		Command::selections->erase(File::getFileName(dirName));
	}
	else if (File::isDir(dirName)) deleteDir(dirName);
	else deleteFile(dirName);


}



void Move::moveSelect(Selection *sel, string destin) {

	for (File *f : *sel) {
		if (File::Exists(f))
			this->run("mv " + f->getFullPath() + " " + destin);
	}
	cout << "\nUSPESNO PREMESTENA SELEKCIJA " << File::getFileName(sel->getName()) << endl;
	Command::selections->erase(sel->getName());
}

void Move::run(string Command) {
	Command = Commands::getCommandLine(Command);

	size_t found = Command.find(" ");
	string  src = Command.substr(0, found);
	string destin = Command.substr(found + 1); if (found == 0)throw Greska("\nNEISPRAVAN UNOS ODREDISTA\n\a");

	if (Aliases::isAlias(alias, src)) { src = (*alias)[src]; }
	else src = File::getFullNameFile(src, Command::tekuci->getFullPath() + "/" + src);

	if (Aliases::isAlias(alias, destin)) { destin = (*alias)[destin]; }
	else destin = File::getFullNameFile(destin, Command::tekuci->getFullPath() + "/" + destin);

	if (!File::isDir(destin))throw Greska("\nODREDISTE NIJE DIREKTORIJUM!\n\a");

	if (Aliases::isAlias(alias, File::getFileName(src))) { src = (*alias)[File::getFileName(src)]; }

	if (Selections::isSelection(File::getFileName(src))) { moveSelect((*Command::selections)[File::getFileName(src)], destin); return; }
	else //kreiranje novog istoimenog foldera ukoliko ne postoji na odredistu
		if (File::isDir(src)) {

			MakeDir* mk = new MakeDir();
			destin += "/" + File::getFileName(src);
			mk->run(destin);
			delete mk;

		}
	Delete *d = new Delete(false);
	Copy *c = new Copy(false);
	c->run("cp " + src + " " + destin);

	d->run(src);
	cout << "USPESNO PREMESTEN " << src << " NA  " << Command.substr(found + 1) << endl;
	delete d; delete c;

}