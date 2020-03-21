RM = rm -f
MKDIR = mkdir -p

NAME = mario_sokoban

SRCDIR = src
INCDIR = include
OBJDIR = build

CXX = g++
CXXFLAGS = -Wall -Wextra -I$(INCDIR) $(shell sdl2-config --cflags) -std=c++98
LDFLAGS = $(shell sdl2-config --libs)

SRC = $(shell find $(SRCDIR) -type f -name "*.cpp")
INC = $(shell find $(INCDIR) -type f -name "*.h" -o -name "*.hpp")
OBJ = $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

all: prebuild $(NAME)

prebuild:
	@$(MKDIR) $(OBJDIR)

$(NAME): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INC)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
