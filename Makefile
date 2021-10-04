CXX := g++
SRCDIR := src
BUILDDIR := release

CFLAGS := -O3 -fopenmp  -I/usr/include/boost -I${LBTROOT}/include/ILP64/x86_64-linux-gnu -std=c++17

# CFLAGS := -O3 -fopenmp  -I/usr/include/boost -I${MKLROOT}/include -std=c++17
LIBFLAGS := -lboost_program_options -L/usr/lib/x86_64-linux-gnu/libboost_program_options -lblastrampoline -L${LBTROOT}/src/build

# LIBFLAGS := -lboost_program_options -L/usr/lib/x86_64-linux-gnu/libboost_program_options -L${MKLROOT}/lib/intel64 -lmkl_intel_lp64-lmkl_intel_thread -lmkl_core -liomp5 -lpthread -lm -ldl

TARGET := $(BUILDDIR)/qtmini

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.cpp=.o))

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	$(CXX) $^ $(LIBFLAGS) -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) -c $(CFLAGS) -o $@ $< 

run: $(TARGET)

clean:
	@echo " Cleaning..."
	@rm -fr $(BUILDDIR) $(TARGET) 2>/dev/null || true

.PHONY: clean
