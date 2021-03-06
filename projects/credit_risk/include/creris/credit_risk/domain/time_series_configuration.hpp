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
#ifndef CRERIS_CREDIT_RISK_DOMAIN_TIME_SERIES_CONFIGURATION_HPP
#define CRERIS_CREDIT_RISK_DOMAIN_TIME_SERIES_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <iosfwd>
#include <string>
#include "creris/credit_risk/domain/generator_configuration.hpp"
#include "creris/credit_risk/domain/time_series_configuration_versioned_key.hpp"
#include "creris/credit_risk/serialization/time_series_configuration_fwd_ser.hpp"

namespace creris {
namespace credit_risk {

/*
 * @brief Defines the structure of a time series.
 *
 * This can be thought of as a time series type or class.
 */
class time_series_configuration {
public:
    time_series_configuration() = default;
    time_series_configuration(const time_series_configuration&) = default;
    time_series_configuration(time_series_configuration&&) = default;

    virtual ~time_series_configuration() noexcept = 0;

public:
    time_series_configuration(
        const std::string& name,
        const std::string& description,
        const std::string& time_axis_label,
        const std::string& value_axis_label,
        const boost::shared_ptr<creris::credit_risk::generator_configuration>& generator_configuration,
        const creris::credit_risk::time_series_configuration_versioned_key& versioned_key);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const time_series_configuration& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, time_series_configuration& v, unsigned int version);

public:
    virtual void to_stream(std::ostream& s) const;

public:
    /*
     * @brief Name for the time series configuration.
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
     * @brief Description of the underlying data that this series class models.
     */
    /**@{*/
    std::string description() const {
        return description_;
    }

    void description(const std::string& v) {
        description_ = v;
    }
    /**@}*/

    /*
     * @brief Label for the time axis.
     */
    /**@{*/
    std::string time_axis_label() const {
        return time_axis_label_;
    }

    void time_axis_label(const std::string& v) {
        time_axis_label_ = v;
    }
    /**@}*/

    /*
     * @brief Label for the value axis.
     */
    /**@{*/
    std::string value_axis_label() const {
        return value_axis_label_;
    }

    void value_axis_label(const std::string& v) {
        value_axis_label_ = v;
    }
    /**@}*/

    /*
     * @brief Source of the points for the time series.
     */
    /**@{*/
    boost::shared_ptr<creris::credit_risk::generator_configuration> generator_configuration() const {
        return generator_configuration_;
    }

    void generator_configuration(const boost::shared_ptr<creris::credit_risk::generator_configuration>& v) {
        generator_configuration_ = v;
    }
    /**@}*/

    creris::credit_risk::time_series_configuration_versioned_key versioned_key() const {
        return versioned_key_;
    }

    void versioned_key(const creris::credit_risk::time_series_configuration_versioned_key& v) {
        versioned_key_ = v;
    }

protected:
    bool compare(const time_series_configuration& rhs) const;
public:
    virtual bool equals(const time_series_configuration& other) const = 0;

protected:
    void swap(time_series_configuration& other) noexcept;

private:
    std::string name_;
    std::string description_;
    std::string time_axis_label_;
    std::string value_axis_label_;
    boost::shared_ptr<creris::credit_risk::generator_configuration> generator_configuration_;
    creris::credit_risk::time_series_configuration_versioned_key versioned_key_;
};

inline time_series_configuration::~time_series_configuration() noexcept { }

inline bool operator==(const time_series_configuration& lhs, const time_series_configuration& rhs) {
    return lhs.equals(rhs);
}

} }



#endif
