NAME = tcptunnel

CC = gcc
LD = gcc
CFLAGS = -Wall -I./
LDFLAGS = -lz -lcrypto
OBJS = tcptunnel.o deal.o kissdb.o

BINDIR = /usr/local/bin/
INSTALL = install
STRIP = strip
RM = /bin/rm -f
CP = cp

all: tcptunnel

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

tcptunnel: $(OBJS)
	@echo $(CC)
	$(LD) -o $(NAME) $(OBJS) $(LDFLAGS)
	$(CP) $(NAME) ..

install:
	$(INSTALL) -d $(BINDIR)
	$(INSTALL) -m 0755 $(NAME) $(BINDIR)
	$(STRIP) $(BINDIR)/$(NAME)

uninstall:
	$(RM) $(BINDIR)/$(NAME)

clean:
	$(RM) *.o *~ $(NAME) ../$(NAME)

