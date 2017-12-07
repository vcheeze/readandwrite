//
// Created by Peeta on 11/26/17.
//

#include <iostream>
#include <sys/shm.h>
#include <unistd.h>
#include <semaphore.h>

using namespace std;

#define DATA_SIZE 20
#define CTRL_SIZE (3*sizeof(sem_t) + sizeof(int))


int main(int argc, char *argv[]) {
  if (argc != 8) {
    cerr << ">> Please enter command in this format: ./writer -r lb ub -d time -s shmid" << endl;
    return -1;
  }

  int lb = 0, ub = 0, shmid = 0, err = 0, i, r, retval;
  unsigned int time = 0;
  int *data;
  sem_t *rw_mutex, *mutex, *turn;

  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-r") == 0) {        // range: followed by lower bound and upper bound
      lb = stoi(argv[i+1]);
      ub = stoi(argv[i+2]);
    } else if (strcmp(argv[i], "-d") == 0) { // number of lines in file to be sorted
      time = static_cast<unsigned int>(stoi(argv[i + 1]));
    } else if (strcmp(argv[i], "-s") == 0) { // number of sorter nodes to be created
      shmid = stoi(argv[i+1]);
    }
  }

  cout << ">> Shared Memory Segment ID: " << shmid << endl;
  cout << ">> Lower Bound: " << lb << " | " << "Upper Bound: " << ub << endl;
  cout << ">> Time: " << time << endl;

  // attachment
  rw_mutex = (sem_t *) shmat(shmid, nullptr, 0);
  if (rw_mutex == (void *) -1) {
    cerr << ">> Writer: Attachment" << endl;
  } else {
    cout << ">> Writer: Attached to Shared Memory Segment whose content is: " << *rw_mutex << endl;
  }

  data = rw_mutex + CTRL_SIZE;
  mutex = rw_mutex + sizeof(sem_t);
  turn = rw_mutex + 2*(sizeof(sem_t));

  // initialize the semaphores
  rw_mutex = sem_open("rw_mutex", O_CREAT|O_EXCL, S_IRUSR|S_IWUSR, 1);
  if (rw_mutex != SEM_FAILED) {
    cout << ">> Created semaphore rw_mutex" << endl;
  } else if (errno == EEXIST) {
    cerr << ">> Writer: semaphore rw_mutex exists already" << endl;
    rw_mutex = sem_open("rw_mutex", 0);
  }
  mutex = sem_open("mutex", O_CREAT|O_EXCL, S_IRUSR|S_IWUSR, 1);
  if (mutex != SEM_FAILED) {
    cout << ">> Created semaphore mutex" << endl;
  } else if (errno == EEXIST) {
    cerr << ">> Writer: semaphore mutex exists already" << endl;
    mutex = sem_open("mutex", 0);
  }
  turn = sem_open("turn", O_CREAT|O_EXCL, S_IRUSR|S_IWUSR, 1);
  if (turn != SEM_FAILED) {
    cout << ">> Created semaphore turn" << endl;
  } else if (errno == EEXIST) {
    cerr << ">> Writer: semaphore turn exists already" << endl;
    turn = sem_open("turn", 0);
  }

  sem_wait(turn);
  sem_wait(rw_mutex);
//  sem_post(turn);

  // Perform write
  for (i = lb; i <= ub; i++) {
    r = rand() % 30 + 20; // random number from 20 - 50
    data[i] = r;
  }

  // Print data
  cout << ">> Writer: wrote data from Shared Memory Segment: " << endl;
  for (i = 0; i < DATA_SIZE; i++) {
    cout << ">> " << data[i] << endl;
  }

  sleep(time);

  sem_post(rw_mutex);
  sem_post(turn);

  err = shmdt((void *) rw_mutex);
  if (err == -1) {
    cerr << ">> Writer: Detachment" << endl;
  } else {
    cout << ">> Writer: Detached from Shared Memory Segment with code " << err << endl;
  }

  return 0;
}
