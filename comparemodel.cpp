#include "comparemodel.h"

#include <QDebug>

CompareModel::CompareModel(const QList<QAbstractTableModel*> &tableModelList,
                           QObject *parent)
  : QAbstractTableModel(parent),
    m_tableModelList(tableModelList)
{

}

int CompareModel::rowCount([[maybe_unused]] const QModelIndex &parent) const
{
  return m_pointList.size();
}

int CompareModel::columnCount([[maybe_unused]] const QModelIndex &parent) const
{
  return 1 + m_tableModelList.size() * m_parameterList.size();
}

QVariant CompareModel::headerData(int section,
                                  Qt::Orientation orientation,
                                  int role) const
{
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
    if (section == 0) {
      return "KKS";
    } else {
      int parameterNumber = (section - 1) / m_tableModelList.size();
      int modelNumber = (section - 1) % m_tableModelList.size();
      return m_parameterList[parameterNumber][modelNumber];
    }
  }
  return QAbstractTableModel::headerData(section, orientation, role);
}

QVariant CompareModel::data(const QModelIndex &index, int role) const
{
  if (role == Qt::DisplayRole) {
    auto row = index.row();
    auto column = index.column();
    if (column == 0) {
      return m_pointList[row]->first;
    } else {
      int parameterNumber = (column - 1) / m_tableModelList.size();
      int modelNumber = (column - 1) % m_tableModelList.size();
      auto model = m_tableModelList.at(modelNumber);
      auto modelRow = m_pointList[row]->second[modelNumber];
      auto modelColumn = [model]() {
        QStringList headers;
        for (int i = 0; i < model->columnCount(); ++i) {
          headers += model->headerData(i, Qt::Horizontal).toString();
        }
        return headers;
      }().indexOf(m_parameterList[parameterNumber][modelNumber]);
      auto modelIndex = model->index(modelRow, modelColumn);
      return model->data(modelIndex);
    }
  }
  return QVariant();
}

void CompareModel::RunComparition()
{
  beginResetModel();
  for(int modelNumber = 0;
      modelNumber < m_tableModelList.size();
      ++modelNumber) {
    auto model = m_tableModelList[modelNumber];
    auto rowCount = model->rowCount();
    for (int row = 0; row < rowCount; ++row) {
      auto kksIndex = model->index(row, 0);
      auto kks = model->data(kksIndex).toString();
      if (!m_pointByKks.contains(kks)) {
        auto data = new QPair<QString, QVector<int>>
            (kks, QVector<int>(m_tableModelList.size(), -1));
        m_pointList.append(data);
        m_pointList.last()->second[modelNumber] = row;
        m_pointByKks.insert(kks, m_pointList.last());
      } else {
        m_pointByKks[kks]->second[modelNumber] = row;
      }
    }
  }
  for (int i = 0; i < m_pointList.size();) {
    auto kks = m_pointList[i]->first;
    auto rows = m_pointList[i]->second;
    int existingRowsCount = 0;
    for (auto row : rows) {
      if (row != -1) {
        ++existingRowsCount;
      }
      if (existingRowsCount > 1) {
        ++i;
        goto skipRemove;
      }
    }
    m_pointList.removeOne(m_pointByKks[kks]);
    m_pointByKks.remove(kks);
    skipRemove:;
  }
  endResetModel();
}
