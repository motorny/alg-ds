# Универсальный Makefile, автоматически ищущий файлы исходного кода в папке src,
# а файлы .h в папке include. Все зависимости определяются автоматически

# Название программы, которую требуется собрать
EXEC:=Join.exe

SRC:=src
TST:=test
HDR:=include
RUN:=run

ifndef BUILD
BIN:=bin
else
BIN:=bin/$(BUILD)
endif
OBJ:=obj

SOURCES:=$(wildcard $(SRC)/*.c)
OBJS:=$(SOURCES:$(SRC)/%.c=$(OBJ)/%.o)

define NEWLINE


endef

DEPEN:=$(shell gcc -MM -I$(HDR) $(SOURCES))
DEPEN:=$(filter %.o: $(HDR)/%.h,$(DEPEN))
DEPEN:=$(patsubst %.o:,$(NEWLINE)$(OBJ)/%.o:, $(DEPEN))

.PHONY: all clean test

ifeq ($(BUILD), Release)
.INTERMEDIATE:  $(OBJS)
endif

all: $(BIN)/$(EXEC)

# Дополнительные зависимости
$(eval $(DEPEN))

$(OBJS): $(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	@echo "Compiling file $<..."
	-gcc -o $@ -Wall -c -I$(HDR)  $< -g 

$(BIN)/$(EXEC): $(OBJS) | $(BIN)
	@echo "Linking..."
	gcc -o $@ $(OBJS)
	@echo "Build succeeded!"

$(BIN) $(OBJ) $(TST)\$(RUN):
	mkdir $@

clean:
	-rd /s/q $(BIN)
	-rd /s/q $(OBJ)
	-rd /s/q $(TST)\$(RUN)
	
OBJS2:=$(subst $(OBJ)/main.o,,$(OBJS))
TESTS:=$(wildcard $(TST)/*.c)
TOBJS:=$(TESTS:$(TST)/%.c=$(TST)/run/%.o)
TEXES:=$(TESTS:$(TST)/%.c=$(TST)/run/%.exe)
TRUNS:=$(TESTS:$(TST)/%.c=%)

.INTERMEDIATE:  $(TOBJS)

test: $(TRUNS)

$(TRUNS) : % : $(TST)/$(RUN)/%.exe
	@echo "Running $@"
	-@$<
	
$(TEXES) : $(TST)/$(RUN)/%.exe : $(TST)/$(RUN)/%.o $(OBJS2) 
	gcc -o $@ $< $(OBJS2)
	
$(TOBJS) : $(TST)/$(RUN)/%.o : $(TST)/%.c | $(TST)\$(RUN)
	-gcc -o $@ -c -I$(HDR)  $< -g 
#-std=c++11