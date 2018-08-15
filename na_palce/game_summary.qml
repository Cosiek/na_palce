import QtQuick 2.7
import QtQuick.Controls 2.1

Item {

    id: summaryComponent

    Column {
        id: column
        spacing: 10
        property Item defaultFocusItem: this
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent

        function get_stats_text(){
            var stats = JSON.parse(stats_handler.get_stats())
            var txt = "🎵 | ✖ | ✔ | ⌛"
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
            txt += "\n--- | " + stats.total_mistakes
            txt += " | " + stats.total_played
            txt += " | " + stats.avg_time
            return txt
        }
        Button {
            text: "▶"
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                stackView.pop()
            }
        }
        Button {
            text: "🚪"
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                stackView.pop(null)
            }
        }
        Text {
            text: "📈\n" + parent.get_stats_text()
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 14
            horizontalAlignment: Text.AlignHCenter
        }
    }
}
