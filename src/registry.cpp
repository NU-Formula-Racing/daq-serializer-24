#include <string>
#include <vector>

#include "registry.hpp"

namespace daq::impl
{
    std::string Registry::LATEST_SCHEMA_FILE = "latest_schema.drive";
    std::vector<std::string> Registry::REGISTERED_SCHEMA_FILES = {"schema.drive"};
}