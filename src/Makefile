CPPFLAGS+=-I../include

all: dogapi_connector.o dogfact.o

dogfact.o: dogfact.cpp
	$(GCC) $(CPPFLAGS) -c dogfact.cpp

dogapi_connector.o: dogapi_connector.cpp
	$(GCC) $(CPPFLAGS) -c dogapi_connector.cpp

clean:
	$(RM) *.o

.PHONY: clean
