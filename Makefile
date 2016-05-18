all:
	gcc ipip_py.c ipip.c -I /usr/include/python2.7  -o ipip.so -shared -fPIC
