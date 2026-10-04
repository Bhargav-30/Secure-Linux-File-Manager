#ifndef CRYPTO_H
#define CRYPTO_H

#include <string>

bool encryptFile(
    const std::string& inputPath,
    const std::string& outputPath,
    const std::string& password
);

bool decryptFile(
    const std::string& inputPath,
    const std::string& outputPath,
    const std::string& password
);

#endif