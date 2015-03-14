#ifndef CHROMIUMLOADER_H
#define CHROMIUMLOADER_H

#include <QObject>
#include <QCoreApplication>
#include <QStandardPaths>
#include <QTimer>
#include <QDir>
#include <QDebug>
#include "chromiumapplication.h"

class ChromiumContext: public QObject
{
    Q_OBJECT

    public:
        ChromiumContext(int argc, char *argv[], QObject* parent = 0);
        ~ChromiumContext();
        void doEvents();

    private:
        void initCEF(int argc, char *argv[]);
        void initCEFSettings();

    private slots:
        void processEvents();
        void stopEvents();

    public:
        static ChromiumContext* createInstance(int argc, char* argv[]);
        static ChromiumContext* instance();

    private:
        CefSettings _settings;
        CefRefPtr<ChromiumApplication> _application;

    public:
        static QString SubProcessPath;

    private:
        QTimer* _timer;
        static ChromiumContext* _context;
};

#endif // CHROMIUMLOADER_H
