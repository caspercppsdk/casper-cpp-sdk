#include "Utils/StringUtil.h"

#include <algorithm>
#include <cassert>
#include <codecvt>
#include <iostream>
#include <locale>
#include <sstream>
#include <iomanip>  // std::setfill, std::setw
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

void swapAndReverse(std::string& str) {
  std::reverse(str.begin(), str.end());
  for (int32_t i = 0; i < str.length() / 2; i += 2) {
    std::swap(str[i], str[i + 1]);
  }
}

using wstring_utf8_converter =
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>;

std::wstring from_utf8(std::string_view s) {
  wstring_utf8_converter converter;
  const char* begin = &(*s.begin());
  const char* end = begin + s.size();
  return converter.from_bytes(begin, end);
}

std::string StringUtil::getStringBytesWithoutLength(const std::string& str) {
  std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
  std::wstring wstr = from_utf8(str);

  std::stringstream input_ss;
  input_ss << std::hex << std::setfill('0');

  for (auto c : wstr) {
    input_ss << std::setw(2) << static_cast<uint32_t>(c);
  }
  std::string output_str = input_ss.str();

  return output_str;
}
std::string StringUtil::stringToHex(const std::string& str) {
  std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
  std::wstring wstr = from_utf8(str);

  /// add length of string and extra 0s, total is 4 bytes
  std::stringstream len_ss;
  len_ss << std::hex << std::setfill('0');

  int32_t str_length = wstr.length();
  len_ss << std::setw(8) << str_length;

  std::string len_str = len_ss.str();
  swapAndReverse(len_str);

  std::stringstream input_ss;
  input_ss << std::hex << std::setfill('0');

  for (auto c : wstr) {
    input_ss << std::setw(2) << static_cast<uint32_t>(c);
  }
  std::string output_str = len_str + input_ss.str();

  return output_str;
}

}  // namespace Casper
