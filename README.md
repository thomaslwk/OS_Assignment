# Operating Systems Assignment
Documentation for OS module assignment. 

## Task 1: Improved Round Robin CPU Scheduling Algorithm 
Paper (5): Round Robin, Shortest Job First and Priority algorithm coupled to increase throughput and decrease waiting time and turnaround time. 

### Algorithm input 
Input Requirement: 
* Number of process 
* Time quantum 
* Burst time for each process 
* Arrival time for process 
* Priority level for process (value 1 to 3) 


Format: 
`no. of process, time quantum, burst time, arrival time, priority`

### Replication of Results 

* Test Case (1): `./p5_testinput < input_test_1.txt`
<img width="600" alt="test1" src="https://user-images.githubusercontent.com/26267783/114757773-d8042800-9d8e-11eb-9d7d-becf32c91079.png">

* Test Case (2): `./p5_testinput < input_test_2.txt`
<img width="600" alt="test2" src="https://user-images.githubusercontent.com/26267783/114758032-1a2d6980-9d8f-11eb-84b6-6888750ac201.png">

## Task 2: Race Condition Simulation with Process 
C program to illustrate Race condition. Requires minimal use of 5 processes and 3 resources. 

### Design and Analysis 
<img width="600" alt="design1" src="https://user-images.githubusercontent.com/26267783/114759304-95434f80-9d90-11eb-9ff5-dac1a6bcf711.png">
The program will first create a shared semaphore which will be used by all the processes when it begins the process of reading and writing to file. It will create 3 text files for the processes to write to. The program will create 6 processes in total, 5 child processes and 1 parent process.
<img width="420" alt="design2" src="https://user-images.githubusercontent.com/26267783/114759442-bb68ef80-9d90-11eb-92df-18d1e9829ea8.png">
The diagram above shows the interaction between the different processes and files. The lock icon is used to simulate the presence of the shared binary semaphore which provides mutual exclusion to the 3 files (jar1, jar2, jar3).

### Results 
#### Mitigated Race Condition - Using Semaphores
<img width="440" alt="race1" src="https://user-images.githubusercontent.com/26267783/114759665-0be04d00-9d91-11eb-92f8-42272aefee28.png">
Section screenshots of program output with use of semaphore. We can observe that the 5 processes (bear) are executed at random but only one process (bear PID) has access to the file (jar1, jar2, jar3) each time. This results in each process incrementing the existing value by 5. With 5 processes, the final value in each file will be consistent and will always be 5.

#### Forced Race Condition - Without Semaphore
<img width="590" alt="race2" src="https://user-images.githubusercontent.com/26267783/114759857-4649ea00-9d91-11eb-9e54-6472abd6ecac.png">
Section screenshots of program output without the use of semaphore. We can observe that the 5 processes (bear) are executed at the same time and all the processes (bear PID) are reading and writing to the same file (jar1, jar2, jar3) at the same time. The write to file method should allow each process to increment the file by 5. However, from the results we can observe that each jar contains a different value and the result is inconsistent due to the race condition.


