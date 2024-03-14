main:
	g++ main.cpp -o $@ -std=c++17 com/foxarc/util/*.cpp com/metanet/*.cpp com/metanet/commands/*.cpp com/metanet/global/*.cpp com/metanet/ui/*.cpp editor/*.cpp flash/utils/*.cpp -lz math/*.cpp simpleFramework/*.cpp simulation/*.cpp simulation/collision/*.cpp simulation/entities/*.cpp simulation/inputsource/*.cpp simulation/ninja/*.cpp tiles/*.cpp
brute brute2: com/foxarc/util/*.cpp com/metanet/*.cpp com/metanet/commands/*.cpp com/metanet/global/*.cpp com/metanet/ui/*.cpp editor/*.cpp flash/utils/*.cpp math/*.cpp simpleFramework/*.cpp simulation/*.cpp simulation/collision/*.cpp simulation/entities/*.cpp simulation/inputsource/*.cpp simulation/ninja/*.cpp tiles/*.cpp
	g++ -O3 $@.cpp -o $@ -std=c++17 $^ -lz
hello:
	echo "Hello, World"
clean:
	rm *.exe