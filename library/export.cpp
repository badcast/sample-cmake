#include <cmath>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

#ifndef __linux__
#define EXPORT extern "C" __declspec(dllexport)
#else
#define EXPORT extern "C"
#endif

using namespace std;

EXPORT const char* module_text() { return "This is text from module "; }

EXPORT char* to_string(char* buf, long value) {
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

EXPORT long to_int64(const char* str) {
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

EXPORT bool checkSort(vector<int>& check, bool toRight) {
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

EXPORT bool checkSort2(vector<int>& check) {
    if (checkSort(check, true) || checkSort(check, false)) return true;
    return false;
}

EXPORT void quickSort(vector<int>& a, const int& l, const int& r) {
    if (r - l < 1) return;

    int p1 = l;
    int p2 = r;
    // 1. Выбрать случайный элемент в сортируемой части
    int p = a[(l + r) / 2];
    // 2. Сделать так, чтоб в левой подчасти были элементы меньше выбранного, в правой - все остальные
    for (; p1 < p2; a[p1] < p ? ++p1 : --p2)
        if (a[p1] > a[p2]) swap(a[p1], a[p2]);

    // 3. Отсортировать отдельно левую и правую подчасть
    quickSort(a, l, p1 - 1);
    quickSort(a, p1 + 1, r);
}

EXPORT int compare(string s1, string s2) {
    int32_t r = -1;  // результат
    uint32_t i, j = 0;
    for (i = 0; i < s1.size(); ++i) {
        if (j == s2.size()) break;
        if (s1[i] == s2[j]) {
            if (r == -1) r = i;
            ++j;
        } else {
            if (r != -1) i = r + 1;
            r = -1;
            j = 0;
        }
    }
    return r;
}
