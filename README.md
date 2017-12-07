# Readers and Writers
Project 3 of Operating Systems class in New York University Abu Dhabi.

Note: this project is designed for MacOS.

## How to run
Enter `make` in the command line in order to compile the files. Run `./creator`
first to create the shared segment. An shmid will print in the terminal. Use
that ID to run the reader and the writer by typing `./reader -r lb ub -d time
-s shmid` or `./writer -r lb ub -d time -s shmid`, where `lb` is the lower
bound of the read/write range, `ub` is the upper bound, **time** is the time
to wait before the reader/writer terminates, and `shmid` is the ID that is
returned by the creator. After reading and writing on the shared segment, free
everything by running `./destroyer -s shmid`, where `shmid` is again the ID
of the shared segment.
