# Chat-via-file
Chat via file using signals. Concept of blocking a process while the other is writing.
# Evaluation of this project
I have given a file named as Chat.Txt. This is an empty file. There are going to
be two Processes in our case project. Both of them have the ability to write/read
the Chat.Txt. These processes can communicate via this file.
The Chat (communication is done one-by-one manner) One-by-One synchronization
and is handled by SIGUSR1 and SIGUSR2 signal usage.

