#HAVE TO MODIFY IT TO ADPT TO OUR PROJECT

#my general makefile template
CXX = gcc
CFLAGS = -Wall -Werror -ansi -pedantic -fpic -g
LIBSDIR = -L. -L/usr/lib
INCLUDEDIR = -I. -I/usr/include

#Library-related macros
LIBTARGET2 = PointList
LIBTARGET = libPointList.so
LIBSOURCE = pointlist
LIBSOURCECFILE = $(LIBSOURCE:=.c)
LIBSOURCEOFILE = $(LIBSOURCE:=.o)

#Application-related macros
TARGET = mypointlist.exe
EXESOURCE = main
EXESOURCECFILE = $(EXESOURCE:=.c)
EXESOURCEOFILE = $(EXESOURCE:=.o)

#To overload the content of the LD_LIBRARY_PATH
# export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:.

#Running the program
run: $(TARGET)
	@echo "\n Executing the executable " $(TARGET)
	sh exportLD.sh $(TARGET)

#Generating the executable
$(TARGET): $(EXESOURCEOFILE) $(LIBTARGET)
	@echo "\n Generating the executable " $@
	$(CXX) $(EXESOURCEOFILE) -l$(LIBTARGET2) -lm $(LIBSDIR) -o $(TARGET)

#Generating the library binary code
$(LIBTARGET): $(LIBSOURCEOFILE)
	@echo "\n Generating the library " $@
	$(CXX) $(CFLAGS) -shared $(LIBSOURCEOFILE) -o $(LIBTARGET)

#Generating an object file from a C file having the same name
.c.o:
	@echo "\n Generating " $@ " from " $<
	$(CXX) $(CFLAGS) $(INCLUDEDIR) -c -o $@ $<

#Cleaning the content of the current directory
clean:
	@echo "\n Cleaning temporary files"
	rm -rf *.o *~ *.so *.exe

	
