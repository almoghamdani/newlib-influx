AUTOMAKE_OPTIONS = cygnus
INCLUDES = $(NEWLIB_CFLAGS) $(CROSS_CFLAGS) $(TARGET_CFLAGS)
AM_CCASFLAGS = $(INCLUDES)
 
INFLUX_LIBA_SOURCES = syscalls.c crt0.c open.c sigaction.c signal.c kill.c wait.c
INFLUX_LIBA_OBJS = syscalls.o open.o sigaction.o signal.o kill.o wait.o
 
noinst_LIBRARIES = lib.a
lib_a_SOURCES = $(INFLUX_LIBA_SOURCES)
lib_a_LIBADD = $(INFLUX_LIBA_OBJS)
lib_a_DEPENDENCIES = $(INFLUX_LIBA_OBJS)      
lib_a_CCASFLAGS = $(AM_CCASFLAGS)
lib_a_CFLAGS = $(AM_CFLAGS)

all: crt0.o
 
ACLOCAL_AMFLAGS = -I ../../..
CONFIG_STATUS_DEPENDENCIES = $(newlib_basedir)/configure.host
