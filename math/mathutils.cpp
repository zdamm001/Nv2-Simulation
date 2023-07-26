class MathUtils {
    private:
        static unsigned int rnd_seed;
    public:
        MathUtils() = delete;
        static void SetRandomSeed(unsigned int seedValue) {
            if (seedValue == 0 || seedValue > 2147483646) {
                rnd_seed = 1;
            } else {
                rnd_seed = seedValue;
            }
        }
};

unsigned int MathUtils::rnd_seed = 1;