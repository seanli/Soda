CXX = u++										# compiler
CXXFLAGS = -g -Wall -Wno-unused-label -MMD		# compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS = Soda.o Config.o
EXEC = soda										# executable name

DEPENDS = ${OBJECTS:.o=.d}						# substitute ".o" with ".d"

#############################################################

.PHONY : all clean

all : ${EXEC}						# build all executables

${EXEC} : ${OBJECTS}				# link step 1st executable
	${CXX} $^ -o $@

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}		# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}					# include *.d files containing program dependences

clean :								# remove files that can be regenerated
	rm -f *.d *.o ${EXEC} interference
