;
; kernel/src/lock.asm
;

[default rel]
[section .text]

global trylock
global getlock
global unlock

trylock:
	xor rax, rax
	lock xchg [rdi], al
	ret

unlock:
	mov byte [rdi], 1
	ret

getlock:
	call trylock
	test al, al
	jz getlock
	ret
