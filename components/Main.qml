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

  header: ToolBar {
    id: header_tool_bar

    height: 40
    NewGameBtn {
      id: btn_new_game

      onClicked: {
        play_field._tv_model.reset()
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
