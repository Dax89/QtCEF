#include "chromiummessageevent.h"

const QEvent::Type ChromiumMessageEvent::MessageEventType = static_cast<QEvent::Type>(QEvent::registerEventType());

ChromiumMessageEvent::ChromiumMessageEvent(const QString &name, const QVariantList &args): QEvent(ChromiumMessageEvent::MessageEventType), _name(name), _args(args)
{

}

ChromiumMessageEvent::~ChromiumMessageEvent()
{

}

QString ChromiumMessageEvent::name() const
{
    return this->_name;
}

QVariantList ChromiumMessageEvent::args() const
{
    return this->_args;
}

