import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
  id: root
  height: 640
  width: height - header_tool_bar.height

  maximumWidth: width
  maximumHeight: height

  minimumWidth: width
  minimumHeight: height

  visible: true
  title: qsTr("Color Lines 1.0")

  Connections {
    target: play_field._tv_model

    onChangeScope: {
      lbl_scope.text = "Scope: " + play_field._tv_model.scope
    }

    onGameOver: {
      gameOverDialog.open()
    }
  }

  Dialog {
    id: gameOverDialog

    title: "Game Over"

    anchors.centerIn: parent

    implicitWidth: parent.width
    implicitHeight: parent.height

    padding: 0

    header: Label {
      text: gameOverDialog.title
      horizontalAlignment: Text.AlignHCenter
      color: "#ffffff"
      font.bold: true
      padding: 10
      background: Rectangle {
        color: "#707070"
        border.width: 1.0
        border.color: "#000000"
      }
    }

    contentItem: Label {
      text: qsTr(lbl_scope.text)
      font.pointSize: 46
      horizontalAlignment: Text.AlignHCenter
      verticalAlignment: Text.AlignVCenter
      color: "#ffffff"
      font.bold: true
      padding: 10
      background: Rectangle {
        color: "#353535"
      }
    }

    onAccepted: {
      btn_new_game.clicked()
    }
  }

  header: ToolBar {
    id: header_tool_bar

    height: 40
    NewGameBtn {
      id: btn_new_game

      onClicked: {
        play_field._tv_model.reset()
        play_field._tv_model.spawn()
        lbl_scope.text = "Scope: " + play_field._tv_model.scope
      }
    }

    Label {
      id: lbl_scope
      text: qsTr("Scope: 0")
      font.pixelSize: 22
      font.italic: true
      color: "steelblue"

      anchors.right: parent.right
      anchors.verticalCenter: parent.verticalCenter
      anchors.margins: 10
    }
  }

  Rectangle {
    color: "steelblue"
    anchors.fill: parent
    radius: 10

    PlayField {
      id: play_field
      anchors.centerIn: parent
      anchors.fill: parent
      anchors.margins: 5
    }
  }
}
