TARGET   = main

CC       = gcc
# compiling flags here
CFLAGS   = -std=gnu11 -Wall #-Wextra -Werror

LINKER   = gcc
# linking flags here
LFLAGS   = -Wall -lm -lrt

# change these to proper directories where each file should be
SRCDIR	= src
OBJDIR	= obj
BINDIR	= bin
INCDIR	= inc

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f

$(BINDIR)/$(TARGET): $(OBJECTS)
	@echo $(LINKER) $(OBJECTS) $(LFLAGS)	-I$(INCDIR) -o $@
	@$(LINKER)	main.c $(OBJECTS) $(LFLAGS)	-I$(INCDIR) -o $@
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -I$(INCDIR) -c $^ -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"
