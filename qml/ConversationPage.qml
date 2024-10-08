
import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14

import io.qt.examples.chattutorial 1.0

Page {
    id: root

    property string inConversationWith

    header: ChatToolBar {
        ToolButton {
            text: qsTr("Back")
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            onClicked: root.StackView.view.pop()
        }

        Label {
            id: pageTitle
            text: inConversationWith
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }

    ColumnLayout {
        anchors.fill: parent

        ListView {
            id: listView
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: pane.leftPadding + messageField.leftPadding
            displayMarginBeginning: 40
            displayMarginEnd: 40
            verticalLayoutDirection: ListView.BottomToTop
            spacing: 12
            model: SqlConversationModel {
                recipient: inConversationWith
            }
            delegate: Column {
                anchors.right: sentByMe ? listView.contentItem.right : undefined
                spacing: 6

                readonly property bool sentByMe: model.recipient !== "Me"

                Row {
                    id: messageRow
                    spacing: 6
                    anchors.right: sentByMe ? parent.right : undefined

                    Image {
                        id: avatar
                        source: !sentByMe ? "qrc:/" + model.author.replace(" ", "_") + ".png" : ""
                    }

                    Rectangle {
                        width: Math.min(messageText.implicitWidth + 24, listView.width - avatar.width - messageRow.spacing)
                        height: messageText.implicitHeight + 24
                        color: sentByMe ? "lightgrey" : "steelblue"

                        Label {
                            id: messageText
                            text: model.message
                            color: sentByMe ? "black" : "white"
                            anchors.fill: parent
                            anchors.margins: 12
                            wrapMode: Label.Wrap
                        }
                    }
                }

                Label {
                    id: timestampText
                    text: Qt.formatDateTime(model.timestamp, "d MMM hh:mm")
                    color: "lightgrey"
                    anchors.right: sentByMe ? parent.right : undefined
                }
            }

            ScrollBar.vertical: ScrollBar {}
        }

        Pane {
            id: pane
            Layout.fillWidth: true


            RowLayout {
                width: parent.width

                Connections{
                    target: cppObj
                    function onCppSignal(receivedMsg){
                        console.log("QML received: " + receivedMsg)
                        messageField.text =receivedMsg
                    }
                }
                TextArea {
                    id: messageField
                    Layout.fillWidth: true
                    placeholderText: qsTr("Compose message")
                    wrapMode: TextArea.Wrap
                    overwriteMode: false

                }
                Button {
                    id: sendButton
                    text: qsTr("Send")
                    enabled: messageField.length > 0
                    MouseArea{
                          anchors.fill: sendButton
                          hoverEnabled: true
                          onEntered: {
                              sendButton.state='Hovering'
                              listView.model.sendMessage(inConversationWith, messageField.text);
                              messageField.text = "";
                              console.log('mouse over ya kbeer');
                          }


                    }

                }
            }
        }
    }
}

