#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include <iostream>
#include <string.h>
#include <vector>
#include <cctype>
#include <fstream>
#include <random>
#include <time.h>

//in the future a lot of these classes will be moved to a gui class, but for now they are stored here as to not clutter up main.cpp
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
    
    struct PasswordRequirementsStruct {
        bool    needSpecial,
                needNumber,
                needCap,
                needNoSpace;
        int     minLength,
                maxLength;
    };
    struct UsernameRequirementsStruct {
        bool    useSpecial, //needs revamp once i implement gui, because for some reason cin detects enter as a character, and then std thinks its a symbol. for now i have disabled this feature in ValidateUsername()
                useNumber,
                useCap,
                needNoSpace;
        int     minLength,
                maxLength;
    };
    struct PasswordRequirementsStruct PasswordRequirements; //declare the struct
    struct UsernameRequirementsStruct UsernameRequirements; //declare the struct for usernames
private:
    //func
    bool ValidateUsername(std::string username, const UsernameRequirementsStruct Requirements);
    bool ValidatePassword(std::string password, const PasswordRequirementsStruct Requirements);
    void printWrongPasswordWarning(const PasswordRequirementsStruct Requirements);
    void printWrongUsernameWarning(const UsernameRequirementsStruct Requirements);
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
