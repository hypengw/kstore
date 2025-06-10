#include "meta_model/qtable_proxy_model.hpp"

namespace meta_model
{
QTableProxyModel::QTableProxyModel(QObject* parent): QAbstractProxyModel(parent) {}

auto QTableProxyModel::mapFromSource(const QModelIndex& sourceIndex) const -> QModelIndex {
    return index(sourceIndex.row(), sourceIndex.column());
}
auto QTableProxyModel::mapToSource(const QModelIndex& sourceIndex) const -> QModelIndex {
    return index(sourceIndex.row(), sourceIndex.column());
}
} // namespace meta_model

#include "meta_model/moc_qtable_proxy_model.cpp"