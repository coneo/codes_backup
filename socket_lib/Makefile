objects = \
    \
    connector.o\
    listener.o\
    connection.o\
    socket.o\
    base.o\
    scope_guard.o\

CC = g++-4.7.3
cc = g++-4.7.3

CXX_FLAGS = -std=c++11 -g

all: $(objects)
	$(cc) $(objects) -o test

test_server: $(objects) test.cpp
	$(cc) $(CXX_FLAGS) -DTEST_SERVER -c test.cpp -o test.o
	$(cc) $(objects) test.o -o test_server

test_client: $(objects) test.cpp
	$(cc) $(CXX_FLAGS) -DTEST_CLIENT -c test.cpp -o test.o
	$(cc) $(objects) test.o -o test_client


%.o: %.cpp
	$(cc) $(CXX_FLAGS) -c $< -o $@


%.d: %.cpp
	@set -e -x; \
	rm -f $@; \
	$(cc) -MM $(CXX_FLAGS) $< > $@.$$$$;  \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@;  \
	rm -f $@.$$$$

-include $(objects:.o=.d)
#sed 's,/($*/)/.o[ :]*,/1.o $@ : ,g' < $@.$$$$ > $@; \

.PHONY: clean
clean:
	-rm -f *.o *.d *.d.*

.PHONY: clean_test
clean_test:
	-rm -f test *.o *.d *.d.*
	-rm -f test_client test_server
