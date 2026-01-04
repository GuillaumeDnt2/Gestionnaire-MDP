#include "AES.hpp"

#include <vector>
#include <openssl/evp.h> 
#include <openssl/rand.h>

const unsigned KEY_SIZE = 32;
const unsigned IV_SIZE = 12;
const unsigned TAG_SIZE = 16;
const unsigned CIPHER_SIZE = 64;

bool AES::encrypt(
    const std::vector<unsigned char>& plaintext,
    const std::vector<unsigned char>& key,
    std::vector<unsigned char>& ciphertext,
    std::vector<unsigned char>& iv,
    std::vector<unsigned char>& tag
){
    // Initialize the encryption context
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) return false;

    // Generate the initialization vector
    iv.resize(IV_SIZE);
    RAND_bytes(iv.data(), iv.size());

    // Define the mode to GCM
    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, nullptr, nullptr) != 1)
        return false;

    // Set the iv length
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, iv.size(), nullptr);

    // Initialise key and iv
    if (EVP_EncryptInit_ex(ctx, nullptr, nullptr, key.data(), iv.data()) != 1)
        return false;

    // Pad the plain text to be match fixed size
    std::vector<unsigned char> paddedText;
    if(!pad(plaintext, paddedText)){
        return false;
    }

    // Start encryption
    ciphertext.resize(CIPHER_SIZE);
    int len;

    if (EVP_EncryptUpdate(ctx, ciphertext.data(), &len, paddedText.data(), paddedText.size()) != 1)
        return false;

    // Finalize encryption
    int ciphertext_len = len;

    if (EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len) != 1)
        return false;

    ciphertext_len += len;
    ciphertext.resize(ciphertext_len);

    // Get the tag
    tag.resize(TAG_SIZE);
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, TAG_SIZE, tag.data());

    // Free resources
    EVP_CIPHER_CTX_free(ctx);

    return true;
}

bool AES::decrypt(
        const std::vector<unsigned char>& ciphertext,
        const std::vector<unsigned char>& key,
        const std::vector<unsigned char>& iv,
        const std::vector<unsigned char>& tag,
        std::vector<unsigned char>& plaintext
){

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) return false;

    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, nullptr, nullptr) != 1)
        return false;

    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, iv.size(), nullptr);

    if (EVP_DecryptInit_ex(ctx, nullptr, nullptr, key.data(), iv.data()) != 1)
        return false;

    plaintext.resize(ciphertext.size());
    int len;

    if (EVP_DecryptUpdate(ctx, plaintext.data(), &len, ciphertext.data(), ciphertext.size()) != 1)
        return false;

    int plaintext_len = len;

    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, tag.size(), (void*)tag.data());

    int ret = EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &len);

    EVP_CIPHER_CTX_free(ctx);

    if (ret > 0) {
        std::vector<unsigned char> depaddedText = std::vector<unsigned char>();
        unpad(plaintext, depaddedText);
        plaintext = depaddedText;
        return true;
    } else {
        return false; // Tag invalide → données modifiées
    }
}

void AES::generateKey(std::vector<unsigned char>& key){
    key.resize(KEY_SIZE);
    RAND_bytes(key.data(), key.size());
}

bool AES::pad(const std::vector<unsigned char>& text, std::vector<unsigned char>& padded){
    
    // Check if the text is not bigger than the max allowed
    // (max - 1 because last byte is the size)
    if(text.size() >= CIPHER_SIZE){
        return false;
    }

    padded = std::vector(text);
    padded.resize(CIPHER_SIZE);
    padded.back() = (unsigned char)text.size();

    return true;
}

bool AES::unpad(const std::vector<unsigned char>& padded, std::vector<unsigned char>& plaintext){
    
    // Check if the text is not bigger than the max allowed
    // (max - 1 because last byte is the size)
    if(padded.size() != CIPHER_SIZE){
        return false;
    }

    plaintext = std::vector<unsigned char>(padded.back());

    for (unsigned char i = 0; i < plaintext.size(); i++){
        plaintext.at(i) = padded.at(i);
    }

    return true;
}