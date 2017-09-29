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
        onCurrentItemChanged: {
            if (currentItem  && currentItem.defaultFocusItem) {
                currentItem.defaultFocusItem.focus = true
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
            property Item defaultFocusItem: this

            function keyPressed(keyName){
                print(game_handler.key_pressed(keyName))
                notes_display.text = game_handler.get_current_state()
            }

            function keyReleased(keyName){
                print(game_handler.key_released(keyName))
                notes_display.text = game_handler.get_current_state()
            }

            Keys.onPressed: {
                if (event.key === Qt.Key_Left){keyPressed("valve1")}
                else if (event.key === Qt.Key_Down){keyPressed("valve2")}
                else if (event.key === Qt.Key_Right){keyPressed("valve3")}
                event.accepted = true;
            }

            Keys.onReleased: {
                if (event.key === Qt.Key_Left){keyReleased("valve1")}
                else if (event.key === Qt.Key_Down){keyReleased("valve2")}
                else if (event.key === Qt.Key_Right){keyReleased("valve3")}
                event.accepted = true;
            }

            Button {
                text: "⬅"
                Layout.preferredHeight: 40
                Layout.preferredWidth: 40
                Layout.columnSpan: 3
                onClicked: stackView.pop()
            }
            Text {
                id: notes_display
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
                onPressed: keyPressed("valve1")
                onReleased: keyReleased("valve1")
            }
            Button {
                id: valve2
                text: "2"
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredHeight: 40
                Layout.preferredWidth: 40
                onPressed: keyPressed("valve2")
                onReleased: keyReleased("valve2")
            }
            Button {
                id: valve3
                text: "3"
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.preferredHeight: 40
                Layout.preferredWidth: 40
                onPressed: keyPressed("valve3")
                onReleased: keyReleased("valve3")
            }

            Component.onCompleted: {
                game_handler.set_state()
                notes_display.text = game_handler.get_current_state()
            }
        }
    }
}
