// Copyright (c) 2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef BITCOIN_VERSION_H
#define BITCOIN_VERSION_H

#include "clientversion.h"
#include <string>

//
// client versioning
//

static const int CLIENT_VERSION =
                           1000000 * CLIENT_VERSION_MAJOR
                         +   10000 * CLIENT_VERSION_MINOR
                         +     100 * CLIENT_VERSION_REVISION
                         +       1 * CLIENT_VERSION_BUILD;

extern const std::string CLIENT_NAME;
extern const std::string CLIENT_BUILD;
extern const std::string CLIENT_DATE;

//
// network protocol versioning
//

//70002 =  r0.1.1
//70003 =  r0.1.2
//70004 =  r0.1.3
//70005 =  r0.1.4       =   (mandatory update)
//70005 =  r0.1.5       =   r0.1.5.1 (non-mandatory update - no protocol version change)
//700051 = r1.5.2 beta4 =   dropped leading "0." on versioning, locked to cakenet. BETA not to be used on mainnet
//700052 = r1.5.3 beta - 1.6b2 =    Locked to cakenet for testing. BETA not to be used on mainnet
//700053 = 1.6b3 =    Locked to cakenet for testing. BETA not to be used on mainnet
//700054 = 1.6b4 =    Locked to cakenet for testing. BETA not to be used on mainnet
static const int PROTOCOL_VERSION = 700054;

// intial proto version, to be increased after version/verack negotiation
static const int INIT_PROTO_VERSION = 209;

// disconnect from peers older than this proto version
static const int MIN_PEER_PROTO_VERSION = 700054;

// nTime field added to CAddress, starting with this version;
// if possible, avoid requesting addresses nodes older than this
static const int CADDR_TIME_VERSION = 31402;

// only request blocks from nodes outside this range of versions
static const int NOBLKS_VERSION_START = 32000;
static const int NOBLKS_VERSION_END = 32400;

// BIP 0031, pong message, is enabled for all versions AFTER this one
static const int BIP0031_VERSION = 60000;

// "mempool" command, enhanced "getdata" behavior starts with this version:
static const int MEMPOOL_GD_VERSION = 60002;

#endif
