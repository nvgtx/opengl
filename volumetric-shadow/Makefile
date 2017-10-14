LIBS:=-lc -lGL -lGLEW -lglut -lGLU

CC:=g++
CCFLAGS:=-c -Wall

LD:=g++
LDFLAGS:=$(LIBS)

find=$(shell find -type f -name $(1))

SOURCESH:=$(call find, '*.h')
SOURCESCPP:=$(call find, '*.cpp')
OBJECTS:=$(SOURCESCPP:.cpp=.o)

#keep intermediate files
.SECONDARY:
#keep additional files
.PRECIOUS: *.map

#keyword targets
.PHONY: all clean

%.o: %.cpp $(SOURCESH)
	@echo ".compiling $<"
	@$(CC) $< -o $@ $(CCFLAGS)

%.elf: $(OBJECTS)
	@echo "..linking $@"
	@$(LD) $^ -o $@ $(LDFLAGS)

all: build.elf
	@echo "...completing $^"

clean:
	@ echo ".cleaning"
	@rm -f $(call find, '*.o')
	@rm -f $(call find, '*~')
	@rm -f *.elf
	@rm -f *.map

