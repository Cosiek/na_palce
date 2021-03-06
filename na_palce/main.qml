import QtQuick 2.7
import QtQuick.Controls 2.1

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Trumpet Fingers 🎺")

    StackView {
        id: stackView
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        initialItem: menuComponent
        onCurrentItemChanged: {
            if (currentItem  && currentItem.defaultFocusItem) {
                currentItem.defaultFocusItem.focus = true
            }
        }
        Keys.onReleased: {
            if (event.key === Qt.Key_Back && stackView.depth > 1) {
                stackView.pop();
                event.accepted = true;
            }
        }
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
                onClicked: stackView.push("qrc:/game.qml")
            }
            Button {
                text: "🖐"
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: stackView.push("qrc:/fingers.qml")
            }
            Button {
                text: "⚙"
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: stackView.push("qrc:/settings.qml")
            }
            Button {
                text: "🚪"
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: Qt.quit()
            }
        }
    }
}
