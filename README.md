# C-Programming
C programming in linux using various IPC mechanisms and other C practice projects.

# A14 Open-ended project with Sockets
Sockets enable us to run the programs across the internet - specifically, client programs from anywhere can connect to the server if they know the IP address and port # to connect to! ~veerasam/linux/sockets has the startup programs. 

Come up with your own application with multi-threaded server to serve multiple clients in parallel. It should be reasonably complex and it will be ideal if the server behavior depends on the current active list of clients. If you cannot think of a good application, I recommend you to start with A12 Instant Messaging App. Implement a few new features like

broadcast I won a million dollars!	Send broadcast message to all the clients
random how are you today?	Select a random client and send the message
close	Close the connection for this client.


Submit the program files in Linux server and submit a few screenshots in elearning to complete this assignment.

turnin a14 *.c
# A13 Conversational Game with Sockets
Sockets enable us to run the programs across the internet - specifically, client programs from anywhere can connect to the server if they know the IP address and port # to connect to! ~veerasam/linux/sockets has the startup programs. Copy and enhance them to complete the functionality.

You can either implement Hangman word guessing game OR number guessing game (OR even your own game that requires conversation between server and client - do include a description in the elearning submission).

After completing the assignment, use the following command to turn in your work: 

turnin a13 sserver.c sclient.c              <-- sclient.c is OPTIONAL, we can use ncat instead.

Additionally, attach the screenshots of sample run here (use different machines for server & client) and submit the assignment. 
# A12 Multi-threaded Instant Messenger
We will develop the basic Instant Messenger functionality. Key limitation: all users are logged in in the same machine.

Continue to use the named pipes to communicate between the server and clients.

Instead of using fork() to take care of each client, use multi-threading - create a new thread instead!

Use global variables (arrays) to keep track of the users' information.

We will support only 2 commands: list & send

Following sample run should explain a lot (Y axis is the time):
 

Capture a few interesting sample runs and submit them in elearning. Use the following command to submit the source files.

turnin a12 imserver.c imclient.c
# A11 Multi-threaded Hashing
While you can develop this assignment in cs1/cs2/cs3, use cs3 to run your experiments. It has a greater number of CPUs than the other machines. If you want to test your code for large number of threads (128 or more), use net01 .. net45 machines.

Multi-threaded hash tree

In this assignment, you will write a multi-threaded program to compute a hash value of a given file. The size of the file can be very large. So, there is a need for the program to be multi-threaded to achieve speedup. While one thread reads a part (block) of the file, other threads can compute hash values of already read blocks.

Binary tree threads

For Fibonacci number program, we created the threads in tree structure to compute fib(n). In this project, you will create the threads in a perfect binary tree structure to compute hash values.

Hash value

The hash value of a string (very long) is a fixed length numeric value. Hash values are typically expressed in hex digits and can be long. In this project we will restrict the hash value type to a 32-bit unsigned integer. A hashing algorithm will read the input string (file) and produce a hash value. There are many hashing algorithms in the literature. For this project we will use Jenkins one_at_a_time hash described in https://en.wikipedia.org/wiki/Jenkins_hash_function.

One of the uses of hash value is to check the integrity of the data (file, database, etc.). One can think of a hash value of a file as a fingerprint of the file. If the file is modified, then the hash value also changes. By comparing the new and old hash values one can easily detect that the file was modified.

Computation of a hash value of a large file (several giga bytes in size) may take a while. Hence a need for a multi-threaded program.

Multi-threaded hashing

A file can be divided into multiple chunks - one chunk for each thread. Assume that the file size is divisible by # of threads . Each thread can compute the hash value of its assigned chunk. Several of these hash values are then combined to form a string whose hash value can be computed as before. These steps can be repeated till one final hash value remain.

We created a tree of threads to compute fib(n). For this assignment, we will create a complete binary tree of threads. Each leaf thread will compute the hash value of the chunk assigned to it and return the hash value to its parent thread (through pthread_exit() call). An interior thread will compute the hash value of the blocks assigned to it, and then wait for its children to return hash values. These hash values should be combined to form a string:

<computed hash value + hash value from left child + hash value from right child>.

(Note that the + sign here means concatenation and not addition. Also, if the interior thread has no right child, only the hash value of the interior thread and the hash value from the left child are combined.) The interior thread then computes hash value of the concatenated string as before and returns the value to its parent, The value returned by the root thread is the hash value of the file.

Usage and hints

All the related files are in ~veerasam/linux7/a11 including the testcase results. Trace the verbose output (hash) files in this folder to get a good understanding of the requirements. Link to the data files using ln command:

ln -s ~veerasam/linux/files/tc? .

Now, you should have 5 symbolic links: tc1, tc2, tc3, tc4 and tc5 - these are the data files for testcases - do not do direct copy from my directory - that will be a waste of space!

Start with copying htree3.c as htree.c - then combine tree2.c functionality into it. You can use the following command to run it

htree filename num_threads

filename is the name of the input file whose hash value needs to be computed. num_threads is the number of threads to be created.

Example: htree tc1 4

Check fstat() to find the file size. How to get the data from input file in each thread? Here are a few approaches:
1. Read the whole data file first - make buffer a global pointer and then each thread can access the data directly with appropriate offset.

2. Open the file upfront, but do not read the data right away. Instead, each thread can read the appropriate data using pread() system call, then do hash computation.

3. But there is an easier way to read a file using mmap(). Check the man page for mmap().

You can use sprintf() to convert an uint to string.

Hand-in Instructions

Turn-in your program in cs1/cs2/cs3 servers and include the screenshots here in elearning to submit the assignment.
turnin a11 htree.c

 

Part 2: Experimental study (OPTIONAL - can be done later!)

The main goal of this study is to find speedup achieved when the number of threads is increased for various input files. For each input file, find the time taken to compute the hash value for 1, 4, 16, 32, 64, and 128 threads.

 

Run your experiments on cs3. It has 48 CPUs. Other machines have lesser number of CPUs.

 

Plot a graph with time on y-axis, and #threads on x-axis for each input file. Plot another graph with speedup on y-axis and #threads on x-axis for each input file.

            speedup = (time taken for single thread)/(time taken for n threads)

 

Write a short report on what you observe. It is expected that the time taken to compute hash value decrease when the number of threads increase. Does it always happen? What is the speed-up achieved when the number of threads increased? Is the speedup proportional to the number of threads increased? Also, briefly describe the experimental set-up at the beginning of your report. (Command ‘lscpu’ provides relevant information for this)

 

Write a high-quality report and share with the professor in MS Teams chat for comments. You can showcase the report in your job interview!
# A10 Hangman game using named pipes
Since this assignment is given bit late, I will accept it without penalty until Tuesday, April 9th (this exception is ONLY for this assignment).

----

~veerasam/linux/namedpipes contains the files we covered in the class. ~veerasam/linux3/a10 has the necessary files to get started with specific assignment. hangman.cpp has been given only for reference.

gserver.c should run the server functionality. It loads all the dictionary words  from dictionary.txt  as part of the setup and waits for input through the named pipe /tmp/NETID. For each request comes through the pipe, server should fork a process - Child process should send its own unique pipename to the client and start the hangman game! Parent process proceeds to wait for new requests. This setup enables the server to support any # of clients in parallel!

gclient.c is a thin client program that gets the user input and passes to the server and shows the reply in the screen. Here is a sample I/O for the client. 



When you are done, run the following command to submit the assignment in cs1. Also attach a few sample runs here and submit this assignment.
turnin a10 gserver.c gclient.c
# A9 Your own shell
There will be 3 major functionalities in your shell.

Display a random quote followed the prompt for the user to enter the command (read all the quotes from quotes.txt when the shell starts up).
It should be able to support any number of commands connected by pipe (similar to bash):
Usage: command1 | command2 | command3 | command4 ....
It should allow 2 commands to pipe the data to each other (new). This can be achieved by having 2 pipes (= signifies that!)
Usage: command1 = command2 
Resource files in ~veerasam/linux/a9 in cs1/cs2/cs3 servers When you are done, submit the program using turnin and submit a screenshot of a few sample runs here & complete in elearning.

turnin a9 mysh.c

Here is a sample run (BTW, no need to worry about wildcard expansion OR shell built-ins)

mysh

<random quote>
# cat data1.txt data2.txt     <-- simple command, without | or =

..

<random quote>

# cat data1.txt | cat | cat | cat data1.txt data2.txt | cat | cat | cat

...

<random quote>

# computer = user

...

<random quote>

# mecho -s 5 -n 10 7 = mecho 3

...

Hints:

1. Use execvp() - we don't even need to find the pathname for the command - it will find it for you!

2. Use strtok() to split the input line to multiple commands. 



OPTIONAL Enhancements: Support ; & < and > operators. Impress Dr. Jey by implementing these & sending the sample runs to him by MS Teams chat :-)

1. Linux allows the user to include multiple commands in one line using ; operator. You need to simply execute them in a sequence - wait for each command to complete, before executing the next one.

Example: ps ; ls -l ; ps -f

2. Linux allows the users to run any command in the background with & at the end. Basically, you don't need to wait until the command is over to display the prompt.

Example: cat data1.txt data2.txt &

3. Linux allows the users to specify the redirection for the standard I/O streams.

Example: cat < data1.txt > temp.txt
# A8 Data Crunching using Pipes
We are going to write calculator.c to compute math expressions using Linux IPCs (Inter-process communication) - program needs to fork() as many times as needed and use pipes to communicate with children. Equation specified in the first line of the data file will determine this setup. Once the setup is done, parent task reads the data from the data file and pumps into various pipes in parallel and results come back to the main task using another pipe.

add, subtract, multiply & divide are the available tools (they can be downloaded from ~veerasam/linux/a8) - let us use binary format for communication. All tasks use standard input stream 0 to read the first argument, use stream 3 to read the 2nd argument and use standard output stream 1 for output. Main task uses the pipe stream numbers directly since it needs standard I/O streams to communicate with the user. 

Main task should read the first line from the data file and create the necessary # of children and setup IPC configuration ignoring the operator precedence rules - simply setup to process the equation left to right. Main program should read the remaining lines, send the values to appropriate pipes, and get the result and print in the screen.

Review the pipe configuration diagrams for a - b * c and a - b * c - d / e  in Dr.Jey's slides to understand the functionality first. Then write meaningful pseudocode, review it carefully, then proceed to write the actual code. Modularize the program as much as you can!

Usage: calculator data.txt

Sample data file content:

a - b * c
30 20 2
500 10 20
90 1 10

Expected output for this input:

20
9800
890


Parent task can close the pipes when eof is reached for input file. When eof is detected in the pipe that brings the results in, parent task can quit.

Use the following command to test your program.

testa8

Use the following command to turn your program in. 

turnin a8 calculator.c

Attach testa8 output here to complete this assignment.
# A6 Board Game
A bunch of friends are coming together to play a game like Monopoly. They all start with the specified initial balance. As the game proceeds, in each transaction, one player divides a specific amount of money equally and gives it to specific folks. After each transaction, output the current balance for each palyer.

We will develop 3 versions of the program, but their functionality will be exactly same. They should keep track of the balance amounts for each player, using text or binary files. Program will be run to setup once, then for each transaction, using command line parameters as shown below. Use a text or binary file to keep track of the names and current balances. No need to worry about negative balances, etc. Commands are in BOLD. We attach a special meaning to "new" when it appears as the first parameter - that means a fresh start - new set of friends with new balances. Format the output nicely using format string in printf(). Use 2 decimal places for points, just like real money. 

gifts1 new Jey 100 John 200 Nhut 300 Miguel 400

   Jey: 100.00

  John: 200.00

  Nhut: 300.00

Miguel: 400.00

 

gifts1 Jey 100 John Miguel

   Jey:   0.00

  John: 250.00

  Nhut: 300.00

Miguel: 450.00

 

gifts1 Nhut 150 Jey John Miguel

   Jey:  50.00

  John: 300.00

  Nhut: 150.00

Miguel: 500.00

 

gifts1 John 300 Nhut

   Jey:  50.00

  John:   0.00

  Nhut: 450.00

Miguel: 500.00

 

gifts1 Miguel 200.50 Jey John

   Jey: 150.25

  John: 100.25

  Nhut: 450.00

Miguel: 299.50

(Same commands should work for gifts2 and gifts3 as well). Copy the startup files using this command:

cp ~veerasam/linux/a6/* .

gifts1.c - use fopen(), fscanf() and fprintf(). Use text data file gifts1.txt

gifts2.c - use the system calls open(), write(), read(), & close(). Use individual arrays for names and amounts. Use a binary data file gifts2.dat

gifts3.c - use standard I/O library functions fopen(), fread(), fwrite(), & fclose(). Use an array of structs. Use a binary data file called gifts3.dat

- Use formatted printf() for nicely formatted output:

printf("%10s %6.2lf\n", name.., balance...);

Once you are done, submit your program in cs1/cs2/cs3 using this command:

turnin a6 gifts?.c

then attach the screenshot of the following command's output here as the evidence of completion in elearning.

testgifts
# A5 Fancy Diagonal Pattern
Copy diagonal.c from the professor's Linux account:

cd ~/linux

mkdir a5

cd a5

cp  ~veerasam/linux/a5/diagonal.c  .

{cslinux1:~/linux/a5} mmake diagonal

{cslinux1:~/linux/a5} diagonal Funny!

diagonal.out has been created. Use od -c diagonal.out to see the contents.

{cslinux1:~/linux/a5} od -c diagonal.out



Now, enhance it to handle any # of words as parameters and output them in a fancy pattern as shown below - use a block of 16x16 characters for each word. Note that 16*16 = 256 (decimal) = 400 (octal).  Save the new program as diagonal2.c  

{cslinux1:~/linux/a5} make diagonal2

{cslinux1:~/linux/a5} diagonal2 Jey Veerasamy Professor UTDallas

diagonal2.out has been created. Use od -c diagonal2.out to see the contents.

{cslinux1:~/linux/a5} od -c diagonal2.out







Test out your programs with testa6 script. 

testpattern
...
testpattern | grep passed
diagonal2 passed.


Now, turn in your source file:
turnin a5 diagonal2.c

and attach testpattern output in elearning and complete the assignment.
# A4 Random password generator & String comparison
Review the last 2 slides of c-basics.pptx in the box folder for the full descriptions of these 2 programs:

- Random password generator

- String comparison

Issue the following command in cs1/cs2/cs3 servers to turn in your code:
turnin a4 randompwd.c compstr.c
Also, take the screenshots of following command's output (bottom portion should look similar to the following) and submit in elearning and complete this assignment.
testa4 
If you want to see the actual commands, you can run the script in debugging mode:
bash -x ~veerasam/bin/testa4


 
Also, you can use the following command to see your previous submissions (there is ~5 minute delay for your submissions to show up in this list)!
turnin a4
# A3 File System Blocks
See the startup program dblocks.c in ~veerasam/linux/a3

cd ~/linux
mkdir a3
cd a3
cp ~veerasam/linux/a3/dblocks.c  .

We learned about the # of storage blocks and overhead blocks required to store files using this inode structore diagram as the guidance. Now, challenge yourself and develop an algorithm and implement it to compute # of storage blocks and overhead blocks required to store a file of any size. Input will be specified in KBs. Output will have 2 numbers: # of storage blocks and # of overhead blocks. Start early and try to do with minimal help!

Here is another view of disk blocks from inode structure - Top array of 15 numbers is part of the inode structure. All others are disk blocks. Green boxes are data blocks, Black boxes are overhead blocks - each of them are 8K in size. I hope this image brings a bit more clarity. 



 

Here is a sample run (to store a file of size 100KB, we need 13 blocks for storage and 1 overhead block). Note that the input is specified as a command line argument.

dblocks 100

13 1

It is a good idea to use long instead of int, as shown in my startup program. When the input file size is too large to accommodate in the filesystem, output -1 for overhead blocks.

Once you complete your program, you can test it with this command (make sure you have Makefile in your directory):

testfsb

Once you complete the program and test it, you can submit using turnin in cs1/cs2/cs3 servers and submit the screenshot of testfsb script output in elearning and complete this assignment.

turnin a3 dblocks.c

Also, you can use the following command to see your previous submissions (there is ~5 minute delay for your submissions to show up in this list)!

turnin a3 


# A2 Find the cow!
See the problem statement in USACO website. Design a brute-force solution in C language and implement as cowfind1.c - it should read the string as the standard input and output just one number indicating the # of combinations (Do NOT look at the web resources - I am sure you will find the solutions - if you see them, learning experience is gone!)
 
I have provided the startup files, test inputs and the corresponding outputs in ~veerasam/linux/a2 to verify your program. You can use the following commands to setup your directory and copy the files in:
cd ~/linux
mkdir a2
cd a2
cp ~veerasam/linux/a2/*  .
ls
If you are not comfortable with VI editor yet, you can edit the file using pico editor (it is like notepad):
pico cowfind1.c
Once you save & quit, you can compile the program using Makefile:
make cowfind1
There are 10 testcase input files: 1.in, 2.in, ... 10.in
You can run the program for each testcase input file like this:
cowfind1 < 1.in
cat 1.out
and compare the output with the contents of 1.out. Do the same for all 10 testcases.
Once you pass all the testcases, use time command to capture the timings for each testcase too.
time cowfind1 < 1.in
 
Now, think hard to come with a more efficient algorithm! Hint: You can read one character at a time in a loop and compute # of combinations using just a few variables, even an array is not needed! If you are stuck after thinking about it after an hour or two, see this video. Let us call this program as cowfind2.c  After validating against the testcases, use time command to capture the timings for each testcase again.
 
Include the screenshots of the programs & timings here. Also, write a few lines about what you learned - include a statement about the timing differences between cowfind1 and cowfind2. No need to turnin anything in cs1 linux server for this assignment.
