herdShell.out: herdShell.c
	gcc -framework GLUT -framework OpenGL -Wno-deprecated-declarations -Wno-implicit-function-declaration -o herdShell.out herdShell.c
	./herdShell.out

shell.out: shell.c
	gcc -framework GLUT -framework OpenGL -Wno-deprecated-declarations -Wno-implicit-function-declaration -o shell.out shell.c
	./shell.out
	
n-body.out: n-body.c
	gcc -framework GLUT -framework OpenGL -Wno-deprecated-declarations -Wno-implicit-function-declaration -o n-body.out n-body.c
	./n-body.out

clean:
	rm -f herdShell.out
	rm -f shell.out
