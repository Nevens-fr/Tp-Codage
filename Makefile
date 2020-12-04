^=codeurArith.c codeur.c decodeur.c
h=codeurHDBN.c codeur.c decodeur.c

all : Arith HDBN


Arith : $^
	gcc $^ -o arith

HDBN : $h
	gcc $h -o hdbn

test : main	
	./main

clean : arith hdbn
	rm arith hdbn