import QtQuick
import QtQuick.Controls

Button {
  id: root
  text: qsTr("New Game")

  anchors.verticalCenter: parent.verticalCenter

  contentItem: Text {
    text: root.text
    color: "#ffffff"
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
    font.pointSize: 10
    font.bold: true
  }

  background: Rectangle {
    Gradient {
      id: normalGradient
      GradientStop {
        position: 0.0
        color: "#252525"
      }
      GradientStop {
        position: 0.5
        color: "#e30000"
      }
      GradientStop {
        position: 1.0
        color: "#252525"
      }
    }

    Gradient {
      id: hoveredGradient
      GradientStop {
        position: 0.0
        color: "#252525"
      }
      GradientStop {
        position: 0.5
        color: "#ff5e5e"
      }
      GradientStop {
        position: 1.0
        color: "#252525"
      }
    }

    Gradient {
      id: pressedGradient
      GradientStop {
        position: 0.0
        color: "#252525"
      }
      GradientStop {
        position: 0.5
        color: "#b00000"
      }
      GradientStop {
        position: 1.0
        color: "#252525"
      }
    }

    implicitWidth: 100
    implicitHeight: 30
    gradient: root.pressed ? pressedGradient : root.hovered ? hoveredGradient : normalGradient
    radius: 10
    border.width: 2.0
    border.color: "#000000"
  }
}
