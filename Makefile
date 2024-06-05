main:
	g++ main.cpp -o $@ -std=c++17 audiovisual/entitygraphics/*.cpp com/foxarc/util/*.cpp com/metanet/*.cpp com/metanet/commands/*.cpp com/metanet/global/*.cpp com/metanet/ui/*.cpp editor/*.cpp flash/utils/*.cpp -lz math/*.cpp simpleFramework/*.cpp simulation/*.cpp simulation/collision/*.cpp simulation/entities/*.cpp simulation/inputsource/*.cpp simulation/ninja/*.cpp tiles/*.cpp
brute brute2: audiovisual/entitygraphics/*.cpp com/foxarc/util/*.cpp com/metanet/*.cpp com/metanet/commands/*.cpp com/metanet/global/*.cpp com/metanet/ui/*.cpp editor/*.cpp flash/utils/*.cpp math/*.cpp simpleFramework/*.cpp simulation/*.cpp simulation/collision/*.cpp simulation/entities/*.cpp simulation/inputsource/*.cpp simulation/ninja/*.cpp tiles/*.cpp
	g++ -O3 $@.cpp -o $@ -std=c++17 $^ -lz
sim: sim.o
	g++ sim.o -o $@ -std=c++17 audiovisual/entitygraphics/*.cpp com/foxarc/util/*.cpp com/metanet/*.cpp com/metanet/commands/*.cpp com/metanet/global/*.cpp com/metanet/ui/*.cpp editor/*.cpp flash/utils/*.cpp -lz math/*.cpp simpleFramework/*.cpp simulation/*.cpp simulation/collision/*.cpp simulation/entities/*.cpp simulation/inputsource/*.cpp simulation/ninja/*.cpp tiles/*.cpp -L".\.sfml-2.5.1\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main
sim.o: sim.cpp
	g++ -c sim.cpp -o sim.o -std=c++17 -I".\.sfml-2.5.1\include" -DSFML_STATIC
hello:
	echo "Hello, World"
clean:
	rm *.exe