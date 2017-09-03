#ifndef SIMPLEGAMEHANDLER_H
#define SIMPLEGAMEHANDLER_H

#include <QObject>
#include <QDebug>

class SimpleGameHandler : public QObject
{
    Q_OBJECT
public:
    explicit SimpleGameHandler(QObject *parent = nullptr);

    Q_INVOKABLE QString key_pressed(QString);
    Q_INVOKABLE QString key_released(QString);

signals:

public slots:
};

#endif // SIMPLEGAMEHANDLER_H
