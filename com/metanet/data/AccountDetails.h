#pragma once
#include <string>

using namespace std;

class AccountDetails {
    public:
        string enteredUserName = "";
        string enteredPassword = "";
        string loggedInUserName = "";
        string email = "";
        string enteredPasswordRetype = "";
        bool loggedIn = false;
        string cookie = "";
        string userID = "";
        string error = "";
        bool useDatabase = true;
        bool isWeb = false;
        bool isKiosk = false;
        bool canAddFavourites = true;
        bool canCreateNewLevel = true;
    public:
        AccountDetails() {};
};
