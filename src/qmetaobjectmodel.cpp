#include "meta_model/qmeta_list_model.hpp"

#include <QMetaProperty>

namespace meta_model
{

namespace detail
{
QMetaListModelBase::QMetaListModelBase(QObject* parent)
    : QMetaModelBase<QAbstractListModel>(parent), m_has_more(false) {}
QMetaListModelBase::~QMetaListModelBase() {}
auto QMetaListModelBase::hasMore() const -> bool { return m_has_more; }
void QMetaListModelBase::setHasMore(bool v) {
    if (m_has_more != v) {
        m_has_more = v;
        hasMoreChanged(v);
    }
}
bool QMetaListModelBase::canFetchMore(const QModelIndex&) const { return m_has_more; }
void QMetaListModelBase::fetchMore(const QModelIndex&) {
    setHasMore(false);
    reqFetchMore(rowCount());
}

} // namespace detail

void detail::update_role_names(QHash<int, QByteArray>& role_names, const QMetaObject& meta) {
    role_names.clear();

    auto roleIndex = Qt::UserRole + 1;
    for (auto i = 0; i < meta.propertyCount(); i++) {
        auto prop = meta.property(i);
        role_names.insert(roleIndex, prop.name());
        ++roleIndex;
    }
}

auto readOnGadget(const QVariant& obj, const char* name) -> QVariant {
    if (auto meta = obj.metaType().metaObject()) {
        if (auto p = meta->property(meta->indexOfProperty(name)); p.isValid()) {
            return p.readOnGadget(obj.constData());
        }
    }
    return {};
}
} // namespace meta_model