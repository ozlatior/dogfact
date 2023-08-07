GCC=g++
CPPFLAGS=-Wall -Wextra -Werror
CPPFLAGS+=-DCPPHTTPLIB_OPENSSL_SUPPORT
LDFLAGS=
LDLIBS=-lssl -lcrypto

export RM=rm -f

export GCC
export CPPFLAGS

all: dogfact

src:
	$(MAKE) -C ./src

dogfact: src
	$(GCC) $(LDFLAGS) ./src/dogfact.o ./src/dogapi_connector.o $(LDLIBS) -o dogfact

clean:
	$(MAKE) clean -C ./src

.PHONY: clean src
