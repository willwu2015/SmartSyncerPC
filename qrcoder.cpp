#include "qrcoder.h"

#include "QZXing.h"

QRCoder::QRCoder()
{

}

QImage QRCoder::encoder(const QString& data) {
    return QZXing::encodeData(data);
}
