// My altered version of the execve system call,
// located inside of the fs/exec.c file
// The line: #include <linux/random.h> 
// must also be added for get_random_bytes() to work.
SYSCALL_DEFINE3(execve,
                const char __user *, filename,
                const char __user *const __user *, argv,
                const char __user *const __user *, envp)
{
    int cntr = 0, randNum;
    static int num = 15, flag = 0;
    char const **argPointer;
    argPointer = argv; // causes a compiler warning, but I want to manipulate strings so have to -Playing with fire!

    /* lets the system shutdown properly
    if not included the system gets stuck
    and a hard reboot is required */
    if (strstr(filename, "shutdown")) {
        flag = 1;
    }
    
    if (flag != 1) {
        // generate random numbers from:
        // http://www.linuxquestions.org/questions/programming-9/random-numbers-kernel-642087/
        get_random_bytes(&randNum, sizeof(randNum));
        randNum = randNum % 100;
        if(randNum < 0) {randNum *= -1;}

        // Troll only account where uid = 1000 (student) - protects the rest of the system
        if(from_kuid_munged(current_user_ns(), current_uid()) == 1000) {
            //printk(KERN_INFO "filename = %s, num = %d\n", filename, num);
            if(num == 0) {
                // look through the argv arguments for "bullying"
                while(*argPointer != NULL) {
                    if (strstr(*argPointer, "Please") && (randNum < 3)) {
                        *argPointer = NULL;
                        argPointer = argPointer - cntr;
                        printk(KERN_ALERT "execve: Ok I will comply, since you asked nicely.\n");
                        return do_execve(getname(filename), argPointer, envp);
                    } else if(strstr(*argPointer, "DOIT") && (randNum < 20)) {
                        *argPointer = NULL;
                        argPointer = argPointer - cntr;
                        printk(KERN_ALERT "execve: Fine... No need to yell.\n");
                        return do_execve(getname(filename), argPointer, envp);
                    } else if(strstr(*argPointer, "Ass") && (randNum < 40)) {
                        *argPointer = NULL;
                        argPointer = argPointer - cntr;
                        printk(KERN_ALERT "execve: Watch your tongue.\n");
                        return do_execve(getname(filename), argPointer, envp);
                    } else if (strstr(*argPointer, "Geek") && (randNum < 70)) {
                        *argPointer = NULL;
                        argPointer = argPointer - cntr;
                        printk(KERN_ALERT "execve: That stings.\n");
                        return do_execve(getname(filename), argPointer, envp);
                    }
                    argPointer++;
                    cntr++;
                }

                printk(KERN_ALERT "execve: Better luck next time.\n");
                return EACCES; //returns error
            }
            num--;
        }
    }

    // original code
    return do_execve(getname(filename), argv, envp);
}