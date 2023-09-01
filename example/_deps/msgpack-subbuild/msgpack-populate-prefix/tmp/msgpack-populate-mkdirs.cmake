# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/data/shared/public/cangshui/bbuf/tokenizers-cpp/example/_deps/msgpack-src"
  "/data/shared/public/cangshui/bbuf/tokenizers-cpp/example/_deps/msgpack-build"
  "/data/shared/public/cangshui/bbuf/tokenizers-cpp/example/_deps/msgpack-subbuild/msgpack-populate-prefix"
  "/data/shared/public/cangshui/bbuf/tokenizers-cpp/example/_deps/msgpack-subbuild/msgpack-populate-prefix/tmp"
  "/data/shared/public/cangshui/bbuf/tokenizers-cpp/example/_deps/msgpack-subbuild/msgpack-populate-prefix/src/msgpack-populate-stamp"
  "/data/shared/public/cangshui/bbuf/tokenizers-cpp/example/_deps/msgpack-subbuild/msgpack-populate-prefix/src"
  "/data/shared/public/cangshui/bbuf/tokenizers-cpp/example/_deps/msgpack-subbuild/msgpack-populate-prefix/src/msgpack-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/data/shared/public/cangshui/bbuf/tokenizers-cpp/example/_deps/msgpack-subbuild/msgpack-populate-prefix/src/msgpack-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/data/shared/public/cangshui/bbuf/tokenizers-cpp/example/_deps/msgpack-subbuild/msgpack-populate-prefix/src/msgpack-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
