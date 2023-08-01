// Copyright (c) 2023-present, Martin TOUZOT & LytroIO contributors.
// Distributed under the GPL-3.0 Licence (https://opensource.org/license/gpl-3-0/)
/** \file include/lytrioio/lytrofile.hpp
 *
 *  \brief Implementation of a structure corresponding a Lytro files (.LPF or .LFR formats)
 *
 * A Lytro file contains various elements (package, metadata, components). This class acts
 * like the
 *
 */

#pragma once

//
// Lytro file structure

#ifndef LYTROFILE_H
#define LYTROFILE_H

#include <lytroio/lytroelement.hpp>
#include <lytroio/lytroparser.hpp>
#include <vector>
#include <iterator>

class LytroFile
{
    public:
        //Custom LytroFile Iterator
        struct LytroIterator
        {
            using iterator_category = std::forward_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = LytroElement;
            using pointer           = LytroElement*;
            using reference         = LytroElement&;

            LytroIterator(pointer ptr) : m_ptr(ptr) {}

            reference operator*() const { return *m_ptr; }
            pointer operator->() { return m_ptr; }
            LytroIterator& operator++() { m_ptr++; return *this; }
            LytroIterator operator++(int) { LytroIterator tmp = *this; ++(*this); return tmp; }
            friend bool operator== (const LytroIterator& a, const LytroIterator& b) { return a.m_ptr == b.m_ptr; };
            friend bool operator!= (const LytroIterator& a, const LytroIterator& b) { return a.m_ptr != b.m_ptr; };

            private:
                pointer m_ptr;
        };

        LytroIterator begin() { return LytroIterator(&elements_->front()); }
        LytroIterator end() { return LytroIterator(&elements_->back()); }

        LytroFile(std::string filename);
        ~LytroFile();

        bool read();

    private:
        std::string filename_;
        std::vector<LytroElement> *elements_;
};

#endif // LYTROFILE_H