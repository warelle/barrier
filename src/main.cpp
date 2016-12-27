#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include "barrier_cond.hpp"

void runblocking(BarrierCond::BarrierCond* bc){
  std::cout << std::this_thread::get_id() << " enter blocking barrier" << std::endl;
  bc->BarrierBlocking();
  std::cout << std::this_thread::get_id() << " leave blocking barrier" << std::endl;
}

void blockingtest(int thnum){
  std::vector<std::thread> threads;
  BarrierCond::BarrierCond bc(thnum+1);

  for(int i=0; i<thnum; i++){
    threads.push_back(std::thread(runblocking, &bc));
  }

  std::cout << std::this_thread::get_id() << " sleep 1sec" << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cout << std::this_thread::get_id() << " wake up" << std::endl;

  bc.BarrierBlocking();
  for(int i=0; i<thnum; i++){
    threads[i].join();
  }
}
void runnonblocking(BarrierCond::BarrierCond* bc){
  std::cout << std::this_thread::get_id() << " enter blocking barrier" << std::endl;
  while(true){

    if(bc->BarrierNonBlocking(BarrierCond::SLAVE)){
      break;
    }
  }
  std::cout << std::this_thread::get_id() << " leave blocking barrier" << std::endl;
}

void nonblockingtest(int thnum){
  std::vector<std::thread> threads;
  BarrierCond::BarrierCond bc(thnum+1, false);

  for(int i=0; i<thnum; i++){
    threads.push_back(std::thread(runnonblocking, &bc));
  }

  std::cout << std::this_thread::get_id() << " sleep 1sec" << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cout << std::this_thread::get_id() << " wake up" << std::endl;

  bc.BarrierNonBlocking(BarrierCond::MASTER);
  for(int i=0; i<thnum; i++){
    threads[i].join();
  }
}

int main(){
  blockingtest(4);
  nonblockingtest(4);

  return 0;
}
