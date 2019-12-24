#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include <iostream>
#include <string.h>
#include <vector>
#include <cctype>
#include <fstream>

/**
 * @todo write docs
 */
class User
{
public:
    //func
    User();
    void PickUsername();
    void PickPassword();
    void LoginUsername();
    void LoginPassword();
    void Setup();
    void SignIn();
    void SignUp();
    void DecideLogin();
    void PrintInfo();
    void SaveInfo();

    
    //vars
    bool debugInfo;
private:
    //func
    std::string ValidateUsername(std::string username);
    std::string ValidatePassword(std::string password);
    void UnwrapAccountInfo();
    std::string infoToString();
    inline bool doesFileExist(const std::string& name);
    void setDirectory();
    
    //vars
    std::string username, tempUsername;
    std::string password, tempPassword;
    std::string cancelValue;//this value is set for validation, if the username/pass is this, it will redo.
    std::string Directory;//where the file for account information is

};

#endif // USER_H_INCLUDED
