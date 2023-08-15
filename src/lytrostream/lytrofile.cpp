// Copyright (c) 2023-present, Martin TOUZOT & LytroIO contributors.
// Distributed under the GPL-3.0 Licence (https://opensource.org/license/gpl-3-0/)

#include <lytroio/lytrostream/lytrofile.hpp>

namespace lytroio
{
    LytroFile::LytroFile(std::string filename) : filename_(filename)
    {
        elements_ = new std::vector<LytroElement>();
    }

    LytroFile::~LytroFile()
    {
        delete elements_;
    }

    bool LytroFile::read()
    {
        return LytroParser::parse(filename_, this->elements_);
    }
} // namespace lytroio