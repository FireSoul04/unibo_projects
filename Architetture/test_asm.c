#include <stdio.h>
#include <string.h>

int main() {
	char* str = "Hello World\n";
	long len = strlen(str);
	int ret = 0;

    int c = 140;

	__asm__("movq $1, %%rax \n\t"
		"movq $1, %%rdi \n\t"
		"movq %1, %%rsi \n\t"
		"movl %2, %%edx \n\t"
		"syscall"
		: "=g"(ret)
		: "g"(str), "g" (len));

    __asm__("label: movq $24, %%rax \n\t"
		"addq %1, %%rax \n\t"
		"cmpq $500, %%rax \n\t"
		"jl label \n\t"
		"end: \n\t"
        : "=g"(c)
		: "g"(c));

    printf("%d", c);

    return 0;
}