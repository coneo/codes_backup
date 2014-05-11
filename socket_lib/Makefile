objects = \
    \
    connector.o\
    listener.o\
    connection.o\
    socket.o\
    endpoint.o\


CC = g++-4.7.3
cc = g++-4.7.3

ln_flags = -L../base -lbase
cc_flags = -std=c++11 -g


target = libnet.a
test_target = test_server test_client

.PHONY:
all: $(target)


$(target) : $(objects)
	ar rs $(target) $(objects)

.PHONY:
t: $(test_target)

test_server: $(target) test.cpp
	$(cc) $(cc_flags) -DTEST_SERVER test.cpp -L. -lnet $(ln_flags) -o test_server

test_client: $(target) test.cpp
	$(cc) $(cc_flags) -DTEST_CLIENT test.cpp -L. -lnet $(ln_flags) -o test_client


$(objects): %.o: %.cpp
	$(cc) $(cc_flags) -c $< -o $@


%.d: %.cpp
	@set -e -x; \
	rm -f $@; \
	$(cc) -MM $(cc_flags) $< > $@.$$$$;  \
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
