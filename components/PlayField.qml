import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import CLModel 1.0

TableView {
  id: _tv

  property alias _tv_model: _clm

  rowSpacing: 5
  columnSpacing: rowSpacing

  delegate: Rectangle {
    id: cell
    implicitWidth: (_tv.width - _tv.columnSpacing * (_clm.cols - 1)) / _clm.cols
    implicitHeight: (_tv.height - _tv.rowSpacing * (_clm.rows - 1)) / _clm.rows

    radius: implicitWidth * 0.1

    MouseArea {
      id: _ma_cell
      anchors.fill: parent

      onClicked: {

        console.log("lfsdjjf")
        model.visible = true
      }
    }

    Rectangle {
      id: _ball

      anchors.centerIn: parent

      visible: model.visible

      width: cell.width * 0.9
      height: cell.height * 0.9

      color: "red"
      radius: width * 0.5

      ScaleAnimator {
        id: _sa_ball
        target: _ball
        from: 0.9
        to: 1
        duration: 1000
      }

      MouseArea {
        id: _ma_ball
        anchors.fill: parent

        onClicked: {
          if (_ball.visible) {
            _sa_ball.running = true
          }
        }
      }
    }
  }

  model: ColorLinesModel {
    id: _clm
  }
}
