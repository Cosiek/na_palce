import QtQuick 2.7
import QtQuick.Controls 2.1

Item {
    id: summaryComponent

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

            function get_stats_text(){
                var stats = JSON.parse(stats_handler.get_stats())
                var txt = "🎵 | ✖ | ✔ | ⌛"
                txt += "\n--- | " + stats.total_mistakes
                txt += " | " + stats.total_played
                txt += " | " + stats.avg_time
                for (var s in stats.notes){
                    var ntStat = stats.notes[s]
                    if (ntStat.mistakes_count === 0 && ntStat.played_count ===0){
                        continue
                    }
                    txt += "\n" + s
                    txt += " | " + ntStat.mistakes_count
                    txt += " | " + ntStat.played_count
                    txt += " | " + ntStat.avg_time
                }
                return txt
            }
            Text {
                id: summaryTxt
                text: "📈\n" + parent.get_stats_text()
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: 14
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
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
