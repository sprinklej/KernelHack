# KernelHack
COMP 3000 - Operating Systems

Alters the execve system call to only run commands when the system is being bullied into doing so. The hack works by looking for specific "bullying" arguments that are passed in along with the command that the user is trying to run.

The myHack.c file contains a replacement execve system call which is located inside of the linux kernel, fs/exec.c

The original version of the system call can be found [here](http://lxr.free-electrons.com/source/fs/exec.c?v=3.16#L1603)

The code was built/tested with Ubuntu 14.04, using linux kernel v3.16

For more information on the project see the [report](https://github.com/sprinklej/KernelHack/blob/master/Joel%20Sprinkle%20-%20Report.pdf)
