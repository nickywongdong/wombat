import QtQuick 2.9
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0
import forker.us 1.0

ApplicationWindow {
    id: root
    width: 1280
    height: 800
    //color: "#0892D0"
    //flags: Qt.FramelessWindowHint
    visible: true
    title: "Qt UI Shell"
    StackView {
        id: stack
        initialItem: startup
    }
Test{
 id: bootdm
}
    Rectangle{
        id: startup
        width: 1280
        height: 800
        color: "#0892D0"

        Text {
            id: words
            anchors.centerIn: startup
            font.pointSize: 44
            text: qsTr("Hello World!")
        }

        Timer{
            interval: 3000; running: true;
            onTriggered: {
                stack.push("mainmenu.qml")
                console.log(bootdm.start_dm())
            }
        }
    }
}
