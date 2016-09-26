// This file is a part of the IncludeOS unikernel - www.includeos.org
//
// Copyright 2015-2016 Oslo and Akershus University College of Applied Sciences
// and Alfred Bratterud
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef MIDDLEWARE_PARSLEY_HPP
#define MIDDLEWARE_PARSLEY_HPP

#include "json.hpp"
#include "middleware.hpp"

namespace middleware {

/**
 * @brief A vegan way to parse JSON Content in a response
 * @details TBC..
 *
 */
class Parsley : public server::Middleware {
public:

  server::Callback handler() override {
    return {this, &Parsley::process};
  }
  /**
   *
   */
  void process(server::Request_ptr req, server::Response_ptr, server::Next next);

private:
  /**
   *
   */
  bool has_json(const server::Request& req) const;
}; //< class Parsley

/**--v----------- Implementation Details -----------v--**/

inline void Parsley::process(server::Request_ptr req, server::Response_ptr, server::Next next) {

  // Request doesn't have JSON attribute
  if(has_json(*req) and not req->has_attribute<json::Json_doc>())
  {
    // Create attribute
    auto json = std::make_shared<json::Json_doc>();

    // Access the document and parse the body
    try {
      json->doc().Parse(req->get_body().c_str());
      #ifdef VERBOSE_WEBSERVER
      printf("<Parsley> Parsed JSON data.\n");
      #endif

      // Add the json attribute to the request
      req->set_attribute(std::move(json));
    }
    catch(const Assert_error& e) {
      printf("<Parsley> Parsing error.\n");
    }

  }

  return (*next)();
}

inline bool Parsley::has_json(const server::Request& req) const {
  auto c_type = http::header_fields::Entity::Content_Type;
  if(not req.has_header(c_type)) return false;
  return (req.header_value(c_type).find("application/json") != std::string::npos);
}

/**--^----------- Implementation Details -----------^--**/

} //< namespace middleware

#endif //< MIDDLEWARE_PARSLEY_HPP
