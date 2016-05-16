//cci_mini_fuser.h  william k. johnson 2015

#pragma once
#define FUSE_USE_VERSION 26


#include <fuse.h>
#include "cci/cci.h"


//callbacks
//
//get_attr
static int cci_getattr( const char* path , struct stat* stbuf );
//------------------------------------------------------------------------
//
//readdir
static int cci_readdir( const char* path ,
                        void_ptr buf ,
                        fuse_fill_dir_t filler ,
           	            off_t offset ,
                        struct fuse_file_info* fi );
//------------------------------------------------------------------------
//
//opem
static int cci_open( const char *path ,
                     struct fuse_file_info* fi );

//------------------------------------------------------------------------
//
//read
static int cci_read( const char *path ,
                     char* buf ,
                     size_t size ,
                     off_t offset ,
       		         struct fuse_file_info* fi );



