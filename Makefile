CXX       = g++
CXXFLAGS  = -O2 -Wall
AR        = ar
ARFLAGS   = rv
RANLIB    = ranlib

INCDIR    = include
SRCDIR    = src
LIBDIR    = lib
BINDIR    = bin
OBJDIR    = obj

SRCS      = Config.cpp \
            Reader.cpp \
            Writer.cpp \
            Util.cpp
OBJS      = $(SRCS:.cpp=.o)

TESTDIR   = test
TESTFLAGS = -Bstatic -lcppunit
TESTSRCS  = Test.cpp \
            ConfigTest.cpp \
            ReaderTest.cpp \
            WriterTest.cpp \
            UtilTest.cpp
TESTOBJS  = $(TESTSRCS:.cpp=.o)

.PHONY: all \
        init \
        libcslcsv.a \
        libcslcsv.so \
        clean \
        test \
        $(LIBDIR)/libcslcsv.a \
        $(LIBDIR)/libcslcsv.so \
        $(OBJDIR)/%.o

all: init libcslcsv.a libcslcsv.so

init:
	mkdir -p $(LIBDIR) $(BINDIR) $(OBJDIR)

libcslcsv.a: $(patsubst %, $(OBJDIR)/%, $(OBJS))
	$(AR) $(ARFLAGS) $(LIBDIR)/$@ $^
	$(RANLIB) $(LIBDIR)/$@

libcslcsv.so: $(patsubst %, $(OBJDIR)/%, $(OBJS))
	$(CXX) $(CXXFLAGS) -shared -o $(LIBDIR)/$@ $^

clean:
	rm -f $(LIBDIR)/* $(BINDIR)/* $(OBJDIR)/*

test: $(patsubst %, $(OBJDIR)/%, $(TESTOBJS)) $(LIBDIR)/libcslcsv.a
	$(CXX) $(CXXFLAGS) $(TESTFLAGS) -I$(INCDIR) $^ -o $(BINDIR)/$@
	./$(BINDIR)/$@
	rm -f ./$(BINDIR)/$@

$(LIBDIR)/libcslcsv.a: libcslcsv.a

$(LIBDIR)/libcslcsv.so: libcslcsv.so

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -o $@ -c $<

$(OBJDIR)/%.o: $(TESTDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -o $@ -c $<

