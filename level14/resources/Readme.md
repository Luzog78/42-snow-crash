# Level 14


<br>

### >> [Flag file](../flag) <<

<br>


## TL;DR:

```bash
gdb -q /bin/getflag << 'EOF'
break *0x804898e
run
set $eax=0
break getuid
continue
finish
set $eax=3014
continue
EOF
```

<br>


## Explanation:


#### Step 1:

- There is absolutely nothing to do in this level. So let's just try to exploit the `getflag` binary.

- Let's see what it does:
```bash
strace /bin/getflag
```

> ```c
> execve("/bin/getflag", ["/bin/getflag"], [/* 18 vars */]) = 0
> brk(0)                                  = 0x804c000
> access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
> mmap2(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0xb7fdb000
> access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
> open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
> fstat64(3, {st_mode=S_IFREG|0644, st_size=21440, ...}) = 0
> mmap2(NULL, 21440, PROT_READ, MAP_PRIVATE, 3, 0) = 0xb7fd5000
> close(3)                                = 0
> access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
> open("/lib/i386-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
> read(3, "\177ELF\1\1\1\0\0\0\0\0\0\0\0\0\3\0\3\0\1\0\0\0000\226\1\0004\0\0\0"..., 512) = 512
> fstat64(3, {st_mode=S_IFREG|0755, st_size=1730024, ...}) = 0
> mmap2(NULL, 1739484, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0xb7e2c000
> mmap2(0xb7fcf000, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1a3) = 0xb7fcf000
> mmap2(0xb7fd2000, 10972, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0xb7fd2000
> close(3)                                = 0
> mmap2(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0xb7e2b000
> set_thread_area({entry_number:-1 -> 6, base_addr:0xb7e2b900, limit:1048575, seg_32bit:1, contents:0, read_exec_only:0, limit_in_pages:1, seg_not_present:0, useable:1}) = 0
> mprotect(0xb7fcf000, 8192, PROT_READ)   = 0
> mprotect(0x804a000, 4096, PROT_READ)    = 0
> mprotect(0xb7ffe000, 4096, PROT_READ)   = 0
> munmap(0xb7fd5000, 21440)               = 0
> ptrace(PTRACE_TRACEME, 0, 0x1, 0)       = -1 EPERM (Operation not permitted)
> fstat64(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 0), ...}) = 0
> mmap2(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0xb7fda000
> write(1, "You should not reverse this\n", 28You should not reverse this
> ) = 28
> exit_group(1)                           = ?
> ```
> It has a protection against reverse engineering. It calls `ptrace(PTRACE_TRACEME)` to prevent debugging. If the program is being debugged, it will exit with an error message.


#### Step 2:

- Where is the `ptrace` call in the binary?
```bash
objdump -d /bin/getflag | grep -C 1 ptrace
```

> ```asm
>
> 08048540 <ptrace@plt>:
>  8048540:	ff 25 2c b0 04 08    	jmp    *0x804b02c
> --
>  8048982:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
>  8048989:	e8 b2 fb ff ff       	call   8048540 <ptrace@plt>
>  804898e:	85 c0                	test   %eax,%eax
> ```
> The `ptrace` call is at address `0x8048989`, and the check is done at `0x804898e`.


#### Step 3:

- To bypass the protection, we can set the return value of the `ptrace` call to 0 (success).

- Let's use `gdb` to do that.
```bash
gdb -q /bin/getflag << 'EOF'  # Simple quote to avoid variable expansion
break *0x804898e
run
set $eax=0
continue
EOF
```

- But it's not enough. To launch sucessfully the `getflag` binary, we need to have the privileges of the `flag14` user.


#### Step 4:

- Let's see what is the uid of the `flag14` user:
```bash
getent passwd flag14
```

> ```
> flag14:x:3014:3014::/home/flag/flag14:/bin/bash
> ```


#### Step 5:

- Let's use `gdb` to change the uid of the process to `3014` before the `getuid()` call.
```bash
gdb -q /bin/getflag << 'EOF'  # Simple quote to avoid variable expansion
break *0x804898e
run
set $eax=0
break getuid
continue
finish
set $eax=3014
continue
EOF
```


<br>

---

[<<](/level13/resources/Readme.md) &nbsp; [[Back to main page]](/Readme.md) &nbsp; >>
