GTEST_DIR=gtest
GTEST_SRC=${GTEST_DIR}/src/gtest-all.cc
TEST_SRC=test1.cpp
CXX=g++
CXX_FLAGS= -isystem gtest/include -isystem ../src -I${GTEST_DIR} -pthread
LD_FLAGS=libgtest.a
OBJS=complete_schedule single_schedule lookup_id lookup_name \
direct_route service shortest_riding shortest_total

all: libgtest.a $(OBJS)

$(OBJS): %: %.cpp
	$(CXX)  $(CXX_FLAGS) $(LD_FLAGS) -o $@.out $<

libgtest.a: gtest-all.o
	ar -rc libgtest.a gtest-all.o

gtest-all.o: ${GTEST_SRC}
	g++ $(CXX_FLAGS) -c ${GTEST_SRC}

clean:
	rm *.o
	rm *.out
	rm *.a

rebuild: clean all
