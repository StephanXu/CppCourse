#ifndef VERIFY_FILE
#define VERIFY_FILE

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>

namespace zjun {
	bool verify_file(std::fstream& fs)
	{
		if (!fs) {
			std::cout << "Error: failed to open file!";
			return false;
		}
		return true;
	}

	bool verify_file(std::ifstream& ifs)
	{
		if (!ifs) {
			std::cout << "Error: failed to open file!";
			return false;
		}
		return true;
	}

	bool verify_file(std::ofstream& ofs)
	{
		if (!ofs) {
			std::cout << "Error: failed to open file!";
			return false;
		}
		return true;
	}
}

#define verify(fs) assert(zjun::verify_file(fs))

#endif // VERIFY_FILE