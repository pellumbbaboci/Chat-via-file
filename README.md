# Chat-via-file
Chat via file using signals. Concept of blocking a process while the other is writing.

## Evaluation of this project
I have given a file named as Chat.Txt. This is an empty file. There are going to
be two Processes in our case project. Both of them have the ability to write/read
the Chat.Txt. These processes can communicate via this file.
The Chat (communication is done one-by-one manner) One-by-One synchronization
and is handled by SIGUSR1 and SIGUSR2 signal usage.

## USER MANUAL
First we have to open three terminals , two of them are used to run the program
(make two processes).In the third terminal we are using it to give the
signals SIGUSR1 to the first process and SIGUSR2 to the second process 
with kill command. 
After we signal the processes we can start chatting between the processes.

We can open one more terminal and we use this one to check the Chat.txt file which
message is written last (this is additional).
