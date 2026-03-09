CXX = g++

CXXFLAGS = -g

EXEC = a.out
SRCS = $(wildcard *.cpp parser/*.cpp fragment/*.cpp state/*.cpp automata/*.cpp)

OBJS = $(SRCS:.cpp=.o)

RM = rm -f

.PHONY: all
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: run
run: $(EXEC)
	./$(EXEC)

.PHONY: clean
clean:
	$(RM) $(OBJS) $(EXEC)
