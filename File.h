#ifndef _File_h_
#define _File_h_

#include <iostream>
#include <string>
#include <fstream>
#include <dirent.h>

using namespace std;




class File{
	string path;
	static File* tekuci;
	
	friend class Cd;

public: 
	static File* getCurrent();
	static File* getCurrentStart();

	File(string nname):path(nname)
	{
	}

	static bool isDir(string path) {
		DIR* dir; 
		if (dir = opendir(path.c_str())) {
			closedir(dir);  return true;
		}
		return false;
	}
	string getFullPath()const { return path; }
	string getName()const {
		size_t found = path.find_last_of("//");
		string fileName = path.substr(found + 1);
		return fileName;
	}
	static string getFileName(string s){		
		size_t found = s.find_last_of("//");
		string fileName = s.substr(found + 1);
		return fileName;
	}

	operator DIR* () { return opendir(path.c_str()); }
	~File()	{ }

	static string getParent(string CurrentPath) {
		if (CurrentPath == "C:/")return CurrentPath;
		size_t found = CurrentPath.find_last_of("//");
		string path = CurrentPath.substr(0, found);
		//string fileName = CurrentPath.substr(found + 1); //<------Ukoliko treba ime FAJLA!
		if (path == "C:")path = "C:/";
		return path;
	}

	static bool Exists(File *f) {
		bool File = false, Direct = false;
		string fullName = f->getFullPath();
		DIR* dir;
		if (dir = opendir(fullName.c_str())) {
			Direct = true;
			closedir(dir);
		}
		ifstream infile(fullName.c_str());
		File = infile.good();
		return File || Direct;
	}
	static string getFullNameFile(string s1,string s2) {
		string z = File::getParent(s1);
		if (File::isDir(z))return s1;
		else return s2;
	}


};



#endif