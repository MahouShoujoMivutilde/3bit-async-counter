SYSTEMC_HOME = /opt/systemc

SYSTEMC_INC_DIR = $(SYSTEMC_HOME)/include
SYSTEMC_LIB_DIR = $(SYSTEMC_HOME)/lib-linux64

EXE = async-counter
SRC_DIR = .
OBJ_DIR = obj
INC_DIR = .

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
INC = $(wildcard $(INC_DIR)/*.h)

CPPFLAGS = -I$(INC_DIR) -I$(SYSTEMC_INC_DIR)
CFLAGS = -Wall -O2
LDFLAGS = -L$(SYSTEMC_LIB_DIR) -pthread
LDLIBS = -lsystemc -lm

CC = g++

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ) $(SYSTEMC_LIB_DIR)/libsystemc.so
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC) $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -rf $(OBJ) $(EXE) $(OBJ_DIR) *.vcd
