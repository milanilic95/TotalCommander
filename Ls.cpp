#include "Ls.h"


void Ls::dirwalk(const char *dir)
{
	char name[MAX_PATH];
	dirent *dp;
	DIR *dfd;

	if ((dfd = opendir(dir)) == NULL) {
		fprintf(stderr, "dirwalk: can't open %s\n", dir);
		return;
	}
	while ((dp = readdir(dfd)) != NULL) {
		if (strcmp(dp->d_name, ".") == 0
			|| strcmp(dp->d_name, "..") == 0)
			continue;    /* skip self and parent */
		if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name))
			fprintf(stderr, "dirwalk: name %s %s too long\n",
				dir, dp->d_name);
		else {
			sprintf(name, "%s/%s", dir, dp->d_name);
			this->fsize(name);
		}
	}
	closedir(dfd);
}

void Ls::fsize(const char *name)
{
	struct stat stbuf;

	if (stat(name, &stbuf) == -1) {
		fprintf(stderr, "\nCan't access %s\n\n", name);
		return;
	}
	if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
		if (samoTekuci) {
			samoTekuci = false;
			dirwalk(name);
		}
		else //else da ne bi stampao i tekuci direktorijum
			printf("<DIR>        %s\n", File::getFileName(name).c_str());
	}
	else { //stampanje podataka o datoteci
		char* t = ctime(&stbuf.st_mtime); /*ukidanje prelaska u novi red*/size_t ln = strlen(t) - 1;	if (*t && t[ln] == '\n')t[ln] = '\0';
		printf("%12ld KB  %s  %s\n", stbuf.st_size / (1024/*KB*/), t, File::getFileName(name).c_str());
	}
}

void Ls::run(string Command){
	Command = Commands::getCommandLine(Command);
	DIR* dir;
	struct dirent *element;
	string elem;
	string dirName = Command::tekuci->getFullPath();
	if (Command == "-l") {
		fsize(dirName.c_str());
		samoTekuci = true;/*dozvoljavamo ispis*/
		return;
	}
	else if (dir = opendir(dirName.c_str())) { //obican pregled fajlova

		while (element = readdir(dir))
		{
			elem = element->d_name;
			cout << elem << endl;
		}

	}
	closedir(dir);
}