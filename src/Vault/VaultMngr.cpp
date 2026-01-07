#include "VaultMngr.hpp"
#include "Vault.hpp"

#include <string>
#include <filesystem>

#include <iostream>

std::string VaultMngr::VAULT_PATH = "/.pswdmngr/vaults/";
const std::string VaultMngr::VAULT_FILE_EXTENSION = ".vlt";

VaultMngr::VaultMngr(){
    // Add the home to the path if not already added
    if(!VAULT_PATH.contains("/home")){
        std::string home = std::getenv("HOME");
        VAULT_PATH = home + VAULT_PATH;
    }

    // Create the vault folder if it doesn't exists
    if(!std::filesystem::exists(VAULT_PATH)){
        std::filesystem::create_directories(VAULT_PATH);
    }

    // Get all the existing vault files
    for(const auto& entry : std::filesystem::directory_iterator(VAULT_PATH)) {
        std::cout << entry.path();
        if(entry.path().has_extension() && entry.path().extension().compare(VAULT_FILE_EXTENSION) == 0){
            vaultNameList.push_back(entry.path().filename()); 
        }
    }     
}

bool VaultMngr::loadVault(const std::string& name, Vault& vault){
    return false;
}

bool VaultMngr::saveAndCryptVault(const Vault& vault){
    return false;
}

const std::vector<std::string> &VaultMngr::getVaultNameList()
{
    return vaultNameList;
}
