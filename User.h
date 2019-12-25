#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include <iostream>
#include <string.h>
#include <vector>
#include <cctype>
#include <fstream>
#include <random>
#include <time.h>

class User
{
public:
    //func
    User();
    void NewUsername();
    void NewPassword();
    void LoginUsername();
    void LoginPassword();
    void Setup();
    void SignIn();
    void SignUp();
    void DecideLogin();
    void PrintInfo();
    void SaveInfo();
    std::string LoadInfo();
    std::string NewCancelValue();
    
    //get and set
    std::string GetUsername();
    std::string GetPassword();
    std::string GetCancelValue();
    std::string GetDirectory();
    void SetDebugInfo(bool tf);
private:
    //func
    std::string ValidateUsername(std::string username);
    std::string ValidatePassword(std::string password);
    std::string infoToString();
    void UnwrapAccountInfo();
    void setDirectory();
    inline bool doesFileExist(const std::string& name);
    
    //vars
    bool debugInfo;
    std::string username, tempUsername;
    std::string password, tempPassword;
    std::string cancelValue;//this value is set for validation, if the username/pass is this, it will redo.
    std::string Directory;//where the file for account information is
};

#endif // USER_H_INCLUDED
