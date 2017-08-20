import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3


ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    StackView {
        id: stackView
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        initialItem: menuComponent
    }

    Component {
        id: menuComponent

        Column {
            spacing: 10

            Text {
                text: "Trumpet Fingers"
                font.bold: true
                font.pointSize: 24
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: 10
                horizontalAlignment: Text.AlignHCenter
            }
            Button {
                text: "Start"
                onClicked: stackView.push(notesComponent)
            }
            Button {
                text: "Exit"
                onClicked: Qt.quit()
            }

        }
    }

    Component {
        id: notesComponent

        Column {
            spacing: 10
            Button {
                text: "Exit"
                onClicked: stackView.pop()
            }
            Text {
                text: "Play Me!"
                font.bold: true
                font.pointSize: 36
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: 10
                horizontalAlignment: Text.AlignHCenter
            }
            Button {
                id: valve1
                text: "1"
            }
            Button {
                id: valve2
                text: "2"
            }
            Button {
                id: valve3
                text: "3"
            }
        }
    }
}
