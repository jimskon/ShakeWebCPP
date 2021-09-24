#MakeFile to build and deploy the Shakespeare lookup

user = skon
CC= g++

#For Optimization
#CFLAGS= -O2
#For debugging
CFLAGS= -std=c++14

RM= /bin/rm -f

all: shakewebcpp PutCGI PutHTML

textindex.o: textindex.cpp textindex.h
	$(CC) $(CFLAGS) textindex.cpp -c

shakewebcpp.o: shakewebcpp.cpp textindex.h
	$(CC) -c $(CFLAGS) shakewebcpp.cpp 

shakewebcpp: shakewebcpp.o textindex.o
	$(CC) shakewebcpp.o -o shakewebcpp textindex.o -L/usr/local/lib -lcgicc

PutCGI: shakewebcpp
	chmod 757 shakewebcpp
	cp shakewebcpp /usr/lib/cgi-bin/$(user)_shakewebcpp.cgi 

	echo "Current contents of your cgi-bin directory: "
	find /usr/lib/cgi-bin/ -type f -mmin -5 -ls	

PutHTML: shakewebcpp.html shakewebcpp.css shakewebcpp.js
	cp shakewebcpp.html /var/www/html/class/softdev/$(user)/ShakeWebCPP/
	cp shakewebcpp.css /var/www/html/class/softdev/$(user)/ShakeWebCPP/
	cp shakewebcpp.js /var/www/html/class/softdev/$(user)/ShakeWebCPP/
	echo "Current contents of your HTML directory: "
	ls -l /var/www/html/class/softdev/$(user)/ShakeWebCPP/
clean:
	rm -f *.o  shakewebcpp
