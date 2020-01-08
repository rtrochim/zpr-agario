TARGETS=BlobTest

all: $(TARGETS)

test: $(TARGETS) $(addprefix run-,$(TARGETS))

%: %.cpp
	$(CXX) -o$@ $^

run-%: %
	-./$^ --log_level=all

clean:
	rm $(TARGETS) *-report.xml
