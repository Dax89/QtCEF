#ifndef LOADREQUEST_H
#define LOADREQUEST_H

#include <QObject>
#include <QUrl>

class LoadRequest : public QObject
{
    Q_OBJECT

    Q_ENUMS(LoadStatus)

    Q_PROPERTY(QUrl url READ url)
    Q_PROPERTY(LoadRequest::LoadStatus loadStatus READ loadStatus)
    Q_PROPERTY(QString errorString READ errorString)
    Q_PROPERTY(QString errorDomain READ errorDomain)
    Q_PROPERTY(int errorCode READ errorCode)

    public:
        enum LoadStatus { LoadStartedStatus, LoadSucceededStatus, LoadFailedStatus };

    public:
        explicit LoadRequest(const QUrl& url, LoadRequest::LoadStatus loadstatus, QObject *parent = 0);
        explicit LoadRequest(const QUrl& url, LoadRequest::LoadStatus loadstatus, const QString& errorstring, const QString& errordomain, int errorcode, QObject *parent = 0);
        ~LoadRequest();

    public:
        const QUrl &url() const;
        LoadRequest::LoadStatus loadStatus() const;
        const QString& errorString();
        const QString& errorDomain();
        int errorCode() const;

    private:
        QUrl _url;
        LoadRequest::LoadStatus _loadstatus;
        QString _errorstring;
        QString _errordomain;
        int _errorcode;
};

#endif // LOADREQUEST_H
