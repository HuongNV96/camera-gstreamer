import QtQuick 2.15
import QtQuick.Window 2.15
import QtGStreamer 1.0
import Gst 1.0

Window {
    id : window
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Column {

        VideoItem {
            id: video

            width: window.width
            height: 260
            surface: player.videoSurface //bound on the context from main()
        }

        GstPlayer {
            id : player
            uri : "http://commondatastorage.googleapis.com/gtv-videos-bucket/sample/ForBiggerEscapes.mp4"
        }

        Row {
            id: buttons

            width: window.width
            height: 35
            spacing: 5

            Rectangle {
                id: playButton
                color: "black"

                width: 60
                height: 30

                Text { text: "Play"; color: "white"; anchors.centerIn: parent }
                MouseArea { anchors.fill: parent; onClicked: player.play() }
            }

            Rectangle {
                id: pauseButton
                color: "black"

                width: 60
                height: 30

                Text { text: "Pause"; color: "white"; anchors.centerIn: parent }
                MouseArea { anchors.fill: parent; onClicked: { player.pause(); } }
            }

            Rectangle {
                id: stopButton
                color: "black"

                width: 60
                height: 30

                Text { text: "Stop"; color: "white"; anchors.centerIn: parent }
                MouseArea { anchors.fill: parent; onClicked: player.stop() }
            }
        }
    }
}
