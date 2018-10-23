#ifndef QRCODER_H
#define QRCODER_H

#include <QImage>
#include <QString>

class QRCoder
{
public:
    QRCoder();

    static QImage encoder(const QString& data);
};

#endif // QRCODER_H
