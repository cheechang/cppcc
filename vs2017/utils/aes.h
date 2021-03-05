#ifndef AES_H_
#define AES_H_

#include <string>
#include <stdio.h>
#include <string.h>
#include "rijndael.h"

using namespace std;

namespace utils
{
	std::string encrypt(const std::string &key, const std::string &in, UINT8* vi);

	std::string decrypt(const std::string &key, const std::string &in, UINT8* vi);

	void getrandstr(int length, char* ouput);
}

#endif
