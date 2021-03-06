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
#include "creris/credit_risk/test_data/time_series_configuration_td.hpp"
#include "creris/credit_risk/test_data/variable_time_series_configuration_td.hpp"



namespace creris {
namespace credit_risk {

variable_time_series_configuration_generator::variable_time_series_configuration_generator() : position_(0) { }

void variable_time_series_configuration_generator::
populate(const unsigned int /*position*/, result_type& /*v*/) {
}

variable_time_series_configuration_generator::result_type
variable_time_series_configuration_generator::create(const unsigned int position) {
    variable_time_series_configuration r;
    creris::credit_risk::time_series_configuration_generator::populate(position, r);
    return r;
}
variable_time_series_configuration_generator::result_type*
variable_time_series_configuration_generator::create_ptr(const unsigned int position) {
    variable_time_series_configuration* p = new variable_time_series_configuration();
    variable_time_series_configuration_generator::populate(position, *p);
    return p;
}

variable_time_series_configuration_generator::result_type
variable_time_series_configuration_generator::operator()() {
    return create(position_++);
}

} }
