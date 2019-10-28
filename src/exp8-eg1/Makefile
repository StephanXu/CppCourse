#basic settings
DIR_OBJ		= ../../build
DIR_TARGET	= ../../build
TARGET_NAME	= exp8-eg1

#source file
SOURCE	:= $(wildcard *.c) $(wildcard *.cpp)
OBJS 	:= $(addprefix $(DIR_OBJ)/,$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCE))))

#target you can change test to what you want
TARGET  := $(DIR_TARGET)/$(TARGET_NAME)

#compile and lib parameter
CC      := g++
LIBS    :=
LIBPATH :=
LDFLAGS :=
DEFINES :=
INCLUDE := -I. -I../common
CFLAGS  := -g -Wall -O3 $(DEFINES) $(INCLUDE)
CXXFLAGS:= $(CFLAGS) -DHAVE_CONFIG_H


#I think you should do anything here
.PHONY : everything objs clean veryclean rebuild

everything : $(TARGET)

all : $(TARGET)

objs : $(OBJS)

rebuild: clean everything

cleanlite :
	rm -f $(OBJS)
    
clean : cleanlite
	rm -f $(TARGET) 

$(OBJS) : $(DIR_OBJ)/%.o : %.cpp
	$(CC) $(CXXFLAGS) -c $< $(LIBPATH) $(LIBS) -o $@

$(TARGET) : $(OBJS)
	$(CC) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS) $(LIBS)