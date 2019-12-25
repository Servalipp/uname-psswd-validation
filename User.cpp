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
                username = ValidateUsername(tempUsername);
                if (username == cancelValue)
                    username = ValidateUsername(tempUsername);
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
                password = ValidatePassword(tempPassword);
                if (password == cancelValue)
                     password = ValidatePassword(tempPassword);
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
        std::string User::ValidateUsername(std::string username){
            char usernameArray[username.length()];
            bool isValid = true;
            
            strcpy(usernameArray, username.c_str());
            
            for (int i=0;i<=username.length();i++){
                if (usernameArray[i] == ' '||
                    std::isupper(usernameArray[i])||
                    usernameArray[i] == '.')
                    isValid = false;
            }
            
            if (!isValid){
                std::cout << "Usernames cannot contain spaces, uppercase letters, or periods!" << std::endl;
                NewUsername();
            }
            else{
                return username;
            }
            
            return cancelValue;
        }
        std::string User::ValidatePassword(std::string password){
            
            char passwordArray[password.length()];
            bool isValid = true;
                //password identifiers
                bool    hasSpecial = false,
                        hasNumber = false,
                        hasCap = false,
                        noSpace = true,
                        goodLength = false;
            
            strcpy(passwordArray, password.c_str());
            
            for (int i=0;i<password.length();i++){
                if(debugInfo)
                    std::cout << passwordArray[i] << ": ";
                
                if      (passwordArray[i] == ' '){//checks for spaces
                    noSpace = false;
                    if(debugInfo)
                        std::cout << "nospFalse\n";
                }
                else if (std::isupper(passwordArray[i])){//checks for uppercase
                    hasCap = true;
                    if (debugInfo)
                        std::cout << "hasCapTrue\n";
                }
                else if (std::isdigit(passwordArray[i])){//checks for number
                    hasNumber = true;
                    if (debugInfo)
                        std::cout << "hasNumTrue\n";
                }
                else if (!(std::isalpha(passwordArray[i]))){//checks for symbol
                    hasSpecial = true;
                    if (debugInfo)
                        std::cout << "hasSpecTrue\n";
                }
                else
                    if (debugInfo)
                        std::cout << "just a plain letter\n";
            }
            
            if (password.length() <= 10)
                if (password.length() >= 5)
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
            
            if (!isValid){
                std::cout <<    "Passwords must:\nhave at least 1 special character\nhave at least 1 number\nhave at lease one capital letter\nshould contain no spaces\nIn between 5 - 10 characters" << std::endl;
                NewPassword();
            }
            else{
                return password;
            }
            return cancelValue;
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
