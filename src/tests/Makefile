TARGETS = BlobTest GameTest UserBlobTest
CXXFLAGS = -std=c++14 -fprofile-arcs -ftest-coverage
LIBS = -L /usr/lib -lsqlite3
INC = -I/usr/include -I ../server/c
LCOV := lcov
GENHTML := genhtml test.info --output-directory coverage
LCOV_FLAGS = --no-external --base-directory ../app/c

all: test

test: db $(TARGETS) $(addprefix run-,$(TARGETS)) lcov genhtml

%: %.cpp
	$(CXX) $(CXXFLAGS) $< $(LIBS) $(INC) -o $@

run-%: %
	-./$^

lcov:
	$(LCOV) $(LCOV_FLAGS) -c -d ./ -o test.info

genhtml:
	$(GENHTML)

clean:
	rm $(TARGETS) *.gcda *.gcno test.info test.db --force
	rm -rf coverage --force

db:
	cp agario.db test.db
