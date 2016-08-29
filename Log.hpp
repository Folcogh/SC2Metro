#ifndef LOG_HPP
#define LOG_HPP

#include <QFile>
#include <QTextStream>

#define LOG_FILENAME "SC2Metro_log.txt"

class Log
{
    public:
        static Log* instance();
        ~Log();
        void write(QString message);
        void newLine();

    private:
        static bool alive;
        static Log* log;
        Log();

        QFile file;
        QTextStream stream;
};

#endif // LOG_HPP
