#include "User.h"

#include <iostream>
#include <string.h>
#include <vector>
#include <cctype>
#include <fstream>
#include <random>
#include <time.h>

        User::User(){
            cancelValue = NewCancelValue();//if usernm/pass is this, it resets.
            
            debugInfo = false;//keep at bottom, so if to override this is wont bug whats above
            
            //setting defaults for PasswordRequirements
            PasswordRequirements.needCap = true;
            PasswordRequirements.needNoSpace = true;
            PasswordRequirements.needNumber = true;
            PasswordRequirements.needSpecial = true;
            PasswordRequirements.maxLength = 15;
            PasswordRequirements.minLength = 5;
            
            //setting defaults for UsernameRequirements
            UsernameRequirements.useCap = true;
            UsernameRequirements.needNoSpace = true;
            UsernameRequirements.useNumber = true;
            UsernameRequirements.useSpecial = true;
            UsernameRequirements.maxLength = 15;
            UsernameRequirements.minLength = 5;
        }
        void User::Setup(){
            std::cout << "Hello! Welcome to a dumb social media\nthat already has a dwindiling userbase\n";
            DecideLogin();
            std::cout << "Alright, theres nothing for us to do now but\nsell your info. Good luck, sucker!\n";
            
            return; 
        }
        void User::DecideLogin(){
            std::string userINPUT;
            std::cout << "Press 1 to Sign In, press 2 to sign up, or press 3 to exit\n";
            std::getline(std::cin, userINPUT);
            if (userINPUT == "1"){
                SignIn();
            }
            else if (userINPUT == "2"){
                SignUp();
            }
            else if (userINPUT == "3"){
                
                std::abort();//Crashes program
            }
            else{
                std::cout << "Sorry, thats's not a valid input." << std::endl;
                DecideLogin();
                if (debugInfo)
                    std::cout << "You typed: " << userINPUT << std::endl;
            }
        }
        void User::SignUp(){
            NewUsername();
            std::cout << "Username is valid!" << std::endl;
            NewPassword();
            std::cout << "Password is valid!" << std::endl;
            if (debugInfo)
                PrintInfo();
            SaveInfo();
        }
        void User::SignIn(){
            LoginUsername();
            std::cout << "User exists!" << std::endl;
            LoginPassword();
            std::cout << "Password is correct." << std::endl;
        }
        void User::NewUsername(){
            std::cout << "Please pick a username: ";
                std::getline(std::cin, tempUsername);
                if (ValidateUsername(tempUsername, UsernameRequirements)){//if this returns true, meaning is has been vaildated.
                    username = tempUsername;
                } else NewUsername();
                setDirectory();
                
                if (doesFileExist(Directory)){//file exists, account already made
                    std::cout << "Sorry, the account already exists somehow.\nNobody even uses this social media!\n";
                    NewUsername();
                }
                else {
                    if (debugInfo)
                        std::cout << "No existing file named " << Directory << std::endl;
                }
                
        }
        void User::NewPassword(){
            std::cout << "\nPlease choose a password: ";
                std::getline(std::cin, tempPassword);
                if (ValidatePassword(tempPassword, PasswordRequirements)){//if this returns true, meaning is has been vaildated.
                    password = tempPassword;
                } else NewPassword();
        }
        void User::LoginUsername(){
            std::cout << "Input your username: ";
                std::getline(std::cin, username);
            setDirectory();
            
            if (doesFileExist(Directory)){
                std::cout << "User found!\n";
            }
            else{
                std::cout << "That user doesn't exist!\n";
                LoginUsername();
            }
            return;
        }
        void User::LoginPassword(){
            std::string userPassword;//the password stored inside the .acc file
            
            userPassword = LoadInfo();
            
            std::cout << "Enter your password: ";
                std::getline(std::cin, tempPassword);
                
            if (tempPassword == userPassword){
                password = userPassword;
            }
            else{
                std::cout << "Invalid password!\n";
                LoginPassword();
            }
        }
        bool User::ValidateUsername(std::string username, const UsernameRequirementsStruct Requirements){
            char usernameArray[username.length()];
            bool isValid = false;
                bool goodLength = false;
            strcpy(usernameArray, username.c_str());
            
            for (int i=0;i<=username.length();i++){
                if(debugInfo) std::cout << usernameArray[i] << ": ";
                
                if (Requirements.needNoSpace){
                    if      (usernameArray[i] == ' '){//checks for spaces
                        if (debugInfo) std::cout << "Contains space\n";
                        return false; //if it finds a space, returns false immediatley
                    } 
                }
                
                /*
                if (!Requirements.useSpecial){
                    if (!(std::isalpha(usernameArray[i]))){//checks for symbol
                        if (debugInfo) std::cout << "Contains symbol\n";
                        return false;
                    }
                }
                *///symbol is being notty, detecing the "enter" button as \n
                
                if (!Requirements.useCap){
                    if (std::isupper(usernameArray[i])){//checks for uppercase
                        if (debugInfo) std::cout << "Contains a capital\n";
                        return false;
                    }
                }
                
                if (!Requirements.useNumber){
                    if (std::isdigit(usernameArray[i])){//checks for number
                        if (debugInfo) std::cout << "Contains number\n";
                        return false;
                    }
                }
                
                if (username.length() <= Requirements.maxLength)
                    if (username.length() >= Requirements.minLength)
                        goodLength = true;
                    else
                        goodLength = false;
                else
                    goodLength = false;
            }
            
            if (goodLength)
                isValid = true;
            else
                isValid = false;
            
            if (!isValid) printWrongUsernameWarning(Requirements); //if invalid, it tells you what you must have.
            return isValid;
        }
        bool User::ValidatePassword(std::string password, const PasswordRequirementsStruct Requirements){
            
            char passwordArray[password.length()];
            bool isValid = false;
                //password identifiers
                bool    hasSpecial = false,
                        hasNumber = false,
                        hasCap = false,
                        noSpace = true,
                        goodLength = false;
            
            strcpy(passwordArray, password.c_str());
            
            //I am aware this following check code is practically a sin and im going to hell because it checks every instance in every iteration of i.
            //but as Valve developers say when something isnt particularly optimized: "Too bad!"
            for (int i=0;i<password.length();i++){
                if(debugInfo) std::cout << passwordArray[i] << ": ";
                
                if (Requirements.needNoSpace){
                    if      (passwordArray[i] == ' '){//checks for spaces
                    noSpace = false;//this starts out true, so if it finds a space it turns false. it needs to be true to pass.
                    if(debugInfo)
                        std::cout << "nospFalse\n";
                    } 
                } else noSpace = true; //if needNoSpace, is false, we make the bool true to bypass the check at the end.
                
                if (Requirements.needCap){
                    if (std::isupper(passwordArray[i])){//checks for uppercase
                    hasCap = true;
                    if (debugInfo)
                        std::cout << "hasCapTrue\n";
                    }
                } else hasCap = true;//same with last one, this becomes true if we dont need it.
                
                if (Requirements.needNumber){
                    if (std::isdigit(passwordArray[i])){//checks for number
                    hasNumber = true;
                    if (debugInfo)
                        std::cout << "hasNumTrue\n";
                    }
                } else hasNumber = true;
                
                if (Requirements.needSpecial){
                    if (!(std::isalpha(passwordArray[i]))){//checks for symbol
                    hasSpecial = true;
                    if (debugInfo)
                        std::cout << "hasSpecTrue\n";
                    }
                } else hasSpecial = true;
            }
            
            if (password.length() <= Requirements.maxLength)
                if (password.length() >= Requirements.minLength)
                    goodLength = true;
                else
                    goodLength = false;
            else
                goodLength = false;
            
            if (debugInfo){
            std::cout << "\nhasSpecial: " << hasSpecial;
            std::cout << "\nhasNumber: " << hasNumber;
            std::cout << "\nhasCap: " << hasCap;
            std::cout << "\nnoSpace: " << noSpace;
            std::cout << "\ngoodLength: " << goodLength << std::endl;}
            
            //evaluates
            if (hasSpecial && hasNumber && hasCap && noSpace && goodLength)
                isValid = true;
            else
                isValid = false;
            //---------
            
            if (!isValid) printWrongPasswordWarning(Requirements); //if invalid, it tells you what you must have.
            return isValid;
        }
        void User::SaveInfo(){
            if (debugInfo)
                std::cout << "Directory to save is: \"" << Directory << "\"\n";
            
            if (username == "" || username == cancelValue){//if they are invalid, abort
                std::cout << "Username not present. ";
                if(password == "" || password == cancelValue){
                    std::cout << "Password also not present. Aborting.\n";
                    return;
                }
                std::cout << "Aborting...\n";
                return;
            }
            else if (password == "" || password == cancelValue){
                std::cout << "Password not present. Aborting\n";
                return;
            }
            
            if (doesFileExist(Directory)){//if file already exists...
                std::cout << "File already exists... overwriting." << std::endl;
            }
            std::ofstream UserSave;
            
            UserSave.open(Directory, std::ios::trunc | std::ios::out);
            
            UserSave << infoToString();
            
            UserSave.close();
        }
        std::string User::LoadInfo(){
            std::string userInfo;
            std::ifstream UserSave;
            
            UserSave.open(Directory);
            UserSave >> userInfo;
            
            return userInfo;
        }
        void User::PrintInfo(){
            std::cout << "Username: " << username << std::endl;
            std::cout << "Password: " << password << std::endl;
            return;
        }
        
        //get and set
        std::string User::GetUsername(){
            return username;
        }
        std::string User::GetPassword(){
            return password;
        }
        std::string User::GetCancelValue(){
            return cancelValue;
        }
        std::string User::GetDirectory(){
            return Directory;
        }
        void User::SetDebugInfo(bool tf){
            debugInfo = tf;
        }
        
        //misc functions
        std::string User::infoToString(){
            std::string usrInfo;
            //usrInfo = username+"\n"+password; //don't need this for now, but if i choose to make these encrypted
            usrInfo = password;
            return usrInfo;
        }
        inline bool User::doesFileExist(const std::string& name) {
            if (FILE *file = fopen(name.c_str(), "r")) {
                fclose(file);
                return true;
            }
            else {
                return false;
            }   
        }
        void User::setDirectory(){
            Directory = "../Users/" + username + ".acc";
            /* The following code was writted because I got the build file in the
             * wrong place. This was the only workaround I found, however it doesn't
             * work, because it sets the path while building the program. For prebuilt
             * packages, this wouldn't work. I am going to leave it in here for archival purposes.
            std::string workingPath = __FILE__;//sets var to path of .cpp
            std::string directoryPath = workingPath.substr(0, workingPath.rfind("/"));//takes directory, subtracts User.cpp to 
                                                                                    //it by finding the last occurence of "/"
            Directory = directoryPath + "/Users/" + username + ".acc";
            */
            if (debugInfo)
                std::cout << "setting save directory to " << Directory << std::endl;
        }
        std::string User::NewCancelValue(){
            std::srand(time(NULL));//setting seed...
            int randInt = rand();//sets randInt to a random int

            return std::to_string(randInt);//returns a string value.
        }
        void User::printWrongPasswordWarning(const PasswordRequirementsStruct Requirements){
            std::cout << "Invalid Password! Password must:" << std::endl;
                
            if (Requirements.needCap)
                std::cout << "Have one capital letter,\n";
            if (Requirements.needNoSpace)
                std::cout << "Not contain spaces,\n";
            if (Requirements.needNumber)
                std::cout << "Need at least one number,\n";
            if (Requirements.needSpecial)
                std::cout << "Need at least one special character,\n";
                std::cout << "And be at least " << Requirements.maxLength << " characters long,\n";
                std::cout << "And must contain at least " << Requirements.minLength << " characters.\n";
        }
        void User::printWrongUsernameWarning(const UsernameRequirementsStruct Requirements){
            std::cout << "Invalid Username! Usernames must:" << std::endl;
                
            if (!Requirements.useCap)
                std::cout << "Not contain capital letter,\n";
            if (Requirements.needNoSpace)
                std::cout << "Not contain spaces,\n";
            if (!Requirements.useNumber)
                std::cout << "Not contain any numbers,\n";
            if (!Requirements.useSpecial)
                std::cout << "Not contain special characters,\n";
            std::cout << "And be at least " << Requirements.maxLength << " characters long,\n";
            std::cout << "And must contain at least " << Requirements.minLength << " characters.\n";
        }
