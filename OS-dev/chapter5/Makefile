# Default make target
all: os-image

run: all
	qemu-system-x86_64 os-image

# The actual disk image that the computer loads
# which is the combination of our compiled bootsector and kernel
os-image: boot_sect.bin kernel.bin
	cat $^ > os-image

# Build the kernel binary
# $^ is substituted with all of the target's dependency files
#	- The kernel_entry, which jumps to main() in our kernel
#	- the compiled C kernel
kernel.bin : kernel_entry.o kernel.o
	ld -o kernel.bin -Ttext 0x1000 $^ --oformat binary

# Build the kernel object file
# $< is the first dependency and $@ is the target file
kernel.o : kernel.c
	gcc -ffreestanding -c $< -o $@

# Build the kernel entry object file
# same as above
kernel_entry.o : kernel_entry.asm
	nasm $< -f elf64 -o $@

# Assemble the boot sector to raw machine code
#	The -I optionis tells nasm where to find our useful assembly
# 	routines that we include in boot_sect.asm
boot_sect.bin: boot_sect.asm
	nasm $< -f bin -I '../' -o $@

# Clear away all the generated files
clean:
	rm -fr *.bin *.o *.dis os-image *.map

# Disassemble our kernel - might be useful for debugging
kernel.dis : kernel.bin
	ndisasm -b 32 $< > $@