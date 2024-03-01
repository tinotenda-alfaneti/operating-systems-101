all: compile run clean
compile: *.c header/*.h
	@gcc -o out *.c header/*.h

run: out
	@./out

clean: out
	@rm out

manual: compile out
	@./out 1

auto: compile out
	@./out 2