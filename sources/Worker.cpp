// Copyright 2020 Your Name <your_email>

#include <Worker.hpp>

std::mutex lock;
std::queue<ToFile> success;
std::string FileName;
volatile bool Write;
volatile bool Work;

Worker::Worker(volatile std::atomic_int& sig) : _sig(sig) , _work(true) {
  for (uint32_t i = 0; i < 5; i++) _threads.emplace_back(&Worker::HashFinder, this);
  _threads.emplace_back(&Worker::Stop, this);
}

Worker::Worker(volatile std::atomic_int& sig, int count) : _sig(sig) , _work(true) {
  for (uint32_t i = 0; i < count; i++) _threads.emplace_back(&Worker::HashFinder, this);
  _threads.emplace_back(&Worker::Stop, this);
}

Worker::Worker(volatile std::atomic_int& sig, int count, std::string& file_name) : _sig(sig) ,_work(true) {
  for (uint32_t i = 0; i < 1; i++) _threads.emplace_back(&Worker::HashFinder, this);
//  _threads.emplace_back(&Worker::WriteToFile, this);
  _threads.emplace_back(&Worker::Stop, this);
//  _threads[1].join();
  _fileName = file_name + ".json";
}

void Worker::HashFinder() {
  const std::string expected = "0000";
  while (_work) {
    std::string data = std::to_string(std::rand());
    std::string hash = picosha2::hash256_hex_string(data);
    if (hash.substr(hash.size() - expected.size()) == expected) {
      /* BOOST_LOG_TRIVIAL(info) << std::endl
                               << "!found value: ["
                               << data
                               << "] hash is ["
                               << hash << "]!"
                               << std::endl;
                               */
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
    */
  }
}


void Worker::WriteToFile() {
  std::ofstream file(_fileName, std::ios::app);
  if (file.is_open()) file << _result.dump(4);
  _result.clear();
}

void Worker::WriteToFileSync() {
  while (_work) {
    {
      if (_result.size()) {
        std::ofstream file(_fileName);
        std::unique_lock<std::mutex> ulock(lock);
        if (file.is_open()) file << _result.dump(4);
        _result.clear();
      }
//      file << _result.dump(4);
//      _result.clear();
      //std::cout << _result.dump(4) << std::endl;
    }
  }
//  if (!Work)
//    while (!success.empty()) {
//      std::cout << _result[0]["hash"] << std::endl;
//      success.pop();
//    }
}

void Worker::Stop() {
  while (_work) {
//    std::cout << _sig << std::endl;
    if (_sig == 2) {
      _work = false;
      std::cout << "End" << std::endl;
      for (auto& worker : _threads) {
        if (worker.joinable()) worker.join();
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(400));
      if (!_fileName.empty()) WriteToFile();
    }
  }
}

Worker::~Worker()
{
  Stop();
}