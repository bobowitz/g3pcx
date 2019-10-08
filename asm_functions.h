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
  for (i = 0; i < 3; i++) tmp[i] = x_mm[i + 16]; 
  tmp[3] = 0.0;
  __asm__ __volatile__("vmovapd (%0), %%ymm12\n" ::"r"(tmp));
  for (i = 0; i < 3; i++) tmp[i] = x_mm[i + 17]; 
  __asm__ __volatile__("vmovapd (%0), %%ymm14\n" ::"r"(tmp));

  _mm_free(tmp);
}
void rosen_vmovapd_out(double *x_mm) {
	__asm__ __volatile__("vmovapd %%ymm1, (%0)\n"::"r"(x_mm));
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

void rosen_mov_100_1() {
  double *tmp = _mm_malloc(32, 32);
  int i;

  tmp[0] = tmp[1] = tmp[2] = tmp[3] = 100.0;
  __asm__ __volatile__("vmovapd (%0), %%ymm2\n" ::"r"(tmp));

  for (i = 0; i < 4; i++) tmp[i] = 1.0;
  __asm__ __volatile__("vmovapd (%0), %%ymm15\n" ::"r"(tmp));
  _mm_free(tmp);
}
void rosen_mul_4() {
  mul_ymm1_ymm2;
  mul_ymm4_ymm2;
  mul_ymm7_ymm2;
  mul_ymm10_ymm2;
  mul_ymm13_ymm2;
}

void rosen_sub_5() {
  sub_ymm0_ymm15;
  sub_ymm3_ymm15;
  sub_ymm6_ymm15;
  sub_ymm9_ymm15;
  sub_ymm12_ymm15;
}

void rosen_fma_6() {
  fma_ymm0_ymm0_ymm1;
  fma_ymm3_ymm3_ymm4;
  fma_ymm6_ymm6_ymm7;
  fma_ymm9_ymm9_ymm10;
  fma_ymm12_ymm12_ymm13;
}

void rosen_add_7() {
  add_ymm1_ymm4;
  add_ymm7_ymm10;
  add_ymm1_ymm13;
  add_ymm1_ymm7;
}
