//
// Created by Peeta on 11/26/17.
//

#include <iostream>
#include <sys/shm.h>

using namespace std;


int main(int argc, char *argv[]) {
  if (argc != 8) {
    cerr << "Please enter command in this format: ./reader -r lb ub -d time -s shmid" << endl;
    return -1;
  }

  int lb = 0, ub = 0, time = 0, shmid = 0, err = 0;
  int *mem;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-r") == 0) {        // range: followed by lower bound and upper bound
      lb = stoi(argv[i+1]);
      ub = stoi(argv[i+2]);
    } else if (strcmp(argv[i], "-d") == 0) { // number of lines in file to be sorted
      time = stoi(argv[i+1]);
    } else if (strcmp(argv[i], "-s") == 0) { // number of sorter nodes to be created
      shmid = stoi(argv[i+1]);
    }
  }

  cout << "Shared Memory Segment ID: " << shmid << endl;
  cout << "Lower Bound: " << lb << " | " << "Upper Bound: " << ub << endl;
  cout << "Time: " << time << endl;

  mem = (int *) shmat(shmid, nullptr, 0);
  if (*mem == -1) {
    cerr << "Reader: Attachment" << endl;
  } else {
    cout << ">> Reader: Attached to Shared Memory Segment whose content is: " << *mem << endl;
  }

  err = shmdt((void *) mem);
  if (err == -1) {
    cerr << "Reader: Detachment" << endl;
  } else {
    cout << ">> Reader: Detached from Shared Memory Segment with code " << err << endl;
  }

  return 0;
}
