import QtQuick 2.13
import QtQuick.Controls 2.13
import Qt.labs.settings 1.1

ApplicationWindow {
	visible: true
	width: 640
	height: 480
	title: qsTr("Hello World")

	Settings {
		id: settings

		category: "wasm-test"
		property alias text: testField.text
	}

	TextField {
		id: testField
		anchors.centerIn: parent
		width: parent.width * 0.8
		placeholderText: "This text is stored in the settings"
	}

	Button {
		id: syncBtn
		text: "Sync"

		onClicked: settings.sync()
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.top: testField.bottom
		anchors.topMargin: 16
	}
}
