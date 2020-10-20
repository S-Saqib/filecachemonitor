all:
	gcc -o pagestatus pagestatus.c -lpthread
clean:
	rm -rf pagestatus
