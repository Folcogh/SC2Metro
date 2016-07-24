#ifndef MODIFIED_HPP
#define MODIFIED_HPP

#include <QObject>

class Modified: public QObject
{
        Q_OBJECT

    public:
        Modified();
        bool isModified();
        void setModified(bool modified);

    private:
        Q_DISABLE_COPY(Modified)
        bool modified;

    signals:
        void changed(bool modified);
};

#endif // MODIFIED_HPP
