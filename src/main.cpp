#include "Console/LinuxConsole.hpp"
#include "Menu/Menu.hpp"
#include "Encryption/AES.hpp"
#include <string>
#include <functional>
#include <iostream>
#include <sstream>

#include <vector>
#include <openssl/evp.h> 
#include <openssl/rand.h>

const unsigned AES_KEY_SIZE = 32; // 256 bits
const unsigned AES_IV_SIZE = 12;  // 96 bits

bool encryptAES(
    const std::vector<unsigned char>& plaintext,
    const std::vector<unsigned char>& key,
    std::vector<unsigned char>& ciphertext,
    std::vector<unsigned char>& iv,
    std::vector<unsigned char>& tag
);

std::vector<unsigned char> stringToVector(std::string str){
    std::vector<unsigned char> buffer = std::vector<unsigned char>();
    for(auto ite = str.begin(); ite != str.end(); ite++){
        buffer.push_back(*ite);
    }

    return buffer;
}

std::string vectorToString(std::vector<unsigned char> vec){
    std::string buffer = "";
    for(auto ite = vec.begin(); ite != vec.end(); ite++){
        buffer += *ite;
    }

    return buffer;
}

std::string vectorToByteString(std::vector<unsigned char> vec){
    std::stringstream ss;
    for(auto ite = vec.begin(); ite != vec.end(); ite++){
        ss << " " << std::hex << (int)*ite;
    }

    return ss.str();
}

std::vector<unsigned char> ciphertext = std::vector<unsigned char>();
std::vector<unsigned char> iv = std::vector<unsigned char>(AES_IV_SIZE);
std::vector<unsigned char> tag = std::vector<unsigned char>();

std::vector<unsigned char> key = std::vector<unsigned char>(AES_KEY_SIZE);

void askToEcode(){
    LinuxConsole console = LinuxConsole();
    console.write("Entrer un texte à chiffrer: ");
    std::string text = console.readLine();

    std::vector<unsigned char> plaintext = stringToVector(text);

    
    AES::generateKey(key);

    AES::encrypt(plaintext, key, ciphertext, iv, tag);

    console.clear();
    console.write("Text  : " + vectorToByteString(plaintext) + "\n");
    console.write("Key   : " + vectorToByteString(key) + "\n");
    console.write("Cipher: " + vectorToByteString(ciphertext) + "\n");
    console.write("Iv    : " + vectorToByteString(iv) + "\n");
    console.write("Tag   : " + vectorToByteString(tag) + "\n");
}

void decode(){
    std::vector text = std::vector<unsigned char>();
    AES::decrypt(ciphertext, key, iv, tag, text);
    LinuxConsole().write("Decoded: " + vectorToString(text) + "\n");
}

void displayMenu(Console* console, Menu &menu)
{
    // Clear the screen
    console->clear();
    console->write(menu.show());
}



int main() {
    const std::vector<std::string> menuItems = {
            "Chiffrer",
            "Déchiffrer",
            "Exit"
    };

    const std::vector<std::function<void()>> menuActions = {
        askToEcode,
        decode,
        [](){exit(0);}
    };

    int c;
    Console* console = new LinuxConsole();
    Menu menu = Menu(menuItems, menuActions);

    displayMenu(console, menu);

    while (true)
    {
        c = console->readKey();
        if (c == 27) { // ESC 
            if (console->readKey() == '[') { 
                switch (console->readKey()) { 
                    case 'A': 
                        menu.select(-1);
                        break; // flèche haut 
                    case 'B': 
                        menu.select(1);
                        break; // flèche bas 
                    } 
                }
        } else if (c == 10) { // Enter key
            menu.executeSelected();
            console->write("Press any key to continue...\n");
            console->readKey();
        } else {
            break; // Exit on any other key
        }
        displayMenu(console, menu);
    }
    
    delete console;
    return 0;
}


bool encryptAES(
    const std::vector<unsigned char>& plaintext,
    const std::vector<unsigned char>& key,
    std::vector<unsigned char>& ciphertext,
    std::vector<unsigned char>& iv,
    std::vector<unsigned char>& tag
) {
    // Initialize the encryption context
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) return false;

    iv.resize(12); // IV recommandé pour GCM
    RAND_bytes(iv.data(), iv.size());

    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, nullptr, nullptr) != 1)
        return false;

    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, iv.size(), nullptr);

    if (EVP_EncryptInit_ex(ctx, nullptr, nullptr, key.data(), iv.data()) != 1)
        return false;

    ciphertext.resize(plaintext.size());
    int len;

    if (EVP_EncryptUpdate(ctx, ciphertext.data(), &len, plaintext.data(), plaintext.size()) != 1)
        return false;

    int ciphertext_len = len;

    if (EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len) != 1)
        return false;

    ciphertext_len += len;
    ciphertext.resize(ciphertext_len);

    tag.resize(16);
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, 16, tag.data());

    EVP_CIPHER_CTX_free(ctx);
    return true;
}

// bool decryptAES(
//     const std::vector<unsigned char>& ciphertext,
//     const std::vector<unsigned char>& key,
//     const std::vector<unsigned char>& iv,
//     const std::vector<unsigned char>& tag,
//     std::vector<unsigned char>& plaintext
// ) {
//     EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
//     if (!ctx) return false;

//     if (EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, nullptr, nullptr) != 1)
//         return false;

//     EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, iv.size(), nullptr);

//     if (EVP_DecryptInit_ex(ctx, nullptr, nullptr, key.data(), iv.data()) != 1)
//         return false;

//     plaintext.resize(ciphertext.size());
//     int len;

//     if (EVP_DecryptUpdate(ctx, plaintext.data(), &len, ciphertext.data(), ciphertext.size()) != 1)
//         return false;

//     int plaintext_len = len;

//     EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, tag.size(), (void*)tag.data());

//     int ret = EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &len);

//     EVP_CIPHER_CTX_free(ctx);

//     if (ret > 0) {
//         plaintext_len += len;
//         plaintext.resize(plaintext_len);
//         return true;
//     } else {
//         return false; // Tag invalide → données modifiées
//     }
// }

// int main() {
//     std::string message = "Bonjour, ceci est un test AES‑256‑GCM !";

//     std::vector<unsigned char> plaintext(message.begin(), message.end());
//     std::vector<unsigned char> key(32); // 256 bits
//     RAND_bytes(key.data(), key.size());

//     std::vector<unsigned char> ciphertext, iv, tag;

//     if (!encryptAES(plaintext, key, ciphertext, iv, tag)) {
//         std::cerr << "Erreur de chiffrement\n";
//         return 1;
//     }

//     std::cout << "Chiffrement OK\n";

//     std::vector<unsigned char> decrypted;

//     if (!decryptAES(ciphertext, key, iv, tag, decrypted)) {
//         std::cerr << "Erreur de déchiffrement\n";
//         return 1;
//     }

//     std::cout << "Déchiffrement OK\n";
//     std::cout << "Message : " << std::string(decrypted.begin(), decrypted.end()) << "\n";

//     return 0;
// }
