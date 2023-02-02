This homework is for the Abdullah Gül University Operating Systems' HW2.
The Code is the one of the solution to the dining philosophers with some parameters.

The MAKEFILE is working on UBUNTU/LINUX. In order to run this cod on a Windows machine, you can download needed OS(Ubuntu) with VM (Virtual Machine).

First, You just need to type to the terminal "make".

After make, you just need to give the sample input such as:

./phsp 5 500 1000 50 100 exponential 20



The Dining Philosophers Problem: N philosophers are sitting at a round table. In the center of the table, there is a bowl of rice. Between each pair of philosopher is a single chopstick. A philosopher is in one of three states: thinking, hungry and eating. At various times a thinking philosopher gets hungry. A hungry philosopher attempts to pick up one of the adjacent chopsticks, then the other one (not both at the same time). If the philosopher is able to obtain the pair of chopsticks, then the philosopher eats for a period of time. After eating, the philosopher puts the chopsticks down and returns thinking.     

In this project, you are supposed to write a program for the dining philosopher problem, which will implement a deadlock-free solution with maximum concurrency. The program should work for any number of philosophers (odd numbers, maximum 27). In the program, a thread will express a philosopher. These threads will be spawned by the main thread, which is not a philosopher. You need to use Pthreads, mutex and condition variables to synchronize. You can use monitor based solutions or semaphores that are deadlock free. The program will be named phsp and will take the following arguments: phsp <num_phsp> <min_think> <max_think> <min_dine> <max_dine> <dst> <num>
For the arguments; <min_think> is the minimum thinking time for a philosopher, <max_think> is the maximum thinking time; <min_dine> is the minimum dining time, <max_dine> is the maximum dining time. Use miliseconds as unit. The highest value that these parameters can take is 60seconds and lowest value that these parameters can take is 1ms. <dst> is the distribution and it can be either “uniform” or “exponential”. The mean parameters for exponential distributions are (min_think+max_think)/2 or (min_dine+max_dine)/2. The thinking time and dining time for a philosopher will be selected randomly according to the specified dst and the mean value. For exponential distribution; simply generate a random value with exponential distribution; and if the value is not in range, repeat it. Each philosopher will dine <num> times. The program should terminate after all of the philosophers complete dining (num times).
A sample initiation could be:
phsp 5 500 1000 50 100 exponential 100

