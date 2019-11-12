 all: main clean

main: main.o Arquivos.o H1.o H2.o Solucao_Otima.o
		gcc -Wall Arquivos.o H1.o H2.o Solucao_Otima.o main.o -o tp

main.o: main.c Arquivos.h H1.h H2.h Solucao_Otima.h
		gcc -Wall -c main.c

Arquivos.o: Arquivos.c Arquivos.h
		gcc -Wall -c Arquivos.c

H1.o: H1.c H1.h
		gcc -Wall -c H1.c

H2.o: H2.c H2.h
		gcc -Wall -c H2.c

Solucao_Otima.o: Solucao_Otima.c Solucao_Otima.h
		gcc -Wall -c Solucao_Otima.c

clean:
		rm *.o
