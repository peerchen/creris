/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef CRERIS_CACHE_DOMAIN_MODEL_CONFIGURATION_UNVERSIONED_GET_HPP
#define CRERIS_CACHE_DOMAIN_MODEL_CONFIGURATION_UNVERSIONED_GET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <vector>
#include "creris/cache/serialization/model_configuration/unversioned/get_fwd_ser.hpp"
#include "creris/credit_risk/domain/model_configuration_unversioned_key.hpp"

namespace creris {
namespace cache {
namespace model_configuration {
namespace unversioned {

class get final {
public:
    get() = default;
    get(const get&) = default;
    get(get&&) = default;
    ~get() = default;

public:
    explicit get(const std::vector<creris::credit_risk::model_configuration_unversioned_key>& key);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const get& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, get& v, unsigned int version);

public:
    std::vector<creris::credit_risk::model_configuration_unversioned_key> key() const {
        return key_;
    }

    void key(const std::vector<creris::credit_risk::model_configuration_unversioned_key>& v) {
        key_ = v;
    }

public:
    bool operator==(const get& rhs) const;
    bool operator!=(const get& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(get& other) noexcept;
    get& operator=(get other);

private:
    std::vector<creris::credit_risk::model_configuration_unversioned_key> key_;
};

} } } }

namespace std {

template<>
inline void swap(
    creris::cache::model_configuration::unversioned::get& lhs,
    creris::cache::model_configuration::unversioned::get& rhs) {
    lhs.swap(rhs);
}

}

#endif
