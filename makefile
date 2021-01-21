ll: 
		gcc -o compiler driver.c lexer.c parser.c ast.c intermediatecode.c semantics.c -lm
