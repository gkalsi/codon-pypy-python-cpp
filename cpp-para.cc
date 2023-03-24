#include <cstdint>
#include <iostream>
#include <mutex>
#include <thread>
#include <utility>
#include <vector>

constexpr uint32_t kThreadCount = 4;

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

class Coordinator {
 public:
  explicit Coordinator(uint64_t range_start, uint64_t range_end, uint64_t chunk_size)
    : chunk_size_(chunk_size)
    , range_end_(range_end)
    , next_start_(range_start) {}

  explicit Coordinator(uint64_t range_start, uint64_t range_end)
    : Coordinator(range_start, range_end, kDefaultChunkSize) {}

  bool GetNextRange(uint64_t* start, uint64_t* end) {
    std::lock_guard<std::mutex> m(chunk_mutex_);

    if (next_start_ >= range_end_) return false;  // No more range left.

    *start = next_start_;
    *end = std::min(range_end_, next_start_ + chunk_size_);

    next_start_ = *end;

    return true;
  }

  void Accumulate(uint64_t n) {
    std::lock_guard<std::mutex> m(total_mutex_);
    total_ += n;
  }

  uint64_t Total() const { return total_; }

 private:
  std::mutex chunk_mutex_;
  static constexpr uint64_t kDefaultChunkSize = 100;
  const uint64_t chunk_size_;
  const uint64_t range_end_;
  uint64_t next_start_;

  std::mutex total_mutex_;
  uint64_t total_ = 0;
};

void Worker(Coordinator* c) {
  uint64_t range_start, range_end;
  while(c->GetNextRange(&range_start, &range_end)) {
    uint64_t range_total = 0;
    for (uint64_t i = range_start; i < range_end; i++) {
      if (is_prime(i)) range_total += 1;
    }
    c->Accumulate(range_total);
  }
}


int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "usage: " << argv[0] << " <limit>" << std::endl;
    return -1;
  }

  uint64_t limit = std::stoul(argv[1]);
  Coordinator c(2, limit);

  std::vector<std::thread> workers;

  for (uint64_t i = 0; i < kThreadCount; i++) {
    workers.emplace_back(Worker, &c);
  }

  for (auto& w : workers) {
    w.join();
  }

  std::cout << "Found " << c.Total() << " primes between 2 and " << limit 
            << std::endl;

  return 0;
}