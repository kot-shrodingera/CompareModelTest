#pragma once

#include <QAbstractTableModel>

class TableModel : public QAbstractTableModel
{
  Q_OBJECT
public:
  TableModel(QObject *parent = nullptr);

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  QVariant headerData(int section,
                      Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;

  void appendRow(const QString& first, const QString& second);

private:
  QVector<QVector<QString>> m_data;
};
