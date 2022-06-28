#include <iostream>
#include <random>

#include "import.h"

int main() {
    time_t t = time(0);
    const int number = localtime(&t)->tm_yday;
    char buf[1024];
    std::vector<int> numbers_unsorted(1024);
    for (uint32_t x = 0; x < numbers_unsorted.size(); ++x) {
        numbers_unsorted[x] = rand() % 1024;
    }

    std::cout << "Get Module Text: " << dll::module_text() << std::endl;
    std::cout << "Number get: " << number << std::endl;
    std::cout << "DLL (convert to string): " << (dll::to_string(buf, number)) << std::endl;
    std::cout << "DLL (convert string to long): " << dll::to_int64(buf) << std::endl;
    std::cout << "DLL sorting: " << numbers_unsorted.size() << " elements" << std::endl;
                                dll::quickSort(numbers_unsorted, 0, numbers_unsorted.size() - 1);
    std::cout << "DLL sorted: " << (dll::checkSort2(numbers_unsorted) ? "Yes" : "No") << std::endl;
    std::cout << "Compare 2 strings: Mike, Mike" << std::endl;
    std::cout << "DLL Compare result: "<< dll::compare("Mike", "Mike") << std::endl;
    std::cout << "Completed operations from DLL" << std::endl;
    return 0;
}
