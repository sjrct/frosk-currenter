;
; kernel/src/semaphore.asm
;

[default rel]
[section .text]

%define WRITER_HAS (-1)

global read_wait
global read_signal
global write_wait
global write_signal

read_wait:
	cmp qword [rdi], WRITER_HAS
	je read_wait

	; decrement the semaphore
	mov rax, [rdi]
	mov rcx, rax
	mov rdx, rax
	inc rcx
	lock cmpxchg [rdi], rcx
	inc qword [rdi]
	cmp rcx, rdx
	je read_wait
	ret

write_wait:
	cmp qword [rdi], 0
	jne write_wait

	; set the semaphore to WRITER_HAS
	xor rax, rax
	mov rcx, WRITER_HAS
	lock cmpxchg [rdi], rcx
	test rax, rax
	jnz write_wait
	ret

read_signal:
	lock dec qword [rdi]
	; TODO: check if equals WRITER_HAS?
	ret

write_signal:
	lock inc qword [rdi]
	ret

