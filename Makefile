CC = cc
CFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
SOURCE = mtm.c
OUTPUT = mtm 

all: $(OUTPUT)

$(OUTPUT): $(SOURCE)
	$(CC) $(SOURCE) $(CFLAGS) -o $(OUTPUT)

clean:
	rm -f $(OUTPUT)
