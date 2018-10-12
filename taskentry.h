#ifndef TASKLISTENTRY_H
#define TASKLISTENTRY_H

#include <QObject>
#include <QString>
#include <QDate>
#include <QList>

//Tasks within the list
class TaskEntry : public QObject
{
    Q_OBJECT

    //Q_PROPERTY(QString name Read name Write setName NOTIFY nameChanged)
public:
    explicit TaskEntry(QObject *parent = nullptr);

    //Setters + Getters
    QString getName() const;
    void setName(const QString &value);

    QDate getDue() const;
    void setDue(const QDate &value);

    int getPercent() const;
    void setPercent(const int &value);

    int getDiff() const;
    void setDiff(const int &value);

signals:
    //Alert is made when a variable is updated
    void nameChanged(); //void <function>Changed()

public slots:

private:
    QString name;   //QT string type
    QDate due;      //QT date type
    int percent;    //importance of grade
    int diff;       //difficulty level scale 0-10

};
#endif // TASKLISTENTRY_H
