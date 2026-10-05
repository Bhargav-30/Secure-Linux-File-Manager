#include "PermissionManager.h"

#include <cerrno>
#include <cstring>
#include <grp.h>
#include <iostream>
#include <pwd.h>
#include <sys/stat.h>

namespace {

std::string getPermissionString(mode_t mode) {

    std::string permissions;

    permissions += S_ISDIR(mode) ? 'd' : '-';

    const mode_t bits[] = {
        S_IRUSR, S_IWUSR, S_IXUSR,
        S_IRGRP, S_IWGRP, S_IXGRP,
        S_IROTH, S_IWOTH, S_IXOTH
    };

    const char symbols[] = {
        'r', 'w', 'x',
        'r', 'w', 'x',
        'r', 'w', 'x'
    };

    for (int i = 0; i < 9; ++i) {
        permissions +=
            (mode & bits[i]) ? symbols[i] : '-';
    }

    return permissions;
}

}

bool PermissionManager::showPermissions(
    const std::string& path) const {

    struct stat info{};

    if (stat(path.c_str(), &info) == -1) {

        std::cerr << "stat() failed: "
                  << std::strerror(errno) << '\n';

        return false;
    }

    passwd* owner = getpwuid(info.st_uid);
    group* groupInfo = getgrgid(info.st_gid);

    std::cout << "Permissions: "
              << getPermissionString(info.st_mode)
              << '\n';

    std::cout << "Owner: "
              << (owner ? owner->pw_name : "unknown")
              << '\n';

    std::cout << "Group: "
              << (groupInfo ? groupInfo->gr_name : "unknown")
              << '\n';

    return true;
}

bool PermissionManager::changePermissions(
    const std::string& path,
    unsigned int mode) const {

    if (mode > 777) {

        std::cerr << "Invalid permission mode.\n";
        return false;
    }

    unsigned int octalMode = 0;
    unsigned int place = 1;

    while (mode > 0) {

        octalMode +=
            (mode % 10) * place;

        mode /= 10;
        place *= 8;
    }

    if (chmod(
            path.c_str(),
            static_cast<mode_t>(octalMode)) == -1) {

        std::cerr << "chmod() failed: "
                  << std::strerror(errno) << '\n';

        return false;
    }

    return true;
}
