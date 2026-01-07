#ifndef VAULTMNGR_HPP
#define VAULTMNGR_HPP

#include "Vault.hpp"

#include <string>
#include <vector>

class VaultMngr
{
private:
    std::vector<std::string> vaultNameList;
public:

    static std::string VAULT_PATH;
    static const std::string VAULT_FILE_EXTENSION;

    VaultMngr();

    bool loadVault(const std::string& name, Vault& vault);
    bool saveAndCryptVault(const Vault& vault);
    const std::vector<std::string> &getVaultNameList();
};

#endif //VAULTMNGR_HPP