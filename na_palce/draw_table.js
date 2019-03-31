
function drawTable(ctx, tableData, width, maxHeight, fontSize, fontFamily) {
    // set ctx style
    ctx.lineWidth = 1;
    ctx.fillStyle = "#000000";
    ctx.strokeStyle = "#000000";
    ctx.textAlign = "center";
    ctx.textBaseline = "top";
    ctx.font = fontSize + 'px ' + fontFamily;
    var margin = 10;
    // path
    ctx.beginPath();
    // calculate column widths
    var colWidth = (width - 2 * margin) / tableData[0].length;
    // calculate row heights
    var rowHeight = Math.min(maxHeight / tableData.length, fontSize + 4);
    // render cells
    for (var rowIdx in tableData){
        var y = Number(rowIdx) * rowHeight;
        if (Number(rowIdx) > 0){
            ctx.moveTo(margin, y);
            ctx.lineTo(width, y);
        }
        for (var cellIdx in tableData[rowIdx]){
            var x = margin + colWidth * Number(cellIdx);
            ctx.fillText(tableData[rowIdx][cellIdx], x + colWidth / 2, y, colWidth);
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
