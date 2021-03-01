#include <Worker.hpp>
#include <iostream>
#include <thread>
#include <vector>

volatile std::atomic_int sig;

void Interupt(int i) {
    std::cout << i << std::endl;
    sig = i;
}

int main() {
  sig = 0;
  std::string filename = "check";
  signal(SIGTERM, Interupt);
  signal(SIGINT, Interupt);
  Worker(sig, 8, filename);


  return 0;
}