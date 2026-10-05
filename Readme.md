<div align="center">

```
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@                                                                              @
@   _____                      _____               _                           @
@  / ____|                    / ____|             | |                          @
@ | (___  _ __   _____      _| |     _ __ __ _ ___| |__                        @
@  \___ \| '_ \ / _ \ \ /\ / / |    | '__/ _` / __| '_ \    ___                @
@  ____) | | | | (_) \ V  V /| |____| | | (_| \__ \ | | |  | _ )_  _           @
@ |_____/|_| |_|\___/ \_/\_/  \_____|_|  \__,_|___/_| |_|  | _ \ || | ysabik   @
@ Good luck & Have fun                                     |___/\_, | cjung-mo @
@                                                               |__/           @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
```

# 42 Cursus - snow-crash

<img src="https://cdn.jsdelivr.net/gh/devicons/devicon@latest/icons/ubuntu/ubuntu-original.svg" height="30" alt="ubuntu" />
<img width="12" />
<img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/bash/bash-original.svg" height="30" alt="bash" />
<img width="12" />
<img src="https://cdn.jsdelivr.net/gh/devicons/devicon@latest/icons/ssh/ssh-original.svg" height="30" alt="ssh" />

<br><br>

</div>


## Details

- **Summary:** *This project is an introduction to computer security. Snow Crash will help you discover security in various sub-domains, with a developer-oriented approach. You will become familiar with several languages (ASM, Perl, Php, etc.), develop a certain logic to understand unknown programs, and become aware of problems related to simple programming errors.*
- **Author(s):** *[ysabik](https://profile.intra.42.fr/users/ysabik)*, *[cjung-mo](https://profile.intra.42.fr/users/cjung-mo)*
- **Public repo:** [GitHub](https://github.com/Luzog78/42-snow-crash)
- **Subject:** [en.subject.pdf *(v3.2)*](https://cdn.intra.42.fr/pdf/pdf/209996/en.subject.pdf)
- **Stack:** *64-bit linux VM ([SnowCrash.iso](https://cdn.intra.42.fr/isos/SnowCrash.iso))*

<br>

- [[snow-crash]](#42-cursus---snow-crash)
	- [[Details]](#details)
	- [[Overview]](#overview)
	- [[Objectives]](#objectives)


<br><br>

## Overview

The goal of the project is to find 10 flags hidden in the SnowCrash.iso VM. The flags are hidden in various ways, and we have to use different techniques to find them. <br>
There are 20 main users: `level00` to `level09` and the corresponding `flag00` to `flag09`. Each time, we have to login to the `flagXX` user and execute the `getflag` command to get the flag, the password for the next `levelXX` user. <br>
That's all for the mandatory part. The project contains a bonus part that extends the challenge with 5 additional flags (`level10` to `level14` and the corresponding `flag10` to `flag14`).

How to start:
1. Download the SnowCrash.iso VM from the 42 intra.
2. Boot the VM (using QEMU, VirtualBox or any other emulator).
3. Connect to the VM using SSH (default credentials: `level00:level00`).
```bash
ssh level00@<machine_ip> -p 4242
```


<br><br>

## Objectives

#### Mandatory

- [x] 1. [level00](./level00/resources/Readme.md) ([Flag](./level00/flag))
- [ ] 2. level01
- [ ] 3. level02
- [ ] 4. level03
- [ ] 5. level04
- [ ] 6. level05
- [ ] 7. level06
- [ ] 8. level07
- [ ] 9. level08
- [ ] 10. level09

#### Bonus

- [ ] 11. level10
- [ ] 12. level11
- [ ] 13. level12
- [ ] 14. level13
- [ ] 15. level14

<br><br>

---

<sup><i>This is an educational project proposed by 42 School through the 42Cursus program.</i><sup>
