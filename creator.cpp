#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>

using namespace std;

int main(int argc, char *argv[]) {
  std::cout << "Creating the shared segment!" << std::endl;

  int shmid = 0, err = 0;
  int *mem;

  // Create shared memory segment
  shmid = shmget(IPC_PRIVATE, 10, 0666);
  if (shmid == -1) {
    cerr << "Shared Memory: Creation failed" << endl;
  } else {
    cout << "Allocated Shared Memory with ID: " << shmid << endl;
  }

  // Attach the segment
  mem = (int *) shmat(shmid, nullptr, 0);
  if (*(int *) mem == -1) {
    cerr << "Shared Memory: Attachment failed" << endl;
  } else {
    cout << "Attached Shared Memory whose content is: " << *mem << endl;
  }

  *mem = 1;
  cout << "Altered Shared Memory content to: " << *mem << endl;

  // Remove shared memory segment
  // err = shmctl(shmid, IPC_RMID, nullptr);
  // if (err == -1) {
  //   cerr << "Shared Memory: Removal" << endl;
  // } else {
  //   cout << "Shared Memory: Removed Shared Segment with code " << err << endl;
  // }


  return 0;
}
