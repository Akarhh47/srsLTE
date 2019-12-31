/*
 * Copyright 2013-2019 Software Radio Systems Limited
 *
 * This file is part of srsLTE.
 *
 * srsLTE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * srsLTE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * A copy of the GNU Affero General Public License can be found in
 * the LICENSE file in the top-level directory of this distribution
 * and at http://www.gnu.org/licenses/.
 *
 */

#ifndef SRSUE_TTCN3_INTERFACES_H
#define SRSUE_TTCN3_INTERFACES_H

#include "srslte/common/common.h"
#include "srslte/interfaces/ue_interfaces.h"

// Interfaces used by system interface to communicate with main component
class ss_ut_interface
{
public:
  virtual void tc_start(const char* name) = 0;
  virtual void tc_end()                   = 0;
  virtual void power_off_ue()             = 0;
  virtual void switch_on_ue()             = 0;
  virtual void switch_off_ue()            = 0;
  virtual void enable_data()              = 0;
  virtual void disable_data()             = 0;
};

class ss_sys_interface
{
public:
  virtual void     add_bcch_dlsch_pdu(const std::string cell_name, srslte::unique_byte_buffer_t pdu)              = 0;
  virtual void     add_pch_pdu(srslte::unique_byte_buffer_t pdu)                                                  = 0;
  virtual void     set_cell_attenuation(std::string cell_name, const float attenuation)                           = 0;
  virtual void     set_cell_config(std::string cell_name, uint32_t earfcn, srslte_cell_t cell, const float power) = 0;
  virtual void     add_srb(uint32_t lcid, srslte::pdcp_config_t pdcp_config)                                      = 0;
  virtual void     del_srb(uint32_t lcid)                                                                         = 0;
  virtual uint32_t get_tti()                                                                                      = 0;
  virtual int      set_as_security(const uint32_t                            lcid,
                                   const std::array<uint8_t, 32>             k_rrc_enc,
                                   const std::array<uint8_t, 32>             k_rrc_int,
                                   const std::array<uint8_t, 32>             k_up_enc,
                                   const srslte::CIPHERING_ALGORITHM_ID_ENUM cipher_algo,
                                   const srslte::INTEGRITY_ALGORITHM_ID_ENUM integ_algo)                          = 0;
};

class ss_srb_interface
{
public:
  virtual void add_ccch_pdu(srslte::unique_byte_buffer_t pdu)                = 0;
  virtual void add_dcch_pdu(uint32_t lcid, srslte::unique_byte_buffer_t pdu) = 0;
  virtual void reestablish_bearer(uint32_t lcid)                             = 0;
};

class syssim_interface_phy
{
public:
  virtual void prach_indication(uint32_t preamble_index, const uint32_t& cell_id)   = 0;
  virtual void sr_req(uint32_t tti_tx)                                              = 0;
  virtual void tx_pdu(const uint8_t* payload, const int len, const uint32_t tx_tti) = 0;
};

class phy_interface_syssim
{
public:
  virtual void     set_current_tti(uint32_t tti)                                                             = 0;
  virtual uint16_t get_dl_sched_rnti(uint32_t tti)                                                           = 0;
  virtual void     new_grant_ul(const srsue::mac_interface_phy_lte::mac_grant_ul_t grant)                    = 0;
  virtual void     new_tb(const srsue::mac_interface_phy_lte::mac_grant_dl_t mac_grant, const uint8_t* data) = 0;
};

#endif // SRSUE_TTCN3_INTERFACES_H