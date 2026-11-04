/* A Shell gives 4 KB of stack; libnix's startup sets up this much instead.
 * Chuckie Egg keeps little on the stack, so 64 KB is plenty.
 * The AmiCradle Team. GPL 3, like Chuckie Egg. */
unsigned long __stack = 64 * 1024;
