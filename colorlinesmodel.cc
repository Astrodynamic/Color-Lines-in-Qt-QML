#include "colorlinesmodel.h"

ColorLinesModel::ColorLinesModel(QObject *parent)
    : QAbstractItemModel(parent)
    , m_empty_cell{m_cols * m_rows}
{
    m_colors.push_back(QColor(14, 94, 78));
    m_colors.push_back(QColor(94, 46, 48));
    m_colors.push_back(QColor(49, 48, 74));
    m_colors.push_back(QColor(39, 34, 65));
    m_colors.push_back(QColor(100, 89, 28));
}

QModelIndex ColorLinesModel::index(int row, int column, const QModelIndex &parent) const {
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    return createIndex(row, column);
}

QModelIndex ColorLinesModel::parent(const QModelIndex &index) const {
    return {};
}

int ColorLinesModel::rowCount(const QModelIndex &parent) const {
    return m_cols;
}

int ColorLinesModel::columnCount(const QModelIndex &parent) const {
    return m_rows;
}

QVariant ColorLinesModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (role == kColorRole) {
        return m_board[index.row()][index.column()].color;
    } else if (role == kVisibleRole) {
        return m_board[index.row()][index.column()].visible;
    }

    return QVariant();
}

bool ColorLinesModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (data(index, role) != value && index.isValid()) {
        if (role == kColorRole) {
            m_board[index.row()][index.column()].color = value.value<QColor>();
        } else if (role == kVisibleRole) {
            m_board[index.row()][index.column()].visible = value.value<bool>();
        }

        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags ColorLinesModel::flags(const QModelIndex &index) const{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

QHash<int, QByteArray> ColorLinesModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[kColorRole] = "color";
    roles[kVisibleRole] = "visible";
    return roles;
}

int ColorLinesModel::cols() {
    return m_cols;
}

int ColorLinesModel::rows() {
    return m_rows;
}

int ColorLinesModel::scope() const {
    return m_scope;
}

void ColorLinesModel::reset() {
    m_scope = 0;
    for (auto &row: m_board) {
        for (auto &cell: row) {
            cell.visible = false;
        }
    }
    emit dataChanged(index(0, 0), index(m_rows - 1, m_cols - 1));
}

void ColorLinesModel::spawn() {
    for (int spawn = 0; spawn < m_number_spawning; ++spawn) {

    }
}
