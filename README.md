<h1 align="center">
	💬 minitalk
</h1>

## 💡 About the project

The purpose of this project is to code a small data exchange program using UNIX signals.


## 📝 Requirements

**Mandatory part:**
- You can have one global variable per program (one for the client and one for the server), but you will have to justify their use
- Name your executable files client and server.
- The server must be started first. After its launch, it has to print its PID.
- The client takes two parameters:
	- 1) The server PID;
	- 2) The string to send.
- The client must send the string passed as a parameter to the server. Once the string has been received, the server must print it.
- The server has to display the string pretty quickly. Quickly means that if you think it takes too long, then it is probably too long (1 second for displaying 100 characters is way too much!)
- Your server should be able to receive strings from several clients in a row without needing to restart.
- The communication between your client and your server has to be done only using UNIX signals.
- You can only use these two signals: SIGUSR1 and SIGUSR2.

**Bonus part:**

- The server acknowledges every message received by sending back a signal to the client.
- Unicode characters support!

## 📋 Testing

To compile, go to the project path and run:

```shell
$ make
```

Start the "server," and note it's PID displayed on the terminal.

```shell
$ ./server
```

In a separate shell tab, launch the "client," providing the server's PID and your message string as arguments

```shell
$ ./client "PID" "Your message string"
```

Your message will be displayed in the server window.
