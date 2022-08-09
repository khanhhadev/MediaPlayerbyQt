#ifndef MEDIACONTROL_H
#define MEDIACONTROL_H

#include <QObject>

class MediaControl : public QObject
{
    Q_OBJECT
public:
    explicit MediaControl(QObject *parent = nullptr);

signals:

};

#endif // MEDIACONTROL_H
