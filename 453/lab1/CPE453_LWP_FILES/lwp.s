	.file	"lwp.c"
	.comm	lwp_ptable,480,32
.globl lwp_procs
	.bss
	.align 4
	.type	lwp_procs, @object
	.size	lwp_procs, 4
lwp_procs:
	.zero	4
.globl lwp_running
	.data
	.align 4
	.type	lwp_running, @object
	.size	lwp_running, 4
lwp_running:
	.long	-1
	.comm	global_sp,4,4
.globl global_sched
	.align 4
	.type	global_sched, @object
	.size	global_sched, 4
global_sched:
	.long	round_robin
	.text
.globl new_lwp
	.type	new_lwp, @function
new_lwp:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$20, %esp
	movl	lwp_procs, %eax
	cmpl	$30, %eax
	jne	.L2
	movl	$-1, %eax
	jmp	.L3
.L2:
	movl	lwp_procs, %eax
	movl	%eax, lwp_running
	addl	$1, %eax
	movl	%eax, lwp_procs
	movl	lwp_running, %edx
	movl	lwp_running, %eax
	sall	$4, %edx
	movl	%eax, lwp_ptable(%edx)
	movl	lwp_running, %ebx
	movl	16(%ebp), %eax
	sall	$2, %eax
	movl	%eax, (%esp)
	call	malloc
	movl	%ebx, %edx
	sall	$4, %edx
	movl	%eax, lwp_ptable+4(%edx)
	movl	lwp_running, %eax
	movl	%eax, %edx
	sall	$4, %edx
	movl	16(%ebp), %eax
	movl	%eax, lwp_ptable+8(%edx)
	movl	lwp_running, %eax
	movl	lwp_running, %edx
	sall	$4, %edx
	movl	lwp_ptable+4(%edx), %edx
	movl	16(%ebp), %ecx
	sall	$4, %ecx
	addl	%ecx, %edx
	sall	$4, %eax
	movl	%edx, lwp_ptable+12(%eax)
	movl	lwp_running, %eax
	sall	$4, %eax
	addl	$lwp_ptable, %eax
	leal	12(%eax), %edx
	movl	12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	set_sp
	movl	lwp_running, %eax
.L3:
	addl	$20, %esp
	popl	%ebx
	popl	%ebp
	ret
	.size	new_lwp, .-new_lwp
.globl lwp_exit
	.type	lwp_exit, @function
lwp_exit:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	lwp_running, %eax
	sall	$4, %eax
	movl	lwp_ptable+4(%eax), %eax
	movl	%eax, (%esp)
	call	free
	movl	lwp_running, %eax
	movl	%eax, -12(%ebp)
	jmp	.L6
.L7:
	movl	-12(%ebp), %eax
	movl	-12(%ebp), %edx
	addl	$1, %edx
	sall	$4, %eax
	sall	$4, %edx
	movl	lwp_ptable(%edx), %ecx
	movl	%ecx, lwp_ptable(%eax)
	movl	lwp_ptable+4(%edx), %ecx
	movl	%ecx, lwp_ptable+4(%eax)
	movl	lwp_ptable+8(%edx), %ecx
	movl	%ecx, lwp_ptable+8(%eax)
	movl	lwp_ptable+12(%edx), %edx
	movl	%edx, lwp_ptable+12(%eax)
	addl	$1, -12(%ebp)
.L6:
	movl	lwp_procs, %eax
	cmpl	%eax, -12(%ebp)
	jl	.L7
	movl	lwp_procs, %eax
	subl	$1, %eax
	movl	%eax, lwp_procs
	movl	lwp_procs, %eax
	testl	%eax, %eax
	je	.L8
	movl	global_sched, %edx
	movl	$round_robin, %eax
	cmpl	%eax, %edx
	je	.L9
	movl	global_sched, %eax
	call	*%eax
	movl	%eax, lwp_running
	jmp	.L10
.L9:
	movl	$0, lwp_running
.L10:
	movl	lwp_running, %eax
	sall	$4, %eax
	movl	lwp_ptable+12(%eax), %eax
#APP
# 56 "lwp.c" 1
	movl  %eax,%esp
# 0 "" 2
# 57 "lwp.c" 1
	popl  %ebp
# 0 "" 2
# 57 "lwp.c" 1
	popl  %edi
# 0 "" 2
# 57 "lwp.c" 1
	popl  %esi
# 0 "" 2
# 57 "lwp.c" 1
	popl  %edx
# 0 "" 2
# 57 "lwp.c" 1
	popl  %ecx
# 0 "" 2
# 57 "lwp.c" 1
	popl  %ebx
# 0 "" 2
# 57 "lwp.c" 1
	popl  %eax
# 0 "" 2
# 57 "lwp.c" 1
	movl  %ebp,%esp
# 0 "" 2
#NO_APP
	jmp	.L12
.L8:
	call	lwp_stop
.L12:
	leave
	ret
	.size	lwp_exit, .-lwp_exit
.globl lwp_getpid
	.type	lwp_getpid, @function
lwp_getpid:
	pushl	%ebp
	movl	%esp, %ebp
	movl	lwp_running, %eax
	sall	$4, %eax
	movl	lwp_ptable(%eax), %eax
	popl	%ebp
	ret
	.size	lwp_getpid, .-lwp_getpid
.globl lwp_yield
	.type	lwp_yield, @function
lwp_yield:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
#APP
# 75 "lwp.c" 1
	pushl %eax
# 0 "" 2
# 75 "lwp.c" 1
	pushl %ebx
# 0 "" 2
# 75 "lwp.c" 1
	pushl %ecx
# 0 "" 2
# 75 "lwp.c" 1
	pushl %edx
# 0 "" 2
# 75 "lwp.c" 1
	pushl %esi
# 0 "" 2
# 75 "lwp.c" 1
	pushl %edi
# 0 "" 2
# 75 "lwp.c" 1
	pushl %ebp
# 0 "" 2
#NO_APP
	movl	lwp_running, %edx
#APP
# 76 "lwp.c" 1
	movl  %esp,%eax
# 0 "" 2
#NO_APP
	sall	$4, %edx
	movl	%eax, lwp_ptable+12(%edx)
	movl	global_sched, %eax
	call	*%eax
	movl	%eax, lwp_running
	movl	lwp_running, %eax
	sall	$4, %eax
	movl	lwp_ptable+12(%eax), %eax
#APP
# 78 "lwp.c" 1
	movl  %eax,%esp
# 0 "" 2
# 79 "lwp.c" 1
	popl  %ebp
# 0 "" 2
# 79 "lwp.c" 1
	popl  %edi
# 0 "" 2
# 79 "lwp.c" 1
	popl  %esi
# 0 "" 2
# 79 "lwp.c" 1
	popl  %edx
# 0 "" 2
# 79 "lwp.c" 1
	popl  %ecx
# 0 "" 2
# 79 "lwp.c" 1
	popl  %ebx
# 0 "" 2
# 79 "lwp.c" 1
	popl  %eax
# 0 "" 2
# 79 "lwp.c" 1
	movl  %ebp,%esp
# 0 "" 2
#NO_APP
	leave
	ret
	.size	lwp_yield, .-lwp_yield
.globl lwp_start
	.type	lwp_start, @function
lwp_start:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
#APP
# 83 "lwp.c" 1
	pushl %eax
# 0 "" 2
# 83 "lwp.c" 1
	pushl %ebx
# 0 "" 2
# 83 "lwp.c" 1
	pushl %ecx
# 0 "" 2
# 83 "lwp.c" 1
	pushl %edx
# 0 "" 2
# 83 "lwp.c" 1
	pushl %esi
# 0 "" 2
# 83 "lwp.c" 1
	pushl %edi
# 0 "" 2
# 83 "lwp.c" 1
	pushl %ebp
# 0 "" 2
# 84 "lwp.c" 1
	movl  %esp,%eax
# 0 "" 2
#NO_APP
	movl	%eax, global_sp
	movl	global_sched, %eax
	call	*%eax
	movl	%eax, lwp_running
	movl	lwp_running, %eax
	sall	$4, %eax
	movl	lwp_ptable+12(%eax), %eax
#APP
# 86 "lwp.c" 1
	movl  %eax,%esp
# 0 "" 2
# 87 "lwp.c" 1
	popl  %ebp
# 0 "" 2
# 87 "lwp.c" 1
	popl  %edi
# 0 "" 2
# 87 "lwp.c" 1
	popl  %esi
# 0 "" 2
# 87 "lwp.c" 1
	popl  %edx
# 0 "" 2
# 87 "lwp.c" 1
	popl  %ecx
# 0 "" 2
# 87 "lwp.c" 1
	popl  %ebx
# 0 "" 2
# 87 "lwp.c" 1
	popl  %eax
# 0 "" 2
# 87 "lwp.c" 1
	movl  %ebp,%esp
# 0 "" 2
#NO_APP
	leave
	ret
	.size	lwp_start, .-lwp_start
.globl lwp_stop
	.type	lwp_stop, @function
lwp_stop:
	pushl	%ebp
	movl	%esp, %ebp
	movl	lwp_procs, %eax
	testl	%eax, %eax
	je	.L20
#APP
# 94 "lwp.c" 1
	pushl %eax
# 0 "" 2
# 94 "lwp.c" 1
	pushl %ebx
# 0 "" 2
# 94 "lwp.c" 1
	pushl %ecx
# 0 "" 2
# 94 "lwp.c" 1
	pushl %edx
# 0 "" 2
# 94 "lwp.c" 1
	pushl %esi
# 0 "" 2
# 94 "lwp.c" 1
	pushl %edi
# 0 "" 2
# 94 "lwp.c" 1
	pushl %ebp
# 0 "" 2
#NO_APP
	movl	lwp_running, %edx
#APP
# 95 "lwp.c" 1
	movl  %esp,%eax
# 0 "" 2
#NO_APP
	sall	$4, %edx
	movl	%eax, lwp_ptable+12(%edx)
	movl	lwp_running, %eax
	subl	$1, %eax
	movl	%eax, lwp_running
.L20:
	movl	global_sp, %eax
#APP
# 98 "lwp.c" 1
	movl  %eax,%esp
# 0 "" 2
# 99 "lwp.c" 1
	popl  %ebp
# 0 "" 2
# 99 "lwp.c" 1
	popl  %edi
# 0 "" 2
# 99 "lwp.c" 1
	popl  %esi
# 0 "" 2
# 99 "lwp.c" 1
	popl  %edx
# 0 "" 2
# 99 "lwp.c" 1
	popl  %ecx
# 0 "" 2
# 99 "lwp.c" 1
	popl  %ebx
# 0 "" 2
# 99 "lwp.c" 1
	popl  %eax
# 0 "" 2
# 99 "lwp.c" 1
	movl  %ebp,%esp
# 0 "" 2
#NO_APP
	popl	%ebp
	ret
	.size	lwp_stop, .-lwp_stop
.globl lwp_set_scheduler
	.type	lwp_set_scheduler, @function
lwp_set_scheduler:
	pushl	%ebp
	movl	%esp, %ebp
	cmpl	$0, 8(%ebp)
	jne	.L23
	movl	$round_robin, %eax
	movl	%eax, global_sched
	jmp	.L25
.L23:
	movl	8(%ebp), %eax
	movl	%eax, global_sched
.L25:
	popl	%ebp
	ret
	.size	lwp_set_scheduler, .-lwp_set_scheduler
.globl round_robin
	.type	round_robin, @function
round_robin:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	lwp_running, %eax
	leal	1(%eax), %edx
	movl	lwp_procs, %eax
	movl	%eax, -4(%ebp)
	movl	%edx, %eax
	sarl	$31, %edx
	idivl	-4(%ebp)
	movl	%edx, %eax
	leave
	ret
	.size	round_robin, .-round_robin
.globl set_sp
	.type	set_sp, @function
set_sp:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	16(%ebp), %edx
	movl	%edx, (%eax)
	leal	-4(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	$lwp_exit, %edx
	movl	%edx, (%eax)
	leal	-4(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	12(%ebp), %edx
	movl	%edx, (%eax)
	leal	-4(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -4(%ebp)
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	leal	-28(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	-4(%ebp), %edx
	movl	%edx, (%eax)
	leave
	ret
	.size	set_sp, .-set_sp
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-16)"
	.section	.note.GNU-stack,"",@progbits
