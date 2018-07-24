import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2

import "draw_notes.js" as NotesRenderer
import Qt.labs.handlers 1.0


Item {
    id: gameView
    property Item defaultFocusItem: this

    function renderDisplay(){
        var currentNotes = JSON.parse(game_handler.get_current_notes())
        notes_text.text = currentNotes[0].name + ' ' + currentNotes[1].name
        notes_display.currentNotes = currentNotes
        notes_display.requestPaint()
    }
    function renderTimer(){
        var currentState = JSON.parse(game_handler.get_current_state())
        timer_display.text = currentState.time_left
        if (currentState.state === "stoped" && currentState.time_left === 0){
            game_handler.exit_game()
            stackView.push(summaryComponent)
            return
        }
    }

    function keyPressed(keyName){
        game_handler.key_pressed(keyName)
        renderDisplay()
    }
    function keyReleased(keyName){
        game_handler.key_released(keyName)
        renderDisplay()
    }

    Keys.onPressed: {
        if (event.isAutoRepeat){return null}
        if (event.key === Qt.Key_Left){keyPressed("valve1")}
        else if (event.key === Qt.Key_Down){keyPressed("valve2")}
        else if (event.key === Qt.Key_Right){keyPressed("valve3")}
        else {return null}
        event.accepted = true;
    }

    Keys.onReleased: {
        if (event.isAutoRepeat){return null}
        if (event.key === Qt.Key_Left){keyReleased("valve1")}
        else if (event.key === Qt.Key_Down){keyReleased("valve2")}
        else if (event.key === Qt.Key_Right){keyReleased("valve3")}
        else {return null}
        event.accepted = true;
    }

    StackView.onActivating: {
        game_handler.init_new_game()
        renderDisplay()
        notes_text.text = qsTr("Press any key to start.")
        game_handler.game_tick_signal.connect(renderTimer)
        game_handler.same_note_signal.connect(renderDisplay)
    }
    StackView.onDeactivating: {
        game_handler.exit_game()
        game_handler.game_tick_signal.disconnect(renderTimer)
        game_handler.same_note_signal.disconnect(renderDisplay)
    }

    GridLayout {
        id: gridLayout
        columns: 3
        rows: 3
        property double basePixelDensity: 4.42
        property double pixelDensityScale: Screen.pixelDensity / basePixelDensity
        anchors.fill: parent

        Button {
            text: "⬅"
            Layout.preferredHeight: 40
            Layout.preferredWidth: 40
            Layout.columnSpan: 2
            onClicked: function(){
                stackView.pop()
                game_handler.exit_game()
            }
        }
        Text {
            id: timer_display
            text: "0"
            font.pixelSize: 16
            Layout.alignment: Qt.AlignRight | Qt.AlignTop
            anchors.right: parent.right
            anchors.rightMargin: 10
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignRight
            Layout.columnSpan: 1
        }
        Canvas {
            id: notes_display
            enabled: false
            visible: true
            contextType: "2d"
            clip: true
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.columnSpan: 3
            property var currentNotes: []

            onPaint: {
                var ctx = notes_display.getContext('2d');
                ctx.save();
                ctx.clearRect(0, 0, notes_display.width, notes_display.height);
                ctx.globalCompositeOperation = "source-over";
                NotesRenderer.render(ctx, this.currentNotes, notes_display.width, notes_display.height);
                ctx.restore();
            }
        }
        Text {
            id: notes_text
            text: "Press any key to start."
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
            Layout.preferredHeight: 60 * parent.pixelDensityScale
            Layout.preferredWidth: 60 * parent.pixelDensityScale
            checkable: true
            checked: tp_valve1.pressed
            MultiPointTouchArea{
                anchors.fill: parent
                touchPoints: TouchPoint { id: tp_valve1 }
                onPressed: keyPressed("valve1")
                onReleased: keyReleased("valve1")
            }
        }
        Button {
            id: valve2
            text: "2"
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: 60 * parent.pixelDensityScale
            Layout.preferredWidth: 60 * parent.pixelDensityScale
            checkable: true
            checked: tp_valve2.pressed
            MultiPointTouchArea{
                anchors.fill: parent
                touchPoints: TouchPoint { id: tp_valve2 }
                onPressed: keyPressed("valve2")
                onReleased: keyReleased("valve2")
            }
        }
        Button {
            id: valve3
            text: "3"
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            Layout.preferredHeight: 60 * parent.pixelDensityScale
            Layout.preferredWidth: 60 * parent.pixelDensityScale
            checkable: true
            checked: tp_valve3.pressed
            MultiPointTouchArea{
                anchors.fill: parent
                touchPoints: TouchPoint { id: tp_valve3 }
                onPressed: keyPressed("valve3")
                onReleased: keyReleased("valve3")
            }
        }
    }
}
