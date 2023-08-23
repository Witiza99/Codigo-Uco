	.file	"prueba.c"
# GNU C17 (Ubuntu 9.4.0-1ubuntu1~20.04.1) version 9.4.0 (x86_64-linux-gnu)
#	compiled by GNU C version 9.4.0, GMP version 6.2.0, MPFR version 4.0.2, MPC version 1.1.0, isl version isl-0.22.1-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed:  -imultiarch x86_64-linux-gnu prueba.c -mtune=generic
# -march=x86-64 -O0 -fverbose-asm -fasynchronous-unwind-tables
# -fstack-protector-strong -Wformat -Wformat-security
# -fstack-clash-protection -fcf-protection
# options enabled:  -fPIC -fPIE -faggressive-loop-optimizations
# -fassume-phsa -fasynchronous-unwind-tables -fauto-inc-dec -fcommon
# -fdelete-null-pointer-checks -fdwarf2-cfi-asm -fearly-inlining
# -feliminate-unused-debug-types -ffp-int-builtin-inexact -ffunction-cse
# -fgcse-lm -fgnu-runtime -fgnu-unique -fident -finline-atomics
# -fipa-stack-alignment -fira-hoist-pressure -fira-share-save-slots
# -fira-share-spill-slots -fivopts -fkeep-static-consts
# -fleading-underscore -flifetime-dse -flto-odr-type-merging -fmath-errno
# -fmerge-debug-strings -fpeephole -fplt -fprefetch-loop-arrays
# -freg-struct-return -fsched-critical-path-heuristic
# -fsched-dep-count-heuristic -fsched-group-heuristic -fsched-interblock
# -fsched-last-insn-heuristic -fsched-rank-heuristic -fsched-spec
# -fsched-spec-insn-heuristic -fsched-stalled-insns-dep -fschedule-fusion
# -fsemantic-interposition -fshow-column -fshrink-wrap-separate
# -fsigned-zeros -fsplit-ivs-in-unroller -fssa-backprop
# -fstack-clash-protection -fstack-protector-strong -fstdarg-opt
# -fstrict-volatile-bitfields -fsync-libcalls -ftrapping-math -ftree-cselim
# -ftree-forwprop -ftree-loop-if-convert -ftree-loop-im -ftree-loop-ivcanon
# -ftree-loop-optimize -ftree-parallelize-loops= -ftree-phiprop
# -ftree-reassoc -ftree-scev-cprop -funit-at-a-time -funwind-tables
# -fverbose-asm -fzero-initialized-in-bss -m128bit-long-double -m64 -m80387
# -malign-stringops -mavx256-split-unaligned-load
# -mavx256-split-unaligned-store -mfancy-math-387 -mfp-ret-in-387 -mfxsr
# -mglibc -mieee-fp -mlong-double-80 -mmmx -mno-sse4 -mpush-args -mred-zone
# -msse -msse2 -mstv -mtls-direct-seg-refs -mvzeroupper

	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$32, %rsp	#,
# prueba.c:6: 	int buffer_size = 10;
	movl	$10, -20(%rbp)	#, buffer_size
# prueba.c:7: 	float *b = (float *) malloc (sizeof(float) * buffer_size);
	movl	-20(%rbp), %eax	# buffer_size, tmp95
	cltq
	salq	$2, %rax	#, _2
	movq	%rax, %rdi	# _2,
	call	malloc@PLT	#
	movq	%rax, -8(%rbp)	# tmp96, b
# prueba.c:8: 	size_t result = 0;
	movq	$0, -16(%rbp)	#, result
# prueba.c:9: 	for (int i= 0; i < buffer_size; i++) b[i] = 1.0;
	movl	$0, -28(%rbp)	#, i
# prueba.c:9: 	for (int i= 0; i < buffer_size; i++) b[i] = 1.0;
	jmp	.L2	#
.L3:
# prueba.c:9: 	for (int i= 0; i < buffer_size; i++) b[i] = 1.0;
	movl	-28(%rbp), %eax	# i, tmp97
	cltq
	leaq	0(,%rax,4), %rdx	#, _4
	movq	-8(%rbp), %rax	# b, tmp98
	addq	%rdx, %rax	# _4, _5
# prueba.c:9: 	for (int i= 0; i < buffer_size; i++) b[i] = 1.0;
	movss	.LC0(%rip), %xmm0	#, tmp99
	movss	%xmm0, (%rax)	# tmp99, *_5
# prueba.c:9: 	for (int i= 0; i < buffer_size; i++) b[i] = 1.0;
	addl	$1, -28(%rbp)	#, i
.L2:
# prueba.c:9: 	for (int i= 0; i < buffer_size; i++) b[i] = 1.0;
	movl	-28(%rbp), %eax	# i, tmp100
	cmpl	-20(%rbp), %eax	# buffer_size, tmp100
	jl	.L3	#,
# prueba.c:10: 	for (int i=0; i < buffer_size; i++) result += b[i];
	movl	$0, -24(%rbp)	#, i
# prueba.c:10: 	for (int i=0; i < buffer_size; i++) result += b[i];
	jmp	.L4	#
.L9:
# prueba.c:10: 	for (int i=0; i < buffer_size; i++) result += b[i];
	movq	-16(%rbp), %rax	# result, tmp101
	testq	%rax, %rax	# tmp101
	js	.L5	#,
	cvtsi2ssq	%rax, %xmm0	# tmp101, _6
	jmp	.L6	#
.L5:
	movq	%rax, %rdx	# tmp101, tmp103
	shrq	%rdx	# tmp103
	andl	$1, %eax	#, tmp104
	orq	%rax, %rdx	# tmp104, tmp103
	cvtsi2ssq	%rdx, %xmm0	# tmp103, tmp102
	addss	%xmm0, %xmm0	# tmp102, _6
.L6:
# prueba.c:10: 	for (int i=0; i < buffer_size; i++) result += b[i];
	movl	-24(%rbp), %eax	# i, tmp105
	cltq
	leaq	0(,%rax,4), %rdx	#, _8
	movq	-8(%rbp), %rax	# b, tmp106
	addq	%rdx, %rax	# _8, _9
	movss	(%rax), %xmm1	# *_9, _10
# prueba.c:10: 	for (int i=0; i < buffer_size; i++) result += b[i];
	addss	%xmm1, %xmm0	# _10, _11
	comiss	.LC1(%rip), %xmm0	#, _11
	jnb	.L7	#,
	cvttss2siq	%xmm0, %rax	# _11, tmp107
	movq	%rax, -16(%rbp)	# tmp107, result
	jmp	.L8	#
.L7:
	movss	.LC1(%rip), %xmm1	#, tmp109
	subss	%xmm1, %xmm0	# tmp109, tmp108
	cvttss2siq	%xmm0, %rax	# tmp108, tmp110
	movq	%rax, -16(%rbp)	# tmp110, result
	movabsq	$-9223372036854775808, %rax	#, tmp111
	xorq	%rax, -16(%rbp)	# tmp111, result
.L8:
	movq	-16(%rbp), %rax	# result, tmp112
	movq	%rax, -16(%rbp)	# tmp112, result
# prueba.c:10: 	for (int i=0; i < buffer_size; i++) result += b[i];
	addl	$1, -24(%rbp)	#, i
.L4:
# prueba.c:10: 	for (int i=0; i < buffer_size; i++) result += b[i];
	movl	-24(%rbp), %eax	# i, tmp113
	cmpl	-20(%rbp), %eax	# buffer_size, tmp113
	jl	.L9	#,
# prueba.c:12: 	return(0);
	movl	$0, %eax	#, _23
# prueba.c:13: }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.section	.rodata
	.align 4
.LC0:
	.long	1065353216
	.align 4
.LC1:
	.long	1593835520
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
