#include "Utils/StringUtil.h"

#include <algorithm>
#include <cassert>
#include <codecvt>
#include <iostream>
#include <locale>
#include <sstream>

namespace Casper {

bool StringUtil::startsWith(const std::string& str, const std::string& cmp) {
  return str.compare(0, cmp.length(), cmp) == 0;
}

std::vector<std::string> StringUtil::splitString(std::string str,
                                                 std::string delim) {
  std::vector<std::string> result;
  std::stringstream ss(str);
  std::string token;

  while (std::getline(ss, token, delim[0])) {
    result.push_back(token);
  }

  return result;
}

std::string StringUtil::toLower(std::string& str) {
  std::transform(str.begin(), str.end(), str.begin(), ::tolower);
  return str;
}

uint32_t StringUtil::hexStrToUint32(const std::string& str) {
  std::stringstream stream{};
  stream << std::hex << str;
  uint32_t parsed;
  stream >> parsed;
  return parsed;
}

std::string StringUtil::hexToUTF8(const std::string& str) {
  uint32_t parsed = hexStrToUint32(str);

  std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;

  return converter.to_bytes(static_cast<char32_t>(parsed));
}

std::string StringUtil::hexToString(const std::string& bytes_str) {
  // first 2 chars are the length of the string
  uint32_t str_size = 2 * hexStrToUint32(bytes_str.substr(0, 2));

  // get the meaningful string hex bytes
  std::string str = bytes_str.substr(bytes_str.length() - str_size);

  std::stringstream ss;
  for (int i = 0; i < str_size / 2; i++) {
    ss << hexToUTF8(str.substr(i * 2, 2));
  }

  std::string str_utf8 = ss.str();
  return str_utf8;
}

}  // namespace Casper
