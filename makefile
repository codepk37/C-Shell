main :
	gcc -g main.c solver.c spec1.c spec2.c spec3.c spec4.c spec5.c spec6.c spec7.c spec8.c    spec9.c spec10.c spec11.c spec12.c spec13.c spec14.c spec15.c spec16.c 

run :
	./a.out

exec :
	gcc -g main.c header.h solver.c spec1.c spec2.c spec3.c spec4.c spec5.c spec6.c spec7.c spec8.c   spec9.c spec10.c spec11.c spec12.c spec13.c spec14.c spec15.c spec16.c
	./a.out

