.DEFAULT_GOAL := help

CXX = g++
CXXFLAGS = -std=c++17 -O3

SFML_CPPFLAGS = -I".\.sfml-2.5.1\include" -DSFML_STATIC
SFML_LDFLAGS = -L".\.sfml-2.5.1\lib"
SFML_LIBS = -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main

COMMON_SRC = \
    $(wildcard audiovisual/entitygraphics/*.cpp) \
    $(wildcard com/foxarc/util/*.cpp) \
    $(wildcard com/metanet/*.cpp) \
    $(wildcard com/metanet/commands/*.cpp) \
	$(wildcard com/metanet/data/*.cpp) \
    $(wildcard com/metanet/global/*.cpp) \
    $(wildcard com/metanet/ui/*.cpp) \
    $(wildcard editor/*.cpp) \
    $(wildcard flash/ui/*.cpp) \
    $(wildcard flash/utils/*.cpp) \
    $(wildcard math/*.cpp) \
    $(wildcard simpleFramework/*.cpp) \
    $(wildcard simulation/*.cpp) \
    $(wildcard simulation/collision/*.cpp) \
    $(wildcard simulation/entities/*.cpp) \
    $(wildcard simulation/inputsource/*.cpp) \
    $(wildcard simulation/ninja/*.cpp) \
	$(wildcard simulation/save/*.cpp) \
    $(wildcard tiles/*.cpp)

COMMON_OBJ = $(COMMON_SRC:.cpp=.o)

main: main.o $(COMMON_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lz

brute: brute.o $(COMMON_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lz

sim: sim.o $(COMMON_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LDFLAGS) $(SFML_LIBS) -lz

sim.o: sim.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(SFML_CPPFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

help:
	@echo "Available targets:"
	@echo "  make main"
	@echo "  make brute"
	@echo "  make sim"
	@echo "  make clean"

clean:
	rm -f $(COMMON_OBJ) *.o *.exe