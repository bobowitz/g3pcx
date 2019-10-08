void rosen_vmovapd(double *x_mm) {
  double *tmp = _mm_malloc(32, 32);
  int i;
  __asm__ __volatile__("vmovapd (%0), %%ymm0\n" ::"r"(x_mm));
  for (i = 0; i < 4; i++) tmp[i] = x_mm[i + 1];
  __asm__ __volatile__("vmovapd (%0), %%ymm2\n" ::"r"(tmp));
  __asm__ __volatile__("vmovapd (%0), %%ymm3\n" ::"r"(x_mm + 4));
  for (i = 0; i < 4; i++) tmp[i] = x_mm[i + 5];
  __asm__ __volatile__("vmovapd (%0), %%ymm5\n" ::"r"(tmp));
  __asm__ __volatile__("vmovapd (%0), %%ymm6\n" ::"r"(x_mm + 8));
  for (i = 0; i < 4; i++) tmp[i] = x_mm[i + 9];
  __asm__ __volatile__("vmovapd (%0), %%ymm8\n" ::"r"(tmp));
  __asm__ __volatile__("vmovapd (%0), %%ymm9\n" ::"r"(x_mm + 12));
  for (i = 0; i < 4; i++) tmp[i] = x_mm[i + 13];
  __asm__ __volatile__("vmovapd (%0), %%ymm11\n" ::"r"(tmp));
  __asm__ __volatile__("vmovapd (%0), %%ymm12\n" ::"r"(x_mm + 16));
  for (i = 0; i < 4; i++) tmp[i] = x_mm[i + 17];
  __asm__ __volatile__("vmovapd (%0), %%ymm14\n" ::"r"(tmp));

  _mm_free(tmp);
}

void rosen_sq_1() {
  square_ymm0toymm1; 
  square_ymm3toymm4; 
  square_ymm6toymm7; 
  square_ymm9toymm10; 
  square_ymm12toymm13;
}

void rosen_sub_2() {
  sub_ymm1_ymm2;
  sub_ymm4_ymm5;
  sub_ymm7_ymm8;
  sub_ymm10_ymm11;
  sub_ymm13_ymm14;
}

void rosen_sq_3() {
  square_ymm1;
  square_ymm4;
  square_ymm7;
  square_ymm10;
  square_ymm13;
}

