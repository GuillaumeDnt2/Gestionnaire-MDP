#include "Vault.hpp"
#include "VaultValue.hpp"
#include "VaultMngr.hpp"

#include <string>
#include <vector>
#include <optional>

Vault::Vault(std::string name) : name(name){}

const std::string &Vault::getName(){
    return name;
}

std::vector<std::string> Vault::getEntriesNames()
{
    std::vector names = std::vector<std::string>(entries.size());
    for(auto entry : entries){
        names.push_back(entry.first);
    }

    return names;
}

std::optional<VaultValue> Vault::getValue(const std::string &name)
{
    auto value = entries.find(name);
    if(value == entries.end()){
        std::nullopt;
    }

    return std::optional(value->second);
}

void Vault::addEntry(VaultValue entry)
{
    // TODO vérifié doublon

    entries[entry.name] = entry;
}

void Vault::removeEntry(const std::string& name)
{
    entries.erase(name);
}
