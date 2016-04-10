#include "File.h"
File* File::tekuci =nullptr;

File* File::getCurrentStart() {
	tekuci = new File("C:/");
	return tekuci;
}

File* File::getCurrent() {
	return tekuci;
}