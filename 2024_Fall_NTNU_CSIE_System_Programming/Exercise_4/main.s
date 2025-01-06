	.file	"main.c"
	.section	.rodata
.LC0:
	.string	"Hello World!"
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$32, %esp
	movl	28(%esp), %eax
	imull	$10000, %eax, %eax
	subl	$365, %eax
	addl	24(%esp), %eax
	movl	%eax, 20(%esp)
	addl	$1, 28(%esp)
	movl	$.LC0, (%esp)
	call	puts
	movl	$0, %eax
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.5.2-8ubuntu4) 4.5.2"
	.section	.note.GNU-stack,"",@progbits
