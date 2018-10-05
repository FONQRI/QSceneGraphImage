import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import DragImage 1.0



    DragableImage{
        id : root
width: 1920
height: 1080
        focus: true // important - otherwise we'll get no key events

        Keys.onReleased: {
            if (event.key === Qt.Key_Back) {
                console.log("Back button captured - wunderbar !")
                event.accepted = true
            }
        }


//Text{
//    text:"hello world"
//color:"white"
//}
Component.onCompleted: {

}

anchors.fill: parent
//        Timer{
//            interval: 50
//            onTriggered: {
//                root.update();
//            }
//            running: true
//            repeat: true
//        }
    }

