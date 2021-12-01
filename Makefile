CXXFLAGS = -std=c++20 -fmax-errors=5 -O0 -g   -Wall -fmessage-length=0 -I $(INCLUDEDIR)  

_OBJS = AOC2021.o util.o
OBJS = $(patsubst %,$(OBJSDIR)/%,$(_OBJS))
INCLUDEDIR = include
OBJSDIR = objs
SRCDIR = src

TARGET =AOC2021 

$(OBJSDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS)  -c -o $@  $<

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) 
	