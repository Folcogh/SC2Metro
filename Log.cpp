#include "Log.hpp"
#include <QDate>
#include <QTime>
#include <QObject>
#include <QMessageBox>

Log* Log::log = nullptr; // Instance pointer
bool Log::alive = true; // Avoid to show an error dialog every time the log file fails to be opened

Log::Log()
{
    this->file.setFileName(QString(LOG_FILENAME));
    if (!this->file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(nullptr, QObject::tr("Warning"), QObject::tr("Couldn't open the log file: %1").arg(LOG_FILENAME), QMessageBox::Ok);
        this->alive = false;
        return;
    }
    this->stream.setDevice(&this->file);
    this->stream << QObject::tr("=== Log started: ") << QDate::currentDate().toString() << " " << QTime::currentTime().toString() << QString(" ===");
    endl(this->stream);
}

Log::~Log()
{
    if (this->log != nullptr) {
        this->stream << QObject::tr("================== End of log ==================");
        endl(this->stream);
        endl(this->stream);

        this->alive = true;
        this->log = nullptr;
    }
}

Log* Log::instance()
{
    if (alive && (log == nullptr)) {
        log = new Log;
    }
    return log;
}

void Log::write(QString message)
{
    if (this->log == nullptr) {
        return;
    }
    this->stream << message;
    endl(this->stream);
}

void Log::newLine()
{
    if (this->log == nullptr) {
        return;
    }
    endl(this->stream);
}
