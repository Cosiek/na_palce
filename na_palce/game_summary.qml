import QtQuick 2.7
import QtQuick.Controls 2.1

import "draw_table.js" as TableRenderer
import "draw_notes.js" as NotesRenderer

Item {
    id: summaryComponent

    StackView.onActivating: {
        // set table display canvas height
        var stats = JSON.parse(stats_handler.get_stats());
        var count = 2;
        for (var s in stats.notes){
            var ntStat = stats.notes[s];
            if (ntStat.mistakes_count === 0 && ntStat.played_count === 0){
                continue
            }
            count += 1;
        }
        table_display.height = (count + 1) * (summaryHead.font.pixelSize + 2) * 4;
    }

    Flickable {
        id: summaryFlickable
        anchors.fill: parent
        contentHeight: exitGameButton.y + exitGameButton.height + summaryColumn.spacing
        contentWidth: parent.width
        interactive: true
        boundsBehavior: Flickable.StopAtBounds

        Column {
            id: summaryColumn
            spacing: 10
            property Item defaultFocusItem: this
            anchors.fill: parent

            Text {
                id: summaryHead
                text: "📈"
                fontSizeMode: Text.VerticalFit
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: 14
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
                    var stats = JSON.parse(stats_handler.get_stats());
                    var tableData = [
                        ["🎵", "✖", "✔", "⌛"],
                        ["∑", stats.total_mistakes, stats.total_played, stats.avg_time],
                    ]
                    // prepare notes data
                    var noteTypes = JSON.parse(game_handler.get_note_types());
                    for (var idx in noteTypes){
                        var noteType = noteTypes[idx];
                        var ntStat = stats.notes[noteType.position + ":" + noteType.name];
                        if (!ntStat || ntStat.mistakes_count === 0 && ntStat.played_count === 0){
                            continue
                        }
                        tableData.push(
                            [noteType, ntStat.mistakes_count,
                             ntStat.played_count, ntStat.avg_time]
                        );
                    }
                    // render
                    var ctx = table_display.getContext('2d');
                    ctx.clearRect(0, 0, table_display.width, table_display.height);
                    TableRenderer.drawTable(ctx, tableData, table_display.width,
                                            table_display.height, summaryHead.font.pixelSize,
                                            summaryHead.font.family);
                }
            }
            Button {
                id: playAgainButton
                text: "▶"
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: { stackView.pop() }
            }
            Button {
                id: exitGameButton
                text: "🚪"
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: { stackView.pop(null) }
            }
        }
    }
}
