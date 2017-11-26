#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>

using namespace std;

int main(int argc, char *argv[]) {
  std::cout << "Creating the shared segment!" << std::endl;

  int id = 0;
  int *mem;

  // Create shared memory segment
  id = shmget(IPC_PRIVATE, 10, 0666);
  if (id == -1) {
    cerr << "Shared Memory: Creation failed" << endl;
  } else {
    cout << "Allocated Shared Memory with ID: " << id << endl;
  }

  // Attach the segment
  mem = (int *) shmat(id, nullptr, 0);
  if (*(int *) mem == -1) {
    cerr << "Shared Memory: Attachment failed" << endl;
  } else {
    cout << "Attached Shared Memory whose content is: " << *mem << endl;
  }

  *mem = 1;
  cout << "Altered Shared Memory content to: " << *mem << endl;

  return 0;
}
