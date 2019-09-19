/*
    * Licensed to the Apache Software Foundation (ASF) under one
    * or more contributor license agreements. See the NOTICE file
    * distributed with this work for additional information
    * regarding copyright ownership. The ASF licenses this file
    * to you under the Apache License, Version 2.0 (the
    * "License"); you may not use this file except in compliance
    * with the License. You may obtain a copy of the License at
    *
    * http://www.apache.org/licenses/LICENSE-2.0
    *
    * Unless required by applicable law or agreed to in writing,
    * software distributed under the License is distributed on an
    * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
    * KIND, either express or implied. See the License for the
    * specific language governing permissions and limitations
    * under the License.
    */

#ifndef TRUCE_DEFS_H_
#define TRUCE_DEFS_H_

#include "sgx_quote.h"

#define SP_CERT                "cert_and_key.pem"
#define SPID                 {{0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F}}
#define QUOTE_SIGN_TYPE        SGX_LINKABLE_SIGNATURE

#define IAS_URL     "https://api.trustedservices.intel.com/sgx/dev/attestation/v3/"
//#define IAS_URL     "https://test-as.sgx.trustedservices.intel.com:443/attestation/sgx/v2/"

#define SP_AS_PORT_DEFAULT    48023
#define SP_RS_PORT_DEFAULT    48033


#endif /* TRUCE_DEFS_H_ */
