	.file	"my_gemm.c"
# GNU C99 (Ubuntu 9.4.0-1ubuntu1~20.04.1) version 9.4.0 (x86_64-linux-gnu)
#	compiled by GNU C version 9.4.0, GMP version 6.2.0, MPFR version 4.0.2, MPC version 1.1.0, isl version isl-0.22.1-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed:  -imultiarch x86_64-linux-gnu -D_REENTRANT my_gemm.c
# -march=bdver4 -mmmx -mno-3dnow -msse -msse2 -msse3 -mssse3 -msse4a -mcx16
# -msahf -mmovbe -maes -mno-sha -mpclmul -mpopcnt -mabm -mlwp -mfma -mfma4
# -mxop -mbmi -mno-sgx -mbmi2 -mno-pconfig -mno-wbnoinvd -mtbm -mavx -mavx2
# -msse4.2 -msse4.1 -mlzcnt -mno-rtm -mno-hle -mno-rdrnd -mf16c -mfsgsbase
# -mno-rdseed -mprfchw -mno-adx -mfxsr -mxsave -mxsaveopt -mno-avx512f
# -mno-avx512er -mno-avx512cd -mno-avx512pf -mno-prefetchwt1
# -mno-clflushopt -mno-xsavec -mno-xsaves -mno-avx512dq -mno-avx512bw
# -mno-avx512vl -mno-avx512ifma -mno-avx512vbmi -mno-avx5124fmaps
# -mno-avx5124vnniw -mno-clwb -mmwaitx -mno-clzero -mno-pku -mno-rdpid
# -mno-gfni -mno-shstk -mno-avx512vbmi2 -mno-avx512vnni -mno-vaes
# -mno-vpclmulqdq -mno-avx512bitalg -mno-avx512vpopcntdq -mno-movdiri
# -mno-movdir64b -mno-waitpkg -mno-cldemote -mno-ptwrite
# --param l1-cache-size=32 --param l1-cache-line-size=64
# --param l2-cache-size=1024 -mtune=bdver4 -O3 -Wall -std=c99 -fopenmp
# -fPIC -fverbose-asm -fasynchronous-unwind-tables -fstack-protector-strong
# -Wformat-security -fstack-clash-protection -fcf-protection
# options enabled:  -fPIC -faggressive-loop-optimizations -falign-functions
# -falign-jumps -falign-labels -falign-loops -fassume-phsa
# -fasynchronous-unwind-tables -fauto-inc-dec -fbranch-count-reg
# -fcaller-saves -fcode-hoisting -fcombine-stack-adjustments -fcommon
# -fcompare-elim -fcprop-registers -fcrossjumping -fcse-follow-jumps
# -fdefer-pop -fdelete-null-pointer-checks -fdevirtualize
# -fdevirtualize-speculatively -fdwarf2-cfi-asm -fearly-inlining
# -feliminate-unused-debug-types -fexpensive-optimizations
# -fforward-propagate -ffp-int-builtin-inexact -ffunction-cse -fgcse
# -fgcse-after-reload -fgcse-lm -fgnu-runtime -fgnu-unique
# -fguess-branch-probability -fhoist-adjacent-loads -fident -fif-conversion
# -fif-conversion2 -findirect-inlining -finline -finline-atomics
# -finline-functions -finline-functions-called-once
# -finline-small-functions -fipa-bit-cp -fipa-cp -fipa-cp-clone -fipa-icf
# -fipa-icf-functions -fipa-icf-variables -fipa-profile -fipa-pure-const
# -fipa-ra -fipa-reference -fipa-reference-addressable -fipa-sra
# -fipa-stack-alignment -fipa-vrp -fira-hoist-pressure
# -fira-share-save-slots -fira-share-spill-slots
# -fisolate-erroneous-paths-dereference -fivopts -fkeep-static-consts
# -fleading-underscore -flifetime-dse -floop-interchange
# -floop-unroll-and-jam -flra-remat -flto-odr-type-merging -fmath-errno
# -fmerge-constants -fmerge-debug-strings -fmove-loop-invariants
# -fomit-frame-pointer -foptimize-sibling-calls -foptimize-strlen
# -fpartial-inlining -fpeel-loops -fpeephole -fpeephole2 -fplt
# -fpredictive-commoning -fprefetch-loop-arrays -free -freg-struct-return
# -freorder-blocks -freorder-blocks-and-partition -freorder-functions
# -frerun-cse-after-loop -fsched-critical-path-heuristic
# -fsched-dep-count-heuristic -fsched-group-heuristic -fsched-interblock
# -fsched-last-insn-heuristic -fsched-rank-heuristic -fsched-spec
# -fsched-spec-insn-heuristic -fsched-stalled-insns-dep -fschedule-fusion
# -fschedule-insns2 -fsemantic-interposition -fshow-column -fshrink-wrap
# -fshrink-wrap-separate -fsigned-zeros -fsplit-ivs-in-unroller
# -fsplit-loops -fsplit-paths -fsplit-wide-types -fssa-backprop
# -fssa-phiopt -fstack-clash-protection -fstack-protector-strong
# -fstdarg-opt -fstore-merging -fstrict-aliasing
# -fstrict-volatile-bitfields -fsync-libcalls -fthread-jumps
# -ftoplevel-reorder -ftrapping-math -ftree-bit-ccp -ftree-builtin-call-dce
# -ftree-ccp -ftree-ch -ftree-coalesce-vars -ftree-copy-prop -ftree-cselim
# -ftree-dce -ftree-dominator-opts -ftree-dse -ftree-forwprop -ftree-fre
# -ftree-loop-distribute-patterns -ftree-loop-distribution
# -ftree-loop-if-convert -ftree-loop-im -ftree-loop-ivcanon
# -ftree-loop-optimize -ftree-loop-vectorize -ftree-parallelize-loops=
# -ftree-partial-pre -ftree-phiprop -ftree-pre -ftree-pta -ftree-reassoc
# -ftree-scev-cprop -ftree-sink -ftree-slp-vectorize -ftree-slsr -ftree-sra
# -ftree-switch-conversion -ftree-tail-merge -ftree-ter -ftree-vrp
# -funit-at-a-time -funswitch-loops -funwind-tables -fverbose-asm
# -fversion-loops-for-strides -fzero-initialized-in-bss
# -m128bit-long-double -m64 -m80387 -mabm -maes -malign-stringops -mavx
# -mavx2 -mavx256-split-unaligned-store -mbmi -mbmi2 -mcx16 -mf16c
# -mfancy-math-387 -mfma -mfma4 -mfp-ret-in-387 -mfsgsbase -mfxsr -mglibc
# -mieee-fp -mlong-double-80 -mlwp -mlzcnt -mmmx -mmovbe -mmwaitx -mpclmul
# -mpopcnt -mprfchw -mpush-args -mred-zone -msahf -msse -msse2 -msse3
# -msse4 -msse4.1 -msse4.2 -msse4a -mssse3 -mstv -mtbm
# -mtls-direct-seg-refs -mvzeroupper -mxop -mxsave -mxsaveopt

	.text
	.p2align 4,,10
	.p2align 3
	.type	saxpy_gemm._omp_fn.0, @function
saxpy_gemm._omp_fn.0:
.LFB560:
	.cfi_startproc
	endbr64	
	pushq	%r15	#
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14	#
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	movq	%rdi, %rax	# tmp169, .omp_data_i
	pushq	%r13	#
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12	#
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp	#
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx	#
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
# my_gemm.c:71:   #pragma omp parallel//nowait
	movq	%rdi, -16(%rsp)	# .omp_data_i, %sfp
	movq	120(%rdi), %rbx	# *.omp_data_i_5(D).ldA, ldA
	movq	136(%rdi), %rcx	# *.omp_data_i_5(D).ldC, ldC
	movq	128(%rdi), %r13	# *.omp_data_i_5(D).ldB, ldB
	movq	72(%rax), %r10	# *.omp_data_i_5(D).M, M
	movq	88(%rdi), %rdi	# *.omp_data_i_5(D).K, K
	movq	56(%rax), %r14	# *.omp_data_i_5(D).B, B
	movq	48(%rax), %r15	# *.omp_data_i_5(D).A, A
	movq	%rbx, -56(%rsp)	# ldA, %sfp
# my_gemm.c:74:   for (m = 0; m < M; ++m) {
	movq	$0, 96(%rax)	#, *.omp_data_i_5(D).m
# my_gemm.c:71:   #pragma omp parallel//nowait
	movq	80(%rax), %rsi	# *.omp_data_i_5(D).N, N
	movq	64(%rax), %rdx	# *.omp_data_i_5(D).C, C
	movq	%rdi, -72(%rsp)	# K, %sfp
	movq	%r10, -64(%rsp)	# M, %sfp
	movq	%r14, -32(%rsp)	# B, %sfp
	movq	%r15, -24(%rsp)	# A, %sfp
# my_gemm.c:74:   for (m = 0; m < M; ++m) {
	testq	%r10, %r10	# M
	je	.L26	#,
	salq	$2, %rbx	#, _205
	vmovaps	(%rax), %xmm2	# *.omp_data_i_5(D)._A, .omp_data_i___A_lsm.20
	vmovaps	16(%rax), %xmm1	# *.omp_data_i_5(D)._B, .omp_data_i___B_lsm.14
	leaq	-17(%rsi), %r11	#, tmp162
	movq	%rbx, -48(%rsp)	# _205, %sfp
	leaq	0(,%rcx,4), %rbx	#, _215
	vmovaps	32(%rax), %xmm0	# *.omp_data_i_5(D)._C, .omp_data_i___C_lsm.16
	salq	$2, %r13	#, _193
	movq	%rbx, -40(%rsp)	# _215, %sfp
	movq	104(%rax), %rax	# *.omp_data_i_5(D).n, .omp_data_i__n_lsm.18
	leaq	(%r15,%rdi,4), %rbp	#, ivtmp.59
	xorl	%r14d, %r14d	# ivtmp.57
	leaq	240(%rdx), %r12	#, ivtmp.64
	xorl	%r15d, %r15d	# ivtmp.61
	xorl	%ecx, %ecx	# .omp_data_i__n_lsm.19
	xorl	%edi, %edi	# .omp_data_i___B_lsm.15
	andq	$-16, %r11	#, _182
	.p2align 4,,10
	.p2align 3
.L4:
# my_gemm.c:75:     for (k = 0; k < K; ++k){
	cmpq	$0, -72(%rsp)	#, %sfp
	je	.L29	#,
	movq	-24(%rsp), %rax	# %sfp, A
	movq	-32(%rsp), %rcx	# %sfp, ivtmp.53
	leaq	(%rax,%r15,4), %r9	#, ivtmp.51
	.p2align 4,,10
	.p2align 3
.L9:
# /usr/lib/gcc/x86_64-linux-gnu/9/include/xmmintrin.h:894:   return __extension__ (__m128)(__v4sf){ __F, __F, __F, __F };
	vbroadcastss	(%r9), %xmm2	# MEM[base: _195, offset: 0B], .omp_data_i___A_lsm.20
# my_gemm.c:77:       for(n = 0; n < N; n+=4){
	testq	%rsi, %rsi	# N
	je	.L30	#,
	cmpq	$16, %rsi	#, N
	jbe	.L15	#,
	leaq	240(%rcx), %r8	#, ivtmp.41
	leaq	16(%r11), %rax	#, .omp_data_i__n_lsm.18
	movq	%r12, %rdi	# ivtmp.64, ivtmp.43
	xorl	%r10d, %r10d	# _63
.L12:
# /usr/lib/gcc/x86_64-linux-gnu/9/include/xmmintrin.h:198:   return (__m128) ((__v4sf)__A * (__v4sf)__B);
	vmulps	-240(%r8), %xmm2, %xmm0	# MEM[base: _118, offset: -240B], .omp_data_i___A_lsm.20, tmp149
	prefetcht0	(%r8)	# ivtmp.41
	movq	%r10, %rbx	# _63, _211
	prefetcht0	(%rdi)	# ivtmp.43
# my_gemm.c:77:       for(n = 0; n < N; n+=4){
	addq	$16, %r10	#, _63
	addq	$64, %r8	#, ivtmp.41
	addq	$64, %rdi	#, ivtmp.43
# /usr/lib/gcc/x86_64-linux-gnu/9/include/xmmintrin.h:186:   return (__m128) ((__v4sf)__A + (__v4sf)__B);
	vaddps	-304(%rdi), %xmm0, %xmm0	# MEM[base: _119, offset: -240B], tmp149, tmp150
# /usr/lib/gcc/x86_64-linux-gnu/9/include/xmmintrin.h:976:   *(__m128 *)__P = __A;
	vmovaps	%xmm0, -304(%rdi)	# tmp150, MEM[base: _119, offset: -240B]
# /usr/lib/gcc/x86_64-linux-gnu/9/include/xmmintrin.h:198:   return (__m128) ((__v4sf)__A * (__v4sf)__B);
	vmulps	-288(%r8), %xmm2, %xmm0	# MEM[base: _118, offset: -224B], .omp_data_i___A_lsm.20, tmp151
# /usr/lib/gcc/x86_64-linux-gnu/9/include/xmmintrin.h:186:   return (__m128) ((__v4sf)__A + (__v4sf)__B);
	vaddps	-288(%rdi), %xmm0, %xmm0	# MEM[base: _119, offset: -224B], tmp151, tmp152
# /usr/lib/gcc/x86_64-linux-gnu/9/include/xmmintrin.h:976:   *(__m128 *)__P = __A;
	vmovaps	%xmm0, -288(%rdi)	# tmp152, MEM[base: _119, offset: -224B]
# /usr/lib/gcc/x86_64-linux-gnu/9/include/xmmintrin.h:198:   return (__m128) ((__v4sf)__A * (__v4sf)__B);
	vmulps	-272(%r8), %xmm2, %xmm0	# MEM[base: _118, offset: -208B], .omp_data_i___A_lsm.20, tmp153
# /usr/lib/gcc/x86_64-linux-gnu/9/include/xmmintrin.h:186:   return (__m128) ((__v4sf)__A + (__v4sf)__B);
	vaddps	-272(%rdi), %xmm0, %xmm0	# MEM[base: _119, offset: -208B], tmp153, tmp154
# /usr/lib/gcc/x86_64-linux-gnu/9/include/xmmintrin.h:976:   *(__m128 *)__P = __A;
	vmovaps	%xmm0, -272(%rdi)	# tmp154, MEM[base: _119, offset: -208B]
# /usr/lib/gcc/x86_64-linux-gnu/9/include/xmmintrin.h:198:   return (__m128) ((__v4sf)__A * (__v4sf)__B);
	vmulps	-256(%r8), %xmm2, %xmm0	# MEM[base: _118, offset: -192B], .omp_data_i___A_lsm.20, tmp155
# /usr/lib/gcc/x86_64-linux-gnu/9/include/xmmintrin.h:186:   return (__m128) ((__v4sf)__A + (__v4sf)__B);
	vaddps	-256(%rdi), %xmm0, %xmm0	# MEM[base: _119, offset: -192B], tmp155, tmp156
# /usr/lib/gcc/x86_64-linux-gnu/9/include/xmmintrin.h:976:   *(__m128 *)__P = __A;
	vmovaps	%xmm0, -256(%rdi)	# tmp156, MEM[base: _119, offset: -192B]
	cmpq	%r11, %rbx	# _182, _211
	jne	.L12	#,
	.p2align 4,,10
	.p2align 3
.L13:
# /usr/lib/gcc/x86_64-linux-gnu/9/include/xmmintrin.h:927:   return *(__m128 *)__P;
	vmovaps	(%rcx,%rax,4), %xmm1	# MEM[base: _100, index: _139, step: 4, offset: 0B], .omp_data_i___B_lsm.14
# /usr/lib/gcc/x86_64-linux-gnu/9/include/xmmintrin.h:198:   return (__m128) ((__v4sf)__A * (__v4sf)__B);
	vmulps	%xmm1, %xmm2, %xmm0	# .omp_data_i___B_lsm.14, .omp_data_i___A_lsm.20, tmp157
# /usr/lib/gcc/x86_64-linux-gnu/9/include/xmmintrin.h:186:   return (__m128) ((__v4sf)__A + (__v4sf)__B);
	vaddps	(%rdx,%rax,4), %xmm0, %xmm0	# MEM[base: _86, index: _139, step: 4, offset: 0B], tmp157, .omp_data_i___C_lsm.16
# /usr/lib/gcc/x86_64-linux-gnu/9/include/xmmintrin.h:976:   *(__m128 *)__P = __A;
	vmovaps	%xmm0, (%rdx,%rax,4)	# .omp_data_i___C_lsm.16, MEM[base: _86, index: _139, step: 4, offset: 0B]
# my_gemm.c:77:       for(n = 0; n < N; n+=4){
	addq	$4, %rax	#, .omp_data_i__n_lsm.18
# my_gemm.c:77:       for(n = 0; n < N; n+=4){
	cmpq	%rax, %rsi	# .omp_data_i__n_lsm.18, N
	ja	.L13	#,
	movl	$1, %edi	#, .omp_data_i___B_lsm.15
.L14:
	addq	$4, %r9	#, ivtmp.51
	addq	%r13, %rcx	# _193, ivtmp.53
# my_gemm.c:75:     for (k = 0; k < K; ++k){
	cmpq	%rbp, %r9	# ivtmp.59, ivtmp.51
	jne	.L9	#,
	movq	-72(%rsp), %r8	# %sfp, .omp_data_i__k_lsm.22
	movl	$1, %ecx	#, .omp_data_i__n_lsm.19
.L10:
	movq	-40(%rsp), %rbx	# %sfp, _215
	addq	-48(%rsp), %rbp	# %sfp, ivtmp.59
	incq	%r14	# ivtmp.57
	addq	-56(%rsp), %r15	# %sfp, ivtmp.61
	addq	%rbx, %rdx	# _215, ivtmp.63
	addq	%rbx, %r12	# _215, ivtmp.64
# my_gemm.c:74:   for (m = 0; m < M; ++m) {
	cmpq	%r14, -64(%rsp)	# ivtmp.57, %sfp
	jne	.L4	#,
	movq	-16(%rsp), %rbx	# %sfp, .omp_data_i
	andl	$1, %edi	#, .omp_data_i___B_lsm.15
	movq	%r8, 112(%rbx)	# .omp_data_i__k_lsm.22, *.omp_data_i_5(D).k
	je	.L5	#,
	vmovaps	%xmm1, 16(%rbx)	# .omp_data_i___B_lsm.14, *.omp_data_i_5(D)._B
	vmovaps	%xmm0, 32(%rbx)	# .omp_data_i___C_lsm.16, *.omp_data_i_5(D)._C
.L5:
	andl	$1, %ecx	#, .omp_data_i__n_lsm.19
	je	.L6	#,
	movq	-16(%rsp), %rbx	# %sfp, .omp_data_i
	movq	%rax, 104(%rbx)	# .omp_data_i__n_lsm.18, *.omp_data_i_5(D).n
	vmovaps	%xmm2, (%rbx)	# .omp_data_i___A_lsm.20, *.omp_data_i_5(D)._A
.L6:
	movq	-16(%rsp), %rax	# %sfp, .omp_data_i
	movq	-64(%rsp), %rbx	# %sfp, M
	movq	%rbx, 96(%rax)	# M, *.omp_data_i_5(D).m
.L26:
# my_gemm.c:71:   #pragma omp parallel//nowait
	popq	%rbx	#
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbp	#
	.cfi_def_cfa_offset 40
	popq	%r12	#
	.cfi_def_cfa_offset 32
	popq	%r13	#
	.cfi_def_cfa_offset 24
	popq	%r14	#
	.cfi_def_cfa_offset 16
	popq	%r15	#
	.cfi_def_cfa_offset 8
	ret	
	.p2align 4,,7
	.p2align 3
.L30:
	.cfi_restore_state
# my_gemm.c:77:       for(n = 0; n < N; n+=4){
	xorl	%eax, %eax	# .omp_data_i__n_lsm.18
	jmp	.L14	#
.L15:
# my_gemm.c:77:       for(n = 0; n < N; n+=4){
	xorl	%eax, %eax	# .omp_data_i__n_lsm.18
	jmp	.L13	#
.L29:
# my_gemm.c:75:     for (k = 0; k < K; ++k){
	xorl	%r8d, %r8d	# .omp_data_i__k_lsm.22
	jmp	.L10	#
	.cfi_endproc
.LFE560:
	.size	saxpy_gemm._omp_fn.0, .-saxpy_gemm._omp_fn.0
	.p2align 4,,10
	.p2align 3
	.globl	my_gemm
	.type	my_gemm, @function
my_gemm:
.LFB558:
	.cfi_startproc
	endbr64	
	pushq	%r15	#
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14	#
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13	#
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12	#
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp	#
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx	#
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$48, %rsp	#,
	.cfi_def_cfa_offset 104
# my_gemm.c:4: void my_gemm(float *A, float *B, float  *C, size_t M, size_t N, size_t K) {
	movq	%rdi, 8(%rsp)	# A, %sfp
	movq	%rdx, 16(%rsp)	# C, %sfp
	movq	%rcx, 24(%rsp)	# M, %sfp
	movq	%r9, 32(%rsp)	# K, %sfp
# my_gemm.c:32:   for (m = 0; m < M; m++)
	testq	%rcx, %rcx	# M
	je	.L61	#,
	testq	%r9, %r9	# K
	je	.L61	#,
	movq	%r8, %rbp	# tmp283, N
	testq	%r8, %r8	# N
	je	.L61	#,
	leaq	0(,%r9,4), %rax	#, _241
	leaq	0(,%r8,4), %r13	#, _247
	shrq	$2, %r8	#, bnd.73
	movq	%rbp, %r14	# N, niters_vector_mult_vf.74
	addq	%rax, %rdi	# _241, ivtmp.133
	movq	%rax, (%rsp)	# _241, %sfp
	andq	$-4, %r14	#, niters_vector_mult_vf.74
	movq	%rsi, %r12	# tmp280, B
	leaq	16(%rdx), %rax	#, ivtmp.140
	movq	%rdi, -112(%rsp)	# ivtmp.133, %sfp
	movq	%rdx, %rbx	# C, ivtmp.134
	movq	%rax, -96(%rsp)	# ivtmp.140, %sfp
	leaq	-5(%r8), %rax	#, tmp206
# my_gemm.c:34:       for (n = 0; n < N; n++)
	movq	$0, -16(%rsp)	#, %sfp
	movq	$0, -24(%rsp)	#, %sfp
	andq	$-4, %rax	#, tmp206
	movq	%rax, -80(%rsp)	# _211, %sfp
# my_gemm.c:32:   for (m = 0; m < M; m++)
	movq	$0, -32(%rsp)	#, %sfp
	addq	$4, %rax	#, _212
	movq	%rax, -8(%rsp)	# _212, %sfp
# my_gemm.c:34:       for (n = 0; n < N; n++)
	leaq	1(%r14), %rax	#, n
	movq	%rax, -72(%rsp)	# n, %sfp
	leaq	2(%r14), %rax	#, n
	movq	%rax, -56(%rsp)	# n, %sfp
	leaq	-1(%rbp), %rax	#, tmp277
	movq	%rax, -88(%rsp)	# tmp277, %sfp
	movq	%r13, -104(%rsp)	# _247, %sfp
	addq	%rdx, %r13	# C, ivtmp.136
	.p2align 4,,10
	.p2align 3
.L33:
	movq	8(%rsp), %rax	# %sfp, A
	movq	-16(%rsp), %rdi	# %sfp, ivtmp.138
	movq	%r12, %r9	# B, ivtmp.124
# my_gemm.c:35:         Crow(m, n) += Arow(m, k) * Brow(k, n);
	xorl	%r11d, %r11d	# ivtmp.126
	movq	16(%rsp), %rsi	# %sfp, C
	leaq	(%rax,%rdi,4), %r10	#, ivtmp.123
	movq	-24(%rsp), %rdi	# %sfp, ivtmp.135
	leaq	(%r14,%rdi), %rax	#, tmp270
	leaq	(%rsi,%rax,4), %rax	#, _5
	movq	%rax, -64(%rsp)	# _5, %sfp
	movq	-72(%rsp), %rax	# %sfp, tmp272
	addq	%rdi, %rax	# ivtmp.135, tmp272
	leaq	(%rsi,%rax,4), %rax	#, _128
	movq	%rax, -48(%rsp)	# _128, %sfp
	movq	-56(%rsp), %rax	# %sfp, tmp274
	addq	%rdi, %rax	# ivtmp.135, tmp274
	leaq	(%rsi,%rax,4), %rax	#, _89
	movq	%rax, -40(%rsp)	# _89, %sfp
	.p2align 4,,10
	.p2align 3
.L43:
	leaq	16(%r9), %rax	#, tmp249
	movq	%r10, %rdi	# ivtmp.123, ivtmp.123
	addq	$4, %r10	#, ivtmp.123
	movq	%rbx, %rcx	# ivtmp.134, vectp.76
	cmpq	%rax, %rbx	# tmp249, ivtmp.134
	movq	%r9, %rsi	# ivtmp.124, vectp.79
	setnb	%dl	#, tmp251
	cmpq	-96(%rsp), %r9	# %sfp, ivtmp.124
	setnb	%al	#, tmp253
	orl	%edx, %eax	# tmp251, tmp254
	cmpq	%r13, %rdi	# ivtmp.136, ivtmp.123
	setnb	%dl	#, tmp256
	cmpq	%r10, %rbx	# ivtmp.123, ivtmp.134
	setnb	%r15b	#, tmp258
	orl	%r15d, %edx	# tmp258, tmp259
	andl	%eax, %edx	# tmp254, tmp262
	andl	$1, %edx	#, tmp262
	je	.L45	#,
	cmpq	$2, -88(%rsp)	#, %sfp
	jbe	.L45	#,
	vbroadcastss	(%rdi), %xmm1	# MEM[base: _226, offset: 0B], vect_cst__110
	cmpq	$4, %r8	#, bnd.73
	jbe	.L44	#,
# my_gemm.c:4: void my_gemm(float *A, float *B, float  *C, size_t M, size_t N, size_t K) {
	xorl	%eax, %eax	# ivtmp_123
.L35:
# my_gemm.c:35:         Crow(m, n) += Arow(m, k) * Brow(k, n);
	vmulps	(%rsi), %xmm1, %xmm0	# MEM[base: vectp.79_113, offset: 0B], vect_cst__110, vect__16.82
	prefetcht0	304(%rsi)	#
	prefetcht0	304(%rcx)	#
	addq	$64, %rcx	#, vectp.76
	movq	%rax, %rdx	# ivtmp_123, ivtmp_203
	addq	$64, %rsi	#, vectp.79
	addq	$4, %rax	#, ivtmp_123
# my_gemm.c:35:         Crow(m, n) += Arow(m, k) * Brow(k, n);
	vaddps	-64(%rcx), %xmm0, %xmm0	# MEM[base: vectp.76_106, offset: 0B], vect__16.82, vect__17.83
	vmovups	%xmm0, -64(%rcx)	# vect__17.83, MEM[base: vectp.76_106, offset: 0B]
# my_gemm.c:35:         Crow(m, n) += Arow(m, k) * Brow(k, n);
	vmulps	-48(%rsi), %xmm1, %xmm0	# MEM[base: vectp.79_113, offset: 16B], vect_cst__110, vect__16.82
# my_gemm.c:35:         Crow(m, n) += Arow(m, k) * Brow(k, n);
	vaddps	-48(%rcx), %xmm0, %xmm0	# MEM[base: vectp.76_106, offset: 16B], vect__16.82, vect__17.83
	vmovups	%xmm0, -48(%rcx)	# vect__17.83, MEM[base: vectp.76_106, offset: 16B]
# my_gemm.c:35:         Crow(m, n) += Arow(m, k) * Brow(k, n);
	vmulps	-32(%rsi), %xmm1, %xmm0	# MEM[base: vectp.79_113, offset: 32B], vect_cst__110, vect__16.82
# my_gemm.c:35:         Crow(m, n) += Arow(m, k) * Brow(k, n);
	vaddps	-32(%rcx), %xmm0, %xmm0	# MEM[base: vectp.76_106, offset: 32B], vect__16.82, vect__17.83
	vmovups	%xmm0, -32(%rcx)	# vect__17.83, MEM[base: vectp.76_106, offset: 32B]
# my_gemm.c:35:         Crow(m, n) += Arow(m, k) * Brow(k, n);
	vmulps	-16(%rsi), %xmm1, %xmm0	# MEM[base: vectp.79_113, offset: 48B], vect_cst__110, vect__16.82
# my_gemm.c:35:         Crow(m, n) += Arow(m, k) * Brow(k, n);
	vaddps	-16(%rcx), %xmm0, %xmm0	# MEM[base: vectp.76_106, offset: 48B], vect__16.82, vect__17.83
	vmovups	%xmm0, -16(%rcx)	# vect__17.83, MEM[base: vectp.76_106, offset: 48B]
	movq	%rcx, %r15	# vectp.76, vectp.84
	cmpq	-80(%rsp), %rdx	# %sfp, ivtmp_203
	jne	.L35	#,
# my_gemm.c:35:         Crow(m, n) += Arow(m, k) * Brow(k, n);
	movq	-8(%rsp), %rdx	# %sfp, ivtmp.97
.L34:
	xorl	%eax, %eax	# ivtmp.96
	.p2align 4,,10
	.p2align 3
.L36:
# my_gemm.c:35:         Crow(m, n) += Arow(m, k) * Brow(k, n);
	vmulps	(%rsi,%rax), %xmm1, %xmm0	# MEM[base: vectp.79_142, index: ivtmp.96_193, offset: 0B], vect_cst__110, vect__16.82
	incq	%rdx	# ivtmp.97
# my_gemm.c:35:         Crow(m, n) += Arow(m, k) * Brow(k, n);
	vaddps	(%rcx,%rax), %xmm0, %xmm0	# MEM[base: vectp.76_141, index: ivtmp.96_193, offset: 0B], vect__16.82, vect__17.83
	vmovups	%xmm0, (%r15,%rax)	# vect__17.83, MEM[base: vectp.84_143, index: ivtmp.96_193, offset: 0B]
	addq	$16, %rax	#, ivtmp.96
	cmpq	%rdx, %r8	# ivtmp.97, bnd.73
	ja	.L36	#,
	cmpq	%r14, %rbp	# niters_vector_mult_vf.74, N
	je	.L39	#,
# my_gemm.c:35:         Crow(m, n) += Arow(m, k) * Brow(k, n);
	leaq	(%r14,%r11), %rax	#, tmp230
# my_gemm.c:35:         Crow(m, n) += Arow(m, k) * Brow(k, n);
	vmovss	(%r12,%rax,4), %xmm0	# *_15, *_15
# my_gemm.c:35:         Crow(m, n) += Arow(m, k) * Brow(k, n);
	movq	-64(%rsp), %rax	# %sfp, _5
# my_gemm.c:35:         Crow(m, n) += Arow(m, k) * Brow(k, n);
	vmulss	(%rdi), %xmm0, %xmm0	# MEM[base: _226, offset: 0B], *_15, tmp231
# my_gemm.c:35:         Crow(m, n) += Arow(m, k) * Brow(k, n);
	vaddss	(%rax), %xmm0, %xmm0	# *_5, tmp231, tmp233
	vmovss	%xmm0, (%rax)	# tmp233, *_5
# my_gemm.c:34:       for (n = 0; n < N; n++)
	movq	-72(%rsp), %rax	# %sfp, n
	cmpq	%rax, %rbp	# n, N
	jbe	.L39	#,
# my_gemm.c:35:         Crow(m, n) += Arow(m, k) * Brow(k, n);
	addq	%r11, %rax	# ivtmp.126, tmp235
# my_gemm.c:35:         Crow(m, n) += Arow(m, k) * Brow(k, n);
	vmovss	(%r12,%rax,4), %xmm0	# *_133, *_133
# my_gemm.c:35:         Crow(m, n) += Arow(m, k) * Brow(k, n);
	movq	-48(%rsp), %rax	# %sfp, _128
# my_gemm.c:35:         Crow(m, n) += Arow(m, k) * Brow(k, n);
	vmulss	(%rdi), %xmm0, %xmm0	# MEM[base: _226, offset: 0B], *_133, tmp236
# my_gemm.c:35:         Crow(m, n) += Arow(m, k) * Brow(k, n);
	vaddss	(%rax), %xmm0, %xmm0	# *_128, tmp236, tmp238
	vmovss	%xmm0, (%rax)	# tmp238, *_128
# my_gemm.c:34:       for (n = 0; n < N; n++)
	movq	-56(%rsp), %rax	# %sfp, n
	cmpq	%rax, %rbp	# n, N
	jbe	.L39	#,
# my_gemm.c:35:         Crow(m, n) += Arow(m, k) * Brow(k, n);
	addq	%r11, %rax	# ivtmp.126, tmp240
# my_gemm.c:35:         Crow(m, n) += Arow(m, k) * Brow(k, n);
	vmovss	(%r12,%rax,4), %xmm0	# *_94, *_94
# my_gemm.c:35:         Crow(m, n) += Arow(m, k) * Brow(k, n);
	movq	-40(%rsp), %rax	# %sfp, _89
# my_gemm.c:35:         Crow(m, n) += Arow(m, k) * Brow(k, n);
	vmulss	(%rdi), %xmm0, %xmm0	# MEM[base: _226, offset: 0B], *_94, tmp241
# my_gemm.c:35:         Crow(m, n) += Arow(m, k) * Brow(k, n);
	vaddss	(%rax), %xmm0, %xmm0	# *_89, tmp241, tmp243
	vmovss	%xmm0, (%rax)	# tmp243, *_89
.L39:
	addq	-104(%rsp), %r9	# %sfp, ivtmp.124
	addq	%rbp, %r11	# N, ivtmp.126
# my_gemm.c:33:     for (k = 0; k < K; k++)
	cmpq	-112(%rsp), %r10	# %sfp, ivtmp.123
	jne	.L43	#,
	movq	-104(%rsp), %rdi	# %sfp, _247
# my_gemm.c:32:   for (m = 0; m < M; m++)
	incq	-32(%rsp)	# %sfp
	movq	(%rsp), %rsi	# %sfp, _241
	movq	32(%rsp), %rcx	# %sfp, K
	movq	-32(%rsp), %rax	# %sfp, m
	addq	%rsi, -112(%rsp)	# _241, %sfp
	addq	%rbp, -24(%rsp)	# N, %sfp
	addq	%rdi, %rbx	# _247, ivtmp.134
	addq	%rdi, %r13	# _247, ivtmp.136
	addq	%rcx, -16(%rsp)	# K, %sfp
	addq	%rdi, -96(%rsp)	# _247, %sfp
# my_gemm.c:32:   for (m = 0; m < M; m++)
	cmpq	%rax, 24(%rsp)	# m, %sfp
	jne	.L33	#,
.L61:
# my_gemm.c:37: }
	addq	$48, %rsp	#,
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx	#
	.cfi_def_cfa_offset 48
	popq	%rbp	#
	.cfi_def_cfa_offset 40
	popq	%r12	#
	.cfi_def_cfa_offset 32
	popq	%r13	#
	.cfi_def_cfa_offset 24
	popq	%r14	#
	.cfi_def_cfa_offset 16
	popq	%r15	#
	.cfi_def_cfa_offset 8
	ret	
	.p2align 4,,7
	.p2align 3
.L45:
	.cfi_restore_state
# my_gemm.c:35:         Crow(m, n) += Arow(m, k) * Brow(k, n);
	movq	%r9, %rdx	# ivtmp.124, ivtmp.91
	movq	%rbx, %rax	# ivtmp.134, ivtmp.90
	.p2align 4,,10
	.p2align 3
.L38:
# my_gemm.c:35:         Crow(m, n) += Arow(m, k) * Brow(k, n);
	vmovss	(%rdi), %xmm0	# MEM[base: _226, offset: 0B], MEM[base: _226, offset: 0B]
	addq	$4, %rax	#, ivtmp.90
	addq	$4, %rdx	#, ivtmp.91
	vmulss	-4(%rdx), %xmm0, %xmm0	# MEM[base: _147, offset: 0B], MEM[base: _226, offset: 0B], tmp245
# my_gemm.c:35:         Crow(m, n) += Arow(m, k) * Brow(k, n);
	vaddss	-4(%rax), %xmm0, %xmm0	# MEM[base: _149, offset: 0B], tmp245, tmp247
	vmovss	%xmm0, -4(%rax)	# tmp247, MEM[base: _149, offset: 0B]
# my_gemm.c:34:       for (n = 0; n < N; n++)
	cmpq	%r13, %rax	# ivtmp.136, ivtmp.90
	jne	.L38	#,
	jmp	.L39	#
.L44:
# my_gemm.c:4: void my_gemm(float *A, float *B, float  *C, size_t M, size_t N, size_t K) {
	movq	%rbx, %r15	# ivtmp.134, vectp.84
	xorl	%edx, %edx	# ivtmp.97
	jmp	.L34	#
	.cfi_endproc
.LFE558:
	.size	my_gemm, .-my_gemm
	.p2align 4,,10
	.p2align 3
	.globl	saxpy_gemm
	.type	saxpy_gemm, @function
saxpy_gemm:
.LFB559:
	.cfi_startproc
	endbr64	
	pushq	%r15	#
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14	#
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	movq	%rcx, %r15	# tmp100, M
	movq	%rdx, %r14	# tmp99, C
	pushq	%r13	#
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12	#
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movq	%rdi, %r12	# tmp97, A
# my_gemm.c:65:   omp_set_num_threads(4);
	movl	$4, %edi	#,
# my_gemm.c:39: void saxpy_gemm(float *A, float *B, float *C, size_t M, size_t N, size_t K) {
	pushq	%rbp	#
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx	#
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%r9, %rbp	# tmp102, K
	movq	%r8, %rbx	# tmp101, N
	subq	$168, %rsp	#,
	.cfi_def_cfa_offset 224
# my_gemm.c:39: void saxpy_gemm(float *A, float *B, float *C, size_t M, size_t N, size_t K) {
	movq	%rsi, %r13	# tmp98, B
	movq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp103
	movq	%rax, 152(%rsp)	# tmp103, D.7487
	xorl	%eax, %eax	# tmp103
# my_gemm.c:65:   omp_set_num_threads(4);
	call	omp_set_num_threads@PLT	#
# my_gemm.c:71:   #pragma omp parallel//nowait
	vxorps	%xmm0, %xmm0, %xmm0	# _A
	xorl	%ecx, %ecx	#
	xorl	%edx, %edx	#
	leaq	saxpy_gemm._omp_fn.0(%rip), %rdi	#,
	movq	%rsp, %rsi	#, tmp95
	movq	%rbx, 136(%rsp)	# N, .omp_data_o.1.ldC
	movq	%rbx, 128(%rsp)	# N, .omp_data_o.1.ldB
	vmovaps	%xmm0, (%rsp)	# _A, .omp_data_o.1._A
	movq	%rbp, 120(%rsp)	# K, .omp_data_o.1.ldA
	movq	%rbp, 88(%rsp)	# K, .omp_data_o.1.K
	movq	%rbx, 80(%rsp)	# N, .omp_data_o.1.N
	vmovaps	%xmm0, 16(%rsp)	# _B, .omp_data_o.1._B
	movq	%r15, 72(%rsp)	# M, .omp_data_o.1.M
	movq	%r14, 64(%rsp)	# C, .omp_data_o.1.C
	vmovaps	%xmm0, 32(%rsp)	# _C, .omp_data_o.1._C
	movq	%r13, 56(%rsp)	# B, .omp_data_o.1.B
	movq	%r12, 48(%rsp)	# A, .omp_data_o.1.A
	movq	$0, 96(%rsp)	#, .omp_data_o.1.m
	movq	$0, 104(%rsp)	#, .omp_data_o.1.n
	movq	$0, 112(%rsp)	#, .omp_data_o.1.k
	call	GOMP_parallel@PLT	#
# my_gemm.c:131: }
	movq	152(%rsp), %rax	# D.7487, tmp104
	xorq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp104
	jne	.L67	#,
	addq	$168, %rsp	#,
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx	#
	.cfi_def_cfa_offset 48
	popq	%rbp	#
	.cfi_def_cfa_offset 40
	popq	%r12	#
	.cfi_def_cfa_offset 32
	popq	%r13	#
	.cfi_def_cfa_offset 24
	popq	%r14	#
	.cfi_def_cfa_offset 16
	popq	%r15	#
	.cfi_def_cfa_offset 8
	ret	
.L67:
	.cfi_restore_state
	call	__stack_chk_fail@PLT	#
	.cfi_endproc
.LFE559:
	.size	saxpy_gemm, .-saxpy_gemm
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
