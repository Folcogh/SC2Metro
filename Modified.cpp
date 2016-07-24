#include "Modified.hpp"

Modified::Modified()
    : modified(false)
{
}

bool Modified::isModified() const
{
    return this->modified;
}

void Modified::setModified(bool modified)
{
    emit changed(modified);
    this->modified = modified;
}
