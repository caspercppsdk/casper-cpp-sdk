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

 1. **Key** parsing does not have inner enum object such as "Hash" or "Account".
 2. **Result(Ok)** and **Result(Err)** CLValueParsed to_json and from_json implementations are missing.
 3. **ToBytes** functions(**binary serialization, obj to bytes**) of everything are missing. 
 4. **CLType and CLValue constructors** are missing like CLValue(int64) or CLValue(vector\<PublicKey>). 
 5. **ED25519/SECP256K1** key pairs Wrappers(https://github.com/make-software/casper-net-sdk/blob/master/Casper.Network.SDK/Types/KeyPair.cs)
6. Inner types of the classes should be **ordered** such as session and payment order in a **deploy** object json.
7. **CLValue explicit type casts** like CLValue->U64 or CLValue->Option\<T> should be implemented like **net-sdk**.