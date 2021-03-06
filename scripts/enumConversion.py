import re


def get_enum_keys(enum_name: str, source: str) -> list:
    compiled_exp = re.compile(r"enum ?(class)? (" + enum_name + r")[\w :]*[\n]?{((.|\n)*)};")
    groups = compiled_exp.search(source)
    keys = []
    for line in groups.group(3).splitlines():
        stripped = line.strip()
        if len(stripped) == 0:
            continue
        key, value = stripped.split("=")
        # print(key.strip(), value.replace(",", "").strip())
        keys.append(key.strip())
    return keys


def generate_enum_to_string_function(keys: list, function_name: str, enum_name: str) -> str:
    return_type = "std::string"
    padding = " " * 4
    result = f"{return_type} {function_name}({enum_name} arg)\n" + "{\n"
    result += padding + "switch(arg)\n"
    result += padding + "{\n"
    for key in keys:
        result += f"{padding * 2}case {enum_name}::{key}: return \"{key}\";\n"
        # result += padding * 2 + "case " + enum_name + "::" + key + ": return \"" + key + "\";\n"
    result += padding + "}\n"
    result += "}"
    return result


def generate_string_to_enum_function(keys: list, function_name: str, enum_name: str, constexpr_hash_function: str) -> str:
    argument_type = "const std::string"
    padding = " " * 4
    result = f"{enum_name} {function_name}({argument_type} &arg)\n"
    result += "{\n"
    result += f"{padding}size_t hash = {constexpr_hash_function}(arg);\n"
    result += f"{padding}switch(hash)\n"
    result += padding + "{\n"
    for key in keys:
        result += f"{padding * 2}case {constexpr_hash_function}(\"{key}\"): return {enum_name}::{key};\n"
    result += padding + "}\n"
    result += "}"
    return result


def main():
    path = "../vanadium/src/platform/default/DefaultKeyCodes.h"
    enum_name = "KeyCode"
    with open(path) as file:
        source = file.read()
    enum_keys = get_enum_keys(enum_name, source)
    # result = generate_enum_to_string_function(enum_keys, "toString", enum_name)
    result = generate_string_to_enum_function(enum_keys, "fromString", enum_name, "hashString")
    print(result)


if __name__ == "__main__":
    main()
