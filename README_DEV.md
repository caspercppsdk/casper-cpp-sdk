### Inherited Class JSON

    inline void to_json(nlohmann::json& j, const URef& p) {
        nlohmann::to_json(j, static_cast<GlobalStateKey>(p));
        j.update({{"access_rights", p.access_rights}});
    }

    inline void from_json(const nlohmann::json& j, URef& p) {
        nlohmann::from_json(j, static_cast<GlobalStateKey&>(p));
        j.at("access_rights").get_to(p.access_rights);
    }

### Inheritance Header - Source file

    In Child.h, you would simply declare:

    Child(int Param, int ParamTwo);

    In Child.cpp, you would then have:

    Child::Child(int Param, int ParamTwo) : Parent(Param) {
        //rest of constructor here
    }

### RPC JSON Examples
    https://docs.rs/crate/casper-client/1.4.3