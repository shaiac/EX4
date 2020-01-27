# ex4
INTRODUCTION:

Our program implements a communication protocol between a server and multiple clients (in parallel), enabling the server to receive a problem from each client and send back a solution.
The server saves the solutions in a file cache, allowing quick O(1) access to the solutions in case of receiving the same problem. 

The program implement several Algorithms for finding paths, so given a searchable object from the client, the shortest path is returned as a string.
In it's current version, the program uses the "AStar" algorithm, after an ampiric expirement was conducted on several matrixes, using all algorithms for comparison.

RUN THE PROGRAM:

Download the source files from GitHub (https://github.com/saraiahrak/Ex4).
Unzip the source files and run the following commands:
1 -- g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread
2 ./a.out <port_number>
**Providing a port number in the second command is optional**

After running the commands, connect to the server as client.
You can use any simple TCP base client program that sends string lines, or use a telnet command- in a seperate Terminal of the same machine, connect to the program as client by running the following command:
telnet 127.0.0.1 <port_number>

If you provided a port number to the program, enter it to the port number of the telnet command. Otherwise, enter "5600" as your port number for the telnet command.

USE THE PROGRAM:

Send a matrix from the client in the following format:

matrix (line-by-line separated by commas)
start point
end point
‘end’

Depending on the algorithm chose in the main function of our program, you will receive the path from start point to end point.
For support you can email us: 
shai.acoca@gmail.com 
omer2445@gmail.com
