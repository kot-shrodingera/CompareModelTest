#pragma once

#include <QAbstractTableModel>

class CompareModel : public QAbstractTableModel
{
  Q_OBJECT
public:
  CompareModel(QList<QAbstractTableModel*> tableModelList,
               QObject *parent = nullptr);

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  QVariant headerData(int section,
                      Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;

  void RunComparition();

private:

  QList<QList<QString>> m_parameterList = {{"Value", "Value"}};
  QList<QPair<QString, QVector<int>>> m_pointList;
  //          kks       rows
  QMap<QString, int> m_kksToIndex;

  QList<QAbstractTableModel*> m_tableModelList;
};
