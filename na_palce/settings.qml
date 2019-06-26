import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2


Item {
    id: settingsView
    property Item defaultFocusItem: this

    StackView.onActivating: {
        // set controls to match saved settings
        var settingsObj = JSON.parse(settings.toJson())
        var children = settingsGridLayout.children
        for (var key in settingsObj){
            for (var k in children){
                if (children[k].objectName === key){
                    children[k].set(settingsObj[key])
                }
            }
        }
    }

    function saveSettings(){
        var children = settingsGridLayout.children;
        var settingsObject = {};
        for (var k in children){
            if (children[k].objectName.length > 0){
                settingsObject[children[k].objectName] = children[k].get();
            }
        }

        settings.loadSettingsFromJson(JSON.stringify(settingsObject));
        settings.saveSettings();
    }

    Flickable {
        id: settingsFlickable
        anchors.fill: parent
        contentHeight: settingsGridLayout.height
        contentWidth: parent.width
        interactive: true
        boundsBehavior: Flickable.StopAtBounds

        GridLayout {
            id: settingsGridLayout
            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: parent.top
            anchors.topMargin: 5
            columns: 2
            rows: 2

            Text {
                text: qsTr("⚙")
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.columnSpan: 2
                font.pointSize: 24
            }

            Text {
                id: displayNoteNamesSettingLabel
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                text: qsTr("🔤")
            }
            Switch {
                id: displayNoteNamesSetting
                objectName: "displayNoteNames"
                scale: 0.5
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                function set(arg){ displayNoteNamesSetting.checked = arg }
                function get(){ return displayNoteNamesSetting.checked }
            }

            Button {
                text: "⬅"
                Layout.preferredHeight: 40
                Layout.preferredWidth: 40
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                onClicked: function(){
                    stackView.pop();
                }
            }
            Button {
                text: "💾"
                Layout.preferredHeight: 40
                Layout.preferredWidth: 40
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                onClicked: function(){
                    saveSettings();
                    stackView.pop();
                }
            }
        }
    }
}
