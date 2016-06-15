CC=clang
CFLAGS=-Wall -I ./include

SRCDIR=src
BUILDDIR=build
OUTDIR=bin

SOURCES=$(wildcard $(SRCDIR)/**/*.c $(SRCDIR)/*.c)
OBJECTS=$(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))
TARGET=tinyserver

all: $(TARGET)
build:
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(OUTDIR)

$(TARGET): build $(OBJECTS)
	$(CC) $(OBJECTS) -o $(OUTDIR)/$(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm server
