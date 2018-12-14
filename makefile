PROGRAM = bookstore

CXX = g++
CXXFLAGS = -g -std=c++17

CPP_FILES = $(wildcard SJTU_Bookstore/*.cpp)
H_FILES = $(wildcard SJTU_Bookstore/*.h)

LDOPTIONS = -L.

$(PROGRAM): $(CPP_FILES) $(H_FILES) 
	$(CXX) -o $(PROGRAM) $(CXXFLAGS) $(LDOPTIONS) $(CPP_FILES)