# Level 00


<br>

### >> [Flag file](../flag) <<

<br>


## TL;DR:

To get the `flag00` user password:
```bash
cat $(find / -user flag00 2> /dev/null)
```

With the password `nottoohardhere`:
```bash
su flag00 -c getflag
```

<br>


## Explanation:


#### Step 1:

- Check the files owned by the `flag00`.
```bash
find / -user flag00 2> /dev/null
```

> ```
> /usr/sbin/john
> /rofs/usr/sbin/john
> ```


#### Step 2:

- Cat both files to find the password for the `flag01` user.
```bash
cat /usr/sbin/john
cat /rofs/usr/sbin/john
```

> ```
> cdiiddwpgswtgt
> cdiiddwpgswtgt
> ```
> After trying, we find that it does not work as password for the `flag00` user.


#### Step 3:

- It looks like a `ROT15` cipher. Let's decode it using the `tr` command.
```bash
echo "cdiiddwpgswtgt" | tr 'a-z' 'l-za-k'
```

> ```
> nottoohardhere
> ```


<br>

---

<< &nbsp; [[Back to main page]](/Readme.md) &nbsp; [>>](/level01/resources/Readme.md)
