#include <iostream>
#include "MD5.h"


int main(int argc,char* argv[]) {
	if (argc != 3) {
		std::cout << "eg:" << std::endl;
		std::cout << argv[0] << "\t1 \tfilename" << std::endl;
		std::cout << argv[0] << "\t2 \tstring" << std::endl;
		return 0;
	}

	//std::string str;
	//std::getline(std::cin, str);
	MD5 md5;
	//std::cout << md5.getStringMD5(str) << std::endl;
	char option = *argv[1];
	switch (option) {
	case '0':
		std::cout << md5.getFiledMDd5(argv[2]) << std::endl;
	case '1':
		std::cout << md5.getFiledMDd5(argv[2]) << std::endl;

	}
	//std::cout << md5.getFiledMDd5(argv[1]) << std::endl;

	return 0;
}