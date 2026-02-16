#include <cctype>
class Solution {
public:
  /**
   * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
   *
   * 验证IP地址
   * @param IP string字符串 一个IP地址字符串
   * @return string字符串
   */
  string solve(string IP) {
    // write code here
    if (IP.find('.') != std::string::npos &&
        IP.find(':') == std::string::npos) {
      if (isIPv4(IP))
        return "IPv4";
    } else if (IP.find(':') != std::string::npos &&
               IP.find('.') == std::string::npos) {
      if (isIPv6(IP))
        return "IPv6";
    }
    return "Neither";
  }

  bool isIPv4(const std::string &IP) {
    auto parts = split(IP, '.');

    if (parts.size() != 4)
      return false;

    for (const auto &part : parts) {
      // 空段或者长度超出3位
      if (part.empty() || part.size() > 3)
        return false;

      // 是否为纯数字
      for (auto c : part) {
        if (!isdigit(c))
          return false;
      }

      // 长度大于1时不能以0开头
      if (IP.size() > 1 && part[0] == '0')
        return false;

      int num = stoi(part);
      if (num < 0 || num > 255)
        return false;
    }
    return true;
  }

  bool isIPv6(const std::string &IP) {
    auto parts = split(IP, ':');

    if (parts.size() != 8)
      return false;

    for (const auto &part : parts) {
      // 空段或者长度超出4位
      if (part.empty() || part.size() > 4)
        return false;

      // 检查每个字符是否为合法的16进制字符
      for (auto c : part) {
        bool is_hex = (isdigit(c) || (tolower(c) >= 'a') &&
                                         (tolower(c) <= 'f')); // 16进制是0-f
        if (!is_hex)
          return false;
      }
    }
    return true;
  }

  std::vector<std::string> split(const std::string &IP, char delim) {
    std::vector<std::string> parts;
    std::string current;
    for (int i = 0; i < IP.size(); ++i) {
      if (IP[i] != delim) {
        current += IP[i];
      } else {
        parts.emplace_back(std::move(current));
      }
    }
    parts.emplace_back(std::move(current));
    return parts;
  }
};