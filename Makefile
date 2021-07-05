all: iso

iso: build_kernel
	@echo 'Creating iso ...'
	cp kernel/kernel.elf iso/boot/kernel.elf
	grub-mkrescue -o os.iso iso
	@echo ''

run: iso
	@echo 'Running iso in Bochs'
	bochs -f bochsrc.txt -q
	@echo ''

build_kernel:
	@echo 'Building kernel ...'
	@make --no-print-directory -C kernel
	@echo ''

clean:
	@echo 'Cleaning kernel ...'
	@make --no-print-directory -C kernel clean 
	@echo ''
	rm -rf os.iso bochslog.txt
