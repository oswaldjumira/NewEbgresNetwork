//
// Generated file, do not edit! Created by opp_msgc 4.1 from EbgresApplLayerMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "EbgresApplLayerMessage_m.h"

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




Register_Class(DataApplMessage);

DataApplMessage::DataApplMessage() : cObject()
{
    for (unsigned int i=0; i<1024; i++)
        this->content_var[i] = 0;
}

DataApplMessage::DataApplMessage(const DataApplMessage& other) : cObject()
{
    operator=(other);
}

DataApplMessage::~DataApplMessage()
{
}

DataApplMessage& DataApplMessage::operator=(const DataApplMessage& other)
{
    if (this==&other) return *this;
    cObject::operator=(other);
    for (unsigned int i=0; i<1024; i++)
        this->content_var[i] = other.content_var[i];
    return *this;
}

void DataApplMessage::parsimPack(cCommBuffer *b)
{
    doPacking(b,this->content_var,1024);
}

void DataApplMessage::parsimUnpack(cCommBuffer *b)
{
    doUnpacking(b,this->content_var,1024);
}

unsigned int DataApplMessage::getContentArraySize() const
{
    return 1024;
}

char DataApplMessage::getContent(unsigned int k) const
{
    if (k>=1024) throw cRuntimeError("Array of size 1024 indexed by %lu", (unsigned long)k);
    return content_var[k];
}

void DataApplMessage::setContent(unsigned int k, char content_var)
{
    if (k>=1024) throw cRuntimeError("Array of size 1024 indexed by %lu", (unsigned long)k);
    this->content_var[k] = content_var;
}

class DataApplMessageDescriptor : public cClassDescriptor
{
  public:
    DataApplMessageDescriptor();
    virtual ~DataApplMessageDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(DataApplMessageDescriptor);

DataApplMessageDescriptor::DataApplMessageDescriptor() : cClassDescriptor("DataApplMessage", "cObject")
{
}

DataApplMessageDescriptor::~DataApplMessageDescriptor()
{
}

bool DataApplMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<DataApplMessage *>(obj)!=NULL;
}

const char *DataApplMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int DataApplMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int DataApplMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *DataApplMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "content",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int DataApplMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "content")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *DataApplMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "char",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *DataApplMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int DataApplMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    DataApplMessage *pp = (DataApplMessage *)object; (void)pp;
    switch (field) {
        case 0: return 1024;
        default: return 0;
    }
}

std::string DataApplMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    DataApplMessage *pp = (DataApplMessage *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getContent(i));
        default: return "";
    }
}

bool DataApplMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    DataApplMessage *pp = (DataApplMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setContent(i,string2long(value)); return true;
        default: return false;
    }
}

const char *DataApplMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
    };
    return (field>=0 && field<1) ? fieldStructNames[field] : NULL;
}

void *DataApplMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    DataApplMessage *pp = (DataApplMessage *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(EbgresApplMessage);

EbgresApplMessage::EbgresApplMessage(const char *name, int kind) : ApplPkt(name,kind)
{
}

EbgresApplMessage::EbgresApplMessage(const EbgresApplMessage& other) : ApplPkt()
{
    setName(other.getName());
    operator=(other);
}

EbgresApplMessage::~EbgresApplMessage()
{
}

EbgresApplMessage& EbgresApplMessage::operator=(const EbgresApplMessage& other)
{
    if (this==&other) return *this;
    ApplPkt::operator=(other);
    for (unsigned int i=0; i<1; i++)
        this->dataApplMessage_var[i] = other.dataApplMessage_var[i];
    return *this;
}

void EbgresApplMessage::parsimPack(cCommBuffer *b)
{
    ApplPkt::parsimPack(b);
    doPacking(b,this->dataApplMessage_var,1);
}

void EbgresApplMessage::parsimUnpack(cCommBuffer *b)
{
    ApplPkt::parsimUnpack(b);
    doUnpacking(b,this->dataApplMessage_var,1);
}

unsigned int EbgresApplMessage::getDataApplMessageArraySize() const
{
    return 1;
}

DataApplMessage& EbgresApplMessage::getDataApplMessage(unsigned int k)
{
    if (k>=1) throw cRuntimeError("Array of size 1 indexed by %lu", (unsigned long)k);
    return dataApplMessage_var[k];
}

void EbgresApplMessage::setDataApplMessage(unsigned int k, const DataApplMessage& dataApplMessage_var)
{
    if (k>=1) throw cRuntimeError("Array of size 1 indexed by %lu", (unsigned long)k);
    this->dataApplMessage_var[k] = dataApplMessage_var;
}

class EbgresApplMessageDescriptor : public cClassDescriptor
{
  public:
    EbgresApplMessageDescriptor();
    virtual ~EbgresApplMessageDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(EbgresApplMessageDescriptor);

EbgresApplMessageDescriptor::EbgresApplMessageDescriptor() : cClassDescriptor("EbgresApplMessage", "ApplPkt")
{
}

EbgresApplMessageDescriptor::~EbgresApplMessageDescriptor()
{
}

bool EbgresApplMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<EbgresApplMessage *>(obj)!=NULL;
}

const char *EbgresApplMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int EbgresApplMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int EbgresApplMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISCOBJECT,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *EbgresApplMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "dataApplMessage",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int EbgresApplMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataApplMessage")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *EbgresApplMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "DataApplMessage",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *EbgresApplMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int EbgresApplMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    EbgresApplMessage *pp = (EbgresApplMessage *)object; (void)pp;
    switch (field) {
        case 0: return 1;
        default: return 0;
    }
}

std::string EbgresApplMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    EbgresApplMessage *pp = (EbgresApplMessage *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getDataApplMessage(i); return out.str();}
        default: return "";
    }
}

bool EbgresApplMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    EbgresApplMessage *pp = (EbgresApplMessage *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *EbgresApplMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        "DataApplMessage",
    };
    return (field>=0 && field<1) ? fieldStructNames[field] : NULL;
}

void *EbgresApplMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    EbgresApplMessage *pp = (EbgresApplMessage *)object; (void)pp;
    switch (field) {
        case 0: return (void *)static_cast<cObject *>(&pp->getDataApplMessage(i)); break;
        default: return NULL;
    }
}


