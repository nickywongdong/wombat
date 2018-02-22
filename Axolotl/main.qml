import QtQuick 2.0
import QtQuick.Controls 1.4
import forker.us 1.0

ApplicationWindow {
    id: root
    width: 1280
    height: 800
    //color: "#0892D0"
    //flags: Qt.FramelessWindowHint
    visible: true
    title: "Qt UI Shell"
            MainMenu { id: pagetwo }
            MusicPage { id: pagethree }
            DataPage { id: pagefour }
    StackView {
        id: stack
        initialItem: startup

    }
    Test{
        id: processor
    }
onClosing: {
    processor.kill_dm()
}
    Item {
        id: startup
        Rectangle{
        width: 1280
        height: 800
        color: "#0892D0"

        Text {
            id: words
            anchors.centerIn: parent
            font.pointSize: 44
            text: qsTr("Hello World!")
        }
        Timer{
            interval: 3000; running: true;
            onTriggered: {
                stack.push(pagetwo)
                console.log(processor.start_dm())
            }
        }
        }
    }
}
