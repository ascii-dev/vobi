CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
LDFLAGS =
OBJFILES = rawMode.o vobi.o
TARGET = vobi

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~

#vobi: vobi.c
#	$(CC) vobi.c -o vobi -Wall -Wextra -pedantic -std=c99
