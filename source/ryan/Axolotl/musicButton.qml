import QtQuick 2.0

Item {
    id: root
    width: 250
    height: 250
    MouseArea{
        anchors.fill: parent
        onCLicked: console.log("Music")
    }
    Text {
        text: qsTr("Music")
    }

}
