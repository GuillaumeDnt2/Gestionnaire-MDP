#ifndef VAULT_HPP
#define VAULT_HPP

#include "VaultValue.hpp"

#include <string>
#include <vector>
#include <optional>
#include <unordered_map>

class VaultMngr;

class Vault
{
private:
    std::string name = "";
    std::unordered_map<std::string, VaultValue> entries = std::unordered_map<std::string, VaultValue>();

public:
    Vault() = default;
    Vault(std::string name);
    const std::string& getName();
    std::vector<std::string> getEntriesNames();
    std::optional<VaultValue> getValue(const std::string& name);
    void addEntry(VaultValue entry);
    void removeEntry(const std::string& name);
};

#endif //VAULT_HPP