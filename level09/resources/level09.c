#include <stdio.h>
#include <unistd.h>
#include <sys/ptrace.h>

typedef unsigned int uint;
typedef unsigned char byte;
typedef enum { false, true } bool;
typedef int (*code)();



/* ************************************************************************** */
/*                                                                            */
/*                             Decompiled version                             */
/*                                                                            */
/*      Decompiled with Ghidra, then manually annotated and cleaned up.       */
/*                                                                            */
/* ************************************************************************** */


/**
 * This gets a string from the user.
 * Ends when the user presses enter (`\n`) or when the limit is reached.
 */
uint syscall_gets(char *buffer,int limit) {
	code *pcVar1;
	int iVar2;
	int local_14;

	local_14 = 0;
	do {
		if (limit - 1U <= local_14) {
			LAB_08048631:
				*(int *)(local_14 + buffer) = 0;
				return local_14;
		}
		pcVar1 = (code *)swi(0x80);
		iVar2 = (*pcVar1)();
		if (iVar2 != 1)
			goto LAB_08048631;
		if (*(char *)(local_14 + buffer) == '\n') {
			local_14 = local_14 + 1;
			goto LAB_08048631;
		}
		local_14 = local_14 + 1;
	} while( true );
}

/**
 * Returns a pointer to the character after the occurrence of `str2` in `str1`.
 * If `str2` is not found in `str1`, returns NULL.
 */
char * afterSubstr(char *str1,char *str2) {
	bool bVar1;
	int i;
	char *tmp;

	bVar1 = false;
	for (tmp = str1; *tmp != '\0'; tmp = tmp + 1) {
		bVar1 = true;
		for (i = 0; (bVar1 && (*(char *)(i + str2) != '\0')); i = i + 1) {
			if (*(char *)(i + str2) != tmp[i]) {
				bVar1 = false;
			}
		}
		if (bVar1)
			break;
	}
	if (bVar1) {
		tmp = tmp + i;
	} else {
		tmp = (char *)0x0;
	}
	return tmp;
}


int isLib(char *param_1,char *param_2) {
	bool hasNum;
	char *after;
	int result;
	int i;
	char *tmp;

	after = afterSubstr(param_1,param_2);
	if (after == (char *)0x0) {
		result = 0;
	} else if (*after == '-') {
		hasNum = false;
		while ((tmp = after + 1, '/' < *tmp && (*tmp < ':'))) {  // While isnumber(after[1])
			hasNum = true;
			after = tmp;  // after++;
		}
		if ((hasNum) && (*tmp == '.')) {
			hasNum = false;
			for (tmp = after + 2; ('/' < *tmp && (*tmp < ':')); tmp = tmp + 1) {
				hasNum = true;
			}
			if (hasNum) {
				for (i = 0; end.3170[i] != '\0'; i = i + 1) {
					if (end.3170[i] != tmp[i]) {
						return 0;
					}
				}
				result = 1;
			} else {
				result = 0;
			}
		} else {
			result = 0;
		}
	} else {
		result = 0;
	}
	return result;
}

size_t main(int argc,char **argv) {
	char c;
	bool bVar2;
	long lVar3;
	size_t hasError;
	int iVar5;
	int iVar6;
	uint revLenCounter;
	int in_GS_OFFSET;
	byte bVar8;
	char *message;
	FILE *outFd;
	int errorCode;
	uint idx;
	char local_114 [256];
	int stackCheck;

	bVar8 = 0;
	stackCheck = *(int *)(in_GS_OFFSET + 0x14);
	bVar2 = false;
	idx = 0xffffffff;
	errorCode = 1;
	outFd = (FILE *)0x0;
	lVar3 = ptrace(PTRACE_TRACEME,0,1,0);
	if (lVar3 < 0) {
		message = "You should not reverse this";
		puts("You should not reverse this");
		hasError = 1;
	} else {
		message = getenv("LD_PRELOAD");
		if (message == (char *)0x0) {
			errorCode = open("/etc/ld.so.preload",0);
			if (errorCode < 1) {
				iVar5 = syscall_open();
				if (iVar5 == -1) {
					errorCode = 0x46;
					outFd = (FILE *)0x1;
					message = "/proc/self/maps is unaccessible, probably a LD_PRELOAD attempt exit..\n";
					fwrite("/proc/self/maps is unaccessible, probably a LD_PRELOAD attempt exit..\n",1,0x46,stderr);
					hasError = 1;
				} else {
					do {
						do {
							while( true ) {
								outFd = (FILE *)0x100;
								message = local_114;
								errorCode = iVar5;
								revLenCounter = syscall_gets(message,0x100);
								hasError = 0;
								if (revLenCounter == 0)
									goto LAB_08048a77_RET;
								iVar6 = isLib(local_114,0x8048c2b ["libc"]);
								if (iVar6 == 0)
									break;
								bVar2 = true;
							}
						} while (!bVar2);
						iVar6 = isLib(local_114,0x8048c30 ["ld"]);
						if (iVar6 != 0) {
							if (argc == 2)
								goto LAB_08048996;
							errorCode = 0x22;
							outFd = (FILE *)0x1;
							message = "You need to provied only one arg.\n";
							hasError = fwrite("You need to provied only one arg.\n",1,0x22,stderr);
							goto LAB_08048a77_RET;
						}
						message = afterSubstr(local_114,0x8048c57 ["00000000 00:00 0"]);
					} while (message != (char *)0x0);
					errorCode = 0x30;
					outFd = (FILE *)0x1;
					message = "LD_PRELOAD detected through memory maps exit ..\n";
					hasError = fwrite("LD_PRELOAD detected through memory maps exit ..\n",1,0x30,stderr);
				}
			} else {
				errorCode = 0x25;
				outFd = (FILE *)0x1;
				message = "Injection Linked lib detected exit..\n";
				fwrite("Injection Linked lib detected exit..\n",1,0x25,stderr);
				hasError = 1;
			}
		} else {
			errorCode = 0x25;
			outFd = (FILE *)0x1;
			message = "Injection Linked lib detected exit..\n";
			fwrite("Injection Linked lib detected exit..\n",1,0x25,stderr);
			hasError = 1;
		}
	}

	LAB_08048a77_RET:
		if (stackCheck == *(int *)(in_GS_OFFSET + 0x14)) { // Almost always true, this is a stack canary check
			return hasError;
		}
		/* WARNING: Subroutine does not return */
		__stack_chk_fail(message,outFd,errorCode);

	LAB_08048996:
		idx = idx + 1; // So the first loop, idx = 0xffffffff + 1 = 0
		revLenCounter = 0xffffffff;
		message = *(char **)(argv + 4);
		do {
			if (revLenCounter == 0)
				break;
			revLenCounter = revLenCounter - 1;
			c = *message;
			message = message + (uint)bVar8 * -2 + 1; // bVar8 is 0, so this is just message++
		} while (c != '\0');
		if (~revLenCounter - 1 <= idx) // if (idx >= strlen(argv[1]))
			goto code_r0x080489ca;
		putchar((int)*(char *)(idx + *(char **)(argv + 4)) + idx); // putchar(argv[1][idx] + idx)
		goto LAB_08048996;

	code_r0x080489ca:
		message = (char *)0xa;
		outFd = stdout;
		hasError = fputc(10,stdout); // Print a newline
		goto LAB_08048a77_RET;
}



/* ************************************************************************** */
/*                                                                            */
/*                             Simplified version                             */
/*                                                                            */
/*                          Deduced after analysis.                           */
/*                                                                            */
/* ************************************************************************** */


size_t main(int argc, char **argv) {
	if (ptrace(PTRACE_TRACEME, 0, 1, 0) < 0) {
		puts("You should not reverse this");
		return 1;
	}

	if (getenv("LD_PRELOAD") != NULL || access("/etc/ld.so.preload", F_OK) == 0) {
		fprintf(stderr, "Injection Linked lib detected exit..\n");
		return 1;
	}

	if (argc != 2) {
		fprintf(stderr, "You need to provide only one arg.\n");
		return 1;
	}

	const char *input = argv[1];
	for (unsigned int idx = 0; input[idx] != '\0'; idx++) {
		putchar(input[idx] + idx);
	}
	putchar('\n');

	return 0;
}
