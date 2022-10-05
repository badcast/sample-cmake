#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <cstring>

#include "import.h"

intmax_t diff = 0;
intmax_t ms() { return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() - diff; }

intmax_t msx;
intmax_t msy;
void start() { msx = ms(); }

void stop() { msy = ms(); }

intmax_t elapse() { return msy - msx; }

void printDelayed() {

    printf("(%d millisec)\n", elapse());
}

void test(void) {
    unsigned long n = std::pow(2, 27);
    void* buffer;
    while((buffer = malloc(n))==nullptr){
        n /= 2;
    }

    diff = ms();

    std::cout << "test 8bit: ";
    start();
    dll::sample_for_8bit((char*)buffer, n);
    stop();
    printDelayed();

    std::cout << "test 16bit: ";
    start();
    dll::sample_for_16bit(buffer, n);
    stop();
    printDelayed();

    std::cout << "test 32bit: ";
    start();
    dll::sample_for_32bit(buffer, n);
    stop();
    printDelayed();

    std::cout << "test 64bit: ";
    start();
    dll::sample_for_64bit(buffer, n);
    stop();
    printDelayed();

    std::cout << "memset: ";
    start();
    std::memset(buffer, 0, n);
    stop();
    printDelayed();
    
    free(buffer);
}

int main() {
  time_t t = time(0);
  const int number = localtime(&t)->tm_yday;
  char buf[1024];
  std::vector<int> numbers_unsorted(1024);
  for (uint32_t x = 0; x < numbers_unsorted.size(); ++x) {
    numbers_unsorted[x] = rand() % 1024;
  }

  std::cout << "Get Module Text: " << dll::sample_module_text() << std::endl;
  std::cout << "Number get: " << number << std::endl;
  std::cout << "DLL (convert to string): " << (dll::sample_to_string(buf, number))
            << std::endl;
  std::cout << "DLL (convert string to long): " << dll::sample_to_int64(buf)
            << std::endl;
  std::cout << "DLL sorting: " << numbers_unsorted.size() << " elements"
            << std::endl;
  dll::sample_quickSort(numbers_unsorted, 0, numbers_unsorted.size() - 1);
  std::cout << "DLL sorted: "
            << (dll::sample_checkSort2(numbers_unsorted) ? "Yes" : "No") << std::endl;
  std::cout << "Compare 2 strings: Mike, Mike" << std::endl;
  std::cout << "DLL Compare result: " << dll::sample_compare("Mike", "Mike")
            << std::endl;
  std::cout << "Run long list: ";
  numbers_unsorted = *dll::sample_get_data();
  std::cout << numbers_unsorted.size();
  std::cout << (numbers_unsorted.size() > 0 ? " ok" : " fail") << std::endl;
  
  test(); // Run test
  
  std::cout << "Completed operations from DLL" << std::endl;
  std::cout.flush();
  return 0;
}
