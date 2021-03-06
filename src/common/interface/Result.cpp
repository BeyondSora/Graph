#include "../_include/Result.h"
#include "../_include/Exception.h"

Result::Result (Type type, bool isSuccess)
: type_(type), isSuccess_(isSuccess)
// Do nothing
{
    if (isSuccess_) {
        switch (type_) {
            case ID_LIST:
                // Special handling for non-trvial union member idList_.
                new(&idList_) IdentityList();
                break;
            default:
                // No extra work needed for trivial union members.
                break;
        }
    }
}

Result::Result (const Result &rhs)
: type_(rhs.type_), isSuccess_(rhs.isSuccess_)
// Required for special handling of non-trivial union member idList_.
{
    if (isSuccess_) {
        switch (type_) {
            case BOOL:
                // Do nothing
                break;
            case ID:
                id_ = rhs.id_;
                break;
            case ID_LIST:
                // Special handling for non-trvial union member idList_.
                new(&idList_) IdentityList(rhs.idList_);
                break;
        }
    }
}

Result::~Result ()
// Special handling for non-trvial union members.
{
    if (type_ == ID_LIST && isSuccess_) {
        idList_.~IdentityList();
    }
}

inline
void Result::validate (Result::Type type) const
{
    if (type_ != type || !isSuccess_) {
        throw LogicExcept();
    }
}

Identity Result::id () const
{
    validate(ID);
    return id_;
}

void Result::setId (const Identity id)
{
    validate(ID);
    id_ = id;
}

IdentityList Result::idList () const
{
    validate(ID_LIST);
    return idList_;
}

void Result::setIdList (const IdentityList idList)
{
    validate(ID_LIST);
    idList_ = idList;
}
