run: programa 
	
clean:  simulation.c
	@echo Tentando apagar o programa.exe
	rm ./simulation

programa: simulation.c 
	@echo "Compilando servidor..." 
	gcc -g -o simulation simulation.c 
	@echo "done"
