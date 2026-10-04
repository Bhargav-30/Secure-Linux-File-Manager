#include "crypto.h"

#include <openssl/evp.h>
#include <openssl/rand.h>

#include <fstream>
#include <vector>
#include <string>

namespace {

const int SALT_SIZE = 16;
const int IV_SIZE = 16;
const int KEY_SIZE = 32;
const int BUFFER_SIZE = 4096;
const int ITERATIONS = 100000;

bool deriveKey(
    const std::string& password,
    const unsigned char* salt,
    unsigned char* key
) {
    return PKCS5_PBKDF2_HMAC(
        password.c_str(),
        static_cast<int>(password.size()),
        salt,
        SALT_SIZE,
        ITERATIONS,
        EVP_sha256(),
        KEY_SIZE,
        key
    ) == 1;
}

}

bool encryptFile(
    const std::string& inputPath,
    const std::string& outputPath,
    const std::string& password
) {
    std::ifstream input(inputPath, std::ios::binary);

    if (!input) {
        return false;
    }

    std::ofstream output(
        outputPath,
        std::ios::binary | std::ios::trunc
    );

    if (!output) {
        return false;
    }

    unsigned char salt[SALT_SIZE];
    unsigned char iv[IV_SIZE];
    unsigned char key[KEY_SIZE];

    if (RAND_bytes(salt, SALT_SIZE) != 1) {
        return false;
    }

    if (RAND_bytes(iv, IV_SIZE) != 1) {
        return false;
    }

    if (!deriveKey(password, salt, key)) {
        return false;
    }

    // File format:
    // [salt 16 bytes][IV 16 bytes][encrypted data]

    output.write(
        reinterpret_cast<const char*>(salt),
        SALT_SIZE
    );

    output.write(
        reinterpret_cast<const char*>(iv),
        IV_SIZE
    );

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    if (!ctx) {
        return false;
    }

    if (EVP_EncryptInit_ex(
            ctx,
            EVP_aes_256_cbc(),
            nullptr,
            key,
            iv
        ) != 1) {

        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    unsigned char inputBuffer[BUFFER_SIZE];
    unsigned char outputBuffer[BUFFER_SIZE + EVP_MAX_BLOCK_LENGTH];

    while (input) {

        input.read(
            reinterpret_cast<char*>(inputBuffer),
            BUFFER_SIZE
        );

        std::streamsize bytesRead = input.gcount();

        if (bytesRead <= 0) {
            continue;
        }

        int bytesEncrypted = 0;

        if (EVP_EncryptUpdate(
                ctx,
                outputBuffer,
                &bytesEncrypted,
                inputBuffer,
                static_cast<int>(bytesRead)
            ) != 1) {

            EVP_CIPHER_CTX_free(ctx);
            return false;
        }

        output.write(
            reinterpret_cast<const char*>(outputBuffer),
            bytesEncrypted
        );
    }

    int finalBytes = 0;

    if (EVP_EncryptFinal_ex(
            ctx,
            outputBuffer,
            &finalBytes
        ) != 1) {

        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    output.write(
        reinterpret_cast<const char*>(outputBuffer),
        finalBytes
    );

    EVP_CIPHER_CTX_free(ctx);

    return true;
}

bool decryptFile(
    const std::string& inputPath,
    const std::string& outputPath,
    const std::string& password
) {
    std::ifstream input(inputPath, std::ios::binary);

    if (!input) {
        return false;
    }

    unsigned char salt[SALT_SIZE];
    unsigned char iv[IV_SIZE];
    unsigned char key[KEY_SIZE];

    input.read(
        reinterpret_cast<char*>(salt),
        SALT_SIZE
    );

    input.read(
        reinterpret_cast<char*>(iv),
        IV_SIZE
    );

    if (!input) {
        return false;
    }

    if (!deriveKey(password, salt, key)) {
        return false;
    }

    std::ofstream output(
        outputPath,
        std::ios::binary | std::ios::trunc
    );

    if (!output) {
        return false;
    }

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    if (!ctx) {
        return false;
    }

    if (EVP_DecryptInit_ex(
            ctx,
            EVP_aes_256_cbc(),
            nullptr,
            key,
            iv
        ) != 1) {

        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    unsigned char inputBuffer[BUFFER_SIZE];
    unsigned char outputBuffer[BUFFER_SIZE + EVP_MAX_BLOCK_LENGTH];

    while (input) {

        input.read(
            reinterpret_cast<char*>(inputBuffer),
            BUFFER_SIZE
        );

        std::streamsize bytesRead = input.gcount();

        if (bytesRead <= 0) {
            continue;
        }

        int bytesDecrypted = 0;

        if (EVP_DecryptUpdate(
                ctx,
                outputBuffer,
                &bytesDecrypted,
                inputBuffer,
                static_cast<int>(bytesRead)
            ) != 1) {

            EVP_CIPHER_CTX_free(ctx);
            output.close();
            std::remove(outputPath.c_str());
            return false;
        }

        output.write(
            reinterpret_cast<const char*>(outputBuffer),
            bytesDecrypted
        );
    }

    int finalBytes = 0;

    if (EVP_DecryptFinal_ex(
            ctx,
            outputBuffer,
            &finalBytes
        ) != 1) {

        EVP_CIPHER_CTX_free(ctx);
        output.close();
        std::remove(outputPath.c_str());
        return false;
    }

    output.write(
        reinterpret_cast<const char*>(outputBuffer),
        finalBytes
    );

    EVP_CIPHER_CTX_free(ctx);

    return true;
}