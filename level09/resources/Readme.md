# Level 09


<br>

### >> [Flag file](../flag) <<

<br>


#### Step 1:

- What's in the home directory:
```bash
ls -la
```

> ```
> dr-x------ 1 level09 level09  140 Mar  5  2016 .
> d--x--x--x 1 root    users    340 Aug 30  2015 ..
> -r-x------ 1 level09 level09  220 Apr  3  2012 .bash_logout
> -r-x------ 1 level09 level09 3518 Aug 30  2015 .bashrc
> -rwsr-sr-x 1 flag09  level09 7640 Mar  5  2016 level09
> -r-x------ 1 level09 level09  675 Apr  3  2012 .profile
> ----r--r-- 1 flag09  level09   26 Mar  5  2016 token
> ```

> The token file is readable but seems to be crypted.
> ```bash
> hexdump -C token
> ```
> > ```
> > 00000000  66 34 6b 6d 6d 36 70 7c  3d 82 7f 70 82 6e 83 82  |f4kmm6p|=..p.n..|
> > 00000010  44 42 83 44 75 7b 7f 8c  89 0a                    |DB.Du{....|
> > 0000001a
> > ```

> The `level09` program, on the other hand, seems to be the one that crypted the token.
> ```bash
> ./level09 "This is a test" | hexdump -C
> ```
> > ```
> > 00000000  54 69 6b 76 24 6e 79 27  69 29 7e 70 7f 81 0a     |Tikv$ny'i)~p...|
> > 0000000f
> > ```


#### Step 2:

> ***If you're smart, with these examples, you can already see the pattern of the crypting algorithm.***
>
> ```bash
> ./level09 "0123456789"
> ./level09 "111111111111111111111111"
> ./level09 "aaaaaaaaaaaaaaaaaaaaaaaa"
> ```
> > ```
> > 02468:<>@B
> > 123456789:;<=>?@ABCDEFGH
> > abcdefghijklmnopqrstuvwx
> > ```
>
> *If it's the case, just skip the the next step. Goto [Step 3](#step-3) directly.*

- Just to be sure, let's decompile the `level09` program and see what it does.

- In the snow-crash machine:
```bash
cp level09 /tmp/level09
```

- In the host machine:
```bash
scp -P 4242 level00@snow-crash:/home/level09/level09 ./level09
```

- Then launch Ghidra to decompile and analyze it.
```bash
ghidra
```

- The fully decompiled and anotated version is in the [level09.c](./level09.c) file.

> The simplified version of the algorithm is:
> ```c
> size_t main(int argc, char **argv) {
> 	if (ptrace(PTRACE_TRACEME, 0, 1, 0) < 0) {
> 		puts("You should not reverse this");
> 		return 1;
> 	}
>
> 	if (getenv("LD_PRELOAD") != NULL || access("/etc/ld.so.preload", F_OK) == 0) {
> 		fprintf(stderr, "Injection Linked lib detected exit..\n");
> 		return 1;
> 	}
>
> 	if (argc != 2) {
> 		fprintf(stderr, "You need to provide only one arg.\n");
> 		return 1;
> 	}
>
> 	const char *input = argv[1];
> 	for (unsigned int idx = 0; input[idx] != '\0'; idx++) {
> 		putchar(input[idx] + idx);
> 	}
> 	putchar('\n');
>
> 	return 0;
> }
> ```


#### Step 3:

- Let's create a script to decrypt the token *([decrypt.c](./decrypt.c))*:
```c
chmod 777 .
cat > decrypt.c << EOF
#include <unistd.h>

int main(int argc, char **argv) {
    char    buffer[1024]; // Because we know that the token is less than 1024 bytes

    int     readResult = read(0, buffer, 1024);
    if (readResult < 0)
        return 1;

    for (int i = 0; i < readResult; i++)
        if (i != readResult - 1 || buffer[i] != '\n') // If the last character is a newline, don't decrypt it
            buffer[i] = buffer[i] - i; // Decrypt the token

    write(1, buffer, readResult);
    return 0;
}
EOF
```


#### Step 4:

- Then we execute it:
```bash
gcc decrypt.c -std=c99 -o decrypt && cat token | ./decrypt
```

> ```bash
> f3iji1ju5yuevaus41q1afiuq
> ```
> It worked! We got the password for the `flag09` user.


#### Step 5:

- Don't forget to get the flag to validate the level:
```bash
su flag09 -c getflag
```


<br>

---

[<<](/level08/resources/Readme.md) &nbsp; [[Back to main page]](/) &nbsp; [>>](/level10/resources/Readme.md)
