#### BUILD modalities
# use 
#   $ make BUILD=release 
# to compile different binaries
BUILD = release
cxxflags.debug = \
 -Wall -std=c++11 -g3
linkflags.debug = \
 -lm
cxxflags.trace = \
 -Wall -std=c++11 -DTRACE_ON
linkflags.trace = \
 -lm
cxxflags.release = \
 -Wall -std=c++11 -O3 -DSTATIC
linkflags.release = \
 -lm -static
cxxflags.gprof = \
 -Wall -std=c++11 -DNDEBUG -O3 -g -pg
linkflags.gprof = \
 -lm -g -pg
cxxflags.stats = \
 -Wall -std=c++11 -DNDEBUG -DSTATS_ON -O3
linkflags.stats = \
 -lm -g -pg

# for g++ <= 4.6
cxxflags.debug0x = \
 -Wall -std=c++0x
linkflags.debug0x = \
 -lm
cxxflags.trace0x = \
 -Wall -std=c++0x -DTRACE_ON
linkflags.trace0x = \
 -lm
cxxflags.release0x = \
 -Wall -std=c++0x -DNDEBUG -O3
linkflags.release0x = \
 -lm
cxxflags.gprof0x = \
 -Wall -std=c++0x -DNDEBUG -O3 -g -pg 
linkflags.gprof0x = \
 -lm -g -pg
cxxflags.stats0x = \
 -Wall -std=c++0x -DNDEBUG -DSTATS_ON -O3
linkflags.stats0x = \
 -lm -g -pg
####

SOURCE_DIR = src
BUILD_DIR = build/$(BUILD)

BINARY = $(BUILD_DIR)/dlv2
GCC = g++
#GCC = g++-fsf-4.8
CXX = $(GCC)
CXXFLAGS = $(cxxflags.$(BUILD))
LINK = $(GCC)
LINKFLAGS = $(linkflags.$(BUILD))
LIBS = -lodbc -lncurses -ltinfo

SRCS = $(shell find $(SOURCE_DIR) -name '*.cpp')

OBJS = $(patsubst $(SOURCE_DIR)%.cpp,$(BUILD_DIR)%.o, $(SRCS))
DEPS = $(patsubst $(SOURCE_DIR)%.cpp,$(BUILD_DIR)%.d, $(SRCS))

all: $(BINARY)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.d: $(SOURCE_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MM -MT '$(@:.d=.o)' $< -MF $@
	
$(BINARY): $(OBJS) $(DEPS)
	$(LINK) $(LINKFLAGS) $(OBJS) $(LIBS) -o $(BINARY) 

static: $(OBJS) $(DEPS)
	$(LINK) $(LINKFLAGS) $(OBJS) $(LIBS) -static -o $(BINARY)

run: $(BINARY)
	./$(BINARY)

parser: $(SOURCE_DIR)/input/aspcore2.l $(SOURCE_DIR)/input/aspcore2.y
	flex -o$(SOURCE_DIR)/input/aspcore2_lexer.hpp $(SOURCE_DIR)/input/aspcore2.l
	bison -y -d -o$(SOURCE_DIR)/input/aspcore2_parser.c $(SOURCE_DIR)/input/aspcore2.y
	bison -y -o$(SOURCE_DIR)/input/aspcore2_parser.hpp $(SOURCE_DIR)/input/aspcore2.y
	rm -f $(SOURCE_DIR)/input/aspcore2_parser.c

TESTS_DIR = tests

TESTS_TESTER = $(TESTS_DIR)/pyregtest.py
TESTS_REPORT_text = $(TESTS_DIR)/text.report.py

TESTS_COMMAND_dlv2_parser = $(BINARY) --printprogram --silent --stdin
TESTS_CHECKER_dlv2_parser = $(TESTS_DIR)/dlv2Parser.checker.py

TESTS_COMMAND_dlv2_depgraph = $(BINARY) --printdepgraph --silent --stdin
TESTS_CHECKER_dlv2_depgraph = $(TESTS_DIR)/depgraph.checker.py

TESTS_DIR_dlv2_parser = $(TESTS_DIR)/parser/
TESTS_SRC_dlv2_parser = $(sort $(shell find $(TESTS_DIR_dlv2_parser) -name '*.test.py'))
TESTS_OUT_dlv2_parser = $(patsubst %.test.py,%.test.py.text, $(TESTS_SRC_dlv2_parser))

TESTS_DIR_dlv2_depgraph = $(TESTS_DIR)/depgraph/
TESTS_SRC_dlv2_depgraph = $(sort $(shell find $(TESTS_DIR_dlv2_depgraph) -name '*.test.py'))
TESTS_OUT_dlv2_depgraph = $(patsubst %.test.py,%.test.py.text, $(TESTS_SRC_dlv2_depgraph))

tests: tests/parser tests/depgraph

tests/parser: $(TESTS_OUT_dlv2_parser)

tests/depgraph: $(TESTS_OUT_dlv2_depgraph) 

$(TESTS_OUT_dlv2_parser):
	@$(TESTS_TESTER) "$(TESTS_COMMAND_dlv2_parser)" $(patsubst %.test.py.text,%.test.py , $@) $(TESTS_CHECKER_dlv2_parser) $(TESTS_REPORT_text)

$(TESTS_OUT_dlv2_depgraph):
	@$(TESTS_TESTER) "$(TESTS_COMMAND_dlv2_depgraph)" $(patsubst %.test.py.text,%.test.py , $@) $(TESTS_CHECKER_dlv2_depgraph) $(TESTS_REPORT_text)

########## Clean

clean-dep:
	rm -f $(DEPS)
clean: clean-dep
	rm -f $(OBJS)

distclean: clean
	rm -fr $(BUILD_DIR)

-include $(DEPS)