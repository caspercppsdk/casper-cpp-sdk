#pragma once

#include <string>
#include "nlohmann/json.hpp"

namespace Casper {

    struct Transfer {
        Transfer (std::string deploy_hash_, std::string from_, std::string to_, std::string source_, std::string target_, std::string amount_, std::string gas_, uint64_t id_)
        : deploy_hash(deploy_hash_), from(from_), to(to_), source(source_), target(target_), amount(amount_), gas(gas_), id(id_) {}

        Transfer() {}

        std::string deploy_hash;
        std::string from;
        std::string to;
        std::string source;
        std::string target;
        std::string amount;
        std::string gas;
        uint64_t id;
    };

    /**
     * @brief Construct a JSON object from a Transfer object.
     *
     * @param j JSON object to construct.
     * @param p Transfer object to construct from.
     */
    inline void to_json(nlohmann::json& j, const Transfer& p) {
        j = nlohmann::json{
            {"deploy_hash", p.deploy_hash},
            {"from", p.from},
            {"to", p.to},
            {"source", p.source},
            {"target", p.target},
            {"amount", p.amount},
            {"gas", p.gas},
            {"id", p.id},
        };
    }

    /**
     * @brief Construct a Transfer object from a JSON object.
     *
     * @param j JSON object to construct the object from.
     * @param p Transfer object to construct.
     */
    inline void from_json(const nlohmann::json& j, Transfer& p) {
        j.at("deploy_hash").get_to(p.deploy_hash);
        j.at("from").get_to(p.from);
        j.at("to").get_to(p.to);
        j.at("source").get_to(p.source);
        j.at("target").get_to(p.target);
        j.at("amount").get_to(p.amount);
        j.at("gas").get_to(p.gas);
        j.at("id").get_to(p.id);
    }

} // namespace Casper