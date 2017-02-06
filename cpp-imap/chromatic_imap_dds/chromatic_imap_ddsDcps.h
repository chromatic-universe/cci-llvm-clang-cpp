//******************************************************************
// 
//  Generated by IDL to C++ Translator
//  
//  File name: chromatic_imap_ddsDcps.h
//  Source: chromatic_imap_ddsDcps.idl
//  Generated: Sun Jul 21 00:54:47 2013
//  OpenSplice V6.3.0OSS
//  
//******************************************************************
#ifndef _CHROMATIC_IMAP_DDSDCPS_H_
#define _CHROMATIC_IMAP_DDSDCPS_H_

#include "sacpp_mapping.h"
#include "sacpp_DDS_DCPS.h"
#include "dds_dcps_interfaces.h"
#include "chromatic_imap_dds.h"
#include "dds_builtinTopics.h"
#include "dds_dcps_builtintopics.h"

namespace chromatic_imap_dds
{
   struct chromatic_imap_command;
   struct chromatic_name_service;

   class chromatic_imap_commandTypeSupportInterface;

   typedef chromatic_imap_commandTypeSupportInterface * chromatic_imap_commandTypeSupportInterface_ptr;
   typedef DDS_DCPSInterface_var < chromatic_imap_commandTypeSupportInterface> chromatic_imap_commandTypeSupportInterface_var;
   typedef DDS_DCPSInterface_out < chromatic_imap_commandTypeSupportInterface> chromatic_imap_commandTypeSupportInterface_out;


   class chromatic_imap_commandDataWriter;

   typedef chromatic_imap_commandDataWriter * chromatic_imap_commandDataWriter_ptr;
   typedef DDS_DCPSInterface_var < chromatic_imap_commandDataWriter> chromatic_imap_commandDataWriter_var;
   typedef DDS_DCPSInterface_out < chromatic_imap_commandDataWriter> chromatic_imap_commandDataWriter_out;


   class chromatic_imap_commandDataReader;

   typedef chromatic_imap_commandDataReader * chromatic_imap_commandDataReader_ptr;
   typedef DDS_DCPSInterface_var < chromatic_imap_commandDataReader> chromatic_imap_commandDataReader_var;
   typedef DDS_DCPSInterface_out < chromatic_imap_commandDataReader> chromatic_imap_commandDataReader_out;


   class chromatic_imap_commandDataReaderView;

   typedef chromatic_imap_commandDataReaderView * chromatic_imap_commandDataReaderView_ptr;
   typedef DDS_DCPSInterface_var < chromatic_imap_commandDataReaderView> chromatic_imap_commandDataReaderView_var;
   typedef DDS_DCPSInterface_out < chromatic_imap_commandDataReaderView> chromatic_imap_commandDataReaderView_out;


   class chromatic_name_serviceTypeSupportInterface;

   typedef chromatic_name_serviceTypeSupportInterface * chromatic_name_serviceTypeSupportInterface_ptr;
   typedef DDS_DCPSInterface_var < chromatic_name_serviceTypeSupportInterface> chromatic_name_serviceTypeSupportInterface_var;
   typedef DDS_DCPSInterface_out < chromatic_name_serviceTypeSupportInterface> chromatic_name_serviceTypeSupportInterface_out;


   class chromatic_name_serviceDataWriter;

   typedef chromatic_name_serviceDataWriter * chromatic_name_serviceDataWriter_ptr;
   typedef DDS_DCPSInterface_var < chromatic_name_serviceDataWriter> chromatic_name_serviceDataWriter_var;
   typedef DDS_DCPSInterface_out < chromatic_name_serviceDataWriter> chromatic_name_serviceDataWriter_out;


   class chromatic_name_serviceDataReader;

   typedef chromatic_name_serviceDataReader * chromatic_name_serviceDataReader_ptr;
   typedef DDS_DCPSInterface_var < chromatic_name_serviceDataReader> chromatic_name_serviceDataReader_var;
   typedef DDS_DCPSInterface_out < chromatic_name_serviceDataReader> chromatic_name_serviceDataReader_out;


   class chromatic_name_serviceDataReaderView;

   typedef chromatic_name_serviceDataReaderView * chromatic_name_serviceDataReaderView_ptr;
   typedef DDS_DCPSInterface_var < chromatic_name_serviceDataReaderView> chromatic_name_serviceDataReaderView_var;
   typedef DDS_DCPSInterface_out < chromatic_name_serviceDataReaderView> chromatic_name_serviceDataReaderView_out;

   struct chromatic_imap_commandSeq_uniq_ {};
   typedef DDS_DCPSUVLSeq < chromatic_imap_command, struct chromatic_imap_commandSeq_uniq_> chromatic_imap_commandSeq;
   typedef DDS_DCPSSequence_var < chromatic_imap_commandSeq> chromatic_imap_commandSeq_var;
   typedef DDS_DCPSSequence_out < chromatic_imap_commandSeq> chromatic_imap_commandSeq_out;
   class chromatic_imap_commandTypeSupportInterface
   :
      virtual public DDS::TypeSupport
   { 
   public:
      typedef chromatic_imap_commandTypeSupportInterface_ptr _ptr_type;
      typedef chromatic_imap_commandTypeSupportInterface_var _var_type;

      static chromatic_imap_commandTypeSupportInterface_ptr _duplicate (chromatic_imap_commandTypeSupportInterface_ptr obj);
      DDS::Boolean _local_is_a (const char * id);

      static chromatic_imap_commandTypeSupportInterface_ptr _narrow (DDS::Object_ptr obj);
      static chromatic_imap_commandTypeSupportInterface_ptr _unchecked_narrow (DDS::Object_ptr obj);
      static chromatic_imap_commandTypeSupportInterface_ptr _nil () { return 0; }
      static const char * _local_id;
      chromatic_imap_commandTypeSupportInterface_ptr _this () { return this; }


   protected:
      chromatic_imap_commandTypeSupportInterface () {};
      ~chromatic_imap_commandTypeSupportInterface () {};
   private:
      chromatic_imap_commandTypeSupportInterface (const chromatic_imap_commandTypeSupportInterface &);
      chromatic_imap_commandTypeSupportInterface & operator = (const chromatic_imap_commandTypeSupportInterface &);
   };

   class chromatic_imap_commandDataWriter
   :
      virtual public DDS::DataWriter
   { 
   public:
      typedef chromatic_imap_commandDataWriter_ptr _ptr_type;
      typedef chromatic_imap_commandDataWriter_var _var_type;

      static chromatic_imap_commandDataWriter_ptr _duplicate (chromatic_imap_commandDataWriter_ptr obj);
      DDS::Boolean _local_is_a (const char * id);

      static chromatic_imap_commandDataWriter_ptr _narrow (DDS::Object_ptr obj);
      static chromatic_imap_commandDataWriter_ptr _unchecked_narrow (DDS::Object_ptr obj);
      static chromatic_imap_commandDataWriter_ptr _nil () { return 0; }
      static const char * _local_id;
      chromatic_imap_commandDataWriter_ptr _this () { return this; }

      virtual DDS::InstanceHandle_t register_instance (const chromatic_imap_command& instance_data) = 0;
      virtual DDS::InstanceHandle_t register_instance_w_timestamp (const chromatic_imap_command& instance_data, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::ReturnCode_t unregister_instance (const chromatic_imap_command& instance_data, DDS::InstanceHandle_t handle) = 0;
      virtual DDS::ReturnCode_t unregister_instance_w_timestamp (const chromatic_imap_command& instance_data, DDS::InstanceHandle_t handle, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::ReturnCode_t write (const chromatic_imap_command& instance_data, DDS::InstanceHandle_t handle) = 0;
      virtual DDS::ReturnCode_t write_w_timestamp (const chromatic_imap_command& instance_data, DDS::InstanceHandle_t handle, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::ReturnCode_t dispose (const chromatic_imap_command& instance_data, DDS::InstanceHandle_t handle) = 0;
      virtual DDS::ReturnCode_t dispose_w_timestamp (const chromatic_imap_command& instance_data, DDS::InstanceHandle_t handle, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::ReturnCode_t writedispose (const chromatic_imap_command& instance_data, DDS::InstanceHandle_t handle) = 0;
      virtual DDS::ReturnCode_t writedispose_w_timestamp (const chromatic_imap_command& instance_data, DDS::InstanceHandle_t handle, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::ReturnCode_t get_key_value (chromatic_imap_command& key_holder, DDS::InstanceHandle_t handle) = 0;
      virtual DDS::InstanceHandle_t lookup_instance (const chromatic_imap_command& instance_data) = 0;

   protected:
      chromatic_imap_commandDataWriter () {};
      ~chromatic_imap_commandDataWriter () {};
   private:
      chromatic_imap_commandDataWriter (const chromatic_imap_commandDataWriter &);
      chromatic_imap_commandDataWriter & operator = (const chromatic_imap_commandDataWriter &);
   };

   class chromatic_imap_commandDataReader
   :
      virtual public DDS::DataReader
   { 
   public:
      typedef chromatic_imap_commandDataReader_ptr _ptr_type;
      typedef chromatic_imap_commandDataReader_var _var_type;

      static chromatic_imap_commandDataReader_ptr _duplicate (chromatic_imap_commandDataReader_ptr obj);
      DDS::Boolean _local_is_a (const char * id);

      static chromatic_imap_commandDataReader_ptr _narrow (DDS::Object_ptr obj);
      static chromatic_imap_commandDataReader_ptr _unchecked_narrow (DDS::Object_ptr obj);
      static chromatic_imap_commandDataReader_ptr _nil () { return 0; }
      static const char * _local_id;
      chromatic_imap_commandDataReader_ptr _this () { return this; }

      virtual DDS::ReturnCode_t read (chromatic_imap_commandSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
      virtual DDS::ReturnCode_t take (chromatic_imap_commandSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
      virtual DDS::ReturnCode_t read_w_condition (chromatic_imap_commandSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::ReturnCode_t take_w_condition (chromatic_imap_commandSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::ReturnCode_t read_next_sample (chromatic_imap_command& received_data, DDS::SampleInfo& sample_info) = 0;
      virtual DDS::ReturnCode_t take_next_sample (chromatic_imap_command& received_data, DDS::SampleInfo& sample_info) = 0;
      virtual DDS::ReturnCode_t read_instance (chromatic_imap_commandSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
      virtual DDS::ReturnCode_t take_instance (chromatic_imap_commandSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
      virtual DDS::ReturnCode_t read_next_instance (chromatic_imap_commandSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
      virtual DDS::ReturnCode_t take_next_instance (chromatic_imap_commandSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
      virtual DDS::ReturnCode_t read_next_instance_w_condition (chromatic_imap_commandSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::ReturnCode_t take_next_instance_w_condition (chromatic_imap_commandSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::ReturnCode_t return_loan (chromatic_imap_commandSeq& received_data, DDS::SampleInfoSeq& info_seq) = 0;
      virtual DDS::ReturnCode_t get_key_value (chromatic_imap_command& key_holder, DDS::InstanceHandle_t handle) = 0;
      virtual DDS::InstanceHandle_t lookup_instance (const chromatic_imap_command& instance) = 0;

   protected:
      chromatic_imap_commandDataReader () {};
      ~chromatic_imap_commandDataReader () {};
   private:
      chromatic_imap_commandDataReader (const chromatic_imap_commandDataReader &);
      chromatic_imap_commandDataReader & operator = (const chromatic_imap_commandDataReader &);
   };

   class chromatic_imap_commandDataReaderView
   :
      virtual public DDS::DataReaderView
   { 
   public:
      typedef chromatic_imap_commandDataReaderView_ptr _ptr_type;
      typedef chromatic_imap_commandDataReaderView_var _var_type;

      static chromatic_imap_commandDataReaderView_ptr _duplicate (chromatic_imap_commandDataReaderView_ptr obj);
      DDS::Boolean _local_is_a (const char * id);

      static chromatic_imap_commandDataReaderView_ptr _narrow (DDS::Object_ptr obj);
      static chromatic_imap_commandDataReaderView_ptr _unchecked_narrow (DDS::Object_ptr obj);
      static chromatic_imap_commandDataReaderView_ptr _nil () { return 0; }
      static const char * _local_id;
      chromatic_imap_commandDataReaderView_ptr _this () { return this; }

      virtual DDS::ReturnCode_t read (chromatic_imap_commandSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
      virtual DDS::ReturnCode_t take (chromatic_imap_commandSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
      virtual DDS::ReturnCode_t read_w_condition (chromatic_imap_commandSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::ReturnCode_t take_w_condition (chromatic_imap_commandSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::ReturnCode_t read_next_sample (chromatic_imap_command& received_data, DDS::SampleInfo& sample_info) = 0;
      virtual DDS::ReturnCode_t take_next_sample (chromatic_imap_command& received_data, DDS::SampleInfo& sample_info) = 0;
      virtual DDS::ReturnCode_t read_instance (chromatic_imap_commandSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
      virtual DDS::ReturnCode_t take_instance (chromatic_imap_commandSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
      virtual DDS::ReturnCode_t read_next_instance (chromatic_imap_commandSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
      virtual DDS::ReturnCode_t take_next_instance (chromatic_imap_commandSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
      virtual DDS::ReturnCode_t read_next_instance_w_condition (chromatic_imap_commandSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::ReturnCode_t take_next_instance_w_condition (chromatic_imap_commandSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::ReturnCode_t return_loan (chromatic_imap_commandSeq& received_data, DDS::SampleInfoSeq& info_seq) = 0;
      virtual DDS::ReturnCode_t get_key_value (chromatic_imap_command& key_holder, DDS::InstanceHandle_t handle) = 0;
      virtual DDS::InstanceHandle_t lookup_instance (const chromatic_imap_command& instance) = 0;

   protected:
      chromatic_imap_commandDataReaderView () {};
      ~chromatic_imap_commandDataReaderView () {};
   private:
      chromatic_imap_commandDataReaderView (const chromatic_imap_commandDataReaderView &);
      chromatic_imap_commandDataReaderView & operator = (const chromatic_imap_commandDataReaderView &);
   };

   struct chromatic_name_serviceSeq_uniq_ {};
   typedef DDS_DCPSUVLSeq < chromatic_name_service, struct chromatic_name_serviceSeq_uniq_> chromatic_name_serviceSeq;
   typedef DDS_DCPSSequence_var < chromatic_name_serviceSeq> chromatic_name_serviceSeq_var;
   typedef DDS_DCPSSequence_out < chromatic_name_serviceSeq> chromatic_name_serviceSeq_out;
   class chromatic_name_serviceTypeSupportInterface
   :
      virtual public DDS::TypeSupport
   { 
   public:
      typedef chromatic_name_serviceTypeSupportInterface_ptr _ptr_type;
      typedef chromatic_name_serviceTypeSupportInterface_var _var_type;

      static chromatic_name_serviceTypeSupportInterface_ptr _duplicate (chromatic_name_serviceTypeSupportInterface_ptr obj);
      DDS::Boolean _local_is_a (const char * id);

      static chromatic_name_serviceTypeSupportInterface_ptr _narrow (DDS::Object_ptr obj);
      static chromatic_name_serviceTypeSupportInterface_ptr _unchecked_narrow (DDS::Object_ptr obj);
      static chromatic_name_serviceTypeSupportInterface_ptr _nil () { return 0; }
      static const char * _local_id;
      chromatic_name_serviceTypeSupportInterface_ptr _this () { return this; }


   protected:
      chromatic_name_serviceTypeSupportInterface () {};
      ~chromatic_name_serviceTypeSupportInterface () {};
   private:
      chromatic_name_serviceTypeSupportInterface (const chromatic_name_serviceTypeSupportInterface &);
      chromatic_name_serviceTypeSupportInterface & operator = (const chromatic_name_serviceTypeSupportInterface &);
   };

   class chromatic_name_serviceDataWriter
   :
      virtual public DDS::DataWriter
   { 
   public:
      typedef chromatic_name_serviceDataWriter_ptr _ptr_type;
      typedef chromatic_name_serviceDataWriter_var _var_type;

      static chromatic_name_serviceDataWriter_ptr _duplicate (chromatic_name_serviceDataWriter_ptr obj);
      DDS::Boolean _local_is_a (const char * id);

      static chromatic_name_serviceDataWriter_ptr _narrow (DDS::Object_ptr obj);
      static chromatic_name_serviceDataWriter_ptr _unchecked_narrow (DDS::Object_ptr obj);
      static chromatic_name_serviceDataWriter_ptr _nil () { return 0; }
      static const char * _local_id;
      chromatic_name_serviceDataWriter_ptr _this () { return this; }

      virtual DDS::InstanceHandle_t register_instance (const chromatic_name_service& instance_data) = 0;
      virtual DDS::InstanceHandle_t register_instance_w_timestamp (const chromatic_name_service& instance_data, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::ReturnCode_t unregister_instance (const chromatic_name_service& instance_data, DDS::InstanceHandle_t handle) = 0;
      virtual DDS::ReturnCode_t unregister_instance_w_timestamp (const chromatic_name_service& instance_data, DDS::InstanceHandle_t handle, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::ReturnCode_t write (const chromatic_name_service& instance_data, DDS::InstanceHandle_t handle) = 0;
      virtual DDS::ReturnCode_t write_w_timestamp (const chromatic_name_service& instance_data, DDS::InstanceHandle_t handle, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::ReturnCode_t dispose (const chromatic_name_service& instance_data, DDS::InstanceHandle_t handle) = 0;
      virtual DDS::ReturnCode_t dispose_w_timestamp (const chromatic_name_service& instance_data, DDS::InstanceHandle_t handle, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::ReturnCode_t writedispose (const chromatic_name_service& instance_data, DDS::InstanceHandle_t handle) = 0;
      virtual DDS::ReturnCode_t writedispose_w_timestamp (const chromatic_name_service& instance_data, DDS::InstanceHandle_t handle, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::ReturnCode_t get_key_value (chromatic_name_service& key_holder, DDS::InstanceHandle_t handle) = 0;
      virtual DDS::InstanceHandle_t lookup_instance (const chromatic_name_service& instance_data) = 0;

   protected:
      chromatic_name_serviceDataWriter () {};
      ~chromatic_name_serviceDataWriter () {};
   private:
      chromatic_name_serviceDataWriter (const chromatic_name_serviceDataWriter &);
      chromatic_name_serviceDataWriter & operator = (const chromatic_name_serviceDataWriter &);
   };

   class chromatic_name_serviceDataReader
   :
      virtual public DDS::DataReader
   { 
   public:
      typedef chromatic_name_serviceDataReader_ptr _ptr_type;
      typedef chromatic_name_serviceDataReader_var _var_type;

      static chromatic_name_serviceDataReader_ptr _duplicate (chromatic_name_serviceDataReader_ptr obj);
      DDS::Boolean _local_is_a (const char * id);

      static chromatic_name_serviceDataReader_ptr _narrow (DDS::Object_ptr obj);
      static chromatic_name_serviceDataReader_ptr _unchecked_narrow (DDS::Object_ptr obj);
      static chromatic_name_serviceDataReader_ptr _nil () { return 0; }
      static const char * _local_id;
      chromatic_name_serviceDataReader_ptr _this () { return this; }

      virtual DDS::ReturnCode_t read (chromatic_name_serviceSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
      virtual DDS::ReturnCode_t take (chromatic_name_serviceSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
      virtual DDS::ReturnCode_t read_w_condition (chromatic_name_serviceSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::ReturnCode_t take_w_condition (chromatic_name_serviceSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::ReturnCode_t read_next_sample (chromatic_name_service& received_data, DDS::SampleInfo& sample_info) = 0;
      virtual DDS::ReturnCode_t take_next_sample (chromatic_name_service& received_data, DDS::SampleInfo& sample_info) = 0;
      virtual DDS::ReturnCode_t read_instance (chromatic_name_serviceSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
      virtual DDS::ReturnCode_t take_instance (chromatic_name_serviceSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
      virtual DDS::ReturnCode_t read_next_instance (chromatic_name_serviceSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
      virtual DDS::ReturnCode_t take_next_instance (chromatic_name_serviceSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
      virtual DDS::ReturnCode_t read_next_instance_w_condition (chromatic_name_serviceSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::ReturnCode_t take_next_instance_w_condition (chromatic_name_serviceSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::ReturnCode_t return_loan (chromatic_name_serviceSeq& received_data, DDS::SampleInfoSeq& info_seq) = 0;
      virtual DDS::ReturnCode_t get_key_value (chromatic_name_service& key_holder, DDS::InstanceHandle_t handle) = 0;
      virtual DDS::InstanceHandle_t lookup_instance (const chromatic_name_service& instance) = 0;

   protected:
      chromatic_name_serviceDataReader () {};
      ~chromatic_name_serviceDataReader () {};
   private:
      chromatic_name_serviceDataReader (const chromatic_name_serviceDataReader &);
      chromatic_name_serviceDataReader & operator = (const chromatic_name_serviceDataReader &);
   };

   class chromatic_name_serviceDataReaderView
   :
      virtual public DDS::DataReaderView
   { 
   public:
      typedef chromatic_name_serviceDataReaderView_ptr _ptr_type;
      typedef chromatic_name_serviceDataReaderView_var _var_type;

      static chromatic_name_serviceDataReaderView_ptr _duplicate (chromatic_name_serviceDataReaderView_ptr obj);
      DDS::Boolean _local_is_a (const char * id);

      static chromatic_name_serviceDataReaderView_ptr _narrow (DDS::Object_ptr obj);
      static chromatic_name_serviceDataReaderView_ptr _unchecked_narrow (DDS::Object_ptr obj);
      static chromatic_name_serviceDataReaderView_ptr _nil () { return 0; }
      static const char * _local_id;
      chromatic_name_serviceDataReaderView_ptr _this () { return this; }

      virtual DDS::ReturnCode_t read (chromatic_name_serviceSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
      virtual DDS::ReturnCode_t take (chromatic_name_serviceSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
      virtual DDS::ReturnCode_t read_w_condition (chromatic_name_serviceSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::ReturnCode_t take_w_condition (chromatic_name_serviceSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::ReturnCode_t read_next_sample (chromatic_name_service& received_data, DDS::SampleInfo& sample_info) = 0;
      virtual DDS::ReturnCode_t take_next_sample (chromatic_name_service& received_data, DDS::SampleInfo& sample_info) = 0;
      virtual DDS::ReturnCode_t read_instance (chromatic_name_serviceSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
      virtual DDS::ReturnCode_t take_instance (chromatic_name_serviceSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
      virtual DDS::ReturnCode_t read_next_instance (chromatic_name_serviceSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
      virtual DDS::ReturnCode_t take_next_instance (chromatic_name_serviceSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states) = 0;
      virtual DDS::ReturnCode_t read_next_instance_w_condition (chromatic_name_serviceSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::ReturnCode_t take_next_instance_w_condition (chromatic_name_serviceSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::ReturnCode_t return_loan (chromatic_name_serviceSeq& received_data, DDS::SampleInfoSeq& info_seq) = 0;
      virtual DDS::ReturnCode_t get_key_value (chromatic_name_service& key_holder, DDS::InstanceHandle_t handle) = 0;
      virtual DDS::InstanceHandle_t lookup_instance (const chromatic_name_service& instance) = 0;

   protected:
      chromatic_name_serviceDataReaderView () {};
      ~chromatic_name_serviceDataReaderView () {};
   private:
      chromatic_name_serviceDataReaderView (const chromatic_name_serviceDataReaderView &);
      chromatic_name_serviceDataReaderView & operator = (const chromatic_name_serviceDataReaderView &);
   };

}
template <>
DDS::BuiltinTopicKey_t_slice* DDS_DCPS_ArrayHelper < DDS::BuiltinTopicKey_t, DDS::BuiltinTopicKey_t_slice, DDS::BuiltinTopicKey_t_uniq_>::alloc ();
template <>
void DDS_DCPS_ArrayHelper < DDS::BuiltinTopicKey_t, DDS::BuiltinTopicKey_t_slice, DDS::BuiltinTopicKey_t_uniq_>::copy (DDS::BuiltinTopicKey_t_slice *to, const DDS::BuiltinTopicKey_t_slice* from);
template <>
void DDS_DCPS_ArrayHelper < DDS::BuiltinTopicKey_t, DDS::BuiltinTopicKey_t_slice, DDS::BuiltinTopicKey_t_uniq_>::free (DDS::BuiltinTopicKey_t_slice *ptr);




#endif 