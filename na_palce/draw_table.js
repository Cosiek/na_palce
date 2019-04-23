
function drawTable(ctx, tableData, width, maxHeight, fontSize, fontFamily) {
    // set ctx style
    ctx.lineWidth = 1;
    ctx.fillStyle = "#000000";
    ctx.strokeStyle = "#000000";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.font = fontSize + 'px ' + fontFamily;
    var margin = 10;
    // path
    ctx.beginPath();
    // calculate column widths
    var colWidth = (width - 2 * margin) / tableData[0].length;
    // calculate row heights
    var rowHeight = maxHeight / tableData.length;
    // calculate dimentions for drawing notes
    var scale = rowHeight / 50;
    var forcedSizes = {
        scale: scale,
        margin: scale,
        leftMargin: 3,
        clefOffset: 5,
        notesOffset: 1,
    }
    // render cells
    for (var rowIdx in tableData){
        var y = Number(rowIdx) * rowHeight;
        // draw horizontal line
        if (Number(rowIdx) > 0){
            ctx.moveTo(margin, y);
            ctx.lineTo(width, y);
            ctx.stroke();
        }
        for (var cellIdx in tableData[rowIdx]){
            var x = margin + colWidth * Number(cellIdx);
            var content = tableData[rowIdx][cellIdx];
            if (content.id){
                NotesRenderer.render(ctx, [content, ], colWidth, rowHeight, x, y, forcedSizes);
            } else {
                ctx.fillText(content, x + colWidth / 2, y + rowHeight / 2, colWidth);
            }
        }
    }
    // render vertical table lines
    for (var colIdx = 1; colIdx < tableData[0].length; colIdx++){
        x = margin + colWidth * Number(colIdx);
        ctx.moveTo(x, 0);
        ctx.lineTo(x, maxHeight);
    }
    ctx.stroke();
}
