#include "colorlinesmodel.h"

std::random_device ColorLinesModel::rd;
std::default_random_engine ColorLinesModel::generator(rd());
std::uniform_int_distribution<int> ColorLinesModel::distribution_cell(0, m_rows - 1);
std::uniform_int_distribution<int> ColorLinesModel::distribution_color(0, 4);

ColorLinesModel::ColorLinesModel(QObject *parent)
    : QAbstractItemModel(parent), m_empty_cell{m_cols * m_rows} {
  m_colors.push_back(QColor(140, 94, 78));
  m_colors.push_back(QColor(94, 146, 48));
  m_colors.push_back(QColor(49, 48, 74));
  m_colors.push_back(QColor(139, 34, 95));
  m_colors.push_back(QColor(100, 89, 28));
}

QModelIndex ColorLinesModel::index(int row, int column, const QModelIndex &parent) const {
  if (!hasIndex(row, column, parent)) {
    return QModelIndex();
  }

  return createIndex(row, column);
}

QModelIndex ColorLinesModel::parent([[maybe_unused]] const QModelIndex &index) const {
  return {};
}

int ColorLinesModel::rowCount([[maybe_unused]] const QModelIndex &parent) const {
  return m_cols;
}

int ColorLinesModel::columnCount([[maybe_unused]] const QModelIndex &parent) const {
  return m_rows;
}

QVariant ColorLinesModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();

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

Qt::ItemFlags ColorLinesModel::flags(const QModelIndex &index) const {
  if (!index.isValid()) return Qt::NoItemFlags;

  return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

QHash<int, QByteArray> ColorLinesModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[kColorRole] = "color";
  roles[kVisibleRole] = "visible";
  return roles;
}

int ColorLinesModel::cols() { return m_cols; }

int ColorLinesModel::rows() { return m_rows; }

int ColorLinesModel::scope() const { return m_scope; }

void ColorLinesModel::reset() {
  m_scope = 0;
  for (auto &row : m_board) {
    for (auto &cell : row) {
      cell.visible = false;
    }
  }
  m_empty_cell = m_rows * m_cols;
  emit dataChanged(index(0, 0), index(m_rows - 1, m_cols - 1));
}

void ColorLinesModel::spawn() {
  int row{};
  int col{};
  for (int spawn = 0; spawn < m_number_spawning; ++spawn) {
    do {
      row = distribution_cell(generator);
      col = distribution_cell(generator);
    } while (!isEmptyCell(row, col));
    m_board[row][col].color = m_colors[distribution_color(generator)];
    m_board[row][col].visible = true;

    --m_empty_cell;
    if (m_empty_cell < m_number_spawning) {
        emit gameOver();
    }

    emit dataChanged(index(row, col), index(row, col));
  }
}

void ColorLinesModel::setChosenPosition(int row, int col) {
  m_chosen_row_element = row;
  m_chosen_col_element = col;
}

void ColorLinesModel::moveElement(int row, int col) {
  if (m_chosen_row_element != -1 || m_chosen_col_element != -1) {
    m_board[m_chosen_row_element][m_chosen_col_element].visible = false;

    emit dataChanged(index(m_chosen_row_element, m_chosen_col_element), index(m_chosen_row_element, m_chosen_col_element));

    m_board[row][col].color = m_board[m_chosen_row_element][m_chosen_col_element].color;

    m_chosen_row_element = row;
    m_chosen_col_element = col;

    m_board[m_chosen_row_element][m_chosen_col_element].visible = true;

    emit dataChanged(index(m_chosen_row_element, m_chosen_col_element), index(m_chosen_row_element, m_chosen_col_element));

    m_chosen_row_element = -1;
    m_chosen_col_element = -1;
  }
}

bool ColorLinesModel::sequenceSearch() {
  bool flag{false};

  if (rowSequenceSearch()) {
      flag = true;
  }

  if (colSequenceSearch()) {
      flag = true;
  }

  emit dataChanged(index(0, 0), index(m_rows - 1, m_cols - 1));

  return flag;
}

bool ColorLinesModel::isChosePosition() {
    return m_chosen_row_element >= 0 && m_chosen_col_element >= 0;
}

int ColorLinesModel::empty_cell() const {
    return m_empty_cell;
}

bool ColorLinesModel::isEmptyCell(int row, int col) {
    return !m_board[row][col].visible;
}

bool ColorLinesModel::rowSequenceSearch() {
    bool flag{false};
    QColor color{};
    for (int i = 0; i < m_board.size(); ++i) {
        int sequence_count{};
        for (int j = 0; j < m_board[i].size(); ++j) {
            if (m_board[i][j].visible) {
                if (!sequence_count) {
                    color = m_board[i][j].color;
                    ++sequence_count;
                } else if (m_board[i][j].color == color) {
                    ++sequence_count;

                    if (j == m_board.size() - 1) {
                        if (sequence_count >= m_sequence) {
                            for (int k = j - sequence_count + 1; k <= j; ++k) {
                                m_board[i][k].visible = false;
                            }
                            m_empty_cell += sequence_count;
                            m_scope += 10;
                            flag = true;
                        }
                    }
                } else {
                    if (sequence_count >= m_sequence) {
                        for (int k = j - sequence_count; k < j; ++k) {
                            m_board[i][k].visible = false;
                        }
                        m_empty_cell += sequence_count;
                        m_scope += 10;
                        flag = true;
                    }
                    color = m_board[i][j].color;
                    sequence_count = 1;
                }
            } else {
                if (sequence_count >= m_sequence) {
                    for (int k = j - sequence_count; k < j; ++k) {
                        m_board[i][k].visible = false;
                    }
                    m_empty_cell += sequence_count;
                    m_scope += 10;
                    flag = true;
                }
                sequence_count = 0;
            }
        }
    }

    if (flag) {
        emit changeScope();
    }

    return flag;
}

bool ColorLinesModel::colSequenceSearch() {
    bool flag{false};
    QColor color{};
    for (int i = 0; i < m_board.size(); ++i) {
        int sequence_count{};
        for (int j = 0; j < m_board.size(); ++j) {
            if (m_board[j][i].visible) {
                if (!sequence_count) {
                    color = m_board[j][i].color;
                    ++sequence_count;
                } else if (m_board[j][i].color == color) {
                    ++sequence_count;

                    if (j == (m_board.size() - 1)) {
                        if (sequence_count >= m_sequence) {
                            for (int k = j - sequence_count + 1; k <= j; ++k) {
                                m_board[k][i].visible = false;
                            }
                            m_empty_cell += sequence_count;
                            m_scope += 10;
                            flag = true;
                        }
                    }
                } else {
                    if (sequence_count >= m_sequence) {
                        for (int k = j - sequence_count; k < j; ++k) {
                            m_board[k][i].visible = false;
                        }
                        m_empty_cell += sequence_count;
                        m_scope += 10;
                        flag = true;
                    }
                    color = m_board[j][i].color;
                    sequence_count = 1;
                }
            } else {
                if (sequence_count >= m_sequence) {
                    for (int k = j - sequence_count; k < j; ++k) {
                        m_board[k][i].visible = false;
                    }
                    m_empty_cell += sequence_count;
                    m_scope += 10;
                    flag = true;
                }
                sequence_count = 0;
            }
        }
    }

    if (flag) {
        emit changeScope();
    }

    return flag;
}
