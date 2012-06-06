//
// Generated file, do not edit! Created by opp_msgc 4.1 from EbgresApplLayerMessage.msg.
//

#ifndef _EBGRESAPPLLAYERMESSAGE_M_H_
#define _EBGRESAPPLLAYERMESSAGE_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0401
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif

// cplusplus {{
#include <ApplPkt_m.h>
// }}



/**
 * Class generated from <tt>EbgresApplLayerMessage.msg</tt> by opp_msgc.
 * <pre>
 * class DataApplMessage
 * {
 *     char	content[1024];
 * }
 * </pre>
 */
class DataApplMessage : public ::cObject
{
  protected:
    char content_var[1024];

    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const DataApplMessage&);

  public:
    DataApplMessage();
    DataApplMessage(const DataApplMessage& other);
    virtual ~DataApplMessage();
    DataApplMessage& operator=(const DataApplMessage& other);
    virtual DataApplMessage *dup() const {return new DataApplMessage(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual unsigned int getContentArraySize() const;
    virtual char getContent(unsigned int k) const;
    virtual void setContent(unsigned int k, char content_var);
};

inline void doPacking(cCommBuffer *b, DataApplMessage& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, DataApplMessage& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>EbgresApplLayerMessage.msg</tt> by opp_msgc.
 * <pre>
 * message EbgresApplMessage extends ApplPkt
 * {
 *     DataApplMessage dataApplMessage[1];
 * }
 * </pre>
 */
class EbgresApplMessage : public ::ApplPkt
{
  protected:
    ::DataApplMessage dataApplMessage_var[1];

    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const EbgresApplMessage&);

  public:
    EbgresApplMessage(const char *name=NULL, int kind=0);
    EbgresApplMessage(const EbgresApplMessage& other);
    virtual ~EbgresApplMessage();
    EbgresApplMessage& operator=(const EbgresApplMessage& other);
    virtual EbgresApplMessage *dup() const {return new EbgresApplMessage(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual unsigned int getDataApplMessageArraySize() const;
    virtual DataApplMessage& getDataApplMessage(unsigned int k);
    virtual const DataApplMessage& getDataApplMessage(unsigned int k) const {return const_cast<EbgresApplMessage*>(this)->getDataApplMessage(k);}
    virtual void setDataApplMessage(unsigned int k, const DataApplMessage& dataApplMessage_var);
};

inline void doPacking(cCommBuffer *b, EbgresApplMessage& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, EbgresApplMessage& obj) {obj.parsimUnpack(b);}


#endif // _EBGRESAPPLLAYERMESSAGE_M_H_
