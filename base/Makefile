objects = \
    \
    tools.o\
    exception.o\
    scope_guard.o\
    datetime.o\

CC = g++-4.7.3
cc = g++4.7

cc_flags = -std=c++11 -fPIC -g

target = libbase
test_target = test

.PHONY:
all: $(target).a $(target).so

.PHONY:
t : $(test_target)

$(test_target) : $(target).so test.cpp
	$(cc) $(cc_flags) -o $(test_target) test.cpp -L. -lbase -lrt -Wl,-rpath,.


$(target).a : $(objects)
	ar rs $(target) $(objects)

$(target).so : $(objects)
	$(cc) -shared $(objects) -o $(target).so

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
	-rm -f *.o *.d *.d.* $(target).o $(target).so

.PHONY: clean_test
clean_test:
	-rm -f *.o *.d *.d.* $(test_target)
