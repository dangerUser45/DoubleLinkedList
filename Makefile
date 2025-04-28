SRC                = src/
B                  = build/
D                  = dump/
GRAPH              = Graphviz_dot/
IMG                = images/

CXX                = g++

AR                 = ar
ARFLAGS            = rcs

CXXFLAGS_DEBUG     = -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector
CXXFLAGS_RELEASE   = -O3
CXXFLAGS           = -I./include/

NAME_TEST          = ListTest
CMD_TEST           = $(B)$(NAME_TEST).out

LIB_LIST           = $(B)libList.a

LDFLAGS            = -L$(B) -lList

CPPSRC             = $(SRC)ListCtorDtor.cpp $(SRC)ListToolFunctions.cpp $(SRC)ListDump.cpp
CPPOBJ             = $(CPPSRC:$(SRC)%.cpp=$(B)%.o)
CPPDEP             = $(patsubst %.o, %.d, $(CPPOBJ))
#==================================================================================
#----------------------------------------------------------------------------------
#==================================================================================

BUILD ?= release

ifeq ($(BUILD), debug)
	CXXFLAGS += $(CXXFLAGS_DEBUG)

else ifeq ($(BUILD), release)
	CXXFLAGS += $(CXXFLAGS_RELEASE)

else
$(error Unknown build type: $(BUILD). Use debug or release)
endif
#----------------------------------------------------------------------------------

ASSERT ?= on

ifeq ($(ASSERT), on)
	CXXFLAGS += -DASSERT_ON

else ifeq ($(ASSERT), off)

else
$(error Unknown assert mode: $(ASSERT). Use on or off)
endif
#==================================================================================
#----------------------------------------------------------------------------------
#==================================================================================

.PHONY: lib test testrun clear
#----------------------------------------------------------------------------------

lib: $(LIB_LIST)

$(LIB_LIST): $(CPPOBJ)
	$(AR) $(ARFLAGS) $@ $(CPPOBJ)

$(CMD_TEST): $(SRC)$(NAME_TEST).cpp $(LIB_LIST)
	$(CXX) $< -o $@ $(CXXFLAGS) $(LDFLAGS)

$(B)%.o: $(SRC)%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -MMD -MT '$@ $(@:.o=.d)' -c $< -o $@
	@echo \n
-include $(CPPDEP)
#----------------------------------------------------------------------------------

test: $(CMD_TEST)
#----------------------------------------------------------------------------------

testrun: test
	$(CMD_TEST)
#----------------------------------------------------------------------------------

clear:
	rm -rf $(B)* $(D)*.html $(D)$(GRAPH)*.txt $(D)$(GRAPH)$(IMG)*
#----------------------------------------------------------------------------------
