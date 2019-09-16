#include <ATen/core/OpsAlreadyMovedToC10.h>

#include <string>
#include <cstring>
#include <utility>
#include <unordered_set>
#include <ATen/core/operator_name.h>

// ${generated_comment}

// TODO Once all ATen ops are moved to c10, this file should be removed

namespace at {

namespace {
struct OpNameEquals final {
  bool operator()(const std::pair<const char*, const char*>& lhs, const std::pair<const char*, const char*>& rhs) const {
      return 0 == strcmp(lhs.first, rhs.first) && 0 == strcmp(lhs.second, rhs.second);
  }
};

struct OpNameHash final {
  size_t operator()(const std::pair<const char*, const char*>& p) const {
      // use std::hash<std::string> because std::hash<const char*> would hash pointers and not pointed-to strings
      return std::hash<std::string>()(p.first) ^ (~ std::hash<std::string>()(p.second));
  }
};
}

bool aten_op_is_already_moved_to_c10(const c10::OperatorName& opName) {
  static std::unordered_set<std::pair<const char*, const char*>, OpNameHash, OpNameEquals> ops {
    ${c10_ops_already_moved_from_aten_to_c10}
    {"", ""}
  };
  return ops.count(std::make_pair(opName.name.c_str(), opName.overload_name.c_str())) != 0;
}

bool aten_op_is_not_moved_to_c10_yet(const c10::OperatorName& opName) {
  static std::unordered_set<std::pair<const char*, const char*>, OpNameHash, OpNameEquals> ops {
    ${c10_ops_not_moved_from_aten_to_c10_yet}
    {"", ""}
  };
  return ops.count(std::make_pair(opName.name.c_str(), opName.overload_name.c_str())) != 0;
}

}
