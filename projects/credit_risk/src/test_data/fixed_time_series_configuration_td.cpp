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
#include <sstream>
#include "creris/credit_risk/test_data/fixed_time_series_configuration_td.hpp"
#include "creris/credit_risk/test_data/time_series_configuration_td.hpp"

namespace {

unsigned int create_unsigned_int(const unsigned int position) {
    return static_cast<unsigned int>(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::vector<std::string> create_std_vector_std_string(unsigned int position) {
    std::vector<std::string> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

}

namespace creris {
namespace credit_risk {

fixed_time_series_configuration_generator::fixed_time_series_configuration_generator() : position_(0) { }

void fixed_time_series_configuration_generator::
populate(const unsigned int position, result_type& v) {
    v.length(create_unsigned_int(position + 0));
    v.points_configuration(create_std_vector_std_string(position + 1));
}

fixed_time_series_configuration_generator::result_type
fixed_time_series_configuration_generator::create(const unsigned int position) {
    fixed_time_series_configuration r;
    creris::credit_risk::time_series_configuration_generator::populate(position, r);
    fixed_time_series_configuration_generator::populate(position, r);
    return r;
}
fixed_time_series_configuration_generator::result_type*
fixed_time_series_configuration_generator::create_ptr(const unsigned int position) {
    fixed_time_series_configuration* p = new fixed_time_series_configuration();
    fixed_time_series_configuration_generator::populate(position, *p);
    return p;
}

fixed_time_series_configuration_generator::result_type
fixed_time_series_configuration_generator::operator()() {
    return create(position_++);
}

} }
