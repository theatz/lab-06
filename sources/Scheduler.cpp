// Copyright 2020 Your Name <your_email>

#include <Scheduler.hpp>

std::mutex lock;
std::queue<ToFile> success;
std::string FileName;
volatile bool Write;
volatile bool Work;

ToFile finder() {
  const std::string expected = "0000";
  std::string data = std::to_string(std::rand());
  std::string hash = picosha2::hash256_hex_string(data);
//  if (hash.substr(hash.size() - expected.size()) == expected) {
//  auto js = nlohmann::json::object();
//  js["timestamp(ms)"] = data;
//  js["hash"] = hash;
//  js["data"] = data;
//  }
  return ToFile{data, hash, data};
}

Scheduler::Scheduler(std::atomic_int& sig)
    : _sig(sig), _work(true), _logger(){
  for (uint32_t i = 0; i < 5; i++)
    _threads.emplace_back(&Scheduler::Work, this);
  for (auto& worker : _threads)
    if (worker.joinable()) worker.join();
}

Scheduler::Scheduler(std::atomic_int& sig, int count)
    : _sig(sig), _work(true), _logger() {
  for (uint32_t i = 0; i < count; i++)
    _threads.emplace_back(&Scheduler::Work, this);
  for (auto& worker : _threads)
    if (worker.joinable()) worker.join();
}

Scheduler::Scheduler(std::atomic_int& sig, int count, std::string& file_name)
    : _sig(sig), _work(true), _logger(file_name) {
  for (uint32_t i = 0; i < 1; i++)
    _threads.emplace_back(&Scheduler::Work, this);
  _threads.emplace_back(&Scheduler::Stop, this);
  for (auto& worker : _threads)
    if (worker.joinable()) worker.join();
}

/*
void Scheduler::HashFinder() {
  const std::string expected = "0000";
  while (_work) {
    std::string data = std::to_string(std::rand());
    std::string hash = picosha2::hash256_hex_string(data);
    if (hash.substr(hash.size() - expected.size()) == expected) {
       BOOST_LOG_TRIVIAL(info) << std::endl
                               << "!found value: ["
                               << data
                               << "] hash is ["
                               << hash << "]!"
                               << std::endl;
      //      if (Write) {
      //        if (lock.try_lock_for(std::chrono::milliseconds(100))) {
      //          ToFile tmp{data, hash, data};
      //          success.push(tmp);
      //          lock.unlock();
      //        }
      auto js = nlohmann::json::object();
      js["timestamp(ms)"] = data;
      js["hash"] = hash;
      js["data"] = data;

      std::unique_lock<std::mutex> ulock(lock);
      _result.push_back(js);
      std::cout << data << std::endl;

      //        std::cout << _result.dump(4) << std::endl;

      //      }
    } /* else {
      BOOST_LOG_TRIVIAL(trace) << std ::endl
                               << "!found value ["
                               << data
                               << "] hash is ["
                               << hash << "]!"
                               << std::endl;
    }
  }
}



void Scheduler::WriteToFile() {
  std::ofstream file(_fileName, std::ios::app);
  if (file.is_open()) file << _result.dump(4);
  _result.clear();
}

void Scheduler::WriteToFileSync() {
  while (_work) {
    {
      if (!_result.empty()) {
        std::ofstream file(_fileName);
        std::unique_lock<std::mutex> ulock(lock);
        if (file.is_open()) file << _result.dump(4);
        _result.clear();
      }
      //      file << _result.dump(4);
      //      _result.clear();
      // std::cout << _result.dump(4) << std::endl;
    }
  }
  //  if (!Work)
  //    while (!success.empty()) {
  //      std::cout << _result[0]["hash"] << std::endl;
  //      success.pop();
  //    }
}

*/

void Scheduler::Stop() {
  while (_work) {
    if (_sig == 2) {
      _work = false;
      std::cout << "End" <<std::endl;
    }
  }
}




void Scheduler::Work() {
  while (_work) {
    auto info = finder();
    std::unique_lock<std::mutex> ulock(lock);
    _logger << info;
  }
}
