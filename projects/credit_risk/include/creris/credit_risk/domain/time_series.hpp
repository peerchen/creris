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
#ifndef CRERIS_CREDIT_RISK_DOMAIN_TIME_SERIES_HPP
#define CRERIS_CREDIT_RISK_DOMAIN_TIME_SERIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <string>
#include <vector>
#include "creris/credit_risk/domain/time_point.hpp"
#include "creris/credit_risk/domain/time_series_configuration_versioned_key.hpp"
#include "creris/credit_risk/domain/time_series_versioned_key.hpp"
#include "creris/credit_risk/serialization/time_series_fwd_ser.hpp"

namespace creris {
namespace credit_risk {

class time_series final {
public:
    time_series() = default;
    time_series(const time_series&) = default;
    time_series(time_series&&) = default;
    ~time_series() = default;

public:
    time_series(
        const std::string& name,
        const creris::credit_risk::time_series_configuration_versioned_key& time_series_configuration,
        const std::vector<creris::credit_risk::time_point>& points,
        const creris::credit_risk::time_series_versioned_key& versioned_key);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const time_series& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, time_series& v, unsigned int version);

public:
    /*
     * @brief Name for this time series
     */
    /**@{*/
    std::string name() const {
        return name_;
    }

    void name(const std::string& v) {
        name_ = v;
    }
    /**@}*/

    /*
     * @brief Configuration to which this type of time series belongs to.
     */
    /**@{*/
    creris::credit_risk::time_series_configuration_versioned_key time_series_configuration() const {
        return time_series_configuration_;
    }

    void time_series_configuration(const creris::credit_risk::time_series_configuration_versioned_key& v) {
        time_series_configuration_ = v;
    }
    /**@}*/

    /*
     * @brief FIXME: boost::dense_series<double>, still not supported by Dogen at this point
     */
    /**@{*/
    std::vector<creris::credit_risk::time_point> points() const {
        return points_;
    }

    void points(const std::vector<creris::credit_risk::time_point>& v) {
        points_ = v;
    }
    /**@}*/

    creris::credit_risk::time_series_versioned_key versioned_key() const {
        return versioned_key_;
    }

    void versioned_key(const creris::credit_risk::time_series_versioned_key& v) {
        versioned_key_ = v;
    }

public:
    bool operator==(const time_series& rhs) const;
    bool operator!=(const time_series& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(time_series& other) noexcept;
    time_series& operator=(time_series other);

private:
    std::string name_;
    creris::credit_risk::time_series_configuration_versioned_key time_series_configuration_;
    std::vector<creris::credit_risk::time_point> points_;
    creris::credit_risk::time_series_versioned_key versioned_key_;
};

} }

namespace std {

template<>
inline void swap(
    creris::credit_risk::time_series& lhs,
    creris::credit_risk::time_series& rhs) {
    lhs.swap(rhs);
}

}

#endif
