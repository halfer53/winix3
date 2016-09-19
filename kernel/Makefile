sources = main.c proc.c system.c exception.c idle.c
compile = main.s proc.s system.s exception.s idle.s
assemble = main.o proc.o system.o exception.o idle.o wramp.o util/limits_head.o util/limits_tail.o

all: $(assemble)

$(compile): %.s: %.c
	wcc -S -I../include -o $@ $<

$(assemble): %.o: %.s
	wasm $< -o $@

$(link): $(assemble)
	wlink -o $(link) $(assemble)

depend:
	makedepend $(sources)

clean:
	-rm $(compile) $(assemble)

.DELETE_ON_ERROR:
