#include "tablemodel.h"

TableModel::TableModel(QObject *parent)
  : QAbstractTableModel(parent)
{
}

int TableModel::rowCount([[maybe_unused]] const QModelIndex &parent) const
{
  return m_data.size();
}

int TableModel::columnCount([[maybe_unused]] const QModelIndex &parent) const
{
  return 2;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
  if (role == Qt::DisplayRole) {
    auto row = index.row();
    auto column = index.column();
    return m_data[row][column];
  }
  return QVariant();
}

QVariant TableModel::headerData(int section,
                                Qt::Orientation orientation,
                                int role) const
{
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
    if (section == 0) {
      return "KKS";
    } else {
      return "Value";
    }
  }
  return QAbstractTableModel::headerData(section, orientation, role);
}

void TableModel::appendRow(const QString &first, const QString &second)
{
  beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
  m_data.append({first, second});
  endInsertRows();
}
