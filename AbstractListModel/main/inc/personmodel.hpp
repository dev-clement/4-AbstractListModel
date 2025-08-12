#ifndef PERSONMODEL_HPP
#define PERSONMODEL_HPP

#include <QtQml>
#include <QObject>
#include <QAbstractListModel>
#include "person.hpp"

class PersonModel : public QAbstractListModel {
    Q_OBJECT
    QML_ELEMENT
    enum {
        NamesRole = Qt::UserRole + 1
        , FavoriteColorRole
        , AgeRole
    };
public:
    explicit PersonModel(QObject *po_parent = nullptr);

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &o_parent) const;
    QVariant data(const QModelIndex &o_idx, int i_role) const;
    QHash<int, QByteArray> roleNames() const;
    Qt::ItemFlags flags(const QModelIndex &o_idx) const;
    bool setData(const QModelIndex &o_idx, const QVariant &o_value, int i_role);

    // Function to edit the person's object
    bool changePersonsName(Person *po_person, const QString &o_name);
    bool changePersonsFavoriteColor(Person *po_person, const QString &o_favoriteColor);
    bool changePersonsAge(Person *po_person, int i_age);

    // Helper functions
    Q_INVOKABLE void addPerson();
    Q_INVOKABLE void addPerson(const QString &o_name, const QString &o_favoriteColor, int i_age);
    Q_INVOKABLE void addPerson(Person *po_person);
    Q_INVOKABLE void removeLastPerson();
    Q_INVOKABLE void removePerson(int i_idx);
signals:

private:
    QList<Person *> _o_persons;
};

#endif // PERSONMODEL_HPP
