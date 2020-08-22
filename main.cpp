//USER MADE CLASSES
#include "User.h"

int main() {
    User UserHandle;
    UserHandle.SetDebugInfo(false);
    UserHandle.PasswordRequirements.needCap = false;
    UserHandle.Setup();
    return 0;
}
