#ifndef AES_HPP
#define AES_HPP

#include <vector>

class AES
{
private:
    static bool pad(const std::vector<unsigned char>& text, std::vector<unsigned char>& padded);
    static bool unpad(const std::vector<unsigned char>& padded, std::vector<unsigned char>& plaintext);

public:
    static bool encrypt(
        const std::vector<unsigned char>& plaintext,
        const std::vector<unsigned char>& key,
        std::vector<unsigned char>& ciphertext,
        std::vector<unsigned char>& iv,
        std::vector<unsigned char>& tag);

    static bool decrypt(
        const std::vector<unsigned char>& ciphertext,
        const std::vector<unsigned char>& key,
        const std::vector<unsigned char>& iv,
        const std::vector<unsigned char>& tag,
        std::vector<unsigned char>& plaintext);

    static void generateKey(std::vector<unsigned char>& key);
};

#endif