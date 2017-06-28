#include <physfs.h>
#include <string>

#include "filesystem.h"
#include "vendor/physfs/extras/physfsrwops.h"
#include "vendor/filesystem/filesystem/path.h"

#include <iostream>

using namespace filesystem;

namespace chaigame {

	bool filesystem::load(std::string file) {
		PHYSFS_init(NULL);

		// Retrieve the parent path and file extension.
		if (file.empty()) {
			std::cout << "\nMOUNTING ROOT DIR";
			return mount(".", "/");
		}
		path p(file.c_str());
		std::string extension(p.extension());
		path parent(p.parent_path());
		std::string parentPath(parent.str());
		std::cout << "\nExtension: "<< extension;
		std::cout << "\nParent: "<< parentPath;

		// Allow loading from an Archive.
		if (extension == "chaigame") {
			return mount(file.c_str(), "/");
		}

		if (parentPath.empty()) {
			std::cout << "\nRegistering root: ";
			return mount(".", "/");
		}

		return mount(parentPath.c_str(), "/");

		/*
		//parentPath.make_absolute();
		path newP = parent.make_absolute();
		std::string parentPAccc(newP.str());
		parentPAccc += "/";
		std::cout << "\nRegistering root: " << parentPAccc;
		return mount(parentPAccc.c_str(), "/");
		*/
	}

	bool filesystem::unload() {
		PHYSFS_deinit();
	}

	SDL_RWops* filesystem::openRW(std::string filename) {
		SDL_RWops* rw = PHYSFSRWOPS_openRead(filename.c_str());
		if (rw != NULL) {
			return rw;
		}
		// TODO: Add error reporting.
		return NULL;
	}

	char* filesystem::readChar(std::string filename) {
		PHYSFS_file* myfile = PHYSFS_openRead(filename.c_str());
		PHYSFS_sint64 file_size = PHYSFS_fileLength(myfile);

		char *myBuf = new char[file_size];
		int length_read = PHYSFS_readBytes(myfile, myBuf, file_size);
		PHYSFS_close(myfile);
		return myBuf;
	}

	std::string filesystem::read(std::string filename) {
		char *myBuf = readChar(filename);
		std::string contents(myBuf);
		return contents;
	}

	bool filesystem::mount(const char* archive, const char* mountpoint) {
		int returnValue = PHYSFS_mount(archive, mountpoint, 0);
		return returnValue != 0;
	}
}
