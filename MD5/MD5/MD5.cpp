
#include "MD5.h"

MD5::MD5():_chunkByte(N){
	init();
	memset(_chunk, 0, _chunkByte);
	_totalByte = _lastByte =  0;

}

std::string MD5::getStringMD5(const std::string& str) {
	if (str.empty()) {
		return"";
	} else {
		unsigned char* pstr = (unsigned char*)str.c_str();
		size_t num_Chunk = str.size() / _chunkByte;
		for (size_t i = 0; i < num_Chunk; ++i) {
			_totalByte += _chunkByte;
			calculateMD5((size_t*)pstr + i * _chunkByte);
		}

		_lastByte = str.size() % _chunkByte;
		memcpy(_chunk, pstr + _totalByte, _lastByte);
		calculateMD5Final();
	}
	return changeHex(_a) + changeHex(_b) + changeHex(_c) + changeHex(_d);

}

std::string MD5::getFiledMDd5(const char* filename) {
	std::ifstream fin(filename,std::ifstream::binary);
	if (fin.is_open()) {
		while (!fin.eof()) {
			fin.read((char*)_chunk, _chunkByte);
			if (_chunkByte != fin.gcount())
				break;

			_totalByte += _chunkByte;
			calculateMD5((size_t*)_chunk);
		}
		_lastByte = fin.gcount();
		_totalByte += _lastByte;
		calculateMD5Final();
	}

	return (changeHex(_a) + changeHex(_b) + changeHex(_c) + changeHex(_d));
}

std::string MD5::changeHex(size_t num) {
	static std::string strMap = "0123456789abcdef";
	std::string ret;
	std::string byteStr;
	for (int i = 0; i < 4; ++i) {
		byteStr = "";
		size_t b = (num >> (i * 8)) & 0xff;
		for (int j = 0; j < 2; ++j) {
			byteStr.insert(0, 1, strMap[b % 16]);
			b /= 16;
		}
		ret += byteStr;
	}
	return ret;
}

void MD5::init(){
	// ��ʼ�� ABCD
	_a = 0x67452301;
	_b = 0xefcdab89;
	_c = 0x98badcfe;
	_d = 0x10325476;

	size_t s[] = { 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7,
					12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
					4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10,
					15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21 };
	// TODO

	memcpy(_sft, s, sizeof(s));
	// k[i] 2^32 * abs(sin(i))
	for (int i = 0; i < 64; ++i) {
		_k[i] = (size_t)(pow(2, 32)*abs(sin(i + 1)));
	}
}


void MD5::calculateMD5Final() {
	// lastByte�� С��64���ֽڣ���ʾ���һ�����ݴ�С
	unsigned char* p = _chunk + _lastByte;
	//���λ��ǰ��λ : 1000 0000 0x80 
	*p++ = 0x80;
	size_t remainFillByte = _chunkByte - _lastByte - 1;
	// ʣ������ֽ��� С��8 ���ֽ�
	if (remainFillByte < 8) {
		// ����һ���Լ�����ʼ ȫ���� 0
		memset(p, 0, remainFillByte);
		calculateMD5((size_t*)_chunk);
		memset(_chunk, 0, _chunkByte);
	} else {
		// ��� 0 �� ʣ���ֽ��� ���ڵ��� 8 ���ֽ�  8���ֽ�ǰ �м�ȫ���� 0 
		memset(p, 0, remainFillByte);
	}
	// ����64 bit ���ԭʼ�ĵ���bit����
	
	// char ���� ���Χ 256 �������� ����Ҫ��long long ���ʹ��
	//_chunk = _totalByte * 8;
	((unsigned long long*) _chunk)[7] = _totalByte * 8;
	calculateMD5((size_t*)_chunk);

}


void MD5::calculateMD5(size_t* chunk) {

	size_t a = _a;
	size_t b = _b;
	size_t c = _c;
	size_t d = _d;
	// chunk[g]
	// f �� ��ϣ��������ֵ 
	size_t f, g;



	// 64 �α任�� 4�ֲ�����ÿһ�ֲ�����16�Ӳ���

	for (size_t i = 0; i < 64; ++i) {
		/*
		if (0 <= i < 16) g = i;
		if (16 <= i < 32) g = (5 * i + 1) % 16;
		if (32 <= i < 48) g = (3 * i + 5) % 16;
		if(48 <= i < 63) g = (7 * i) % 16;*/

		/*
		F(x,y,z) = (x & y) | ((~x) & z)
		G(x,y,z) = (x & z) | ( y & (~z))
		H(x,y,z) = x ^ y ^ z
		I(x,y,z) = y ^ (x | (~z))
		*/
		if (0 <= i && i < 16) {
			f = F(b, c, d);
			g = i;
		}
		if (16 <= i && i < 32) {
			f = G(b, c, d);
			g = (5 * i + 1) % 16;
		}
		if (32 <= i && i < 48) {
			f = H(b, c, d);
			g = (3 * i + 5) % 16;
		}
		if (48 <= i && i < 64) {
			f = I(b, c, d);
			g = (7 * i) % 16;
		}

		size_t dtmp = d;
		d = c;
		c = b;
		b = b + shiftLeftRotate(a + f + _k[i]+chunk[g], _sft[i]);
		a = dtmp;
	}

	_a += a;
	_b += b;
	_c += c;
	_d += d;
}