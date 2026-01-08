#ifndef VAULTMNGR_HPP
#define VAULTMNGR_HPP

#include "Vault.hpp"

#include <string>
#include <vector>
#include <optional>

class VaultMngr
{
private:
    static std::vector<std::string> vaultNameList;
    static bool notLoaded;
public:

    static std::string VAULT_PATH;
    static const std::string VAULT_FILE_EXTENSION;

    static std::optional<Vault> loadVault(const std::string& name, const std::string &password);
    static bool saveAndCryptVault(const Vault& vault);
    static const std::vector<std::string> &getVaultNameList();
};

#endif //VAULTMNGR_HPP