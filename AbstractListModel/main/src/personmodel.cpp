#include <QDebug>
#include "personmodel.hpp"

PersonModel::PersonModel(QObject *po_parent)
    : QAbstractListModel{po_parent} {
    addPerson("Jamie Lannister", "red", 33);
    addPerson("Marry Lane", "cyan", 26);
    addPerson("Steve Moors", "yellow", 44);
    addPerson("Victor Trunk", "dodgerblue", 30);
    addPerson("Ariel Geeny", "blue", 33);
    addPerson("Knut Vikran", "lightblue", 26);
}

int PersonModel::rowCount(const QModelIndex &o_parent) const {
    Q_UNUSED(o_parent);
    return _o_persons.size();
}

QVariant PersonModel::data(const QModelIndex &o_idx, int i_role) const {
    if (o_idx.row() < 0 || o_idx.row() >= _o_persons.size()) {
        qDebug() << "Index passed to data is invalid: " << o_idx.row();
        return QVariant{};
    }

    Person *po_person = _o_persons[o_idx.row()];
    return i_role == NamesRole ? po_person->names()
            : i_role == FavoriteColorRole ? po_person->favoriteColor()
            : i_role == AgeRole ? po_person->age()
            : QVariant{};
}

QHash<int, QByteArray> PersonModel::roleNames() const {
    QHash<int, QByteArray> o_roles;
    o_roles[NamesRole] = "names";
    o_roles[FavoriteColorRole] = "favoriteColor";
    o_roles[AgeRole] = "age";
    return o_roles;
}

Qt::ItemFlags PersonModel::flags(const QModelIndex &o_idx) const {
    if (!o_idx.isValid()) {
        return Qt::NoItemFlags;
    }
    return Qt::ItemIsEditable;
}

bool PersonModel::setData(const QModelIndex &o_idx, const QVariant &o_value, int i_role) {
    if (o_idx.row() >= _o_persons.size() || o_idx.row() < 0) {
        return false;
    }
    Person *po_person = _o_persons.at(o_idx.row());
    bool b_somethingChanged{false};
    if (i_role == NamesRole) {
        b_somethingChanged = changePersonsName(po_person, o_value.toString());
    } else if (i_role == FavoriteColorRole) {
        b_somethingChanged = changePersonsFavoriteColor(po_person, o_value.toString());
    } else if (i_role == AgeRole) {
        b_somethingChanged = changePersonsAge(po_person, o_value.toInt());
    }
    if (b_somethingChanged) {
        emit dataChanged(o_idx, o_idx, QList<int>() << i_role);
    }
    return b_somethingChanged;
}

bool PersonModel::changePersonsName(Person *po_person, const QString &o_name) {
    if (po_person->names() == o_name) {
        return false;
    }
    po_person->setNames(o_name);
    return true;
}

bool PersonModel::changePersonsFavoriteColor(Person *po_person, const QString &o_favoriteColor) {
    if (po_person->favoriteColor() == o_favoriteColor) {
        return false;
    }
    po_person->setFavoriteColor(o_favoriteColor);
    return true;
}

bool PersonModel::changePersonsAge(Person *po_person, int i_age) {
    if (po_person->age() == i_age) {
        return false;
    }
    po_person->setAge(i_age);
    return true;
}

void PersonModel::addPerson() {
    Person *po_person = new Person("Name", "Favorite colour", 45, this);
    addPerson(po_person);
}

void PersonModel::addPerson(const QString &o_name, const QString &o_favoriteColor, int i_age) {
    Person *po_person = new Person(o_name, o_favoriteColor, i_age);
    addPerson(po_person);
}

void PersonModel::addPerson(Person *po_person) {
    const int i_idx = _o_persons.size();
    beginInsertRows(QModelIndex{}, i_idx, i_idx);
    _o_persons.append(po_person);
    endInsertRows();
}

void PersonModel::removeLastPerson() {
    removePerson(_o_persons.size() - 1);
}

void PersonModel::removePerson(int i_idx) {
    beginRemoveRows(QModelIndex{}, i_idx, i_idx);
    _o_persons.removeAt(i_idx);
    endRemoveRows();
}
