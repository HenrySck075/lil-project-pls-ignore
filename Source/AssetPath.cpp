#include "AssetPath.h"
#include <string>

std::string kys::assetPath(std::string p) {
#ifdef __linux__
  return "Content/"+p;
#else
  return p;
#endif
}
