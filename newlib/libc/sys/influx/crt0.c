#include <fcntl.h>
#include <stdint.h>

extern void exit(int code);
extern int main(uint64_t argc, const char **argv, const char **envp);
extern char **environ;

void _start(uint64_t argc, const char **argv, const char **envp)
{
	// Set env pointer
	environ = (char **)envp;

	// Call the main function and exit from the program
	int code = main(argc, argv, envp);
	exit(code);
}