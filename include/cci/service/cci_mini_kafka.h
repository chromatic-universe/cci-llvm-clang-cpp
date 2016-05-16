//cci_mini_kafka.h william k. johnson 2015
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma once

#include "librdkafka/rdkafka.h"
#include "cci/cci.h"

//kafka logger callback
//------------------------------------------------------------------------
extern void cci_kf_logger ( const rd_kafka_t *rk ,
                            int level ,
                            const char *fac ,
                            const char *buf );

extern int run;
extern rd_kafka_t *rk;
extern int exit_eof;
extern int quiet;
extern void stop ( int sig );
static  enum {
	OUTPUT_HEXDUMP,
	OUTPUT_RAW,
} output = OUTPUT_HEXDUMP;

//types
typedef FILE* file_ptr;
typedef rd_kafka_message_t*                     message_ptr_k;
typedef struct rd_kafka_metadata*               metadata_ptr_k;
typedef struct rd_kafka_metadata_topic*         metadata_topic_ptr_k;
typedef struct rd_kafka_metadata_partition*     metadata_partition_ptr_k;
typedef rd_kafka_topic_t*                       topic_ptr_k;
typedef rd_kafka_conf_t*                        conf_k_ptr;
typedef rd_kafka_topic_conf_t*                  topic_conf_k_ptr;


//signal handlers
//
//
extern void sig_usr1 ( int sig );

//callbacks
//
//optional logging callback
extern void cci_kf_logger ( const rd_kafka_t *rk ,
                            int level ,
           	                const char *fac ,
                            const char *buf );
//------------------------------------------------------------------------
//
//message delivery callback
extern void cci_kf_msg_delivered( rd_kafka_t *rk ,
                                  const message_ptr_k rkmessage ,
                                  void_ptr opaque );
//------------------------------------------------------------------------
//services
//
//message consume
extern void cci_kf_msg_consume( message_ptr_k rkmessage , void_ptr opaque );
//------------------------------------------------------------------------
//
//hex dump
extern void cci_kf_hex_dump( file_ptr fp, const char *name, const void_ptr ptr , size_t len );
//------------------------------------------------------------------------
//
//metadata print
extern void cci_kf_metadata_print ( const char *topic , const metadata_ptr_k metadata );
//------------------------------------------------------------------------
//mini run
//
extern void cci_kf_mini_run( int argc , char** argv );



