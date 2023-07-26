class mathutils {
    private:
        static unsigned int rnd_seed;
    public:
        mathutils() = delete;
        static void SetRandomSeed(unsigned int seedValue);
};

unsigned int mathutils::rnd_seed = 1;

void mathutils::SetRandomSeed(unsigned int seedValue) {
    if (seedValue == 0 || seedValue > 2147483646) {
        rnd_seed = 1;
    } else {
        rnd_seed = seedValue;
    }
}