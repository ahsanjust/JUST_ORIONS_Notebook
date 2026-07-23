// Inline x86 GCD via idiv | faster than __gcd on old compilers.
// Avoid for large inputs; prefer std::gcd (C++17) otherwise.
int gcdFast(int a, int b) {
  int result;
  __asm__ __volatile__(
      "movl %1, %%eax;"
      "movl %2, %%ebx;"
      "CONTD: cmpl $0, %%ebx;"
      "je DONE;"
      "xorl %%edx, %%edx;"
      "idivl %%ebx;"
      "movl %%ebx, %%eax;"
      "movl %%edx, %%ebx;"
      "jmp CONTD;"
      "DONE: movl %%eax, %0;"
      : "=g"(result)
      : "g"(a), "g"(b));
  return result;
}
