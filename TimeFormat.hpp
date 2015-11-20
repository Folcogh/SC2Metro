#ifndef TIMEFORMAT_HPP
#define TIMEFORMAT_HPP

#include <QChar>
#include <QString>

#define FORMAT_DURATION_mm_ss(seconds) QString("%1:%2").arg(seconds / 60, 2, 10, QChar('0')).arg(seconds % 60, 2, 10, QChar('0'))

#endif // TIMEFORMAT_HPP
