#ifndef OFFER_H
#define OFFER_H
#include "uint256.h"
#include "util.h"
#include "bitcoinrpc.h"
#include "leveldb.h"
#include "script.h"
#include <vector>
#include "serialize.h"
class CTransaction;
class CTxOut;
class CValidationState;
class CCoinsViewCache;
class COutPoint;
class CCoins;
class CScript;
class CWalletTx;
class CDiskTxPos;

bool CheckOfferInputs(CBlockIndex *pindex, const CTransaction &tx, CValidationState &state, CCoinsViewCache &inputs, bool fBlock, bool fMiner, bool fJustCheck);
bool ExtractOfferAddress(const CScript& script, std::string& address);
bool IsOfferMine(const CTransaction& tx);
bool IsOfferMine(const CTransaction& tx, const CTxOut& txout);
std::string SendOfferMoneyWithInputTx(CScript scriptPubKey, int64 nValue, int64 nNetFee, CWalletTx& wtxIn, CWalletTx& wtxNew, 
    bool fAskFee, const std::string& txData = "");
bool CreateOfferTransactionWithInputTx(const std::vector<std::pair<CScript, int64> >& vecSend, CWalletTx& wtxIn, int nTxOut, 
    CWalletTx& wtxNew, CReserveKey& reservekey, int64& nFeeRet, const std::string& txData);
int CheckTransactionAtRelativeDepth(CBlockIndex* pindexBlock,
		const CCoins *txindex, int maxDepth);
bool DecodeOfferTx(const CTransaction& tx, int& op, int& nOut, std::vector<std::vector<unsigned char> >& vvch, int nHeight);
bool DecodeOfferTx(const CCoins& tx, int& op, int& nOut, std::vector<std::vector<unsigned char> >& vvch, int nHeight);
bool DecodeOfferTxInputs(const CTransaction& tx, int& op, int& nOut, std::vector<std::vector<unsigned char> >& vvch, CCoinsViewCache &inputs);

bool DecodeOfferScript(const CScript& script, int& op, std::vector<std::vector<unsigned char> > &vvch);
bool IsOfferOp(int op);
int IndexOfOfferOutput(const CTransaction& tx);
bool GetValueOfOfferTxHash(const uint256 &txHash, std::vector<unsigned char>& vchValue, uint256& hash, int& nHeight);
int64 GetTxHashHeight(const uint256 txHash);
int GetTxPosHeight(const CDiskTxPos& txPos);
int GetTxPosHeight2(const CDiskTxPos& txPos, int nHeight);
int GetOfferDisplayExpirationDepth();
int64 GetOfferNetworkFee(const std::vector<unsigned char>& vchCurrency, opcodetype seed, unsigned int nHeight);
int64 GetOfferNetFee(const CTransaction& tx);
bool InsertOfferFee(CBlockIndex *pindex, uint256 hash, uint64 nValue);
int64 convertCurrencyCodeToSyscoin(const std::vector<unsigned char> &vchCurrencyCode, const double &nPrice, const unsigned int &nHeight, int &precision);
std::string offerFromOp(int op);
static const char* norefund = "norefund";
static const char* inprogress = "inprogress";
static const char* complete = "complete";
static const std::vector<unsigned char> OFFER_NOREFUND = std::vector<unsigned char>(norefund, norefund + strlen(norefund));
static const std::vector<unsigned char> OFFER_REFUND_PAYMENT_INPROGRESS = std::vector<unsigned char>(inprogress, inprogress + strlen(inprogress));
static const std::vector<unsigned char> OFFER_REFUND_COMPLETE = std::vector<unsigned char>(complete, complete + strlen(complete));

class CBitcoinAddress;
class COfferAccept {
public:
	std::vector<unsigned char> vchRand;
    std::vector<unsigned char> vchMessage;
	uint256 txHash;
	uint64 nHeight;
	unsigned int nQty;
	float nPrice;
	bool bPaid;
	bool bRefunded;
	uint256 txRefundId;
	std::vector<unsigned char> vchRefundAddress;
	std::vector<unsigned char> vchLinkOfferAccept;
	std::vector<unsigned char> vchCertLink;
	std::vector<unsigned char> vchEscrowLink;
	std::vector<unsigned char> vchBuyerKey;	
	COfferAccept() {
        SetNull();
    }

    IMPLEMENT_SERIALIZE (
        READWRITE(vchRand);
        READWRITE(vchMessage);
		READWRITE(txHash);
		READWRITE(VARINT(nHeight));
        READWRITE(VARINT(nQty));
    	READWRITE(nPrice);
    	READWRITE(bPaid);
		READWRITE(bRefunded);
		READWRITE(txRefundId);
		READWRITE(vchRefundAddress);
		READWRITE(vchLinkOfferAccept);
		READWRITE(vchCertLink);
		READWRITE(vchEscrowLink);
		READWRITE(vchBuyerKey);	
		
    )

    friend bool operator==(const COfferAccept &a, const COfferAccept &b) {
        return (
        a.vchRand == b.vchRand
        && a.vchMessage == b.vchMessage
        && a.txHash == b.txHash
        && a.nHeight == b.nHeight
        && a.nQty == b.nQty
        && a.nPrice == b.nPrice
        && a.bPaid == b.bPaid
		&& a.bRefunded == b.bRefunded
		&& a.txRefundId == b.txRefundId
		&& a.vchRefundAddress == b.vchRefundAddress
		&& a.vchLinkOfferAccept == b.vchLinkOfferAccept
		&& a.vchCertLink == b.vchCertLink
		&& a.vchEscrowLink == b.vchEscrowLink
		&& a.vchBuyerKey == b.vchBuyerKey
        );
    }

    COfferAccept operator=(const COfferAccept &b) {
        vchRand = b.vchRand;
        vchMessage = b.vchMessage;
        txHash = b.txHash;
        nHeight = b.nHeight;
        nQty = b.nQty;
        nPrice = b.nPrice;
        bPaid = b.bPaid;
		bRefunded = b.bRefunded;
		txRefundId = b.txRefundId;
		vchRefundAddress = b.vchRefundAddress;
		vchLinkOfferAccept = b.vchLinkOfferAccept;
		vchCertLink = b.vchCertLink;
		vchEscrowLink = b.vchEscrowLink;
		vchBuyerKey = b.vchBuyerKey;
        return *this;
    }

    friend bool operator!=(const COfferAccept &a, const COfferAccept &b) {
        return !(a == b);
    }

    void SetNull() { nHeight = nPrice = nQty = 0; txHash = 0; bPaid = false; txRefundId=0; vchBuyerKey.clear(); bRefunded=false;vchRefundAddress.clear();vchLinkOfferAccept.clear();vchCertLink.clear(); vchEscrowLink.clear();}
    bool IsNull() const { return (txHash == 0 && nHeight == 0 && nPrice == 0 && nQty == 0 && bPaid == 0 && bRefunded == false && txRefundId == 0); }

};
class COfferLinkWhitelistEntry {
public:
	std::vector<unsigned char> certLinkVchRand;
	int nDiscountPct;
	COfferLinkWhitelistEntry() {
		SetNull();
	}

    IMPLEMENT_SERIALIZE (
        READWRITE(certLinkVchRand);
		READWRITE(VARINT(nDiscountPct));
	)

    friend bool operator==(const COfferLinkWhitelistEntry &a, const COfferLinkWhitelistEntry &b) {
        return (
           a.certLinkVchRand == b.certLinkVchRand
		&& a.nDiscountPct == b.nDiscountPct
        );
    }

    COfferLinkWhitelistEntry operator=(const COfferLinkWhitelistEntry &b) {
    	certLinkVchRand = b.certLinkVchRand;
		nDiscountPct = b.nDiscountPct;
        return *this;
    }

    friend bool operator!=(const COfferLinkWhitelistEntry &a, const COfferLinkWhitelistEntry &b) {
        return !(a == b);
    }
    
    void SetNull() { certLinkVchRand.clear(); nDiscountPct = 0;}
    bool IsNull() const { return (certLinkVchRand.empty() && nDiscountPct == 0); }

};
class COfferLinkWhitelist {
public:
	std::vector<COfferLinkWhitelistEntry> entries;
	bool bExclusiveResell;
	COfferLinkWhitelist() {
		SetNull();
	}

    IMPLEMENT_SERIALIZE (
        READWRITE(entries);
		READWRITE(bExclusiveResell);

	)
    bool GetLinkEntryByHash(std::vector<unsigned char> ahash, COfferLinkWhitelistEntry &entry) {
    	for(unsigned int i=0;i<entries.size();i++) {
    		if(entries[i].certLinkVchRand == ahash) {
    			entry = entries[i];
    			return true;
    		}
    	}
    	return false;
    }
    bool RemoveWhitelistEntry(std::vector<unsigned char> ahash) {
    	for(unsigned int i=0;i<entries.size();i++) {
    		if(entries[i].certLinkVchRand == ahash) {
    			return entries.erase(entries.begin()+i) != entries.end();
    		}
    	}
    	return false;
    }	
    void PutWhitelistEntry(COfferLinkWhitelistEntry &theEntry) {
    	for(unsigned int i=0;i<entries.size();i++) {
    		COfferLinkWhitelistEntry entry = entries[i];
    		if(theEntry.certLinkVchRand == entry.certLinkVchRand) {
    			entries[i] = theEntry;
    			return;
    		}
    	}
    	entries.push_back(theEntry);
    }
    friend bool operator==(const COfferLinkWhitelist &a, const COfferLinkWhitelist &b) {
        return (
           a.entries == b.entries
		&& a.bExclusiveResell == b.bExclusiveResell

        );
    }

    COfferLinkWhitelist operator=(const COfferLinkWhitelist &b) {
    	entries = b.entries;
		bExclusiveResell = b.bExclusiveResell;
        return *this;
    }

    friend bool operator!=(const COfferLinkWhitelist &a, const COfferLinkWhitelist &b) {
        return !(a == b);
    }
    
    void SetNull() { entries.clear();bExclusiveResell = false;}
    bool IsNull() const { return (entries.empty() && bExclusiveResell == false);}

};
class COffer {

public:
	std::vector<unsigned char> vchRand;
	std::string aliasName;
	std::vector<unsigned char> vchPubKey;
    uint256 txHash;
    uint64 nHeight;
	std::vector<unsigned char> sCategory;
	std::vector<unsigned char> sTitle;
	std::vector<unsigned char> sDescription;
	float nPrice;
	int nCommission;
	unsigned int nQty;
	std::vector<COfferAccept>accepts;
	std::vector<unsigned char> vchLinkOffer;
	std::vector<unsigned char> sCurrencyCode;
	std::vector<unsigned char> vchCert;
	COfferLinkWhitelist linkWhitelist;
	std::vector<std::vector<unsigned char> > offerLinks;
	bool bPrivate;
	COffer() { 
        SetNull();
    }

    COffer(const CTransaction &tx) {
        SetNull();
        UnserializeFromTx(tx);
    }

    IMPLEMENT_SERIALIZE (
        READWRITE(vchRand);
        READWRITE(sCategory);
        READWRITE(sTitle);
        READWRITE(sDescription);
		READWRITE(txHash);
		READWRITE(VARINT(nHeight));
    	READWRITE(nPrice);
    	READWRITE(VARINT(nQty));
    	READWRITE(accepts);
		READWRITE(vchLinkOffer);
		READWRITE(linkWhitelist);
		READWRITE(sCurrencyCode);
		READWRITE(VARINT(nCommission));
		READWRITE(offerLinks);
		READWRITE(aliasName);
		READWRITE(vchPubKey);
		READWRITE(vchCert);
		READWRITE(bPrivate);
		
		
	)
	float GetPrice(const COfferLinkWhitelistEntry& entry=COfferLinkWhitelistEntry()){
		double price = nPrice;
		if(!entry.IsNull())
		{
			double discountPct = entry.nDiscountPct;
			if(entry.nDiscountPct < -99 || entry.nDiscountPct > 99)
				discountPct = 0;
			double fDiscount = (double)discountPct / 100.0;
			price -= fDiscount*price;

		}
		// add commission
		double fCommission = (double)nCommission / 100.0;
		price = price + price*fCommission;
		return price;
	}
	void SetPrice(float price){
		nPrice = price;
	}
    bool GetAcceptByHash(std::vector<unsigned char> ahash, COfferAccept &ca) {
    	for(unsigned int i=0;i<accepts.size();i++) {
    		if(accepts[i].vchRand == ahash) {
    			ca = accepts[i];
    			return true;
    		}
    	}
    	return false;
    }

    void PutOfferAccept(COfferAccept &theOA) {
    	for(unsigned int i=0;i<accepts.size();i++) {
    		COfferAccept oa = accepts[i];
    		if(theOA.vchRand == oa.vchRand) {
    			accepts[i] = theOA;
    			return;
    		}
    	}
    	accepts.push_back(theOA);
    }

    void PutToOfferList(std::vector<COffer> &offerList) {
        for(unsigned int i=0;i<offerList.size();i++) {
            COffer o = offerList[i];
            if(o.nHeight == nHeight) {
                offerList[i] = *this;
                return;
            }
        }
        offerList.push_back(*this);
    }

    bool GetOfferFromList(const std::vector<COffer> &offerList) {
        if(offerList.size() == 0) return false;
        for(unsigned int i=0;i<offerList.size();i++) {
            COffer o = offerList[i];
            if(o.nHeight == nHeight) {
                *this = offerList[i];
                return true;
            }
        }
        *this = offerList.back();
        return false;
    }

    friend bool operator==(const COffer &a, const COffer &b) {
        return (
           a.vchRand == b.vchRand
        && a.sCategory==b.sCategory
        && a.sTitle == b.sTitle 
        && a.sDescription == b.sDescription 
        && a.nPrice == b.nPrice 
        && a.nQty == b.nQty 
        && a.txHash == b.txHash
        && a.nHeight == b.nHeight
        && a.accepts == b.accepts
		&& a.vchLinkOffer == b.vchLinkOffer
		&& a.linkWhitelist == b.linkWhitelist
		&& a.sCurrencyCode == b.sCurrencyCode
		&& a.nCommission == b.nCommission
		&& a.vchPubKey == b.vchPubKey
		&& a.aliasName == b.aliasName
		&& a.vchCert == b.vchCert
		&& a.bPrivate == b.bPrivate
		
        );
    }

    COffer operator=(const COffer &b) {
    	vchRand = b.vchRand;
        sCategory = b.sCategory;
        sTitle = b.sTitle;
        sDescription = b.sDescription;
        nPrice = b.nPrice;
        nQty = b.nQty;
        txHash = b.txHash;
        nHeight = b.nHeight;
        accepts = b.accepts;
		vchLinkOffer = b.vchLinkOffer;
		linkWhitelist = b.linkWhitelist;
		sCurrencyCode = b.sCurrencyCode;
		offerLinks = b.offerLinks;
		nCommission = b.nCommission;
		vchPubKey = b.vchPubKey;
		aliasName = b.aliasName;
		vchCert = b.vchCert;
		bPrivate = b.bPrivate;
        return *this;
    }

    friend bool operator!=(const COffer &a, const COffer &b) {
        return !(a == b);
    }
    
    void SetNull() { nHeight = nPrice = nQty = 0; txHash = 0; bPrivate = false; aliasName = ""; accepts.clear(); vchRand.clear(); sTitle.clear(); sDescription.clear();vchLinkOffer.clear();linkWhitelist.SetNull();sCurrencyCode.clear();offerLinks.clear();nCommission=0;vchPubKey.clear();vchCert.clear();}
    bool IsNull() const { return (txHash == 0 && nHeight == 0 && nPrice == 0 && nQty == 0 &&  linkWhitelist.IsNull() && offerLinks.empty() && nCommission == 0 && bPrivate == false); }

    bool UnserializeFromTx(const CTransaction &tx);
    std::string SerializeToString();
};


class COfferDB : public CLevelDB {
public:
	COfferDB(size_t nCacheSize, bool fMemory, bool fWipe) : CLevelDB(GetDataDir() / "offers", nCacheSize, fMemory, fWipe) {}

	bool WriteOffer(const std::vector<unsigned char>& name, std::vector<COffer>& vtxPos) {
		return Write(make_pair(std::string("offeri"), name), vtxPos);
	}

	bool EraseOffer(const std::vector<unsigned char>& name) {
	    return Erase(make_pair(std::string("offeri"), name));
	}

	bool ReadOffer(const std::vector<unsigned char>& name, std::vector<COffer>& vtxPos) {
		return Read(make_pair(std::string("offeri"), name), vtxPos);
	}

	bool ExistsOffer(const std::vector<unsigned char>& name) {
	    return Exists(make_pair(std::string("offeri"), name));
	}

	bool WriteOfferAccept(const std::vector<unsigned char>& name, std::vector<unsigned char>& vchValue) {
		return Write(make_pair(std::string("offera"), name), vchValue);
	}

	bool EraseOfferAccept(const std::vector<unsigned char>& name) {
	    return Erase(make_pair(std::string("offera"), name));
	}

	bool ReadOfferAccept(const std::vector<unsigned char>& name, std::vector<unsigned char>& vchValue) {
		return Read(make_pair(std::string("offera"), name), vchValue);
	}

	bool ExistsOfferAccept(const std::vector<unsigned char>& name) {
	    return Exists(make_pair(std::string("offera"), name));
	}
    bool WriteOfferIndex(std::vector<std::vector<unsigned char> >& vtxPos) {
        return Write(make_pair(std::string("offera"), std::string("offerndx")), vtxPos);
    }

    bool ReadOfferIndex(std::vector<std::vector<unsigned char> >& vtxPos) {
        return Read(make_pair(std::string("offera"), std::string("offerndx")), vtxPos);
    }

    bool ScanOffers(
            const std::vector<unsigned char>& vchName,
            unsigned int nMax,
            std::vector<std::pair<std::vector<unsigned char>, COffer> >& offerScan);

    bool ReconstructOfferIndex(CBlockIndex *pindexRescan);
};

bool GetTxOfOffer(COfferDB& dbOffer, const std::vector<unsigned char> &vchOffer, COffer& txPos, CTransaction& tx);
#endif // OFFER_H
