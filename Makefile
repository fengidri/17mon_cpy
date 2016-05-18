all:
	gcc $(pkg-config --cflags --libs python2) ipip_py.c ipip.c -o ipip.so -shared -fPIC
