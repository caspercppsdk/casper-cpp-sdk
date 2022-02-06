### Inherited Class JSON

    inline void to_json(nlohmann::json& j, const URef& p) {
        nlohmann::to_json(j, static_cast<GlobalStateKey>(p));
        j.update({{"access_rights", p.access_rights}});
    }

    inline void from_json(const nlohmann::json& j, URef& p) {
        nlohmann::from_json(j, static_cast<GlobalStateKey&>(p));
        j.at("access_rights").get_to(p.access_rights);
    }