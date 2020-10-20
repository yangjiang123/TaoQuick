import QtQuick 2.9
import QtQuick.Controls 2.2
import TaoQuick 1.0
import "./Page"
import "./Pane"
//import Qt.labs.platform 1.1
CusBackground {
    id: rootItem
    width: 1024
    height: 720

    //    SystemTrayIcon {
    //        id: sysTray
    //        visible: true
    //        icon.source: imgPath + "logo/milk.png"
    //        menu: Menu {
    //            MenuItem {
    //                text: qsTr("Quit")
    //                onTriggered: {
    //                    Qt.quit()
    //                }
    //            }
    //        }
    //    }
    //    AboutDialog {
    //        id: aboutDialog
    //    }
    //    SettingsDialog {
    //        id: settingDialog
    //    }
    TitlePane {
        id: title
        width: parent.width
        height: 60
    }
    Item {
        id: content
        width: parent.width
        anchors {
            top: title.bottom
            bottom: parent.bottom
        }
        CusFPS {
            anchors {
                right: parent.right
                top: parent.top
                rightMargin: 5
            }
        }

        LeftPane {
            id: leftPane
            property real targetW: parent.width * 0.233
            width: targetW
            height: parent.height
            property bool isOpen: true
            x: isOpen ? 0 : -targetW - 1
            Behavior on x {
                NumberAnimation { duration: 350}
            }
            onLoadHome: {
                rightPane.source = rightPane.homeUrl
            }
            onLoadContent: {
                rightPane.source = contentsPath + path
            }
        }
        CusButton_ImageColorOverlay {
            btnImgNormal: imgPath + "Common/menu.png"
            anchors.verticalCenter: parent.verticalCenter
            anchors {
                left: leftPane.right
                top: leftPane.top
                topMargin: 5
            }
            width: 32
            height: 32
            onClicked: {
                leftPane.isOpen = !leftPane.isOpen
            }
        }
        Rectangle {
            width: 1
            anchors {
                top: leftPane.top
                bottom: leftPane.bottom
                right: leftPane.right
            }
            color: CusConfig.controlBorderColor
        }
        RightPane {
            id: rightPane
            anchors {
                left: leftPane.right
                leftMargin: 40
                right: parent.right
            }
            height: parent.height
        }
    }
}
