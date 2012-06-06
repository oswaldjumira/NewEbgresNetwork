//
// Generated file, do not edit! Created by opp_msgc 4.1 from EbgresNetwMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "EbgresNetwMessage_m.h"

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




Register_Class(SelectMessage);

SelectMessage::SelectMessage() : cObject()
{
    this->selectNodeAddress_var = 0;
}

SelectMessage::SelectMessage(const SelectMessage& other) : cObject()
{
    operator=(other);
}

SelectMessage::~SelectMessage()
{
}

SelectMessage& SelectMessage::operator=(const SelectMessage& other)
{
    if (this==&other) return *this;
    cObject::operator=(other);
    this->selectNodeAddress_var = other.selectNodeAddress_var;
    this->selectNodePos_var = other.selectNodePos_var;
    return *this;
}

void SelectMessage::parsimPack(cCommBuffer *b)
{
    doPacking(b,this->selectNodeAddress_var);
    doPacking(b,this->selectNodePos_var);
}

void SelectMessage::parsimUnpack(cCommBuffer *b)
{
    doUnpacking(b,this->selectNodeAddress_var);
    doUnpacking(b,this->selectNodePos_var);
}

int SelectMessage::getSelectNodeAddress() const
{
    return selectNodeAddress_var;
}

void SelectMessage::setSelectNodeAddress(int selectNodeAddress_var)
{
    this->selectNodeAddress_var = selectNodeAddress_var;
}

Coord& SelectMessage::getSelectNodePos()
{
    return selectNodePos_var;
}

void SelectMessage::setSelectNodePos(const Coord& selectNodePos_var)
{
    this->selectNodePos_var = selectNodePos_var;
}

class SelectMessageDescriptor : public cClassDescriptor
{
  public:
    SelectMessageDescriptor();
    virtual ~SelectMessageDescriptor();

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

Register_ClassDescriptor(SelectMessageDescriptor);

SelectMessageDescriptor::SelectMessageDescriptor() : cClassDescriptor("SelectMessage", "cObject")
{
}

SelectMessageDescriptor::~SelectMessageDescriptor()
{
}

bool SelectMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<SelectMessage *>(obj)!=NULL;
}

const char *SelectMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int SelectMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int SelectMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *SelectMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "selectNodeAddress",
        "selectNodePos",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int SelectMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "selectNodeAddress")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "selectNodePos")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *SelectMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "Coord",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *SelectMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int SelectMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    SelectMessage *pp = (SelectMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string SelectMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    SelectMessage *pp = (SelectMessage *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getSelectNodeAddress());
        case 1: {std::stringstream out; out << pp->getSelectNodePos(); return out.str();}
        default: return "";
    }
}

bool SelectMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    SelectMessage *pp = (SelectMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setSelectNodeAddress(string2long(value)); return true;
        default: return false;
    }
}

const char *SelectMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        "Coord",
    };
    return (field>=0 && field<2) ? fieldStructNames[field] : NULL;
}

void *SelectMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    SelectMessage *pp = (SelectMessage *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getSelectNodePos()); break;
        default: return NULL;
    }
}

Register_Class(DataMessage);

DataMessage::DataMessage() : cObject()
{
    this->residualEnergySender_var = 0;
}

DataMessage::DataMessage(const DataMessage& other) : cObject()
{
    operator=(other);
}

DataMessage::~DataMessage()
{
}

DataMessage& DataMessage::operator=(const DataMessage& other)
{
    if (this==&other) return *this;
    cObject::operator=(other);
    this->destinationPos_var = other.destinationPos_var;
    this->sourcePos_var = other.sourcePos_var;
    this->idealPos_var = other.idealPos_var;
    this->residualEnergySender_var = other.residualEnergySender_var;
    return *this;
}

void DataMessage::parsimPack(cCommBuffer *b)
{
    doPacking(b,this->destinationPos_var);
    doPacking(b,this->sourcePos_var);
    doPacking(b,this->idealPos_var);
    doPacking(b,this->residualEnergySender_var);
}

void DataMessage::parsimUnpack(cCommBuffer *b)
{
    doUnpacking(b,this->destinationPos_var);
    doUnpacking(b,this->sourcePos_var);
    doUnpacking(b,this->idealPos_var);
    doUnpacking(b,this->residualEnergySender_var);
}

Coord& DataMessage::getDestinationPos()
{
    return destinationPos_var;
}

void DataMessage::setDestinationPos(const Coord& destinationPos_var)
{
    this->destinationPos_var = destinationPos_var;
}

Coord& DataMessage::getSourcePos()
{
    return sourcePos_var;
}

void DataMessage::setSourcePos(const Coord& sourcePos_var)
{
    this->sourcePos_var = sourcePos_var;
}

Coord& DataMessage::getIdealPos()
{
    return idealPos_var;
}

void DataMessage::setIdealPos(const Coord& idealPos_var)
{
    this->idealPos_var = idealPos_var;
}

double DataMessage::getResidualEnergySender() const
{
    return residualEnergySender_var;
}

void DataMessage::setResidualEnergySender(double residualEnergySender_var)
{
    this->residualEnergySender_var = residualEnergySender_var;
}

class DataMessageDescriptor : public cClassDescriptor
{
  public:
    DataMessageDescriptor();
    virtual ~DataMessageDescriptor();

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

Register_ClassDescriptor(DataMessageDescriptor);

DataMessageDescriptor::DataMessageDescriptor() : cClassDescriptor("DataMessage", "cObject")
{
}

DataMessageDescriptor::~DataMessageDescriptor()
{
}

bool DataMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<DataMessage *>(obj)!=NULL;
}

const char *DataMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int DataMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int DataMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *DataMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "destinationPos",
        "sourcePos",
        "idealPos",
        "residualEnergySender",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int DataMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationPos")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourcePos")==0) return base+1;
    if (fieldName[0]=='i' && strcmp(fieldName, "idealPos")==0) return base+2;
    if (fieldName[0]=='r' && strcmp(fieldName, "residualEnergySender")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *DataMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "Coord",
        "Coord",
        "Coord",
        "double",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *DataMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int DataMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    DataMessage *pp = (DataMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string DataMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    DataMessage *pp = (DataMessage *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getDestinationPos(); return out.str();}
        case 1: {std::stringstream out; out << pp->getSourcePos(); return out.str();}
        case 2: {std::stringstream out; out << pp->getIdealPos(); return out.str();}
        case 3: return double2string(pp->getResidualEnergySender());
        default: return "";
    }
}

bool DataMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    DataMessage *pp = (DataMessage *)object; (void)pp;
    switch (field) {
        case 3: pp->setResidualEnergySender(string2double(value)); return true;
        default: return false;
    }
}

const char *DataMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        "Coord",
        "Coord",
        "Coord",
        NULL,
    };
    return (field>=0 && field<4) ? fieldStructNames[field] : NULL;
}

void *DataMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    DataMessage *pp = (DataMessage *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getDestinationPos()); break;
        case 1: return (void *)(&pp->getSourcePos()); break;
        case 2: return (void *)(&pp->getIdealPos()); break;
        default: return NULL;
    }
}

Register_Class(AckMessage);

AckMessage::AckMessage() : cObject()
{
    this->intermediateNodeAddress_var = 0;
    this->residualEnergySender_var = 0;
}

AckMessage::AckMessage(const AckMessage& other) : cObject()
{
    operator=(other);
}

AckMessage::~AckMessage()
{
}

AckMessage& AckMessage::operator=(const AckMessage& other)
{
    if (this==&other) return *this;
    cObject::operator=(other);
    this->intermediateNodeAddress_var = other.intermediateNodeAddress_var;
    this->intermediatePos_var = other.intermediatePos_var;
    this->residualEnergySender_var = other.residualEnergySender_var;
    return *this;
}

void AckMessage::parsimPack(cCommBuffer *b)
{
    doPacking(b,this->intermediateNodeAddress_var);
    doPacking(b,this->intermediatePos_var);
    doPacking(b,this->residualEnergySender_var);
}

void AckMessage::parsimUnpack(cCommBuffer *b)
{
    doUnpacking(b,this->intermediateNodeAddress_var);
    doUnpacking(b,this->intermediatePos_var);
    doUnpacking(b,this->residualEnergySender_var);
}

int AckMessage::getIntermediateNodeAddress() const
{
    return intermediateNodeAddress_var;
}

void AckMessage::setIntermediateNodeAddress(int intermediateNodeAddress_var)
{
    this->intermediateNodeAddress_var = intermediateNodeAddress_var;
}

Coord& AckMessage::getIntermediatePos()
{
    return intermediatePos_var;
}

void AckMessage::setIntermediatePos(const Coord& intermediatePos_var)
{
    this->intermediatePos_var = intermediatePos_var;
}

double AckMessage::getResidualEnergySender() const
{
    return residualEnergySender_var;
}

void AckMessage::setResidualEnergySender(double residualEnergySender_var)
{
    this->residualEnergySender_var = residualEnergySender_var;
}

class AckMessageDescriptor : public cClassDescriptor
{
  public:
    AckMessageDescriptor();
    virtual ~AckMessageDescriptor();

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

Register_ClassDescriptor(AckMessageDescriptor);

AckMessageDescriptor::AckMessageDescriptor() : cClassDescriptor("AckMessage", "cObject")
{
}

AckMessageDescriptor::~AckMessageDescriptor()
{
}

bool AckMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<AckMessage *>(obj)!=NULL;
}

const char *AckMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int AckMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int AckMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *AckMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "intermediateNodeAddress",
        "intermediatePos",
        "residualEnergySender",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int AckMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "intermediateNodeAddress")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "intermediatePos")==0) return base+1;
    if (fieldName[0]=='r' && strcmp(fieldName, "residualEnergySender")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *AckMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "Coord",
        "double",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *AckMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int AckMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    AckMessage *pp = (AckMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string AckMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    AckMessage *pp = (AckMessage *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getIntermediateNodeAddress());
        case 1: {std::stringstream out; out << pp->getIntermediatePos(); return out.str();}
        case 2: return double2string(pp->getResidualEnergySender());
        default: return "";
    }
}

bool AckMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    AckMessage *pp = (AckMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setIntermediateNodeAddress(string2long(value)); return true;
        case 2: pp->setResidualEnergySender(string2double(value)); return true;
        default: return false;
    }
}

const char *AckMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        "Coord",
        NULL,
    };
    return (field>=0 && field<3) ? fieldStructNames[field] : NULL;
}

void *AckMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    AckMessage *pp = (AckMessage *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getIntermediatePos()); break;
        default: return NULL;
    }
}

Register_Class(AnalysisData);

AnalysisData::AnalysisData() : cObject()
{
    routeNodes_arraysize = 0;
    this->routeNodes_var = 0;
}

AnalysisData::AnalysisData(const AnalysisData& other) : cObject()
{
    routeNodes_arraysize = 0;
    this->routeNodes_var = 0;
    operator=(other);
}

AnalysisData::~AnalysisData()
{
    delete [] routeNodes_var;
}

AnalysisData& AnalysisData::operator=(const AnalysisData& other)
{
    if (this==&other) return *this;
    cObject::operator=(other);
    delete [] this->routeNodes_var;
    this->routeNodes_var = (other.routeNodes_arraysize==0) ? NULL : new int[other.routeNodes_arraysize];
    routeNodes_arraysize = other.routeNodes_arraysize;
    for (unsigned int i=0; i<routeNodes_arraysize; i++)
        this->routeNodes_var[i] = other.routeNodes_var[i];
    return *this;
}

void AnalysisData::parsimPack(cCommBuffer *b)
{
    b->pack(routeNodes_arraysize);
    doPacking(b,this->routeNodes_var,routeNodes_arraysize);
}

void AnalysisData::parsimUnpack(cCommBuffer *b)
{
    delete [] this->routeNodes_var;
    b->unpack(routeNodes_arraysize);
    if (routeNodes_arraysize==0) {
        this->routeNodes_var = 0;
    } else {
        this->routeNodes_var = new int[routeNodes_arraysize];
        doUnpacking(b,this->routeNodes_var,routeNodes_arraysize);
    }
}

void AnalysisData::setRouteNodesArraySize(unsigned int size)
{
    int *routeNodes_var2 = (size==0) ? NULL : new int[size];
    unsigned int sz = routeNodes_arraysize < size ? routeNodes_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        routeNodes_var2[i] = this->routeNodes_var[i];
    for (unsigned int i=sz; i<size; i++)
        routeNodes_var2[i] = 0;
    routeNodes_arraysize = size;
    delete [] this->routeNodes_var;
    this->routeNodes_var = routeNodes_var2;
}

unsigned int AnalysisData::getRouteNodesArraySize() const
{
    return routeNodes_arraysize;
}

int AnalysisData::getRouteNodes(unsigned int k) const
{
    if (k>=routeNodes_arraysize) throw cRuntimeError("Array of size %d indexed by %d", routeNodes_arraysize, k);
    return routeNodes_var[k];
}

void AnalysisData::setRouteNodes(unsigned int k, int routeNodes_var)
{
    if (k>=routeNodes_arraysize) throw cRuntimeError("Array of size %d indexed by %d", routeNodes_arraysize, k);
    this->routeNodes_var[k]=routeNodes_var;
}

class AnalysisDataDescriptor : public cClassDescriptor
{
  public:
    AnalysisDataDescriptor();
    virtual ~AnalysisDataDescriptor();

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

Register_ClassDescriptor(AnalysisDataDescriptor);

AnalysisDataDescriptor::AnalysisDataDescriptor() : cClassDescriptor("AnalysisData", "cObject")
{
}

AnalysisDataDescriptor::~AnalysisDataDescriptor()
{
}

bool AnalysisDataDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<AnalysisData *>(obj)!=NULL;
}

const char *AnalysisDataDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int AnalysisDataDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int AnalysisDataDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *AnalysisDataDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "routeNodes",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int AnalysisDataDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='r' && strcmp(fieldName, "routeNodes")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *AnalysisDataDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *AnalysisDataDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int AnalysisDataDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    AnalysisData *pp = (AnalysisData *)object; (void)pp;
    switch (field) {
        case 0: return pp->getRouteNodesArraySize();
        default: return 0;
    }
}

std::string AnalysisDataDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    AnalysisData *pp = (AnalysisData *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getRouteNodes(i));
        default: return "";
    }
}

bool AnalysisDataDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    AnalysisData *pp = (AnalysisData *)object; (void)pp;
    switch (field) {
        case 0: pp->setRouteNodes(i,string2long(value)); return true;
        default: return false;
    }
}

const char *AnalysisDataDescriptor::getFieldStructName(void *object, int field) const
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

void *AnalysisDataDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    AnalysisData *pp = (AnalysisData *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(EbgresNetwMessage);

EbgresNetwMessage::EbgresNetwMessage(const char *name, int kind) : NetwPkt(name,kind)
{
    this->type_var = 0;
    this->nextHopAddr_var = 0;
    this->receivedFromAddr_var = 0;
    this->dataMessageId_var = 0;
}

EbgresNetwMessage::EbgresNetwMessage(const EbgresNetwMessage& other) : NetwPkt()
{
    setName(other.getName());
    operator=(other);
}

EbgresNetwMessage::~EbgresNetwMessage()
{
}

EbgresNetwMessage& EbgresNetwMessage::operator=(const EbgresNetwMessage& other)
{
    if (this==&other) return *this;
    NetwPkt::operator=(other);
    this->type_var = other.type_var;
    this->nextHopAddr_var = other.nextHopAddr_var;
    this->receivedFromAddr_var = other.receivedFromAddr_var;
    this->dataMessageId_var = other.dataMessageId_var;
    for (unsigned int i=0; i<1; i++)
        this->selectMessage_var[i] = other.selectMessage_var[i];
    for (unsigned int i=0; i<1; i++)
        this->dataMessage_var[i] = other.dataMessage_var[i];
    for (unsigned int i=0; i<1; i++)
        this->AckMessage_var[i] = other.AckMessage_var[i];
    for (unsigned int i=0; i<1; i++)
        this->analysisData_var[i] = other.analysisData_var[i];
    return *this;
}

void EbgresNetwMessage::parsimPack(cCommBuffer *b)
{
    NetwPkt::parsimPack(b);
    doPacking(b,this->type_var);
    doPacking(b,this->nextHopAddr_var);
    doPacking(b,this->receivedFromAddr_var);
    doPacking(b,this->dataMessageId_var);
    doPacking(b,this->selectMessage_var,1);
    doPacking(b,this->dataMessage_var,1);
    doPacking(b,this->AckMessage_var,1);
    doPacking(b,this->analysisData_var,1);
}

void EbgresNetwMessage::parsimUnpack(cCommBuffer *b)
{
    NetwPkt::parsimUnpack(b);
    doUnpacking(b,this->type_var);
    doUnpacking(b,this->nextHopAddr_var);
    doUnpacking(b,this->receivedFromAddr_var);
    doUnpacking(b,this->dataMessageId_var);
    doUnpacking(b,this->selectMessage_var,1);
    doUnpacking(b,this->dataMessage_var,1);
    doUnpacking(b,this->AckMessage_var,1);
    doUnpacking(b,this->analysisData_var,1);
}

int EbgresNetwMessage::getType() const
{
    return type_var;
}

void EbgresNetwMessage::setType(int type_var)
{
    this->type_var = type_var;
}

int EbgresNetwMessage::getNextHopAddr() const
{
    return nextHopAddr_var;
}

void EbgresNetwMessage::setNextHopAddr(int nextHopAddr_var)
{
    this->nextHopAddr_var = nextHopAddr_var;
}

int EbgresNetwMessage::getReceivedFromAddr() const
{
    return receivedFromAddr_var;
}

void EbgresNetwMessage::setReceivedFromAddr(int receivedFromAddr_var)
{
    this->receivedFromAddr_var = receivedFromAddr_var;
}

int EbgresNetwMessage::getDataMessageId() const
{
    return dataMessageId_var;
}

void EbgresNetwMessage::setDataMessageId(int dataMessageId_var)
{
    this->dataMessageId_var = dataMessageId_var;
}

unsigned int EbgresNetwMessage::getSelectMessageArraySize() const
{
    return 1;
}

SelectMessage& EbgresNetwMessage::getSelectMessage(unsigned int k)
{
    if (k>=1) throw cRuntimeError("Array of size 1 indexed by %lu", (unsigned long)k);
    return selectMessage_var[k];
}

void EbgresNetwMessage::setSelectMessage(unsigned int k, const SelectMessage& selectMessage_var)
{
    if (k>=1) throw cRuntimeError("Array of size 1 indexed by %lu", (unsigned long)k);
    this->selectMessage_var[k] = selectMessage_var;
}

unsigned int EbgresNetwMessage::getDataMessageArraySize() const
{
    return 1;
}

DataMessage& EbgresNetwMessage::getDataMessage(unsigned int k)
{
    if (k>=1) throw cRuntimeError("Array of size 1 indexed by %lu", (unsigned long)k);
    return dataMessage_var[k];
}

void EbgresNetwMessage::setDataMessage(unsigned int k, const DataMessage& dataMessage_var)
{
    if (k>=1) throw cRuntimeError("Array of size 1 indexed by %lu", (unsigned long)k);
    this->dataMessage_var[k] = dataMessage_var;
}

unsigned int EbgresNetwMessage::getAckMessageArraySize() const
{
    return 1;
}

AckMessage& EbgresNetwMessage::getAckMessage(unsigned int k)
{
    if (k>=1) throw cRuntimeError("Array of size 1 indexed by %lu", (unsigned long)k);
    return AckMessage_var[k];
}

void EbgresNetwMessage::setAckMessage(unsigned int k, const AckMessage& AckMessage_var)
{
    if (k>=1) throw cRuntimeError("Array of size 1 indexed by %lu", (unsigned long)k);
    this->AckMessage_var[k] = AckMessage_var;
}

unsigned int EbgresNetwMessage::getAnalysisDataArraySize() const
{
    return 1;
}

AnalysisData& EbgresNetwMessage::getAnalysisData(unsigned int k)
{
    if (k>=1) throw cRuntimeError("Array of size 1 indexed by %lu", (unsigned long)k);
    return analysisData_var[k];
}

void EbgresNetwMessage::setAnalysisData(unsigned int k, const AnalysisData& analysisData_var)
{
    if (k>=1) throw cRuntimeError("Array of size 1 indexed by %lu", (unsigned long)k);
    this->analysisData_var[k] = analysisData_var;
}

class EbgresNetwMessageDescriptor : public cClassDescriptor
{
  public:
    EbgresNetwMessageDescriptor();
    virtual ~EbgresNetwMessageDescriptor();

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

Register_ClassDescriptor(EbgresNetwMessageDescriptor);

EbgresNetwMessageDescriptor::EbgresNetwMessageDescriptor() : cClassDescriptor("EbgresNetwMessage", "NetwPkt")
{
}

EbgresNetwMessageDescriptor::~EbgresNetwMessageDescriptor()
{
}

bool EbgresNetwMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<EbgresNetwMessage *>(obj)!=NULL;
}

const char *EbgresNetwMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int EbgresNetwMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount(object) : 8;
}

unsigned int EbgresNetwMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISCOBJECT,
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISCOBJECT,
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISCOBJECT,
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISCOBJECT,
    };
    return (field>=0 && field<8) ? fieldTypeFlags[field] : 0;
}

const char *EbgresNetwMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "type",
        "nextHopAddr",
        "receivedFromAddr",
        "dataMessageId",
        "selectMessage",
        "dataMessage",
        "AckMessage",
        "analysisData",
    };
    return (field>=0 && field<8) ? fieldNames[field] : NULL;
}

int EbgresNetwMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+0;
    if (fieldName[0]=='n' && strcmp(fieldName, "nextHopAddr")==0) return base+1;
    if (fieldName[0]=='r' && strcmp(fieldName, "receivedFromAddr")==0) return base+2;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataMessageId")==0) return base+3;
    if (fieldName[0]=='s' && strcmp(fieldName, "selectMessage")==0) return base+4;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataMessage")==0) return base+5;
    if (fieldName[0]=='A' && strcmp(fieldName, "AckMessage")==0) return base+6;
    if (fieldName[0]=='a' && strcmp(fieldName, "analysisData")==0) return base+7;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *EbgresNetwMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
        "int",
        "SelectMessage",
        "DataMessage",
        "AckMessage",
        "AnalysisData",
    };
    return (field>=0 && field<8) ? fieldTypeStrings[field] : NULL;
}

const char *EbgresNetwMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int EbgresNetwMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    EbgresNetwMessage *pp = (EbgresNetwMessage *)object; (void)pp;
    switch (field) {
        case 4: return 1;
        case 5: return 1;
        case 6: return 1;
        case 7: return 1;
        default: return 0;
    }
}

std::string EbgresNetwMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    EbgresNetwMessage *pp = (EbgresNetwMessage *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getType());
        case 1: return long2string(pp->getNextHopAddr());
        case 2: return long2string(pp->getReceivedFromAddr());
        case 3: return long2string(pp->getDataMessageId());
        case 4: {std::stringstream out; out << pp->getSelectMessage(i); return out.str();}
        case 5: {std::stringstream out; out << pp->getDataMessage(i); return out.str();}
        case 6: {std::stringstream out; out << pp->getAckMessage(i); return out.str();}
        case 7: {std::stringstream out; out << pp->getAnalysisData(i); return out.str();}
        default: return "";
    }
}

bool EbgresNetwMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    EbgresNetwMessage *pp = (EbgresNetwMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setType(string2long(value)); return true;
        case 1: pp->setNextHopAddr(string2long(value)); return true;
        case 2: pp->setReceivedFromAddr(string2long(value)); return true;
        case 3: pp->setDataMessageId(string2long(value)); return true;
        default: return false;
    }
}

const char *EbgresNetwMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
        NULL,
        "SelectMessage",
        "DataMessage",
        "AckMessage",
        "AnalysisData",
    };
    return (field>=0 && field<8) ? fieldStructNames[field] : NULL;
}

void *EbgresNetwMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    EbgresNetwMessage *pp = (EbgresNetwMessage *)object; (void)pp;
    switch (field) {
        case 4: return (void *)static_cast<cObject *>(&pp->getSelectMessage(i)); break;
        case 5: return (void *)static_cast<cObject *>(&pp->getDataMessage(i)); break;
        case 6: return (void *)static_cast<cObject *>(&pp->getAckMessage(i)); break;
        case 7: return (void *)static_cast<cObject *>(&pp->getAnalysisData(i)); break;
        default: return NULL;
    }
}


