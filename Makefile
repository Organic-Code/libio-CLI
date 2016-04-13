 #########################################################################################
 #                                                                                       #
 # Copyright (C) 2016 LAZARE Lucas (lazarelucas@yahoo.fr)                                #
 #                                                                                       #
 # This software is provided 'as-is', WITHOUT ANY EXPRESS OR IMPLIED WARRANTY.           #
 # In NO EVENT will the authors be held liable for any damages arising from the          #
 # use of this software.                                                                 #
 #                                                                                       #
 # Permission is granted to anyone to use this software for any purpose,                 #
 # including commercial applications, and to alter it and redistribute it freely,        #
 # subject to the following restrictions:                                                #
 #                                                                                       #
 # 1. The origin of this software must not be misrepresented;                            #
 # you must not claim that you wrote the original software.                              #
 # If you use this software in a product, an acknowledgment                              #
 # in the product documentation would be appreciated but is not required.                #
 #                                                                                       #
 # 2. Altered source versions must be plainly marked as such,                            #
 # and must not be misrepresented as being the original software.                        #
 #                                                                                       #
 # 3. This notice may not be removed or altered from any source distribution.            #
 #                                                                                       #
 #########################################################################################


COMPILER	= gcc
COMPFLAGS	= -Wdisabled-optimization -Wstrict-prototypes -Winvalid-pch -Wdouble-promotion -Wformat -Wall -pedantic -pedantic-errors -Wunreachable-code -Winline -Wfloat-equal -Wundef -Wcast-align -Wredundant-decls -Winit-self -Wswitch-enum -fPIC -O2 -std=gnu99
DEBUGGER	= gdb
LEAKCHECKER	= valgrind --leak-check=full --show-leak-kinds=all
DISPLAY		= printf
MKDIR		= mkdir -p
RMDIR		= rmdir
RM		= rm -f
LD		= ld -r
LIBPREFIX	= lib
VOIDECHO	= > /dev/null 2>&1
BUILDDIR	= build/
LIBBUILDDIR	= $(BUILDDIR)lib/
OBJDIR		= $(BUILDDIR)obj/
SOURCEDIR	= src/io/
INCLUDEDIR	= -I/usr/include -I. -Iinclude/
LIBSDIR		= -L/usr/lib -L.
LIBSOURCENAME	= console_management cursor geometry input  output sprite_display sprite_management coordinates
LIBNAME		= libio
EXAMPLESOURCE	= src/sample/game.c src/sample/sample.c
EXAMPLEBIN	= $(BUILDDIR)example.elf
LINKS		= -lm

LIBFINALOBJ	= $(OBJDIR)$(LIBNAME).o
LIBFINAL	= $(LIBBUILDDIR)$(LIBNAME).so
LIBSOURCES	= $(foreach lib,$(LIBSOURCENAME),$(SOURCEDIR)$(lib).c)
LIBOBJECTS	= $(foreach lib,$(LIBSOURCENAME),$(OBJDIR)$(lib).o)
VPATH		= $(SOURCEDIR)

CHARACTERS := A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
CHARACTERS += a b c d e f g h i j k l m n o p q r s t u v w y z
CHARACTERS += 0 1 2 3 4 5 6 7 8 9 / \\ - _ . + \ 
STRLEN = $(strip $(eval __temp := $(subst $(sp),x,$1))$(foreach a,$(CHARACTERS),$(eval __temp := $$(subst $a,x,$(__temp))))$(eval __temp := $(subst x,x ,$(__temp)))$(words $(__temp)))

LIBSDIR += -L$(BUILDDIR)

.PHONY: $(LIBNAME)
$(LIBNAME): $(LIBFINAL)

$(LIBFINAL): $(LIBFINALOBJ)
	@$(DISPLAY) "\n\033[1m\033[92m+\033[0m Building \033[33m$(LIBFINAL)\033[0m from \033[33m$(OBJDIR)$(LIBNAME).o\033[0m..."
	@$(MKDIR) $(LIBBUILDDIR)
	@$(COMPILER) $(COMPFLAGS) $(LIBSDIR) $(LINKS) -shared $(OBJDIR)$(LIBNAME).o -o $(LIBFINAL)
	@for i in `seq 1 $(shell expr 65 - $(call STRLEN,$(OBJDIR)$(LIBNAME).o) - $(call STRLEN,$(LIBFINAL)))`; do $(DISPLAY) " "; done
	@$(DISPLAY) " -> Done\n"
	@$(DISPLAY) "\n"

$(LIBFINALOBJ): $(LIBOBJECTS)
	@$(DISPLAY) "\n\n\033[1m\033[92m+\033[0m Merging objects files into \033[33m$(OBJDIR)$(LIBNAME).o\033[0m..."
	@$(LD) $(LIBOBJECTS) -o $(OBJDIR)$(LIBNAME).o
	@for i in `seq 1 $(shell expr 52 - $(call STRLEN,$(OBJDIR)$(LIBNAME).o))`; do $(DISPLAY) " "; done
	@$(DISPLAY) " -> Done\n"


$(OBJDIR)%.o: %.c
	@$(DISPLAY) "\n\033[1m\033[92m+\033[0m Building \033[33m$@\033[0m from \033[33m$^\033[0m..."
	@$(MKDIR) $(OBJDIR)
	@$(COMPILER) $(COMPFLAGS) $(INCLUDEDIR) -c $^ -o $@
	@for i in `seq 1 $(shell expr 65 - $(call STRLEN,$^) - $(call STRLEN,$@))`; do $(DISPLAY) " "; done
	@$(DISPLAY) " -> Done"

.PHONY: example
example: $(EXAMPLEBIN)

.PHONY: run
run: $(EXAMPLEBIN)
	@$(DISPLAY) "\n\033[1m\033[92m+\033[0m Launching \033[33m$(EXAMPLEBIN)\033[0m\n"
	@LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:$(LIBBUILDDIR) $(EXAMPLEBIN)

$(EXAMPLEBIN): $(LIBFINAL) $(EXAMPLESOURCE)
	@$(DISPLAY) "\n\n\033[1m\033[92m+\033[0m Building \033[33m$(EXAMPLEBIN)\033[0m from \033[33m$(EXAMPLESOURCE)\033[0m..."
	@$(COMPILER) $(COMPFLAGS) $(INCLUDEDIR) $(LIBSDIR) $(EXAMPLESOURCE) -o $(EXAMPLEBIN) -l:$(LIBFINAL)
	@for i in `seq 1 $(shell expr 65 - $(call STRLEN,$(EXAMPLEBIN)) - $(call STRLEN,$(EXAMPLESOURCE)))`; do $(DISPLAY) " "; done
	@$(DISPLAY) " -> Done\n"

.PHONY: debug
debug: COMPFLAGS = -g -fPIC
debug: $(LIBFINAL) $(EXAMPLESOURCE)
	@$(COMPILER) $(COMPFLAGS) $(INCLUDEDIR) $(LIBSDIR) $(EXAMPLESOURCE) -o $(BUILDDIR)example.elf -l:$(LIBFINAL)
	@LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:$(LIBBUILDDIR) $(DEBUGGER) $(BUILDDIR)example.elf

.PHONY: memleak
memleak: COMPFLAGS = -g -fPIC
memleak: $(LIBFINAL) $(EXAMPLESOURCE)
	@$(COMPILER) $(COMPFLAGS) $(INCLUDEDIR) $(LIBSDIR) $(EXAMPLESOURCE) -o $(BUILDDIR)example.elf -l:$(LIBFINAL)
	@LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:$(LIBBUILDDIR) $(LEAKCHECKER) $(BUILDDIR)example.elf
.PHONY: clean
clean:
	@$(DISPLAY) "\033[0mCleaning files and folders...\n"
	@$(RM) $(LIBOBJECTS) $(LIBFINAL) $(OBJDIR)$(LIBNAME).o $(BUILDDIR)example.elf
	@$(RMDIR) $(LIBBUILDDIR) $(OBJDIR) $(BUILDDIR) $(VOIDECHO) || true
	@$(DISPLAY) "Done\n"
