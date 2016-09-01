#RSA Challenge
##What's it?
This program tests RSA numbers with random trial division.

##Is it a joke?
Maybe. I'm just boring. You have an extremely small possibility to find the factor of RSA number. However, it seems to be more meaningful to me than lottery.

##Usage
This program doesn't provide any GUI, so you should run it from a terminal.
Use `RSAChallenge --help` to see all the options.
You must use `--rsa=xxx` or `-r xxx`to tell the program that which RSA number is going to be tested. For example, `RSAChallenge --rsa=230` means that the program is going to test the RSA-230.
If you want to turn on the multi-thread support, you can use `--npos=xxx`. For example, `RSAChallenge --rsa=230 --npos=5` means to test RSA-230 with 5 computing threads. This option has a default value 1.

##Dependencies
- **boost::random**
- **boost::program_options**
- **boost::multiprecison**
- **gmp**
- **C++ 11 thread**


##Some tips
- The data of RSA numbers is read from the data folder, so do not change the relative location of the main executable program and all the file in the data folder.
- You should notice that the actual number of threads of this program equals to the number of threads you provide by`--npos=xxx` plus one. The reason is that the main thread is not involved in the trial division. That is, if you use `--npos=6`, then the program will have 7 threads after a short period of time, in which we have 6 computing threads which will do the trial division and the left one to be waiting.

##TODO
- Add more RSA numbers in the data folder.
- Add user define number trial division.
- Add more note in the code.

