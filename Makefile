objs = kernel/*.o lib/*.o user/*.o

all:
	$(MAKE) -C kernel
	$(MAKE) -C lib
	$(MAKE) -C user
	wlink -o winix.srec kernel/util/limits_head.o $(objs) kernel/util/limits_tail.o
	
clean:
	$(MAKE) -C kernel clean
	$(MAKE) -C lib clean
	$(MAKE) -C user clean
	rm winix.srec
	
stat:
	@echo "C Lines: "
	@find . -name "*.c" -exec cat {} \; | wc -l
	@echo "Header LoC: "
	@find . -name "*.h" -exec cat {} \; | wc -l
	@echo "Assembly LoC: "
	@find . -name "*.s" -exec cat {} \; | wc -l
	
.DELETE_ON_ERROR: