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
#include <ostream>
#include "creris/credit_risk/io/model_configuration_unversioned_key_io.hpp"
#include "creris/credit_risk/io/rating_evaluation_io.hpp"

namespace creris {
namespace credit_risk {

std::ostream& operator<<(std::ostream& s, const rating_evaluation& v) {
    s << " { "
      << "\"__type__\": " << "\"rating_evaluation\"" << ", "
      << "\"initial_year\": " << v.initial_year() << ", "
      << "\"projection_years\": " << v.projection_years() << ", "
      << "\"number_of_trials\": " << v.number_of_trials() << ", "
      << "\"model_configuration_key\": " << v.model_configuration_key()
      << " }";
    return(s);
}

} }