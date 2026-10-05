#ifndef PERMISSION_MANAGER_H
#define PERMISSION_MANAGER_H

#include <string>

class PermissionManager {
public:
    bool showPermissions(const std::string& path) const;

    bool changePermissions(
        const std::string& path,
        unsigned int mode) const;
};

#endif
