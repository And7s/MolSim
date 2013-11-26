root := ../../xsd/examples

include $(root)/build/cxx/rules.make
include $(root)/build/xsd/tree-rules.make


# Build.
#
filereader: filereader.o input.o

input.o: input.cxx input.hxx
filereader.o: filereader.cxx input.hxx

input.cxx input.hxx: input.xsd


# Test.
#
.PHONY: test
test: filereader input.xml
	./driver input.xml


# Clean.
#
.PHONY: clean
clean:
	rm -f input.o input.?xx filereader.o filereader

