import QtQuick 2.0
import QtQuick.Controls 1.4
import forker.us 1.0
Item {
    id: mainmenupage
    Rectangle{
        id: box
        width: 1280
        height: 800
        color: "#0892D0"
    }
        Row{

            spacing: 55
            anchors.centerIn: box
            Rectangle {
                id: menubutton1
                width: 300
                height: 200
                radius: 10
                border.color: "black"
                color: "#ffb347"
                Image {
                    source: "icons8-musical-notes-50.png"
                    anchors.centerIn: parent
                }
                Item {
                    id: clicker1
                    anchors.fill: parent
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            stack.push(pagethree)
                        }
                    }
                }

            }
            Rectangle {
                width: 300
                height: 200
                radius: 10
                border.color: "black"
                color: "#ffb347"
                Test{
                    id: processor

                }

                MouseArea{
                    anchors.fill: parent
                    onClicked: console.log(processor.start_navit())
                }
                Image {
                    source: "icons8-america-50.png"
                    anchors.centerIn: parent
                }
            }
            Rectangle {
                width: 300
                height: 200
                radius: 10
                border.color: "black"
                color: "#ffb347"
                MouseArea{
                    anchors.fill: parent
                    onClicked: console.log("Data")

                }
                Image {
                    source: "icons8-line-chart-50.png"
                    anchors.centerIn: parent
                }
            }
        }
}
