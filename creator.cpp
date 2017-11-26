/**
 * Operating Systems Project 3
 * Reader and Writers Problem
 * Implementing a starvation free solution
 */

#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>

using namespace std;


int main(int argc, char *argv[]) {
  std::cout << "Creating the shared segment!" << std::endl;

  int shmid = 0;
  int *mem;

  // Create shared memory segment
  shmid = shmget(IPC_PRIVATE, 20*sizeof(int), 0666); // instantiate with size for int[20]
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
    cout << "Attached Shared Memory whose content is: " << mem[1] << endl;
  }

  mem[1] = 1;
  cout << "Altered Shared Memory content to: " << mem[1] << endl;

  // Remove shared memory segment
//  err = shmctl(shmid, IPC_RMID, nullptr);
//  if (err == -1) {
//    cerr << "Shared Memory: Removal" << endl;
//  } else {
//    cout << "Shared Memory: Removed Shared Segment with code " << err << endl;
//  }


  return 0;
}
