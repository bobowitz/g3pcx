// simd sqaure
#ifndef square_ymm0toymm1
	#define square_ymm0toymm1 \
	__asm__ __volatile__("vmulpd %%ymm0, %%ymm0, %%ymm1\n"::);
#endif
#ifndef square_ymm1
	#define square_ymm1 \
	__asm__ __volatile__("vmulpd %%ymm1, %%ymm1, %%ymm1\n"::);
#endif
#ifndef square_ymm3toymm4
	#define square_ymm3toymm4 \
	__asm__ __volatile__("vmulpd %%ymm3, %%ymm3, %%ymm4\n"::);
#endif
#ifndef square_ymm4
	#define square_ymm4 \
	__asm__ __volatile__("vmulpd %%ymm4, %%ymm4, %%ymm4\n"::);
#endif
#ifndef square_ymm6toymm7
	#define square_ymm6toymm7 \
	__asm__ __volatile__("vmulpd %%ymm6, %%ymm6, %%ymm7\n"::);
#endif
#ifndef square_ymm7
	#define square_ymm7 \
	__asm__ __volatile__("vmulpd %%ymm7, %%ymm7, %%ymm7\n"::);
#endif
#ifndef square_ymm9toymm10
	#define square_ymm9toymm10 \
	__asm__ __volatile__("vmulpd %%ymm9, %%ymm9, %%ymm10\n"::);
#endif
#ifndef square_ymm10
	#define square_ymm10 \
	__asm__ __volatile__("vmulpd %%ymm10, %%ymm10, %%ymm10\n"::);
#endif
#ifndef square_ymm12toymm13
	#define square_ymm12toymm13 \
	__asm__ __volatile__("vmulpd %%ymm12, %%ymm12, %%ymm13\n"::);
#endif
#ifndef square_ymm13
	#define square_ymm13 \
	__asm__ __volatile__("vmulpd %%ymm13, %%ymm13, %%ymm13\n"::);
#endif
#ifndef square_ymm0
	#define square_ymm0 \
	__asm__ __volatile__("vmulpd %%ymm0, %%ymm0, %%ymm0\n"::);
#endif
#ifndef square_ymm3
	#define square_ymm3 \
	__asm__ __volatile__("vmulpd %%ymm3, %%ymm3, %%ymm3\n"::);
#endif
#ifndef square_ymm6
	#define square_ymm6 \
	__asm__ __volatile__("vmulpd %%ymm6, %%ymm6, %%ymm6\n"::);
#endif
#ifndef square_ymm9
	#define square_ymm9 \
	__asm__ __volatile__("vmulpd %%ymm9, %%ymm9, %%ymm9\n"::);
#endif
#ifndef square_ymm12
	#define square_ymm12 \
	__asm__ __volatile__("vmulpd %%ymm12, %%ymm12, %%ymm12\n"::);
#endif

// simd sub
#ifndef sub_ymm1_ymm2
	#define sub_ymm1_ymm2 \
	__asm__ __volatile__("vsubpd %%ymm2, %%ymm1, %%ymm1\n"::);
#endif
#ifndef sub_ymm4_ymm5
	#define sub_ymm4_ymm5 \
	__asm__ __volatile__("vsubpd %%ymm5, %%ymm4, %%ymm4\n"::);
#endif
#ifndef sub_ymm7_ymm8
	#define sub_ymm7_ymm8 \
	__asm__ __volatile__("vsubpd %%ymm8, %%ymm7, %%ymm7\n"::);
#endif
#ifndef sub_ymm10_ymm11
	#define sub_ymm10_ymm11 \
	__asm__ __volatile__("vsubpd %%ymm11, %%ymm10, %%ymm10\n"::);
#endif
#ifndef sub_ymm13_ymm14
	#define sub_ymm13_ymm14 \
	__asm__ __volatile__("vsubpd %%ymm14, %%ymm13, %%ymm13\n"::);
#endif
#ifndef sub_ymm0_ymm15
	#define sub_ymm0_ymm15 \
	__asm__ __volatile__("vsubpd %%ymm15, %%ymm0, %%ymm0\n"::);
#endif
#ifndef sub_ymm3_ymm15
	#define sub_ymm3_ymm15 \
	__asm__ __volatile__("vsubpd %%ymm15, %%ymm3, %%ymm3\n"::);
#endif
#ifndef sub_ymm6_ymm15
	#define sub_ymm6_ymm15 \
	__asm__ __volatile__("vsubpd %%ymm15, %%ymm6, %%ymm6\n"::);
#endif
#ifndef sub_ymm9_ymm15
	#define sub_ymm9_ymm15 \
	__asm__ __volatile__("vsubpd %%ymm15, %%ymm9, %%ymm9\n"::);
#endif
#ifndef sub_ymm12_ymm15
	#define sub_ymm12_ymm15 \
	__asm__ __volatile__("vsubpd %%ymm15, %%ymm12, %%ymm12\n"::);
#endif

// simd fma
#ifndef fma_ymm0_ymm0_ymm1
	#define fma_ymm0_ymm0_ymm1 \
	__asm__ __volatile__( "vfmadd231pd %%ymm0, %%ymm0, %%ymm1\n"::);
#endif
#ifndef fma_ymm3_ymm3_ymm4
	#define fma_ymm3_ymm3_ymm4 \
	__asm__ __volatile__( "vfmadd231pd %%ymm3, %%ymm3, %%ymm4\n"::);
#endif
#ifndef fma_ymm6_ymm6_ymm7
	#define fma_ymm6_ymm6_ymm7 \
	__asm__ __volatile__( "vfmadd231pd %%ymm6, %%ymm6, %%ymm7\n"::);
#endif
#ifndef fma_ymm9_ymm9_ymm10
	#define fma_ymm9_ymm9_ymm10 \
	__asm__ __volatile__( "vfmadd231pd %%ymm9, %%ymm9, %%ymm10\n"::);
#endif
#ifndef fma_ymm12_ymm12_ymm13
	#define fma_ymm12_ymm12_ymm13 \
	__asm__ __volatile__( "vfmadd231pd %%ymm12, %%ymm12, %%ymm13\n"::);
#endif

// simd mul
#ifndef mul_ymm1_ymm2
	#define mul_ymm1_ymm2 \
	__asm__ __volatile__( "vmulpd %%ymm1, %%ymm2, %%ymm1\n"::);
#endif
#ifndef mul_ymm4_ymm2
	#define mul_ymm4_ymm2 \
	__asm__ __volatile__( "vmulpd %%ymm4, %%ymm2, %%ymm4\n"::);
#endif
#ifndef mul_ymm7_ymm2
	#define mul_ymm7_ymm2 \
	__asm__ __volatile__( "vmulpd %%ymm7, %%ymm2, %%ymm7\n"::);
#endif
#ifndef mul_ymm10_ymm2
	#define mul_ymm10_ymm2 \
	__asm__ __volatile__( "vmulpd %%ymm10, %%ymm2, %%ymm10\n"::);
#endif
#ifndef mul_ymm13_ymm2
	#define mul_ymm13_ymm2 \
	__asm__ __volatile__( "vmulpd %%ymm13, %%ymm2, %%ymm13\n"::);
#endif
// simd add
#ifndef add_ymm1_ymm4
	#define add_ymm1_ymm4 \
	__asm__ __volatile__( "vaddpd %%ymm1, %%ymm4, %%ymm1\n"::);
#endif
#ifndef add_ymm7_ymm10
	#define add_ymm7_ymm10 \
	__asm__ __volatile__( "vaddpd %%ymm7, %%ymm10, %%ymm7\n"::);
#endif
#ifndef add_ymm1_ymm13
	#define add_ymm1_ymm13 \
	__asm__ __volatile__( "vaddpd %%ymm1, %%ymm13, %%ymm1\n"::);
#endif
#ifndef add_ymm1_ymm7
	#define add_ymm1_ymm7 \
	__asm__ __volatile__( "vaddpd %%ymm1, %%ymm7, %%ymm1\n"::);
#endif
