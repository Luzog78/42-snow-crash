# Level 01


<br>

### >> [Flag file](../flag) <<

<br>


## Explanation:


#### Step 1:

- Check the `/etc/passwd` file to find the users that have a `flag` in their name.
```bash
cat /etc/passwd | grep flag
```

> ```
> flag00:x:3000:3000::/home/flag/flag00:/bin/bash
> flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash
> flag02:x:3002:3002::/home/flag/flag02:/bin/bash
> flag03:x:3003:3003::/home/flag/flag03:/bin/bash
> flag04:x:3004:3004::/home/flag/flag04:/bin/bash
> flag05:x:3005:3005::/home/flag/flag05:/bin/bash
> flag06:x:3006:3006::/home/flag/flag06:/bin/bash
> flag07:x:3007:3007::/home/flag/flag07:/bin/bash
> flag08:x:3008:3008::/home/flag/flag08:/bin/bash
> flag09:x:3009:3009::/home/flag/flag09:/bin/bash
> flag10:x:3010:3010::/home/flag/flag10:/bin/bash
> flag11:x:3011:3011::/home/flag/flag11:/bin/bash
> flag12:x:3012:3012::/home/flag/flag12:/bin/bash
> flag13:x:3013:3013::/home/flag/flag13:/bin/bash
> flag14:x:3014:3014::/home/flag/flag14:/bin/bash
> ```
> We can see that the line of the user `flag01` contains its password.
> But it does not work as password.


#### Step 2:

- We'll decrypt the password using the [John the Ripper](https://github.com/openwall/john) ([Homepage](https://www.openwall.com/john/)) tool.
```bash
echo "flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash" > /tmp/passwd
john --show /tmp/passwd
```

> ```
> flag01:abcdefg:3001:3001::/home/flag/flag01:/bin/bash
> 
> 1 password hash cracked, 0 left
> ```


<br>

---

[<<](/level00/resources/Readme.md) &nbsp; [[Back to main page]](/) &nbsp; >>
