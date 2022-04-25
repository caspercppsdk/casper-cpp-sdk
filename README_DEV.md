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

### Exceptional JSON Examples

    Rust Enums -> StoredValue.h
    Rust Option -> Delegator.h, Transfer.h

### Optional TODO

    1. MacOS and Windows support
    2. Doxygen examples support (https://www.doxygen.nl/manual/commands.html#cmdexample)
    3. "sudo apt-get install graphviz -y" can be added to dependencies

# Casper C++ SDK MS3 TODOs

 1. **Result(Ok)** and **Result(Err)** CLValueParsed to_json and from_json implementations are missing.
 2. Some of the **CLType and CLValue constructors** are missing like CLValue(vector\<PublicKey>) or CLValue(ResultSuccess), or Tuples.
 3. KeyPair from SECP256K1 and ED25519 are missing. 
