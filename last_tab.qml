import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtCharts 2.0

Item {
    height: 1000
    width: 1000
    GridLayout {
        id: grid
        columns: 2


        ChartView {
                   id: chart_view
                   antialiasing: true
                   height: 600
                   width: 600
                   axes: [
                        ValueAxis{
                            id: xAxis
                            min: -10.0
                            max: 10.0
                        },
                        ValueAxis{
                            id: yAxis
                            min: -10.0
                            max: 10.0
                        }
                   ]
               }

        TextInput {
                    id: xCoordinate
                    cursorVisible: true
                    anchors.margins: 5
                    color: "#151515"; selectionColor: "green"
                    font.pixelSize: 16;
                    maximumLength: 5
                    validator: DoubleValidator {}
                    horizontalAlignment: Text.AlignLeft
                    focus: true
                    property string placeholderText: "Enter X here..."
                    /*Text {
                        text: xCoordinate.placeholderText
                        color: red
                        visible: !xCoordinate.text && !xCoordinate.activeFocus
                    }*/
                }
}


}
