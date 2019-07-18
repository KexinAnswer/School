#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#define N 64

class MD5{
public:
	MD5();
	std::string getFiledMDd5(const char* filename);
	std::string getStringMD5(const std::string& str);

private:
	void init();

	void calculateMD5Final();
	std::string changeHex(size_t num);


	size_t F(size_t x, size_t y, size_t z) {
		return (x & y) | ((~x) & z);
	}
	size_t G(size_t x, size_t y, size_t z) {
		return (x & z) | (y & (~z));
	}
	size_t H(size_t x, size_t y, size_t z) {
		return x ^ y ^ z;
	}
	size_t I(size_t x, size_t y, size_t z) {
		return y ^ (x | (~z));
	}

	size_t shiftLeftRotate(size_t num, size_t n) {
		return (num << n) | (num >> (32 - n));
	}

	// 经过 64轮操作
	//每次操作处理 4 个字节
	void calculateMD5(size_t* chunk);

private:
	size_t _a;
	size_t _b;
	size_t _c;
	size_t _d;
	
	size_t _k[N];
	size_t _sft[N];
	size_t _lastByte;

	const size_t _chunkByte;
	unsigned char _chunk[N];
	unsigned long long _totalByte;
};
