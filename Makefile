#### BUILD modalities
# use 
#   $ make BUILD=release 
# to compile different binaries
BUILD = release
cxxflags.debug = \
 -Wall -std=c++11
linkflags.debug = \
 -lm
cxxflags.trace = \
 -Wall -std=c++11 -DTRACE_ON
linkflags.trace = \
 -lm
cxxflags.release = \
 -Wall -std=c++11 -DNDEBUG -O3
linkflags.release = \
 -lm
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
linkflags.trace = \
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
CXX = $(GCC)
CXXFLAGS = $(cxxflags.$(BUILD))
LINK = $(GCC)
LINKFLAGS = $(linkflags.$(BUILD))

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
	$(LINK) $(LINKFLAGS) $(LIBS) $(OBJS) -o $(BINARY)

static: $(OBJS) $(DEPS)
	$(LINK) $(LINKFLAGS) $(LIBS) $(OBJS) -static -o $(BINARY)

run: $(BINARY)
	./$(BINARY)

parser: $(SOURCE_DIR)/aspcore2.l $(SOURCE_DIR)/aspcore2.y
	flex -o$(SOURCE_DIR)/aspcore2_lexer.hpp $(SOURCE_DIR)/aspcore2.l
	bison -y -d -o$(SOURCE_DIR)/aspcore2_parser.c $(SOURCE_DIR)/aspcore2.y
	bison -y -o$(SOURCE_DIR)/aspcore2_parser.hpp $(SOURCE_DIR)/aspcore2.y
	rm -f $(SOURCE_DIR)/aspcore2_parser.c

########## Clean

clean-dep:
	rm -f $(DEPS)
clean: clean-dep
	rm -f $(OBJS)

distclean: clean
	rm -fr $(BUILD_DIR)

-include $(DEPS)
