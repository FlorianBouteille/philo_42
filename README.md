#Philosophers

This is the classic philosophers problem. 

It consists in creating a simulation in which philosophers are sitting aroung a round table and have to alternatively eat, sleep and think.
The amount of philosophers is given as a parameter of the program, as well as how long it takes them to eat, sleep and starve to death if they don't eat in time.
Philosphers need two forks to eat, but they have to share forks with their neighbors, this is where the problem begins. As any philosophers cant eat as long as both their neighbors have dropped their forks, we have to organize them so that they get to eat as often as possible to avoid death.

In terms of algorithm, this projects is about threads, mutexes and concurent programming. Each Philospher is represented by a thread and executes is routine at the same time as the others. We first need to make sure that every bit of shared data (such as forks) is protected by a mutex when a philosopher tries to access it.
Then we have to make sure there are no deadlocks, situations where two threads are each holding on to a mutex while waiting for the other one to unlock theirs. 

This project was fun and i nailed it. 
