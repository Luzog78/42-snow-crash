#include <unistd.h>

int main(int argc, char **argv) {
	char    buffer[1024]; // Because we know that the token is less than 1024 bytes

	int     readResult = read(0, buffer, 1024);
	if (readResult < 0)
		return 1;

	for (int i = 0; i < readResult; i++)
		if (i != readResult - 1 || buffer[i] != '\n') // If the last character is a newline, don't decrypt it
			buffer[i] = buffer[i] - i; // Decrypt the token

	write(1, buffer, readResult);
	return 0;
}
