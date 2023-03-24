#include <iostream>
#include <cstdint>

bool is_prime(uint64_t n) {
  // This is not a very efficient way of testing if a number is prime but
  // we're using it to maintain parity with the python code.
  unsigned int factors = 0;
  for (uint64_t i = 2; i < n; i++) {
    if (n % i == 0) {
      factors++;
    }
  }
  return factors == 0;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "usage: " << argv[0] << " <limit>" << std::endl;
    return -1;
  }

  uint64_t limit = std::stoul(argv[1]);
  uint64_t total = 0;

  for (uint64_t i = 2; i < limit; i++) {
    if (is_prime(i)) total += 1;
  }

  std::cout << "Found " << total << " primes between 2 and " << limit 
            << std::endl;

  return 0;
}