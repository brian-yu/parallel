ray.out: ray.c
	gcc ray.c -std=c99 -lm -o ray.out
	./ray.out
	display output.ppm
	rm ray.out

ray_omp.out: ray_omp.c
	gcc -fopenmp omp_demo.c -std=c99 -lm -o ray_omp.out
	./ray_omp.out
	display output.ppm
	rm ray_omp.out

omp_demo.out: omp_demo.c
	gcc-5 -fopenmp omp_demo.c -std=c99 -lm -o omp_demo.out
	./omp_demo.out
	rm omp_demo.out