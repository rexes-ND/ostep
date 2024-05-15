all: syscall context_switch

clean:
	rm -f syscall context_switch

syscall: syscall.c
	gcc -o syscall syscall.c -Wall

context_switch: context_switch.c
	gcc -o context_switch context_switch.c -Wall
