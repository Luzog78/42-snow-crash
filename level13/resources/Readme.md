# Level 13


<br>

### >> [Flag file](../flag) <<

<br>


## TL;DR:

```bash
gdb -q ./level13 << 'EOF'
break *0x804859a
run
set $eax=4242
continue
EOF
```

<br>


## Explanation:


#### Step 1:

- What's in the home directory:
```bash
ls -la
```

> ```
> dr-x------ 1 level13 level13  120 Mar  5  2016 .
> d--x--x--x 1 root    users    340 Aug 30  2015 ..
> -r-x------ 1 level13 level13  220 Apr  3  2012 .bash_logout
> -r-x------ 1 level13 level13 3518 Aug 30  2015 .bashrc
> -rwsr-sr-x 1 flag13  level13 7303 Aug 30  2015 level13
> -r-x------ 1 level13 level13  675 Apr  3  2012 .profile
> ```

> ```bash
> ./level13
> ```
> > ```
> > UID 2013 started us but we we expect 4242
> > ```


#### Step 2:

- Let's decompile the binary to see what it does:
```bash
objdump -s -d ./level13
```

> ```asm
> 0804858c <main>:
>  804858c:	55                   	push   %ebp
>  804858d:	89 e5                	mov    %esp,%ebp
>  804858f:	83 e4 f0             	and    $0xfffffff0,%esp
>  8048592:	83 ec 10             	sub    $0x10,%esp
>  8048595:	e8 e6 fd ff ff       	call   8048380 <getuid@plt>  ; if (getuid()
>  804859a:	3d 92 10 00 00       	cmp    $0x1092,%eax          ;         == 0x1092 [4242])
>  804859f:	74 2a                	je     80485cb <main+0x3f>   ;    goto <main+63>
>  80485a1:	e8 da fd ff ff       	call   8048380 <getuid@plt>
>  80485a6:	ba c8 86 04 08       	mov    $0x80486c8,%edx
>  80485ab:	c7 44 24 08 92 10 00 	movl   $0x1092,0x8(%esp)
>  80485b2:	00
>  80485b3:	89 44 24 04          	mov    %eax,0x4(%esp)
>  80485b7:	89 14 24             	mov    %edx,(%esp)
>  80485ba:	e8 a1 fd ff ff       	call   8048360 <printf@plt>  ; Prints error message
>  80485bf:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
>  80485c6:	e8 d5 fd ff ff       	call   80483a0 <exit@plt>    ; exit(1)
>  80485cb:	c7 04 24 ef 86 04 08 	movl   $0x80486ef,(%esp)     ; --- <main+63> ---
>  80485d2:	e8 9d fe ff ff       	call   8048474 <ft_des>      ; Compute the flag
>  80485d7:	ba 09 87 04 08       	mov    $0x8048709,%edx
>  80485dc:	89 44 24 04          	mov    %eax,0x4(%esp)
>  80485e0:	89 14 24             	mov    %edx,(%esp)
>  80485e3:	e8 78 fd ff ff       	call   8048360 <printf@plt>  ; Prints it
>  80485e8:	c9                   	leave
>  80485e9:	c3                   	ret
> ```

> Another way to dissasemble the binary is to use `gdb`:
> ```bash
> gdb -q ./level13 <<< "disas main"
> ```


#### Step 3:

- It would be wonderful if we could change the value of `eax` to `4242` before the `cmp` instruction. Then the program would compute and print the flag.

- Let's use `gdb` to do that.
```bash
gdb -q ./level13 << 'EOF'  # Simple quote to avoid variable expansion
break *0x804859a
run
set $eax=4242
continue
EOF
```


<br>

---

[<<](/level12/resources/Readme.md) &nbsp; [[Back to main page]](/Readme.md) &nbsp; >>
