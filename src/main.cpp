#include "Console/GlobalCsl.hpp"
#include "Menu/Menu.hpp"
#include "Encryption/AES.hpp"
#include "Vault/VaultMngr.hpp"

#include <string>
#include <functional>
#include <iostream>
#include <sstream>
#include <vector>

void handleVault(Vault &vault){

}

void openAVault(){
    // List all the available vaults
    std::vector<std::string> vaultNames = VaultMngr::getVaultNameList();
    std::vector<std::function<void()>> actions{};

    for(const std::string name : vaultNames){
        actions.push_back([name](){
            // Action when a vault is selected
            GlobaleCSL::get()->write("Enter le mot de passe: ");
            std::string password = GlobaleCSL::get()->readLine();

            auto optVault = VaultMngr::loadVault(name, password);
            
            if(optVault.has_value()){
                handleVault(optVault.value());
            } else {
                GlobaleCSL::get()->write("Mot de passe incorrect :(\nAppuyer sur n'importe quelle touche pour continuer ...");
                GlobaleCSL::get()->readKey();
            }
        });
    }

    Menu vaultListMenu = Menu(vaultNames, actions);
    vaultListMenu.launch();
}

void createVault(){

}

void deleteVault(){

}

int main() {
    // Make sure to delete console at the end of programme
    std::atexit([](){GlobaleCSL::del();});

    const std::vector<std::string> mainMenuItems = {
            "Ouvrir un coffre",
            "Créer un coffre",
            "Supprimer un coffre"
    };

    const std::vector<std::function<void()>> mainMenuActions = {
        openAVault,
        createVault,
        deleteVault
    };

    
    Menu menu = Menu(mainMenuItems, mainMenuActions, true);
    menu.addAction(std::string("Quitter"), [&menu](){menu.stop();});

    try{
        menu.launch();
    } catch (const char* msg){
        GlobaleCSL::get()->write(std::string("Une erreur est survenue: ") + msg + "\n");
    }
    
    return 0;
}

// bool encryptAES(
//     const std::vector<unsigned char>& plaintext,
//     const std::vector<unsigned char>& key,
//     std::vector<unsigned char>& ciphertext,
//     std::vector<unsigned char>& iv,
//     std::vector<unsigned char>& tag
// );

// std::vector<unsigned char> stringToVector(std::string str){
//     std::vector<unsigned char> buffer = std::vector<unsigned char>();
//     for(auto ite = str.begin(); ite != str.end(); ite++){
//         buffer.push_back(*ite);
//     }

//     return buffer;
// }

// std::string vectorToString(std::vector<unsigned char> vec){
//     std::string buffer = "";
//     for(auto ite = vec.begin(); ite != vec.end(); ite++){
//         buffer += *ite;
//     }

//     return buffer;
// }

// std::string vectorToByteString(std::vector<unsigned char> vec){
//     std::stringstream ss;
//     for(auto ite = vec.begin(); ite != vec.end(); ite++){
//         ss << " " << std::hex << (int)*ite;
//     }

//     return ss.str();
// }

// std::vector<unsigned char> ciphertext = std::vector<unsigned char>();
// std::vector<unsigned char> iv = std::vector<unsigned char>(AES_IV_SIZE);
// std::vector<unsigned char> tag = std::vector<unsigned char>();

// std::vector<unsigned char> key = std::vector<unsigned char>(AES_KEY_SIZE);

// void askToEcode(){
//     LinuxConsole console = LinuxConsole();
//     console.write("Entrer un texte à chiffrer: ");
//     std::string text = console.readLine();

//     std::vector<unsigned char> plaintext = stringToVector(text);

    
//     AES::generateKey(key);

//     AES::encrypt(plaintext, key, ciphertext, iv, tag);

//     console.clear();
//     console.write("Text  : " + vectorToByteString(plaintext) + "\n");
//     console.write("Key   : " + vectorToByteString(key) + "\n");
//     console.write("Cipher: " + vectorToByteString(ciphertext) + "\n");
//     console.write("Iv    : " + vectorToByteString(iv) + "\n");
//     console.write("Tag   : " + vectorToByteString(tag) + "\n");
// }

// void decode(){
//     std::vector text = std::vector<unsigned char>();
//     AES::decrypt(ciphertext, key, iv, tag, text);
//     LinuxConsole().write("Decoded: " + vectorToString(text) + "\n");
// }