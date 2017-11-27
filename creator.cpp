/**
 * Operating Systems Project 3
 * Reader and Writers Problem
 * Implementing a starvation free solution
 */

#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>

using namespace std;

#define DATA_SIZE 20


int main(int argc, char *argv[]) {
  std::cout << "Creating the shared segment!" << std::endl;

  int shmid = 0;
  int *mem;

  // Create shared memory segment
  shmid = shmget(IPC_PRIVATE, DATA_SIZE*(sizeof(pid_t) + sizeof(int)), 0666); // instantiate with size for int[20]
  if (shmid == -1) {
    cerr << "Shared Memory: Creation failed" << endl;
  } else {
    cout << "Allocated Shared Memory with ID: " << shmid << endl;
  }

  // Attach the segment
  mem = (int *) shmat(shmid, nullptr, 0);
  if (*mem == -1) {
    cerr << "Shared Memory: Attachment failed" << endl;
  } else {
    cout << "Attached Shared Memory" << endl;
  }

  for (int i = 0; i < DATA_SIZE; i++) {
    mem[i] = i;
  }

  return 0;
}
