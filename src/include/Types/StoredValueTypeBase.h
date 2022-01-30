enum StoredValueType {
    CLVALUE = 1,
    ACCOUNT = 2,
    CONTRACTWASM = 3,
    CONTRACT = 4,
    CONTRACTPACKAGE = 5,
    TRANSFER = 6,
    DEPLOYINFO = 7,
    ERAINFO = 8,
    BID = 9,
    WITHDRAW = 10
};

// Defines the base type for StoredValue types.
struct StoredValueTypeBase {
    StoredValueType type;

    void to_json(nlohmann::json& j);
};