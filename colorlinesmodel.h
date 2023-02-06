#ifndef COLORLINESMODEL_H
#define COLORLINESMODEL_H

#include <QAbstractItemModel>
#include <QColor>

#include <array>
#include <vector>
#include <random>

struct Ball {
    QColor color;
    bool visible{false};
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
    Q_PROPERTY(int empty_cell READ empty_cell CONSTANT)

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
    int empty_cell() const;

    Q_INVOKABLE void reset();
    Q_INVOKABLE void spawn();
    Q_INVOKABLE void setChosenPosition(int row, int col);
    Q_INVOKABLE void moveElement(int row, int col);
    Q_INVOKABLE bool sequenceSearch();
    Q_INVOKABLE bool isChosePosition();

signals:
    void changeScope();
    void gameOver();

private:
    static constexpr int m_cols = 9;
    static constexpr int m_rows = 9;
    static constexpr int m_sequence = 5;
    static constexpr int m_number_colors = 4;
    static constexpr int m_number_spawning = 3;

    int m_chosen_row_element{-1};
    int m_chosen_col_element{-1};

    int m_scope{};
    int m_empty_cell;

    std::array<std::array<Ball, m_cols>, m_rows> m_board;

    std::vector<QColor> m_colors;

    static std::random_device rd;
    static std::default_random_engine generator;
    static std::uniform_int_distribution<int> distribution_cell;
    static std::uniform_int_distribution<int> distribution_color;

    bool isEmptyCell(int row, int col);
    bool rowSequenceSearch();
    bool colSequenceSearch();
};

#endif // COLORLINESMODEL_H
