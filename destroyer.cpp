//
// Created by Peeta on 11/26/17.
//

#include <iostream>
#include <sys/shm.h>

using namespace std;

int main(int argc, char *argv[]) {
  cout << "Destroying Shared Memory Segment!" << endl;
  int shmid = stoi(argv[2]), err = 0;

  err = shmctl(shmid, IPC_RMID, nullptr);
  if (err == -1) {
    cerr << "Shared Memory: Removal" << endl;
  } else {
    cout << "Shared Memory: Removed Shared Segment with code " << err << endl;
  }

  return 0;
}
