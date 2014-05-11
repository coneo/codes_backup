objects = \
    \
    tools.o\
    exception.o\
    scope_guard.o\

CC = g++-4.7.3
cc = g++-4.7.3

cc_flags = -std=c++11 -g

target = libbase.a
test_target = test

.PHONY:
all: $(target)

.PHONY:
t : $(test_target)

$(test_target): $(target) test.cpp
	$(cc) $(cc_flags) -o $(test_target) test.cpp -L. -lbase


$(target) : $(objects)
	ar rs $(target) $(objects)


%.o: %.cpp
	$(cc) $(cc_flags) -c $< -o $@

%.d: %.cpp
	@set -e -x; \
	rm -f $@; \
	$(cc) $(cc_flags) -MM $< > $@.$$$$;  \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@;  \
	rm -f $@.$$$$

-include $(objects:.o=.d)

.PHONY: clean
clean:
	-rm -f *.o *.d *.d.* $(target)

.PHONY: clean_test
clean_test:
	-rm -f *.o *.d *.d.* $(test_target)
