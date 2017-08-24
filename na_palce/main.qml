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
            id: column
            spacing: 10

            Text {
                text: "🎺"
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: 24
                horizontalAlignment: Text.AlignHCenter
            }
            Button {
                text: "▶"
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: stackView.push(notesComponent)
            }
            Button {
                text: "🚪"
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: Qt.quit()
            }

        }
    }

    Component {
        id: notesComponent

        GridLayout {
            id: gridLayout
            columns: 3
            rows: 3

            Button {
                text: "⬅"
                Layout.preferredHeight: 40
                Layout.preferredWidth: 40
                Layout.columnSpan: 3
                onClicked: stackView.pop()
            }
            Text {
                text: "🎼\nPres any key to start."
                font.pointSize: 36
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: 10
                horizontalAlignment: Text.AlignHCenter
                Layout.columnSpan: 3
            }
            Button {
                id: valve1
                text: "1"
                Layout.preferredHeight: 40
                Layout.preferredWidth: 40
                onPressed: print("valve1 pressed")
                onReleased: print("valve1 relased")
            }
            Button {
                id: valve2
                text: "2"
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredHeight: 40
                Layout.preferredWidth: 40
                onPressed: print("valve2 pressed")
                onReleased: print("valve2 relased")
            }
            Button {
                id: valve3
                text: "3"
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.preferredHeight: 40
                Layout.preferredWidth: 40
                onPressed: print("valve3 pressed")
                onReleased: print("valve3 relased")
            }
        }
    }
}
