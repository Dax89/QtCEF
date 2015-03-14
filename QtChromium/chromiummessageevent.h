#ifndef CHROMIUMMESSAGEEVENT_H
#define CHROMIUMMESSAGEEVENT_H

#include <QEvent>
#include <QString>
#include <QVariant>

class ChromiumMessageEvent: public QEvent
{
    public:
        static const QEvent::Type MessageEventType;

    public:
        ChromiumMessageEvent(const QString& name, const QVariantList& args);
        ~ChromiumMessageEvent();

    public:
        QString name() const;
        QVariantList args() const;

    private:
        QString _name;
        QVariantList _args;
};

#endif // CHROMIUMMESSAGEEVENT_H
