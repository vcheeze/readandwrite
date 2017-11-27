/**
 * Operating Systems Project 3
 * Reader and Writers Problem
 * Implementing a starvation free solution
 */

#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>

using namespace std;

#define DATA_SIZE 20
#define CTRL_SIZE 3*sizeof(sem_t) + sizeof(int)


int main(int argc, char *argv[]) {
  std::cout << "Creating the shared segment!" << std::endl;

  int shmid = 0;
  int *mem, *data;

  // Create shared memory segment: size of semaphores + int
  shmid = shmget(IPC_PRIVATE, CTRL_SIZE + DATA_SIZE*sizeof(int), 0666); // instantiate with size for int[20]
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
  data = mem + CTRL_SIZE;

  for (int i = 0; i < DATA_SIZE; i++) {
    data[i] = i;
  }

  return 0;
}
