#define EXPORT_SAMPLE

#include <cmath>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

#include <cstdio>
#include <cstdlib>

#include "import.h"

using namespace std;

	constexpr long long  value = -1;
	template <typename targetType>
	void* sample_for_bit(void* buf, int len) {
		int y = len / sizeof(targetType);
		targetType* _start = static_cast<targetType*>(buf);
		targetType* _end = static_cast<targetType*>(buf) + y;
		for (; _start < _end; ++_start) *_start = value;

		char* h = (char*)_start;
		char* h2 = (char*)buf + len;
		for (; h < h2; ++h) *h = -1;
		return buf;
	}

namespace dll {
	PORT const char* sample_module_text() { return "This is text from module "; }

	PORT std::vector<int>* sample_get_data() {
		static std::vector<int> longl = std::vector<int>(1024, -1);
		for (int x = 0; x < longl.size(); ++x) {
			longl[x] = x;
		}
		return &longl;
	}

	PORT char* sample_to_string(char* buf, long value) {
		unsigned short levels = 0;
		unsigned long long digits = 1;
		unsigned char sign = value < 0;
		unsigned short i = 0;
		long x = value = std::abs(value);
		long y = 0;

		do {
			++levels;
			digits *= 10;
		} while (value / digits != 0);
		digits /= 10;

		for (i = 0; i < levels; ++i, digits /= 10) {
			x = x / digits;
			buf[i + sign] = x;
			x = value - x * digits - y;
			y += buf[i + sign] * digits;
			buf[i + sign] += 48;
		}
		buf[i] = '\0';
		return buf;
	}

	PORT long sample_to_int64(const char* str) {
		long target = 0;
		unsigned char x = 80;  // 10 reserve
		if (*str == '-') {
			x |= 0x80;  // write sign
			str++;
		}
		for (; *str >= '0' && *str <= '9'; ++str) {
			x = ((*str - 48) & 0xf) | (x & 0xF0);  // char to int number
			target *= (x & 0x50) >> 3;
			target += x & 0xf;
		}

		if (x & 0x80)  // is sign
			target *= ~0;
		return target;
	}

	PORT bool sample_checkSort(vector<int>& check, bool toRight) {
		size_t sz = check.size() - 1;
		size_t i = 0;
		if (toRight)
			for (; i < sz; ++i) {
				if (*(check.data() + i) > *(check.data() + i + 1)) return false;
			}
		else
			for (; i < sz; ++i) {
				if (*(check.data() + i) < *(check.data() + i + 1)) return false;
			}
		return true;
	}

	PORT bool sample_checkSort2(vector<int>& check) {
		if (sample_checkSort(check, true) || sample_checkSort(check, false)) return true;
		return false;
	}

	PORT void sample_quickSort(vector<int>& a, const int& l, const int& r) {
		if (r - l < 1) return;

		int p1 = l;
		int p2 = r;
		// 1. Выбрать случайный элемент в сортируемой части
		int p = a[(l + r) / 2];
		// 2. Сделать так, чтоб в левой подчасти были элементы меньше выбранного, в правой - все остальные
		for (; p1 < p2; a[p1] < p ? ++p1 : --p2)
			if (a[p1] > a[p2]) swap(a[p1], a[p2]);

		// 3. Отсортировать отдельно левую и правую подчасть
		sample_quickSort(a, l, p1 - 1);
		sample_quickSort(a, p1 + 1, r);
	}

	PORT int sample_compare(string s1, string s2) {
		int32_t r = -1;  // результат
		uint32_t i, j = 0;
		for (i = 0; i < s1.size(); ++i) {
			if (j == s2.size()) break;
			if (s1[i] == s2[j]) {
				if (r == -1) r = i;
				++j;
			}
			else {
				if (r != -1) i = r + 1;
				r = -1;
				j = 0;
			}
		}
		return r;
	}

	PORT void* sample_for_8bit(char* buf, int len) {
		char* end = buf + len;
		for (; buf < end; ++buf) *buf = value;
		return buf;
	}

	PORT void* sample_for_16bit(void* buf, int len){
		return sample_for_bit<short>(buf,len);
	}

	PORT void* sample_for_32bit(void* buf, int len) {
		return sample_for_bit<int>(buf,len);
	}

	PORT void* sample_for_64bit(void* buf, int len)
	{
		return sample_for_bit<long long>(buf,len);
	}
}
