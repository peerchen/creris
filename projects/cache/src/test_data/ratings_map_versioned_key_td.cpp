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
#include "creris/credit_risk/test_data/ratings_map_versioned_key_td.hpp"

namespace {

unsigned int create_unsigned_int(const unsigned int position) {
    return static_cast<unsigned int>(position);
}

}

namespace creris {
namespace credit_risk {

ratings_map_versioned_key_generator::ratings_map_versioned_key_generator() : position_(0) { }

void ratings_map_versioned_key_generator::
populate(const unsigned int position, result_type& v) {
    v.id(create_unsigned_int(position + 0));
    v.version(create_unsigned_int(position + 1));
}

ratings_map_versioned_key_generator::result_type
ratings_map_versioned_key_generator::create(const unsigned int position) {
    ratings_map_versioned_key r;
    ratings_map_versioned_key_generator::populate(position, r);
    return r;
}
ratings_map_versioned_key_generator::result_type*
ratings_map_versioned_key_generator::create_ptr(const unsigned int position) {
    ratings_map_versioned_key* p = new ratings_map_versioned_key();
    ratings_map_versioned_key_generator::populate(position, *p);
    return p;
}

ratings_map_versioned_key_generator::result_type
ratings_map_versioned_key_generator::operator()() {
    return create(position_++);
}

} }
