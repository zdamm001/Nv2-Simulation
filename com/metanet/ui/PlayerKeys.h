#include <vector>
#include <sstream>

using namespace std;

class PlayerKeys {
    public:
        static const unsigned int JUMP = 0;
        static const unsigned int LEFT = 1;
        static const unsigned int RIGHT = 2;
        static const unsigned int SUICIDE = 3;
    private:
        static const unsigned int NUMBER_OF_PLAYER_KEYS = 4;
        static const unsigned int MAX_NUMBER_OF_PLAYERS = 4;
        vector<int> _playerBindings;
    public:
        PlayerKeys();
        void bindActionKeyForPlayer(unsigned int keyType, unsigned int binding, unsigned int playerIndex);
        int getActionKeyForPlayer(unsigned int keyType, unsigned int playerIndex) const;
        vector<int> getActions(const vector<int>& actionKeys);
        string GetKeyConfigString() const;
        void SetKeyConfigString(const string& configString);
};
