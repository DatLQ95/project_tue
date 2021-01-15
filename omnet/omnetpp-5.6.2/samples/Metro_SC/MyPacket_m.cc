//
// Generated file, do not edit! Created by nedtool 5.2 from MyPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include "MyPacket_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(MyPacket)

MyPacket::MyPacket(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->source = 0;
    this->destination = 0;
    this->arrivalAtBuffer = 0;
    this->Index = 0;
    this->flag = 0;
    for (unsigned int i=0; i<100; i++)
        this->dst_table[i] = 0;
    this->dst_intra = 0;
    this->dst_inter = 0;
    this->End2EndStartTime = 0;
    this->channel = 0;
    this->pri_latency = 0;
    this->pri_realiablity = 0;
    this->application_index = 0;
}

MyPacket::MyPacket(const MyPacket& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

MyPacket::~MyPacket()
{
}

MyPacket& MyPacket::operator=(const MyPacket& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void MyPacket::copy(const MyPacket& other)
{
    this->source = other.source;
    this->destination = other.destination;
    this->arrivalAtBuffer = other.arrivalAtBuffer;
    this->Index = other.Index;
    this->flag = other.flag;
    for (unsigned int i=0; i<100; i++)
        this->dst_table[i] = other.dst_table[i];
    this->dst_intra = other.dst_intra;
    this->dst_inter = other.dst_inter;
    this->End2EndStartTime = other.End2EndStartTime;
    this->channel = other.channel;
    this->pri_latency = other.pri_latency;
    this->pri_realiablity = other.pri_realiablity;
    this->application_index = other.application_index;
}

void MyPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->source);
    doParsimPacking(b,this->destination);
    doParsimPacking(b,this->arrivalAtBuffer);
    doParsimPacking(b,this->Index);
    doParsimPacking(b,this->flag);
    doParsimArrayPacking(b,this->dst_table,100);
    doParsimPacking(b,this->dst_intra);
    doParsimPacking(b,this->dst_inter);
    doParsimPacking(b,this->End2EndStartTime);
    doParsimPacking(b,this->channel);
    doParsimPacking(b,this->pri_latency);
    doParsimPacking(b,this->pri_realiablity);
    doParsimPacking(b,this->application_index);
}

void MyPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->source);
    doParsimUnpacking(b,this->destination);
    doParsimUnpacking(b,this->arrivalAtBuffer);
    doParsimUnpacking(b,this->Index);
    doParsimUnpacking(b,this->flag);
    doParsimArrayUnpacking(b,this->dst_table,100);
    doParsimUnpacking(b,this->dst_intra);
    doParsimUnpacking(b,this->dst_inter);
    doParsimUnpacking(b,this->End2EndStartTime);
    doParsimUnpacking(b,this->channel);
    doParsimUnpacking(b,this->pri_latency);
    doParsimUnpacking(b,this->pri_realiablity);
    doParsimUnpacking(b,this->application_index);
}

int MyPacket::getSource() const
{
    return this->source;
}

void MyPacket::setSource(int source)
{
    this->source = source;
}

int MyPacket::getDestination() const
{
    return this->destination;
}

void MyPacket::setDestination(int destination)
{
    this->destination = destination;
}

::omnetpp::simtime_t MyPacket::getArrivalAtBuffer() const
{
    return this->arrivalAtBuffer;
}

void MyPacket::setArrivalAtBuffer(::omnetpp::simtime_t arrivalAtBuffer)
{
    this->arrivalAtBuffer = arrivalAtBuffer;
}

int MyPacket::getIndex() const
{
    return this->Index;
}

void MyPacket::setIndex(int Index)
{
    this->Index = Index;
}

int MyPacket::getFlag() const
{
    return this->flag;
}

void MyPacket::setFlag(int flag)
{
    this->flag = flag;
}

unsigned int MyPacket::getDst_tableArraySize() const
{
    return 100;
}

int MyPacket::getDst_table(unsigned int k) const
{
    if (k>=100) throw omnetpp::cRuntimeError("Array of size 100 indexed by %lu", (unsigned long)k);
    return this->dst_table[k];
}

void MyPacket::setDst_table(unsigned int k, int dst_table)
{
    if (k>=100) throw omnetpp::cRuntimeError("Array of size 100 indexed by %lu", (unsigned long)k);
    this->dst_table[k] = dst_table;
}

int MyPacket::getDst_intra() const
{
    return this->dst_intra;
}

void MyPacket::setDst_intra(int dst_intra)
{
    this->dst_intra = dst_intra;
}

int MyPacket::getDst_inter() const
{
    return this->dst_inter;
}

void MyPacket::setDst_inter(int dst_inter)
{
    this->dst_inter = dst_inter;
}

double MyPacket::getEnd2EndStartTime() const
{
    return this->End2EndStartTime;
}

void MyPacket::setEnd2EndStartTime(double End2EndStartTime)
{
    this->End2EndStartTime = End2EndStartTime;
}

int MyPacket::getChannel() const
{
    return this->channel;
}

void MyPacket::setChannel(int channel)
{
    this->channel = channel;
}

int MyPacket::getPri_latency() const
{
    return this->pri_latency;
}

void MyPacket::setPri_latency(int pri_latency)
{
    this->pri_latency = pri_latency;
}

int MyPacket::getPri_realiablity() const
{
    return this->pri_realiablity;
}

void MyPacket::setPri_realiablity(int pri_realiablity)
{
    this->pri_realiablity = pri_realiablity;
}

int MyPacket::getApplication_index() const
{
    return this->application_index;
}

void MyPacket::setApplication_index(int application_index)
{
    this->application_index = application_index;
}

class MyPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    MyPacketDescriptor();
    virtual ~MyPacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(MyPacketDescriptor)

MyPacketDescriptor::MyPacketDescriptor() : omnetpp::cClassDescriptor("MyPacket", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

MyPacketDescriptor::~MyPacketDescriptor()
{
    delete[] propertynames;
}

bool MyPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<MyPacket *>(obj)!=nullptr;
}

const char **MyPacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *MyPacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int MyPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 13+basedesc->getFieldCount() : 13;
}

unsigned int MyPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<13) ? fieldTypeFlags[field] : 0;
}

const char *MyPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "source",
        "destination",
        "arrivalAtBuffer",
        "Index",
        "flag",
        "dst_table",
        "dst_intra",
        "dst_inter",
        "End2EndStartTime",
        "channel",
        "pri_latency",
        "pri_realiablity",
        "application_index",
    };
    return (field>=0 && field<13) ? fieldNames[field] : nullptr;
}

int MyPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "source")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destination")==0) return base+1;
    if (fieldName[0]=='a' && strcmp(fieldName, "arrivalAtBuffer")==0) return base+2;
    if (fieldName[0]=='I' && strcmp(fieldName, "Index")==0) return base+3;
    if (fieldName[0]=='f' && strcmp(fieldName, "flag")==0) return base+4;
    if (fieldName[0]=='d' && strcmp(fieldName, "dst_table")==0) return base+5;
    if (fieldName[0]=='d' && strcmp(fieldName, "dst_intra")==0) return base+6;
    if (fieldName[0]=='d' && strcmp(fieldName, "dst_inter")==0) return base+7;
    if (fieldName[0]=='E' && strcmp(fieldName, "End2EndStartTime")==0) return base+8;
    if (fieldName[0]=='c' && strcmp(fieldName, "channel")==0) return base+9;
    if (fieldName[0]=='p' && strcmp(fieldName, "pri_latency")==0) return base+10;
    if (fieldName[0]=='p' && strcmp(fieldName, "pri_realiablity")==0) return base+11;
    if (fieldName[0]=='a' && strcmp(fieldName, "application_index")==0) return base+12;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *MyPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "simtime_t",
        "int",
        "int",
        "int",
        "int",
        "int",
        "double",
        "int",
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<13) ? fieldTypeStrings[field] : nullptr;
}

const char **MyPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *MyPacketDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int MyPacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    MyPacket *pp = (MyPacket *)object; (void)pp;
    switch (field) {
        case 5: return 100;
        default: return 0;
    }
}

const char *MyPacketDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    MyPacket *pp = (MyPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string MyPacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    MyPacket *pp = (MyPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getSource());
        case 1: return long2string(pp->getDestination());
        case 2: return simtime2string(pp->getArrivalAtBuffer());
        case 3: return long2string(pp->getIndex());
        case 4: return long2string(pp->getFlag());
        case 5: return long2string(pp->getDst_table(i));
        case 6: return long2string(pp->getDst_intra());
        case 7: return long2string(pp->getDst_inter());
        case 8: return double2string(pp->getEnd2EndStartTime());
        case 9: return long2string(pp->getChannel());
        case 10: return long2string(pp->getPri_latency());
        case 11: return long2string(pp->getPri_realiablity());
        case 12: return long2string(pp->getApplication_index());
        default: return "";
    }
}

bool MyPacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    MyPacket *pp = (MyPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setSource(string2long(value)); return true;
        case 1: pp->setDestination(string2long(value)); return true;
        case 2: pp->setArrivalAtBuffer(string2simtime(value)); return true;
        case 3: pp->setIndex(string2long(value)); return true;
        case 4: pp->setFlag(string2long(value)); return true;
        case 5: pp->setDst_table(i,string2long(value)); return true;
        case 6: pp->setDst_intra(string2long(value)); return true;
        case 7: pp->setDst_inter(string2long(value)); return true;
        case 8: pp->setEnd2EndStartTime(string2double(value)); return true;
        case 9: pp->setChannel(string2long(value)); return true;
        case 10: pp->setPri_latency(string2long(value)); return true;
        case 11: pp->setPri_realiablity(string2long(value)); return true;
        case 12: pp->setApplication_index(string2long(value)); return true;
        default: return false;
    }
}

const char *MyPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *MyPacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    MyPacket *pp = (MyPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


