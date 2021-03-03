// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <algorithm>
#include <chrono>
#include <csignal>
#include <mutex>
#include <nlohmann/json.hpp>
#include <queue>
#include <string>
#include <thread>
#include <atomic>

#include "Logger.hpp"
#include "picosha2.h"




class Scheduler {
 public:
  Scheduler(std::atomic_int& sig, int count);
  Scheduler(std::atomic_int& sig);
  Scheduler(std::atomic_int& sig, int count, std::string& file_name);

  void Stop();


  ~Scheduler() = default;
//  void Interupt(volatile std::atomic_int& sig);
  void WriteToFileSync();
  void Work();
  void Task();
  void WriteToFile();
  void HashFinderWriteToFile();
  void HashFinder();

 private:
  std::vector<std::thread> _threads;
  volatile std::atomic_bool _work;
  Logger _logger;
  std::atomic_int& _sig;
};

#endif  // INCLUDE_HEADER_HPP_
