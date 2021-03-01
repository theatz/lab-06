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

#include "Logging.hpp"
#include "picosha2.h"

struct ToFile {
  std::string data;
  std::string hash;
  std::string time;
};



class Worker {


 public:
  Worker(volatile std::atomic_int& sig, int count);
  Worker(volatile std::atomic_int& sig);
  Worker(volatile std::atomic_int& sig, int count, std::string& file_name);

  void Stop();


  ~Worker();
//  void Interupt(volatile std::atomic_int& sig);
  void WriteToFileSync();
  void WriteToFile();
  void HashFinderWriteToFile();
  void HashFinder();

 private:
  std::vector<std::thread> _threads;
  volatile std::atomic_bool _work;
  nlohmann::json _result;
  std::string _fileName;
  volatile std::atomic_int& _sig;
};

#endif  // INCLUDE_HEADER_HPP_
