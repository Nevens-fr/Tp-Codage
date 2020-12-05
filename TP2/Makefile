j=main.c fonctions.c
g=main_gold.c fonctions.c

all : jpl gold

jpl : $j
	gcc $j -lm -o mainJpl

gold : $g
	gcc $g -lm -o mainGold

clean : mainJpl mainGold
	rm mainJpl mainGold