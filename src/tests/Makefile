TARGETS=BlobTest

all:
    g++ -o BlobTest -fprofile-arcs -ftest-coverage BlobTest.cpp -L /usr/lib -I/usr/include
    g++ -o UserBlobTest -fprofile-arcs -ftest-coverage UserBlobTest.cpp -L /usr/lib -I/usr/include

test: $(TARGETS) $(addprefix run-,$(TARGETS))

%: %.cpp
	g++ -o BlobTest -fprofile-arcs -ftest-coverage BlobTest.cpp -L /usr/lib -I/usr/include

run-%: %
	-./$^ --log_level=all

clean:
	rm $(TARGETS) *-report.xml
	rm *.gcda
	rm *.gnca

