#ifndef COLORLINESMODEL_H
#define COLORLINESMODEL_H

#include <QAbstractItemModel>
#include <QColor>

#include <array>
#include <vector>

struct Ball {
    QColor color;
    bool visible{true};
};

enum Role {
    kColorRole = Qt::UserRole,
    kVisibleRole
};

class ColorLinesModel : public QAbstractItemModel {
    Q_OBJECT

    Q_PROPERTY(int cols READ cols CONSTANT)
    Q_PROPERTY(int rows READ rows CONSTANT)
    Q_PROPERTY(int scope READ scope CONSTANT)

public:
    explicit ColorLinesModel(QObject *parent = nullptr);

    // Basic functionality:
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    QHash<int, QByteArray> roleNames() const override;

    static int cols();
    static int rows();
    int scope() const;

    Q_INVOKABLE void reset();
    Q_INVOKABLE void spawn();

private:
    static constexpr int m_cols = 9;
    static constexpr int m_rows = 9;
    static constexpr int m_number_colors = 4;
    static constexpr int m_number_spawning = 3;

    int m_scope{};
    int m_empty_cell;

    std::array<std::array<Ball, m_cols>, m_rows> m_board;

    std::vector<QColor> m_colors;
};

#endif // COLORLINESMODEL_H
