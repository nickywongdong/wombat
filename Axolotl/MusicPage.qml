import QtQuick 2.0
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.0

Item {
    id: media
    Rectangle{
        id: base
        width: 1280
        height: 800
        color: "#0892D0"
    }

        Column{
            id: navBar
            spacing: 30
            Rectangle{
                id: musicback
                width: 60
                height: 60
                radius: 10
                border.color: "black"
                color: "#ffb347"
                Image {
                    anchors.centerIn: parent
                    source: "icons8-go-back-50.png"
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        stack.pop()
                    }
                }
            }
            Rectangle {
                width: 200
                height: 100
                radius: 10
                border.color: "black"
                color: "#ffb347"
                Text {
                    text: qsTr("FM Radio")
                    font.pointSize: 20
                    anchors.centerIn: parent
                }
                Item {
                    anchors.fill: parent
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            console.log("Radio")
                        }
                    }
                }
            }
            Rectangle {
                width: 200
                height: 100
                radius: 10
                border.color: "black"
                color: "#ffb347"
                Text {
                    text: qsTr("Aux")
                    font.pointSize: 20
                    anchors.centerIn: parent
                }
                Item {
                    anchors.fill: parent
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            console.log("Aux")
                        }
                    }
                }
            }
            Rectangle {
                width: 200
                height: 100
                radius: 10
                border.color: "black"
                color: "#ffb347"
                Text {
                    text: qsTr("Bluetooth")
                    font.pointSize: 20
                    anchors.centerIn: parent
                }
                Item {
                    anchors.fill: parent
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            console.log("Bluetooth")
                        }
                    }
                }
            }

        }
}
