//USER MADE CLASSES
#include "User.h"

int main() {
    User UserHandle;
    UserHandle.SetDebugInfo(true);
    UserHandle.PasswordRequirements.needCap = false;
    UserHandle.UsernameRequirements.needNoSpace = false;
    UserHandle.UsernameRequirements.useSpecial = false;
    UserHandle.Setup();
    return 0;
}
