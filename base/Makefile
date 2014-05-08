objects = \
    \
    tools.o\
    exception.o\
    scope_guard.o\

CC = g++4.7
cc = g++4.7

CXX_FLAGS = -std=c++11 -g

link_name=base
target = lib$(link_name).a
test_target = test

.PHONY:
all: $(target)

$(test_target): $(target) test.cpp
	$(cc) $(CXX_FLAGS) -o $(test_target) test.cpp -L. -lbase


$(target) : $(objects)
	ar r $(target) $(objects)
	ranlib $(target)


%.o: %.cpp
	$(cc) $(CXX_FLAGS) -c $< -o $@

%.d: %.cpp
	@set -e -x; \
	rm -f $@; \
	$(cc) $(CXX_FLAGS) -MM $< > $@.$$$$;  \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@;  \
	rm -f $@.$$$$

-include $(objects:.o=.d)

.PHONY: clean
clean:
	-rm -f *.o *.d *.d.* $(target)

.PHONY: clean_test
clean_test:
	-rm -f *.o *.d *.d.* $(test_target)
