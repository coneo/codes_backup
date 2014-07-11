objects = \
    \
    connector.o\
    listener.o\
    connection.o\
    socket.o\
    endpoint.o\
    epoller.o\


CC = g++4.7
cc = g++4.7

ln_flags = -L../base -lbase
cc_flags = -std=c++11 -g


target = libnet.a
test_target = test_server test_client
test_target_ln_flags = -lrt -lnet -Wl,-rpath,../base

.PHONY:
all: $(target)


$(target) : $(objects)
	ar rs $(target) $(objects)

.PHONY:
t: $(test_target)

.PHONY:
t_epoller : $(test_target)

test_server: $(target) test.cpp
	$(cc) $(cc_flags) -DTEST_SERVER test.cpp -L. $(test_target_ln_flags) $(ln_flags) -o test_server

test_client: $(target) test.cpp
	$(cc) $(cc_flags) -DTEST_CLIENT test.cpp -L. $(test_target_ln_flags) $(ln_flags) -o test_client


$(objects): %.o: %.cpp
	$(cc) $(cc_flags) -c $< -o $@


%.d: %.cpp
	@#set -x ; 
	@set -e ; \
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
test_clean:
	-rm -f test *.o *.d *.d.*
	-rm -f test_client test_server
