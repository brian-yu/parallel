omp_demo.out: omp_demo.c
	if [ -a omp_demo.out ]; then rm omp_demo.out; fi;
	gcc-5 omp_demo.c -fopenmp -std=c99 -lm -03 -o omp_demo.out;
	./omp_demo.out;

summation.out: summation.c
	if [ -a summation.out ]; then rm summation.out; fi;
	gcc-5 -fopenmp summation.c -fopenmp -std=c99 -lm -o summation.out;
	./summation.out;
	
prefix.out: prefix.c
	if [ -a prefix.out ]; then rm prefix.out; fi;
	gcc-5 -fopenmp prefix.c -fopenmp -std=c99 -O3 -lm -o prefix.out;
	./prefix.out;

test.out: test.c
	if [ -a test.out ]; then rm test.out; fi;
	gcc-5 -fopenmp test.c -fopenmp -std=c99 -O3 -lm -o test.out;
	./test.out;
	
nearestone.out: nearestone.c
	if [ -a nearestone.out ]; then rm nearestone.out; fi;
	gcc-5 -fopenmp nearestone.c -fopenmp -std=c99 -O3 -lm -o nearestone.out;
	./nearestone.out;

merge.out: merge.c
	if [ -a merge.out ]; then rm merge.out; fi;
	gcc-5 -fopenmp merge.c -fopenmp -std=c99 -o merge.out;
	./merge.out;