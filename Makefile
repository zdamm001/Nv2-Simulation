main:
	g++ main.cpp -o $@ -std=c++17 com/foxarc/util/*.cpp com/metanet/*.cpp com/metanet/commands/*.cpp com/metanet/global/*.cpp com/metanet/ui/*.cpp editor/*.cpp flash/utils/*.cpp -lz math/*.cpp simpleFramework/*.cpp simulation/*.cpp simulation/collision/*.cpp simulation/entities/*.cpp simulation/inputsource/*.cpp simulation/ninja/*.cpp tiles/*.cpp
brute:
	g++ brute.cpp -o $@ -std=c++17 com/foxarc/util/*.cpp com/metanet/*.cpp com/metanet/commands/*.cpp com/metanet/global/*.cpp com/metanet/ui/*.cpp editor/*.cpp flash/utils/*.cpp -lz math/*.cpp simpleFramework/*.cpp simulation/*.cpp simulation/collision/*.cpp simulation/entities/*.cpp simulation/inputsource/*.cpp simulation/ninja/*.cpp tiles/*.cpp
hello:
	echo "Hello, World"
clean:
	rm main.exe
	rm brute.exe