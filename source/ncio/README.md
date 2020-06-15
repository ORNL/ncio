# source/ncio 

Internal private library source code 
 
* common : Common headers to private and public interfaces. Installed under `prefix/include/common`
 
* core : Core components of the ncio library, map private implementation of bindings objects

* schema : Schema specific definitions and functionality exposed within a particular `ncio::schema::`schemaName namespace. Example: `ncio::schema::nexus::ToString<T>()` 
  - nexus : namespace ncio::nexus 
   
* transport - Lowest layer of the library. Glue code to underlying library dependencies.
  - HDF5 : glue to HDF5 library
  - Null : null transport to measure overhead of other transports
 