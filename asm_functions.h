void rosen_vmovpd(double *x_mm) {
  __asm__ __volatile__("vmovpd (%0), %ymm0\n", ::"r"(x_mm));
  __asm__ __volatile__("vmovpd (%0), %ymm2\n", ::"r"(x_mm + 1));
  __asm__ __volatile__("vmovpd (%0), %ymm3\n", ::"r"(x_mm + 4));
  __asm__ __volatile__("vmovpd (%0), %ymm5\n", ::"r"(x_mm + 5));
  __asm__ __volatile__("vmovpd (%0), %ymm6\n", ::"r"(x_mm + 8));
  __asm__ __volatile__("vmovpd (%0), %ymm8\n", ::"r"(x_mm + 9));
  __asm__ __volatile__("vmovpd (%0), %ymm9\n", ::"r"(x_mm + 12));
  __asm__ __volatile__("vmovpd (%0), %ymm11\n", ::"r"(x_mm + 13));
  __asm__ __volatile__("vmovpd (%0), %ymm12\n", ::"r"(x_mm + 16));
  __asm__ __volatile__("vmovpd (%0), %ymm14\n", ::"r"(x_mm + 17));
}
