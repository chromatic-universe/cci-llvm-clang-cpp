	.text
	.file	"sum.bc"
	.globl	sum
	.align	16, 0x90
	.type	sum,@function
sum:                                    # @sum
# BB#0:                                 # %entry
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	12(%ebp), %eax
	movl	8(%ebp), %ecx
	movl	%ecx, -4(%ebp)
	movl	%eax, -8(%ebp)
	addl	-4(%ebp), %eax
	addl	$8, %esp
	popl	%ebp
	retl
.Lfunc_end0:
	.size	sum, .Lfunc_end0-sum


	.ident	"clang version 3.7.0 (tags/RELEASE_370/final)"
	.section	".note.GNU-stack","",@progbits
