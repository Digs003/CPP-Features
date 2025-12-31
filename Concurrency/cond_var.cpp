#include <mutex>
#include <condition_variable>
#include <queue>


std::mutex mtx;
std::condition_variable cv;
std::queue<data_chunk> data_queue;

void data_preparation_thread() {
  while(more_data_to_prepare()){
    data_chunk const data = prepare_data();
    {
      std::lock_guard<std::mutex> lk(mtx);
      data_queue.push(data);
    }
    cv.notify_one();
  }
}

void data_processing_thread() {
  while(true)
  {
    std::unique_lock<std::mutex> lk(mtx);
    cv.wait(lk, []{return !data_queue.empty();});
    data_chunk data = data_queue.front();
    data_queue.pop();
    lk.unlock();
    process_data(data);
    if(is_last_chunk(data))
      break;
  }
}

