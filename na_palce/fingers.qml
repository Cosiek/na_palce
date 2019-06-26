import QtQuick 2.7
import QtQuick.Controls 2.1

import "draw_table.js" as TableRenderer
import "draw_notes.js" as NotesRenderer


Item {
    id: fingersComponent

    StackView.onActivating: {
        // set table display canvas height
        var noteTypes = JSON.parse(game_handler.get_note_types());
        var count = noteTypes.length + 1;
        table_display.height = (count + 1) * (fingersHead.font.pixelSize / 2) * 4;
    }

    Flickable {
        id: fingersFlickable
        anchors.fill: parent
        contentHeight: exitFingersButton.y + exitFingersButton.height + fingersColumn.spacing
        contentWidth: parent.width
        interactive: true
        boundsBehavior: Flickable.StopAtBounds

        Column {
            id: fingersColumn
            spacing: 10
            property Item defaultFocusItem: this
            anchors.fill: parent

            Text {
                id: fingersHead
                text: "🖐"
                fontSizeMode: Text.VerticalFit
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: 24
                horizontalAlignment: Text.AlignHCenter
            }
            Canvas {
                id: table_display
                enabled: false
                visible: true
                width: parent.width - 20;
                anchors.horizontalCenter: parent.horizontalCenter
                contextType: qsTr("2d")

                onPaint: {
                    // prepare table data
                    var tableData = [ ["🎵", "🔤", "🖐"], ]
                    // prepare notes data
                    var noteTypes = JSON.parse(game_handler.get_note_types());
                    var keys = ""
                    var noteType = null
                    for (var idx in noteTypes){
                        noteType = noteTypes[idx];

                        keys = noteType.valve1 ? "●" : "○"
                        keys += noteType.valve2 ? "●" : "○"
                        keys += noteType.valve3 ? "●" : "○"
                        tableData.push([noteType, noteType.name, keys]);
                    }
                    // render
                    var ctx = table_display.getContext('2d');
                    ctx.clearRect(0, 0, table_display.width, table_display.height);
                    TableRenderer.drawTable(ctx, tableData, table_display.width,
                                            table_display.height, fingersHead.font.pixelSize / 2,
                                            fingersHead.font.family);
                }
            }
            Button {
                id: exitFingersButton
                text: "🚪"
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: { stackView.pop(null) }
            }
        }
    }
}
