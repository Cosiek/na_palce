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
            return stats['total_mistakes']
        }

        Text {
            text: "Koniec\n" + parent.get_stats_text()
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 24
            horizontalAlignment: Text.AlignHCenter
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
    }
}
